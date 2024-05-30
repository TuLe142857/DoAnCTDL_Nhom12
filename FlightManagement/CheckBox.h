#pragma once
#include"GraphicObject.h"

class CheckBox {
private:
    int x;
    int y;
    int size = 30;
    bool clicked = false;
public:
    void setup(int x, int y, int size = 30);
    void setx(int x);
    void sety(int y);
    void setsize(int size);
    void setclick(bool clicked);

    int getx();
    int gety();
    int getsize();
    bool isclicked();

    void print();
    void click();
    bool inside(int mx, int my);
};

void CheckBox::setup(int x, int y, int size){
    this->x = x;
    this->y = y;
    this->size = size;
}

void CheckBox::setx(int x){
    this->x = x;
}

void CheckBox::sety(int y){
    this->y = y;
}

void CheckBox::setsize(int size){
    this->size = size;
}

void CheckBox::setclick(bool clicked){
    this->clicked = clicked;
}


int CheckBox::getx(){
    return x;
}

int CheckBox::gety(){
    return y;
}

int CheckBox::getsize(){
    return size;
}

bool CheckBox::isclicked(){
    return clicked;
}


void CheckBox::print(){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    if(clicked == false){
        setfillstyle(SOLID_FILL, WHITE);
        bar(x, y, x + size, y + size);
        rounded_rect(x, y, size, size, BLACK);
    }else{
        rounded_bar(x, y, size, size, LIGHTGREEN);
        rounded_rect(x, y, size, size, LIGHTGREEN);
        setcolor(WHITE); 
        setlinestyle(SOLID_LINE, 0, 3);
        line(x+5, y+(size/2), x+size/2, (y+size)-5);
        line(x+size/2, (y+size)-5, x+size-5, y+5); 
    }
    setgraphicsettings(&currentsettings);
}

void CheckBox::click(){
    clicked = !clicked;
    print();
}

bool CheckBox::inside(int mx, int my){
    return ((mx >= x && mx <= (x + size)) && (my >= y && my <= (y + size)));
}
