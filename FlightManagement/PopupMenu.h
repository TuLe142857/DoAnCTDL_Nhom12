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

    int textcolor_normal = BLACK;
    int textcolor_highlight = RED;
    int textcolor_unactive = DARKGRAY;

    int background_normal = LIGHTGRAY;
    int background_highlight = WHITE;

    int textfont = 10;
    int textsize = 1;
public:
    void settextcolor(int normal, int highlight, int unactive);
    void setbackgroundcolor(int normal, int highlight);
    void settext(int font, int size){
        textfont = font;
        textsize = size;
    }
    int getwidth();
    int getheight();
    void add(string option);
    void active_option(int index);
    void unactive_option(int index);
    void active_alloption();
    void unactive_alloption();

    int choose(int x, int y);
};

void PopupMenu::settextcolor(int normal, int highlight, int unactive){
    textcolor_normal = normal;
    textcolor_highlight = highlight;
    textcolor_unactive = unactive;
}
void PopupMenu::setbackgroundcolor(int normal, int highlight){
    background_normal = normal;
    background_highlight = highlight;
}

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
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    settextstyle(textfont, HORIZ_DIR, textsize);
    if(width < (textwidth(option) + 20))
        width = textwidth(option) + 20;
    if(height < (textheight(option) + 10))
        height = textheight(option) + 10;
    setgraphicsettings(&currentsettings);
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
    
    rounded_bar(x, y, width, 10 + (height*n), background_normal);
    rounded_rect(x, y, width, 10 + (height*n), BLACK);

    settextstyle(textfont, HORIZ_DIR, textsize);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    setbkcolor(background_normal);
    for(int i = 0; i < n; i++){
        setcolor((list[i].isactive)?(textcolor_normal):(textcolor_unactive));
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
                        setcolor(textcolor_normal);
                        setbkcolor(background_normal);
                        rounded_bar(x + 5, y + 5 + choice*height, width-10, height, background_normal );
                        outtextxy(x + width/2, y + 5 + choice*height + (height - textheight(list[choice].option))/2, list[choice].option);
                        choice = -1;
                        break;
                    }
                    else if(list[i].isactive){
                        setcolor(textcolor_highlight);
                        setbkcolor(background_highlight);
                        rounded_bar(x + 5, y + 5 + i*height, width-10, height, background_highlight );
                        outtextxy(x + width/2, y + 5 + i*height + (height - textheight(list[i].option))/2, list[i].option);

                        if(choice != -1){
                            setcolor(textcolor_normal);
                            setbkcolor(background_normal);
                            rounded_bar(x + 5, y + 5 + choice*height, width-10, height, background_normal );
                            outtextxy(x + width/2, y + 5 + choice*height + (height - textheight(list[choice].option))/2, list[choice].option);
                        }
                        choice = i;
                        break;
                    }

                }
            }
            if(!take_an_option && choice != -1){
                setcolor(textcolor_normal);
                setbkcolor(background_normal);
                rounded_bar(x + 5, y + 5 + choice*height, width-10, height, background_normal );
                outtextxy(x + width/2, y + 5 + choice*height + (height - textheight(list[choice].option))/2, list[choice].option);
                choice = -1;
            }
        }
        delay(100);
    }
    setgraphicsettings(&currentsettings);
    return choice;
}
