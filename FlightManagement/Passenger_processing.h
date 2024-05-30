#pragma once
#include"passenger_tree.h"
#include"DefaultGraphic.h"

int Passenger_processing(){
    print_workspace();

    int mx, my;
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);

            //return
            for(int i = 0; i < MAX_TAB; i++){
                if(tab_button[i].inside(mx, my)){
                    unclick_tab(PASSENGER_TAB);
                    if(i == PASSENGER_TAB) return MAIN_MENU;
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