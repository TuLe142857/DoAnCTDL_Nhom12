#pragma once
#include"Flight.h"
#include"DefaultGraphic.h"

//=============== FUNCTION PROTOTYPE ==================
int Flight_processing();

//=============== FUNCTION DEFINITION =================
int Flight_processing(){
    print_workspace();
    int mx, my;
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);

            //return
            for(int i = 0; i < MAX_TAB; i++){
                if(tab_button[i].inside(mx, my)){
                    unclick_tab(FLIGHT_TAB);
                    if(i == FLIGHT_TAB) return MAIN_MENU;
                    click_tab(i);
                    return i;
                }
            }
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            for(int i = 0; i < MAX_TAB; i++){
                if(tab_button[i].inside(mx, my))
                    tab_button[i].hover();
                else 
                    tab_button[i].unhover();
    
            }
        }
        delay(100);
    }
}