#pragma once
#include"GraphicObject.h"

enum BUTTON_STATUS {NORMAL, HOVER, CLICK, UNACTIVE };

class Button:public GraphicObject{
private:
    string content = "";
    int status = NORMAL;
    int textcolor[4] = {WHITE, BLUE, BLACK, BLACK}; //textcolor :NORMAL, HOVER, CLICK, UNACTIVE 
    int backgroundcolor[4] = {LIGHTGREEN, GREEN, LIGHTCYAN, LIGHTGRAY};
public:
    void setup(int x, int y, int width, int height, string content);
    void setcontent(string content);
    void setstatus(int status);
    void settextcolor(int normal, int hover, int click, int unactive);
    void setbackground(int normal, int hover, int click, int unactive);

    string getcontent();
    int getstatus();
    bool isactive();

    void print();
    void hover();
    void click();
    void unhover();
    void unclick();
};

void Button::setup(int x, int y, int width, int height, string content){
    GraphicObject::setup(x, y, width, height);
    this->content = content;
}

void Button::setcontent(string content){
    this->content = content;
}

void Button::setstatus(int status){
    if(status >= NORMAL && status <= UNACTIVE)
        this->status = status;
}

void Button::settextcolor(int normal, int hover, int click, int unactive){
    //Mau chi nhan gia tri (0->15)
    if(normal >= 0 && normal <= 15)
        textcolor[NORMAL] = normal;
    if(hover >= 0 && hover <= 15)
        textcolor[HOVER] = hover;
    if(click >= 0 && click <= 15)
        textcolor[CLICK] = click;
    if(unactive >= 0 && unactive <= 15)
        textcolor[UNACTIVE] = unactive;
}

void Button::setbackground(int normal, int hover, int click, int unactive){
    //Mau chi nhan gia tri (0->15)
    if(normal >= 0 && normal <= 15)
        backgroundcolor[NORMAL] = normal;
    if(hover >= 0 && hover <= 15)
        backgroundcolor[HOVER] = hover;
    if(click >= 0 && click <= 15)
        backgroundcolor[CLICK] = click;
    if(unactive >= 0 && unactive <= 15)
        backgroundcolor[UNACTIVE] = unactive;
}

string Button::getcontent(){
    return content;
}

int Button::getstatus(){
    return status;
}

bool Button::isactive(){
    return (status != UNACTIVE);
}


void Button::print(){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    
    settextstyle(textfont, textdirection, textsize);
    setcolor(textcolor[status]);
    setbkcolor(backgroundcolor[status]);
    settextjustify(CENTER_TEXT, TOP_TEXT);

    rounded_bar(x, y, width, height, backgroundcolor[status]);
    outtextxy(x + width/2, y + (height - textheight(content))/2, content);

    setgraphicsettings(&currentsettings);
}

void Button::hover(){
    if(status == NORMAL){
        status = HOVER;
        print();
    }
}

void Button::click(){
    if(status != CLICK && status != UNACTIVE){
        status = CLICK;
        print();
    }
}

void Button::unhover(){
    if(status == HOVER){
        status = NORMAL;
        print();
    }
}

void Button::unclick(){
    if(status == CLICK){
        status = NORMAL;
        print();
    }
}
