#include"Plane_processing.h"
#include"Flight_processing.h"
#include"Passenger_processing.h"
  
int MainMenu();                 
void SetupGraphic();    
                                          
int main(){ 
    cout << "Khoi dong CT" << endl;
    //Khai bao cac danh sach va load data
    DSMayBay plane_list;
    PTR_FLIGHT flight_list = NULL;
    PNode *root = buildAVLTree(); 
	     
	//Load data            
    readfile(plane_list);           
    if(!load_flight_from_file("Data\\Flights.dat", flight_list, plane_list))
     	return 0;  
        
   cout << "Load xong tat ca du lieu" << endl;
       
    //Khoi tao do hoa
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);                                   
    SetupGraphic();
    int choosen_tab = MainMenu(); 
    graphicsettingstype defaultgraphicsettings;
    getgraphicsettings(&defaultgraphicsettings);           
    while(choosen_tab != EXIT){                             
        switch(choosen_tab){                                                
            case PLANE_TAB:{        
                setgraphicsettings(&defaultgraphicsettings);      
                choosen_tab = Plane_processing(plane_list, flight_list);  
                break;
            }    
            case FLIGHT_TAB:{
                setgraphicsettings(&defaultgraphicsettings);
                choosen_tab = Flight_processing(flight_list, plane_list, root);
                break;
            }  
            case PASSENGER_TAB:{
                setgraphicsettings(&defaultgraphicsettings);
                choosen_tab = Passenger_processing(root, flight_list, plane_list); 
                break;
            }
            case MAIN_MENU:{      
                choosen_tab = MainMenu();  
                break;
            }          
        }   
    }
                                                                 
    closegraph();
 
    //Giai phong bo nho cac danh sach, cac bien cap phat dong tai day
    //...
    freeing_flight_memory(flight_list, plane_list);
    deleteTree(root);
    return 0;
}

int MainMenu(){ 
    setcolor(TEXT_COLOR);
    setbkcolor(BACKGROUND_COLOR);
    setlinestyle(SOLID_LINE, 0, 1);
    settextstyle(TEXT_FONT, HORIZ_DIR, TEXT_SIZE);

    cleardevice(); 
    print_workspace();
    //Intro
    setbkcolor(WORKSPACE_COLOR);
    outtextxy(WORKSPACE_X + 100, WORKSPACE_Y + 50, "DO AN CUOI KY CAU TRUC DU LIEU VA GIAI THUAT");
    outtextxy(WORKSPACE_X + 100, WORKSPACE_Y + 100, "DE TAI: VIET CHUONG TRINH QUAN LY CHUYEN BAY");
    outtextxy(WORKSPACE_X + 100, WORKSPACE_Y + 150, "NHOM: 12");
    outtextxy(WORKSPACE_X + 100, WORKSPACE_Y + 200, "THANH VIEN:");
    outtextxy(WORKSPACE_X + 150, WORKSPACE_Y + 250, "");
    outtextxy(WORKSPACE_X + 150, WORKSPACE_Y + 300, "");
    outtextxy(WORKSPACE_X + 150, WORKSPACE_Y + 350, "");

    for(int i = 0; i < MAX_TAB; i++)    
        tab_button[i].print();        
    int mx, my;//luu toa do chuot                                             
    while(1){                
        //click chuot trai        
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my); 
            for(int i = 0; i < MAX_TAB; i++)
                if(tab_button[i].inside(mx, my)){
                    click_tab(i);
                    return i;
                }
        }
        //di chuyen chuot
        else if(ismouseclick(WM_MOUSEMOVE)){ 
            getmouseclick(WM_MOUSEMOVE, mx, my);
            for(int i = 0; i < MAX_TAB; i++)
                if(tab_button[i].inside(mx, my))
                    tab_button[i].hover();
                else    
                    tab_button[i].unhover();
        } 
        delay(100);
    }
}                                             
void SetupGraphic(){
    for(int i = 0; i < MAX_TAB; i++){
        tab_button[i].settext(3, HORIZ_DIR, 1);
        tab_button[i].settextcolor(BLACK, BLUE, BLUE, BLUE);
        tab_button[i].setbackground(BACKGROUND_COLOR, WORKSPACE_COLOR, WORKSPACE_COLOR, WORKSPACE_COLOR);
    }
         
    int tabw = (WORKSPACE_WIDTH-10-30)/(3);
    tab_button[PLANE_TAB].      setup(WORKSPACE_X + 5 + tabw*0, 10, tabw-5, 30, "MAY BAY");
    tab_button[FLIGHT_TAB].     setup(WORKSPACE_X + 5 + tabw*1, 10, tabw-5, 30, "CHUYEN BAY");
    tab_button[PASSENGER_TAB].  setup(WORKSPACE_X + 5 + tabw*2, 10, tabw-5, 30, "HANH KHACH");

    tab_button[EXIT].setup(WORKSPACE_X + WORKSPACE_WIDTH - 35, 10, 30, 30, "X");
    tab_button[EXIT].settextcolor(WHITE, WHITE, WHITE, WHITE);  
    tab_button[EXIT].setbackground(RED, LIGHTRED, RED, RED);

    //vo hieu hoa nut thoat CT
    //Ham "EnableMenuItem" nay lay tren mang :))
    //Neu ham nay loi thi xoa chu ko biet fix dau :))
    EnableMenuItem(GetSystemMenu(GetForegroundWindow(), FALSE), SC_CLOSE,
		MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	
	//set graphic cho flight tab
	SetupGraphicFlightTab();
}
