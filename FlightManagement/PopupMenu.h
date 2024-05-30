#pragma once

#include"GraphicObject.h"

#define MAX_ITEM_IN_POPUPMENU 10
struct Item{
    string option;
    bool isactive = true;
};

class PopupMenu{
private:
    Item list[MAX_ITEM_IN_POPUPMENU];
    int n = 0;
    int width = 10;
    int height = 10;
public:
    int getwidth();
    int getheight();
    void add(string option);
    void active_option(int index);
    void unactive_option(int index);
    void active_alloption();
    void unactive_alloption();

    int choose(int x, int y);
};

int PopupMenu::getwidth(){
    return width;
}

int PopupMenu::getheight(){
    return (height*n) + 10;
}

void PopupMenu::add(string option){
    if(n >= MAX_ITEM_IN_POPUPMENU) return;
    list[n].option = option;
    n++;
    if(width < (textwidth(option) + 10))
        width = textwidth(option) + 10;
    if(height < (textheight(option) + 10))
        height = textheight(option) + 10;
}

void PopupMenu::active_option(int index){
    if(!(index >= 0 && index < n)) return;
    list[index].isactive = true;
}

void PopupMenu::unactive_option(int index){
    if(!(index >= 0 && index < n)) return;
    list[index].isactive = false;
}

void PopupMenu::active_alloption(){
    for(int i = 0; i < n; i++)
        list[i].isactive = true;
}

void PopupMenu::unactive_alloption(){
    for(int i = 0; i < n; i++)
        list[i].isactive = false;
}

int PopupMenu::choose(int x, int y){
    if(n == 0) return -1;
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    
    rounded_bar(x, y, width, 10 + (height*n), LIGHTGRAY);
    rounded_rect(x, y, width, 10 + (height*n), BLACK);

    settextstyle(2, HORIZ_DIR, 5);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    setbkcolor(LIGHTGRAY);
    for(int i = 0; i < n; i++){
        setcolor((list[i].isactive)?(BLACK):(DARKGRAY));
        outtextxy(x + width/2, y + 5 + i*height + (height - textheight(list[i].option))/2, list[i].option);
    }

    int choice = -1;
    int mx, my;
    while(1){
        if (ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            break;
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            bool take_an_option = false;
            for(int i = 0; i < n; i++){
                if((mx >= x && mx <= (x + width)) && (my >= (y + 5 + i*height) && my <= (y + 5 + (i+1)*height))){
                    take_an_option = true;
                    if(choice == i) break;
                    if(!list[i].isactive && choice != -1){
                        setcolor(BLACK);
                        setbkcolor(LIGHTGRAY);
                        rounded_bar(x + 5, y + 5 + choice*height, width-10, height, LIGHTGRAY );
                        outtextxy(x + width/2, y + 5 + choice*height + (height - textheight(list[choice].option))/2, list[choice].option);
                        choice = -1;
                        break;
                    }
                    else if(list[i].isactive){
                        setcolor(RED);
                        setbkcolor(WHITE);
                        rounded_bar(x + 5, y + 5 + i*height, width-10, height, WHITE );
                        outtextxy(x + width/2, y + 5 + i*height + (height - textheight(list[i].option))/2, list[i].option);

                        if(choice != -1){
                            setcolor(BLACK);
                            setbkcolor(LIGHTGRAY);
                            rounded_bar(x + 5, y + 5 + choice*height, width-10, height, LIGHTGRAY );
                            outtextxy(x + width/2, y + 5 + choice*height + (height - textheight(list[choice].option))/2, list[choice].option);
                        }
                        choice = i;
                        break;
                    }

                }
            }
            if(!take_an_option && choice != -1){
                setcolor(BLACK);
                setbkcolor(LIGHTGRAY);
                rounded_bar(x + 5, y + 5 + choice*height, width-10, height, LIGHTGRAY );
                outtextxy(x + width/2, y + 5 + choice*height + (height - textheight(list[choice].option))/2, list[choice].option);
                choice = -1;
            }
        }
        delay(100);
    }
    setgraphicsettings(&currentsettings);
    return choice;
}
