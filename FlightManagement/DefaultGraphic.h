#pragma once
#include"Button.h"
#include"CheckBox.h"
#include"InsertBox.h"
#include"Table.h"
#include"PopupMenu.h"
#include"SelectionList.h"

//Kich thuoc cua so
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 750
#define BACKGROUND_COLOR CYAN   


//Font / size chu
#define TEXT_COLOR BLACK
#define TEXT_FONT 10
#define TEXT_SIZE 2

//Work space
#define WORKSPACE_COLOR LIGHTCYAN
#define WORKSPACE_X 10
#define WORKSPACE_Y 50
#define WORKSPACE_WIDTH (WINDOW_WIDTH-30)
#define WORKSPACE_HEIGHT (WINDOW_HEIGHT-75)
void print_workspace(){
    rounded_bar(WORKSPACE_X, WORKSPACE_Y, WORKSPACE_WIDTH, WORKSPACE_HEIGHT, WORKSPACE_COLOR);
}

//Cac tab chinh 
#define MAX_TAB 4
enum MAINTAB {PLANE_TAB, FLIGHT_TAB, PASSENGER_TAB, EXIT, MAIN_MENU};
Button tab_button[MAX_TAB];//index: PLANETAB, FLIGHTTAB, PASSENGERTAB, EXIT

void click_tab(int n){
    if(!(n >= 0 && n < MAX_TAB)) return;
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    setfillstyle(SOLID_FILL, WORKSPACE_COLOR);
    bar(tab_button[n].getx(), 
        tab_button[n].gety() + tab_button[n].getheight() - 5, 
        tab_button[n].getx() + tab_button[n].getwidth(),
        WORKSPACE_Y);
    tab_button[n].click();

    setgraphicsettings(&currentsettings);
}

void unclick_tab(int n){
    if(!(n >= 0 && n < MAX_TAB)) return;
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
    bar(tab_button[n].getx(), 
        tab_button[n].gety() + tab_button[n].getheight() - 5, 
        tab_button[n].getx() + tab_button[n].getwidth(),
        WORKSPACE_Y);
    tab_button[n].unclick();
    
    setgraphicsettings(&currentsettings);
}