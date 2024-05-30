#pragma once
#include"GraphicObject.h"

#define MAX_OPTION_IN_SELECTIONLIST 10
class SelectionList:public GraphicObject{
private:
    string option[MAX_OPTION_IN_SELECTIONLIST];
    int total_option = 0;
    int choice = 0;
    int textcolor_normal = BLACK;
    int textcolor_highlight = RED;
    int background_normal = WHITE;
    int background_highlight = YELLOW;
public:
    void setchoice(int choice);
    void settextcolor(int normal, int highlight);
    void setbackgroundcolor(int normal, int highlight);
    void add_option(string option);

    int getchoice();

    void print();
    int choose(int returnbackground = WHITE);
};

void SelectionList::setchoice(int choice){
    if(choice >= 0 && choice < total_option)
        this->choice = choice;
}

void SelectionList::settextcolor(int normal, int highlight){
    if(normal >= 0 && normal <= 15)
        textcolor_normal = normal;
    if(highlight >= 0 && highlight <= 15)
        textcolor_highlight = highlight;
}

void SelectionList::setbackgroundcolor(int normal, int highlight){
    if(normal >= 0 && normal <= 15)
        background_normal = normal;
    if(highlight >= 0 && highlight <= 15)
        background_highlight = highlight;
}

void SelectionList::add_option(string option){
    if(total_option < MAX_OPTION_IN_SELECTIONLIST){
        this->option[total_option] = option;
        total_option ++;
    }
}

int SelectionList::getchoice(){
    return choice;
}

void SelectionList::print(){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    setcolor(textcolor_normal);
    setbkcolor(background_normal);
    settextstyle(textfont, HORIZ_DIR, textsize);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    setfillstyle(SOLID_FILL, background_normal);

    bar(x, y, x + width, y + height);
    rectangle(x, y, x + width, y + height);

    if(total_option > 0)
        outtextxy(x + width/2, y + (height - textheight(option[choice]))/2, option[choice]);

    setgraphicsettings(&currentsettings);
}

int SelectionList::choose(int returnbackground){
    if(!(total_option > 0)) return -1;
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    
    settextstyle(textfont, HORIZ_DIR, textsize);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    setfillstyle(SOLID_FILL, background_normal);

    int box_x = x,
        box_y = y + height + 2,
        box_width = width,
        box_height = height*total_option;

    setcolor(BLACK);
    bar(box_x, box_y, box_x + box_width, box_y + box_height);
    rectangle(box_x, box_y, box_x + box_width, box_y + box_height);

    setcolor(textcolor_normal);
    setbkcolor(background_normal);
    for(int i = 0; i < total_option; i++){
        outtextxy(box_x + width/2, 
                  box_y + i*height + (height - textheight(option[i]))/2, 
                  option[i]);
    }
    int current_row = -1;
    int mx, my;
    while(1){
        if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(!((mx >= box_x && mx <= (box_x+box_width)) && (my >= box_y && my <=(box_y + box_height)))){
                if(current_row != -1){
                    setcolor(textcolor_normal);
                    setbkcolor(background_normal);
                    setfillstyle(SOLID_FILL, background_normal);

                    bar(box_x + 1, box_y + current_row*height + 1, box_x + box_width - 2, box_y + (current_row+1)*height - 2);
                    outtextxy(box_x + width/2, 
                              box_y + current_row*height + (height - textheight(option[current_row]))/2, 
                              option[current_row]);
                    current_row = -1;
                }
                continue;//while(1)
            }
            for(int i = 0; i < total_option; i++){
                if((mx >= box_x && mx <= (box_x+box_width)) && (my >= box_y + height*i && my <= box_y + height*(i+1))){
                    if(current_row == i) break; //for(i)
                    setcolor(textcolor_highlight);
                    setbkcolor(background_highlight);
                    setfillstyle(SOLID_FILL, background_highlight);

                    bar(box_x + 1, box_y + i*height + 1, box_x + box_width - 2, box_y + (i+1)*height - 2);
                    outtextxy(box_x + width/2, 
                                box_y + i*height + (height - textheight(option[i]))/2, 
                                option[i]);
                    
                    if(current_row != -1){
                        setcolor(textcolor_normal);
                        setbkcolor(background_normal);
                        setfillstyle(SOLID_FILL, background_normal);

                        bar(box_x + 1, box_y + current_row*height + 1, box_x + box_width - 2, box_y + (current_row+1)*height - 2);
                        outtextxy(box_x + width/2, 
                                box_y + current_row*height + (height - textheight(option[current_row]))/2, 
                                option[current_row]);
                    }
                    current_row = i;
                    break;//for(i)

                }
            }
        }
        else if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            for(int i = 0; i < total_option; i++){
                if((mx >= box_x && mx <= (box_x+box_width)) && (my >= box_y + height*i && my <= box_y + height*(i+1))){
                    choice = i;
                    break;//for(i)
                }
            }
            break;//while(1)
        }
        delay(100);
    }

    setfillstyle(SOLID_FILL, returnbackground);
    bar(box_x, box_y, box_x + box_width+1, box_y + box_height+1);
    
    print();
    setgraphicsettings(&currentsettings);
    return choice;
}
