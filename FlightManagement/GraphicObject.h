#pragma once
#include"GraphicFunction.h"

class GraphicObject{
protected:
    int x;
    int y;
    int width;
    int height;

    int textfont = 2;
    int textdirection = HORIZ_DIR;  //horizon direction
    int textsize = 5;
public:
    void setup(int x, int y, int width, int height);
    void setx(int x);
    void sety(int y);
    void setwidth(int width);
    void setheight(int height);
    void settext(int textfont, int textdirection, int textsize);

    int getx();
    int gety();
    int getwidth();
    int getheight();

    bool inside(int mx, int my);
};

//========== FUNTION DEFINITION =================

void GraphicObject::setup(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

}

void GraphicObject::setx(int x){
    this->x = x;
}

void GraphicObject::sety(int y){
    this->y = y;
}

void GraphicObject::setwidth(int width){
    this->width = width;
}

void GraphicObject::setheight(int height){
    this->height = height;
}

void GraphicObject::settext(int textfont, int textdirection, int textsize){
    this->textfont = textfont;
    this->textdirection = textdirection;
    this->textsize = textsize;
}

int GraphicObject::getx(){
    return x;
}

int GraphicObject::gety(){
    return y;
}

int GraphicObject::getwidth(){
    return width;
}

int GraphicObject::getheight(){
    return height;
}

bool GraphicObject::inside(int mx, int my){
    return ((mx >= x && mx <= (x + width)) && (my >= y && my <= (y + height)));
}
