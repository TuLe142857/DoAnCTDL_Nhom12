#pragma once
#include"passenger_tree.h"
#include"DefaultGraphic.h"

#define X1_TABLE 325     //width = 1290
#define Y1_TABLE 180    // height = 470
#define X2_TABLE 1075
#define Y2_TABLE 650
   
#define X_TABLE 200
#define Y_TABLE 180

#define LINE_HEIGHT 42
#define Y_FIRSTROW 230

#define X_CCCD 575
#define X_HO 855
#define X_TEN 1000
#define X_GIOI 1075
#define TABLE_W 750

#define X_FORM 445
#define Y_FORM 170

#include <iostream>
#include <graphics.h>
#include <string.h>
#include <cstring>
#include <cctype> 
#include "passengers.h"
#include "HCOMPONENTS.h"
#include <cmath>

using namespace std;

// this is the list that will be displayed on the screen!!!!
Passenger displayed_passengers[10];

void draw_table(int &page, int& NodeCounter, int& pageMax, PNode**&Plist);
void customer_manage();
void draw_customer_workspace(int NodeCounter, int &pageMax, int &page, PNode **&Plist);
void draw_tool_bar();
void draw_searchBox(int color, char*type, int x1, int y1, int width, int height);
void draw_checkBox(char *content, int x, int y, int width, int height);
void draw_row(int y, Passenger pas);
void draw_add_gui();
void draw_edit_gui(int index);
void draw_delete_gui();
void drawDropDown(int x, int y);
void drawViewFlightGUI(int index, PTR_FLIGHT &flight_list);

void which_hovered_row(int x, int y, int &page, int &pageMax, int &NodeCounter);
int which_checkBox(int x, int y);
int which_input(int x, int y);
int which_button(int x, int y);
void which_hovered_button(int x, int y, int s, int f);
void which_hovered_input(int x, int y, int s, int f);
int which_rclicked_row(int x, int y, int &page, int &pageMax, int &NodeCounter);
int which_lclicked_row(int x, int y);

void button_hightlight(H_Button bt);
void button_unhightlight(H_Button bt); 
void input_hightlight(InputBox ib);
void input_unhightlight(InputBox ib);
void focus_input(InputBox ib, int s, int f);
void row_hightlight(int index, Passenger pas);
void draw_edit_gui_v2();

void get_input(InputBox ib, int s, int f, PNode **&Plist, PNode *root, int &NodeCounter,int &pageMax, int &page, PTR_FLIGHT &flight_list, DSMayBay &plane_list);
void choose_box(CheckBox cb);
void unchoose_box(CheckBox cb);
void fake_btn(int x, int y, int width, int height, int color, char* placeholder);

void render_table_data(int &NodeCounter, int &page, int &pageMax, PNode **&Plist);
void render_s_table(Flight as[], int counter,int page, int pageMax, char* ticket_list[], int& maxRow);

void dropDownOption(int x, int y, int &NodeCounter, int &page, int &pageMax, PNode*& root, PNode**&Plist, PTR_FLIGHT &flight_list, DSMayBay &plane_list
, char *ticket_list[]);

void add_passenger(int &NodeCounter, int &page, int &pageMax, PNode *&root, PNode **&Plist, PTR_FLIGHT &flight_list,DSMayBay &plane_list);
void insert_passenger(int &NodeCounter, PNode*&root, PNode**&Plist);
int delete_passenger_logic(int i, int &NodeCounter, int &page, PNode *&root, PNode **&Plist);
void edit_passenger_logic(int index, int& page, PNode *&root, PNode**&Plist,int &NodeCounter, int &pageMax, PTR_FLIGHT &flight_list, DSMayBay &plane_list);
void edit_passenger(int index, int &page, PNode*&root, PNode**&Plist);

void viewLogic(int index, PTR_FLIGHT &flight_list, DSMayBay &plane_list,char *ticket_list[], int &NodeCounter, int &page, int &pageMax, PNode **&Plist);
void cancelSticket(char* mcb, DSMayBay &plane_list, char *cccd, PTR_FLIGHT &flight_list);

char *check_info(PNode *&root) ;
char *check_info_edit();

bool search_ticket(FlightNode *node, char *cccd, DSMayBay &plane_list);
void filter_by_cccd(char *cccd, PNode **&Plist, PNode *root, int &NodeCounter, int &pageMax, int &page);
void filter_by_flightID(FlightNode *node, char *flightID, PNode **&Plist, PNode *root, int &pageMax, int &page, int &NodeCounter, DSMayBay &plane_list);
void ultimateFilter(PNode **&Plist, PNode *&root, FlightNode *node,int &pageMax, int &page, int &NodeCounter, DSMayBay &plane_list);
void cccd_array_filter(char *cccd, PNode **&Plist, int &page, int &pageMax, int &NodeCounter);

bool isCancel(char *text);
int notification(char *alert);
void notification_v2(char *alert);
void notification_v3(char *alert);

int load_ticket(FlightNode *node, char *cccd, Flight as[], DSMayBay &plane_list, char *ticket_list[]);
int *getRCnum(char *mmb, DSMayBay &plane_list);
char* concatenateStrings(const char* prefix, const char* suffix);
char* removeTrailingSpace(const char* str);
void fillText(int i, int bg);

// button definition

enum Button_id {ADD_BUTTON = 5, NEXTBUTTON, PREVIOUSBUTTON, SUBMITBUTTON, BACKBUTTON, CANCELBUTTON, YESBUTTON, XBUTTON, VIEWBACKBUTTON};


//	H_Button (x1, y1, width, height, type, color)
H_Button addButton(X2_TABLE+ 20,Y1_TABLE - 90, 80, 50,"ADD", 2);

H_Button nextButton(X1_TABLE + 430, Y2_TABLE + 20, 50, 30, ">>", 2);
H_Button previousButton(X1_TABLE + 250, Y2_TABLE + 20, 50, 30, "<<", 2);

H_Button submitAddButton(X_FORM + 200, Y_FORM + 320, 100, 50, "SUBMIT", 2);
H_Button backButton(X_FORM + 460,Y_FORM + 15, 35, 35, "X", 2);
H_Button xButton(X_FORM + 450,Y_FORM + 60, 35, 35, "X", 2);

H_Button cancelButton(X_FORM + 150, Y_FORM + 250, 100, 50,"CANCEL", 2);
H_Button yesButton(X_FORM + 270,Y_FORM + 250, 100, 50, "YES", 2);

H_Button viewBackButton(0+ 25, 0 + 65, 100, 50, "BACK", 2);


#define max_btn 9
extern H_Button btn[max_btn] = {addButton,nextButton, previousButton, submitAddButton, backButton, cancelButton, yesButton, xButton, viewBackButton};

//InputBox(int x, int y, int width, int height, char *type, int color) 
InputBox userIDInput(X1_TABLE + 30, Y1_TABLE - 120 + 45, 20, 30, 8, "CCCD", 0);
InputBox flightIDInput(X1_TABLE + 385, Y1_TABLE - 120 + 45, 20, 30, 8, "FLIGHT_ID",1);

InputBox addCccdInput(X_FORM +50, Y_FORM + 190, 12, 40,8, "CCCD",2);
InputBox addHoInput(X_FORM + 50, Y_FORM + 120, 20,40, 8, "SURNAME",3);
InputBox addTenInput(X_FORM + 50, Y_FORM + 50, 20,40, 8, "NAME", 4);

#define max_ib 5
extern InputBox input[max_ib] = {userIDInput, flightIDInput, addCccdInput, addHoInput, addTenInput};
enum Input_id {USER_ID_INPUT, FLIGHT_ID_INPUT, ADD_CCCD_INPUT, ADD_HO_INPUT, ADD_TEN_INPUT};

H_CheckBox male(X_FORM +  50, Y_FORM + 260, 100, 40, "MALE");
H_CheckBox female(X_FORM +  200, Y_FORM + 260, 150, 40, "FEMALE");

#define max_cb 2
H_CheckBox checkbox[max_cb] = {male,female};
enum checkbox_id {MALE,FEMALE};

string option[2] = {"view", "edit"};

// THIS IS THE MASTER FUNCTION TO CALL IN MAIN.CPP
enum XU_LY{MAYBAY, CHUYENBAY, HANHKHACH, THOATCT, MAINMENU};
int Passenger_processing(PNode *&root, PTR_FLIGHT &flight_list, DSMayBay &plane_list){
    for(int i = 0; i < MAX_TAB; i++) tab_button[i].print();
	
	int mx, my;
	int n = 0;
	int btnVar,inputVar, checkboxVar, lc;
	bool condition;
	PNode **Plist;

	int pageMax;
	int static page = 1;	

	int NodeCounter = countNodes(root);
	
	Plist = new PNode *[NodeCounter];
	
	traverTree_ltl(root,Plist, n);
	
	print_workspace();		
	draw_customer_workspace(NodeCounter, pageMax, page, Plist);	
	
	char *ticket_list[300];
	
	
	while(1){
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, mx, my);

			btnVar = which_button(mx, my);
			inputVar =  which_input(mx, my);
			checkboxVar = which_checkBox(mx, my);
			for(int i = 0; i < MAX_TAB; i++){
                if(tab_button[i].inside(mx, my)){
                    unclick_tab(PASSENGER_TAB);
                    if(i == PASSENGER_TAB) return MAIN_MENU;
                    click_tab(i);
                    return i;
                }
            }
			switch(btnVar) {
				case ADD_BUTTON:
					add_passenger(NodeCounter, page, pageMax, root, Plist, flight_list, plane_list);

					break;
				case NEXTBUTTON:
					for(int i = 0; i < NodeCounter; i++) {
						print(Plist[i]->pas);
					}
					if(page < pageMax) {
						page++;
						render_table_data(NodeCounter, page, pageMax, Plist);
					}
					
					break;
				case PREVIOUSBUTTON:
					if(page >= 2) {
						page--;
						render_table_data(NodeCounter, page, pageMax, Plist);
					}
					break;
			}	     
			
			switch(inputVar) {
				case USER_ID_INPUT:
					get_input(input[USER_ID_INPUT],0,2,Plist, root, NodeCounter, pageMax, page, flight_list, plane_list);
				
					break;
				case FLIGHT_ID_INPUT:
					get_input(input[FLIGHT_ID_INPUT],0,2,Plist, root, NodeCounter, pageMax, page, flight_list, plane_list);
				
					break;
				case 999:
					break;
			}
			switch(lc) {
				case MAYBAY: 
					break;
				case HANHKHACH:
					return HANHKHACH;
			}


			
			
		}
		else if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE, mx, my);
			which_hovered_button(mx, my,0,3);

			which_hovered_input(mx, my,0,2);
			which_hovered_row(mx, my, page, pageMax, NodeCounter);
 
            for(int i = 0; i < MAX_TAB; i++){
                if(tab_button[i].inside(mx, my))
                    tab_button[i].hover();
                else 
                    tab_button[i].unhover();
    
            }										
		}else if(ismouseclick(WM_RBUTTONDOWN)) {
			getmouseclick(WM_RBUTTONDOWN, mx, my); 			
			
			if(page != pageMax) { 
				condition = (mx >= X1_TABLE && mx <= X2_TABLE && my >= Y1_TABLE+50 && my <= Y2_TABLE);
			}else if(NodeCounter == 0) {
				condition == false;
			}else {
				if(NodeCounter % 10 == 0) {
					condition = (mx >= X1_TABLE && mx <= X2_TABLE && my >= Y1_TABLE+50 && my <= (Y1_TABLE + 47 + LINE_HEIGHT*10));
				}else {
					condition = (mx >= X1_TABLE && mx <= X2_TABLE && my >= Y1_TABLE+50 && my <= (Y1_TABLE + 47 + LINE_HEIGHT*(NodeCounter%10)));
				}	
				
			}
					
			if(condition) {
				dropDownOption(mx, my, NodeCounter,page, pageMax,root, Plist, flight_list, plane_list, ticket_list);
			}
		};
		delay(50);
	}
	
	delete []Plist;
	cout << "End customer" << endl;
}

   
// THIS IS DRAW WORKSPACE SECTION

// this is draw function for whole customer tab
void draw_customer_workspace(int NodeCounter,int &pageMax, int& page, PNode **&Plist) {
	if(NodeCounter%10 == 0) {
		if(NodeCounter == 0) {
			pageMax = 1;
		}else {
			pageMax = NodeCounter/10;
		}		
	}else {
		pageMax = NodeCounter/10 + 1;
	}
	
	draw_tool_bar();
	
	addButton.draw_button();
	
	draw_table(page, NodeCounter, pageMax, Plist);
	for(int i = 0; i < 2; i++) {
		if(strcmp(input[i].content, "") != 0) {
			fillText(i, 15);
		}
	}
	
	setbkcolor(11);
	setcolor(0);
	outtextxy(50, Y2_TABLE + 20, "*Right click to open menu");
}

void fillText(int i, int bg) {
	int char_height = textheight("W");
	setbkcolor(bg);   
	setfillstyle(SOLID_FILL, bg);
	bar(input[i].x, input[i].y, input[i].x + input[i].width, input[i].y + input[i].height);
	setcolor(0);
	rectangle(input[i].x,input[i].y,input[i].x + input[i].width, input[i].y + input[i].height);
	moveto(input[i].x + 5, input[i].y + input[i].height/2 - char_height/2);
	
	outtext(input[i].content);
}
// this is the funntion to draw for the main table
void draw_table(int &page, int &NodeCounter, int &pageMax, PNode **&Plist) {

	setfillstyle(SOLID_FILL, 15);
	bar(X1_TABLE, Y1_TABLE, X2_TABLE, Y1_TABLE + 50);
	
	setcolor(0);
	rectangle(X1_TABLE, Y1_TABLE, X2_TABLE, Y1_TABLE + 50);
	
	//Draw header
	
	setbkcolor(15);
	settextstyle(DEFAULT_FONT, HORIZ_DIR,2);
	
	outtextxy(X1_TABLE + 30, Y1_TABLE + 12, "CCCD");
	outtextxy(X_CCCD + 40,Y1_TABLE + 12, "HO");
	outtextxy(X_HO + 40, Y1_TABLE + 12, "TEN");
	outtextxy(X_TEN + 10, Y1_TABLE + 12, "SEX");

	

	//Draw col
	line(X_CCCD, Y1_TABLE, X_CCCD, Y1_TABLE +50);
	line(X_HO, Y1_TABLE, X_HO,  Y1_TABLE +50);
	line(X_TEN, Y1_TABLE, X_TEN,  Y1_TABLE +50);
	line(X_GIOI, Y1_TABLE, X_GIOI,  Y1_TABLE +50);
	
	render_table_data(NodeCounter, page, pageMax, Plist);
	
	nextButton.draw_button();
	previousButton.draw_button();
}

void draw_tool_bar() {
	int x1 = X1_TABLE; 
	int y1 = Y1_TABLE-120; 
	int x2 = X2_TABLE; 
	int y2 = Y1_TABLE - 10;

	setcolor(0);
	setfillstyle(SOLID_FILL, 15);
	bar(x1,y1,x2,y2);

	rectangle(x1, y1, x2, y2);
	// search by ccd
	userIDInput.drawInputBox();
	// seacrh by Flight_ID
	flightIDInput.drawInputBox();	
}

//rounded_bar(int x, int y, int ngang, int doc, int fillcolor, int r = 5)
void button_hightlight(H_Button bt) {

	settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);

	int x1 = bt.x1; int y1 = bt.y1; int x2 = bt.x2; int y2 = bt.y2; int height = bt.height; int width = bt.width; int color = bt.color;
	char *type = bt.button_type;
	
	int h = textheight(type);
	int w = textwidth(type);
	rounded_bar(x1, y1, width, height, 10, 5);
	setbkcolor(10);
	moveto(x1+width/2 - w/2, y1 + height/2 - h/2);
	setcolor(color);
	outtext(type);
}

void button_unhightlight(H_Button bt) {

	settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);

	int x1 = bt.x1; int y1 = bt.y1; int x2 = bt.x2; int y2 = bt.y2; int height = bt.height; int width = bt.width; int color = bt.color;
	char *type = bt.button_type;
	
	int h = textheight(type);
	int w = textwidth(type);

	rounded_bar(x1 , y1 , width , height, color, 5);
	setbkcolor(color);
	moveto(x1+width/2 - w/2, y1 + height/2 - h/2);
	setcolor(15);
	outtext(type);	
}

void input_hightlight(InputBox ib) {
	int x = ib.x, y = ib.y, height = ib.height, width = ib.width,  color = ib.color; char *type = ib.type;
	
	int w = textwidth(type);
	int h = textheight(type);
	
	setfillstyle(SOLID_FILL, 7);
	bar(x,y,x + width, y + height);
	setcolor(0);
	rectangle(x,y,x+width, y+height);
	
	setbkcolor(7);
	moveto(x + width/2 - w/2, y + height/2 - h/2);
	setcolor(15);
	outtext(type);
}

void input_unhightlight(InputBox ib) {
	ib.drawInputBox();
}


void focus_input(InputBox ib, int s, int f) {
	int char_counter = strlen(ib.content);

	int x = ib.x, y = ib.y, height = ib.height, width = ib.width,  color = ib.color; char *type = ib.type;
	int char_height = textheight("W");
	int char_width = textwidth("W");
	setfillstyle(SOLID_FILL, 15);
	
	bar(x, y, x + width, y + height);
	setcolor(0);
	rectangle(x,y,x + width, y + height);
	
	for(int i = s; i < f; i++) {
		if(strcmp(ib.type, input[i].type) == 0) {
			setbkcolor(15);   
			setfillstyle(SOLID_FILL, 15);
			bar(input[i].x, input[i].y, input[i].x + input[i].width, input[i].y + input[i].height);
			setcolor(0);
			rectangle(input[i].x,input[i].y,input[i].x + input[i].width, input[i].y + input[i].height);
			moveto(input[i].x + 5, input[i].y + input[i].height/2 - char_height/2);
			setbkcolor(15);
			outtext(input[i].content);
			if(char_counter < ib.width/16){
				outtextxy(x + char_width*strlen(input[i].content) + 8, y+height/2-5, "-");
				return;
			}
		}else if(strcmp(ib.type, input[i].type) != 0 && strlen(input[i].content) == 0) {
			input_unhightlight(input[i]);
		}
	}
}

void choose_box(H_CheckBox cb) {
	int cx = cb.cx, cy = cb.cy;
	setcolor(0);
	circle(cx, cy, 12);

	setfillstyle(SOLID_FILL, 7);

	floodfill(cx, cy, 0);
}

void unchoose_box(H_CheckBox cb) {
	int cx = cb.cx, cy = cb.cy;
	setfillstyle(SOLID_FILL, 15);
	bar(cx - 16, cy - 16, cx + 16, cy + 16);
	setcolor(0);
	circle(cx, cy, 15);
}

void draw_row(int y, Passenger pas) {
	setcolor(0);
	setfillstyle(SOLID_FILL, 15);
	bar(X1_TABLE, y, X2_TABLE, y + LINE_HEIGHT);
	rectangle(X1_TABLE, y ,X2_TABLE, y +LINE_HEIGHT);
	
	line(X_CCCD, y, X_CCCD, y + LINE_HEIGHT);
	line(X_HO, y, X_HO, y + LINE_HEIGHT);
	line(X_TEN,y, X_TEN, y + LINE_HEIGHT);
	line(X_GIOI, y, X_GIOI, y + LINE_HEIGHT);   
	
	setbkcolor(15);
	outtextxy(X1_TABLE + 2, y+12, pas.getCccd());
	outtextxy(X_CCCD +5, y +12 , pas.getHo());
	outtextxy(X_HO +5, y +12 , pas.getTen());
	outtextxy(X_TEN +4, y + 12, pas.getSex());
}

void row_hightlight(int index, Passenger pas) {
	setcolor(0);
	int y = Y_FIRSTROW + LINE_HEIGHT*index;
	
	setfillstyle(SOLID_FILL, 7);
	bar(X1_TABLE, y, X2_TABLE, y + LINE_HEIGHT);
	
	rectangle(X1_TABLE, y ,X2_TABLE, y +LINE_HEIGHT);
	
	line(X_CCCD, y, X_CCCD, y + LINE_HEIGHT);
	line(X_HO, y, X_HO, y + LINE_HEIGHT);
	line(X_TEN,y, X_TEN, y + LINE_HEIGHT);
	line(X_GIOI, y, X_GIOI, y + LINE_HEIGHT);
	
	setbkcolor(7);
	outtextxy(X1_TABLE + 2, y+12, pas.getCccd());
	outtextxy(X_CCCD +5, y +12 , pas.getHo());
	outtextxy(X_HO +5, y +12 , pas.getTen());
	outtextxy(X_TEN +4, y + 12, pas.getSex());
}

void draw_add_gui() {
	const int xmax = getmaxx();
	const int ymax = getmaxy();	
	
	int height = 400;
	int width = 500;
	int x = xmax/2 - width/2;
	int y = ymax/2 - height/2;

	rounded_bar(WORKSPACE_X,WORKSPACE_Y, WORKSPACE_WIDTH, WORKSPACE_HEIGHT, 11);
	
	setfillstyle(SOLID_FILL, 15);

	bar(x , y, x+width, y+height);
	
	addCccdInput.drawInputBox();
	addHoInput.drawInputBox();
	addTenInput.drawInputBox();
	male.draw_checkBox();
	female.draw_checkBox();
	submitAddButton.draw_button();
	backButton.draw_button();
	setcolor(0);
	rectangle(x , y, x+width, y+height);
}


// THIS IS END DRAW SECTION



// THIS IS LOGIC SECTION

int delete_passenger_logic(int i, int &NodeCounter, int &page, PNode *&root, PNode **&Plist) {
	
	bool re = isCancel("Do you want to delete?");
	
	if(re == true) {
		return HANHKHACH;
	}else {
		root = deleteNode(root, displayed_passengers[i]);
		delete []Plist;
		
		NodeCounter--;
		Plist = new PNode*[NodeCounter];
		int n = 0;
		traverTree_ltl(root, Plist, n);
		saveData(root);
		
		if(NodeCounter % 10 == 0) {
			page--;
		}
   
		return HANHKHACH;
	}
}


void add_passenger(int &NodeCounter, int &page, int &pageMax, PNode *&root, PNode **&Plist, PTR_FLIGHT &flight_list, DSMayBay &plane_list) {
	draw_add_gui();
	int mx, my;
	int btnVar, inputVar, checkVar, checkboxVar;
	
	char *ten, ho, cccd, sex;
	
		while(1){
			if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, mx, my);
			btnVar = which_button(mx, my);
			inputVar =  which_input(mx, my);
			checkboxVar = which_checkBox(mx, my);
			switch(btnVar) {
				case BACKBUTTON:
					strcpy(input[ADD_CCCD_INPUT].content,"");
					strcpy(input[ADD_HO_INPUT].content,"");
					strcpy(input[ADD_TEN_INPUT].content,"");
					
					male.isClicked = false;
					female.isClicked = false;
					
					print_workspace();		
					draw_customer_workspace(NodeCounter, pageMax, page, Plist);	
					return;
				case SUBMITBUTTON:
					char * message = check_info(root);
					if (strcmp(message, "ok") != 0) {
						notification_v3(message);		
					}else {
						if(!isCancel("Are you sure to submit!")){
							insert_passenger(NodeCounter, root, Plist);
							notification_v2("Inserted!!");
							draw_add_gui();
						}else{
							draw_edit_gui_v2();
						}
					}
					break;
			}	     
			

			switch(inputVar) {
				case ADD_CCCD_INPUT:
					get_input(input[ADD_CCCD_INPUT],2,5,Plist, root, NodeCounter, pageMax, page, flight_list, plane_list);

					break;
				case ADD_HO_INPUT:
					get_input(input[ADD_HO_INPUT],2,5,Plist, root, NodeCounter, pageMax, page, flight_list, plane_list);
					break;
				case ADD_TEN_INPUT:
					get_input(input[ADD_TEN_INPUT],2,5,Plist, root, NodeCounter, pageMax, page, flight_list, plane_list);
					break;
				case 999:
					break;
			}
			
			
		}
		else if(ismouseclick(WM_MOUSEMOVE)){
			//			enum Input_id {USER_ID_INPUT, FLIGHT_ID_INPUT, ADD_CCCD_INPUT, ADD_HO_INPUT, ADD_TEN_INPUT};
//			extern H_Button btn[max_btn] = {addButton,nextButton, previousButton, submitAddButton, backButton, cancelButton, yesButton, xButton};
			getmouseclick(WM_MOUSEMOVE, mx, my);
			which_hovered_button(mx, my, 3, 5);

			which_hovered_input(mx, my, 2, 5);											
		};
		delay(50);
	}
}


//enum Input_id {NAME_INPUT, USER_ID_INPUT, FLIGHT_ID_INPUT, ADD_CCCD_INPUT, ADD_HO_INPUT, ADD_TEN_INPUT};
char *check_info(PNode *&root) {
	if(strcmp(input[ADD_CCCD_INPUT].content, "") == 0) return "CCCD Khong The Trong";
	else if(strlen(input[ADD_CCCD_INPUT].content) < 12) return "CCCD phai chinh xac 12 ky tu";
	else if(strcmp(input[ADD_HO_INPUT].content, "") == 0) return "Ho Khong The Trong";
	else if(strcmp(input[ADD_TEN_INPUT].content, "") == 0) return "Ten Khong The Trong";
 	else if(checkbox[MALE].isClicked == false && checkbox[FEMALE].isClicked == false) return "Gioi Tinh Khong Duoc De Trong";
 	else if(search(root, input[ADD_CCCD_INPUT].content) != NULL) return "CCCD was existed";
 	else return "ok";
}

char *check_info_edit() {
	if(strcmp(input[ADD_HO_INPUT].content, "") == 0) return "Ho Khong The Trong";
	else if(strcmp(input[ADD_TEN_INPUT].content, "") == 0) return "Ten Khong The Trong";
 	else if(checkbox[MALE].isClicked == false && checkbox[FEMALE].isClicked == false) return "Gioi Tinh Khong Duoc De Trong";
 	else return "ok";
}

void insert_passenger(int &NodeCounter, PNode *&root, PNode**&Plist) {
    char *cccd = input[ADD_CCCD_INPUT].content;
    char *ho = removeTrailingSpace(input[ADD_HO_INPUT].content);
    char *ten = input[ADD_TEN_INPUT].content;
    char *sex;
    
    if(checkbox[MALE].isClicked == true) {
        sex = "Nam";
    } else {
        sex = "Nu";
    }
    
    Passenger pas(cccd, ho, ten, sex); 
    
    root = insert(root, pas); 
    
    delete []Plist;
	NodeCounter++;
	Plist = new PNode*[NodeCounter];
	int n = 0;
	traverTree_ltl(root, Plist, n);
	strcpy(input[ADD_CCCD_INPUT].content,"");
	strcpy(input[ADD_HO_INPUT].content,"");
	strcpy(input[ADD_TEN_INPUT].content,"");

	checkbox[MALE].isClicked = false;
	checkbox[FEMALE].isClicked = false;
	
	saveData(root);
}



void which_hovered_button(int x, int y, int s, int f) {
	for(int i = s; i < f; i++) {
		if(btn[i].isInside(x, y)){
			if(btn[i].hover_status == false) {
				button_hightlight(btn[i]);
				btn[i].hover_status = true;
			}	
		}else {
			if(btn[i].hover_status == true) {
				button_unhightlight(btn[i]);
				btn[i].hover_status = false;
			}
			
		}
	}
}


void which_hovered_input(int x, int y, int s, int f) {
	for(int i = s; i < f; i++) {

		if(input[i].isInside(x, y)){
			if(input[i].hover_status == false && strlen(input[i].content) == 0) {
				input_hightlight(input[i]);
				input[i].hover_status = true;
			}	
		}else {
			if(strlen(input[i].content) == 0 && input[i].hover_status == true) {
				input_unhightlight(input[i]);
				input[i].hover_status = false;
			}
		}
	}
}

int which_button(int x, int y) {
	for(int i = 0; i < MAX_TAB; i++){
		if(tab_button[i].inside(x, y)){
			if(i == HANHKHACH)
				return MAINMENU;
			return i;
		}
}
		
	for(int i = 0; i < max_btn; i++) {
		if(btn[i].isInside(x,y)) {
			return i+5;
		}
	}
	
	return HANHKHACH;
}

int which_input(int x, int y) {
	for(int i = 0; i < max_ib; i++){
		if(input[i].isInside(x, y)) {
			return i;
		}
	}
	
	return 999;
}

void get_input(InputBox ib, int s, int f, PNode **&Plist, PNode *root, int &NodeCounter, int &pageMax, int &page, PTR_FLIGHT &flight_list,DSMayBay &plane_list) {
	
	int char_width = textwidth("W");
	int char_height = textheight("W");

	int char_counter = strlen(ib.content);

	focus_input(ib,s,f);

	int x = ib.x, y = ib.y, height = ib.height;
	char c;
	char str[20];

	strcpy(str, ib.content);
	
	while(kbhit()){
		getch();
	}

	while(1) {
		if(kbhit()) {  	
			c = getch();
	
			if(c == '\b' && char_counter > 0) {
				str[char_counter - 1] = '\0';
				moveto(x + 5, y+height/2-char_height/2);
				setfillstyle(SOLID_FILL,15);
				bar(ib.x+2, ib.y+2, ib.x + ib.width-4, ib.y + ib.height-4);
				strcpy(input[ib.id].content,str);
				outtext(str);
				char_counter--;
				outtextxy(x + char_width*char_counter+ 8, y+height/2 - 5, "-");

			}else if((isalnum(c) && char_counter < 12 && strcmp(ib.type, "CCCD") == 0 && c >= '0'&& c <= '9') || 
					 (isalnum(c) && char_counter < 20 && strcmp(ib.type, "NAME") == 0 && c >= 'a' && c <= 'z') ||
					 (isalnum(c) && char_counter < 20 && strcmp(ib.type, "SURNAME") == 0 && c >= 'a' && c <= 'z') || 
					 (isalnum(c) && char_counter < 15 && ib.id == 1)){
				if (c >= 'a' && c <= 'z') {
            		 c = c - 'a' + 'A';
       			}
				
				str[char_counter] = c;
				str[char_counter + 1] = '\0';
				char_counter++;
				
				moveto(x + 5, y+height/2-char_height/2);
				strcpy(input[ib.id].content,str);
				outtext(str);
				if((char_counter < 12 && strcmp(ib.type, "CCCD") == 0) || 
				(char_counter < 20 && strcmp(ib.type, "SURNAME") == 0) || 
				(char_counter < 20 && strcmp(ib.type, "NAME") == 0)    ||
				 char_counter < 15 && strcmp(ib.type, "FLIGHT_ID") == 0) {
					outtextxy(x + char_width*(char_counter-1) + char_width + 8, y+height/2 - 5, "-");
				}
			}else if (c == ' ' && char_counter <= 20 && char_counter > 0 && str[char_counter - 1] != ' ') {
				if(strcmp(ib.type, "SURNAME") == 0) {

					str[char_counter] = ' ';
					str[char_counter + 1] = '\0';
					char_counter++;
					setfillstyle(SOLID_FILL,15);
					bar(ib.x+2, ib.y+2, ib.x + ib.width-4, ib.y + ib.height-4);
					moveto(x + 5, y+height/2-char_height/2);
					strcpy(input[ib.id].content,str);
					outtext(str);
					if((char_counter < 11 && strcmp(ib.type, "CCCD"))    || 
					   (char_counter < 19 && strcmp(ib.type, "SURNAME")) || 
					   (char_counter < 19 && strcmp(ib.type, "NAME"))    ||
					   (char_counter < 15 && strcmp(ib.type, "FLIGHT_ID")) ) {
						outtextxy(x + char_width*(char_counter-1) + char_width +8, y+height/2 - 5, "-");
					}	
				}
			}else if(c == '\r' && (ib.id == 0 || ib.id == 1)) {
				ultimateFilter(Plist, root, flight_list, pageMax, page, NodeCounter, plane_list);
			}
		}else if(ismouseclick(WM_LBUTTONDOWN)) {
			int xc, yc;
			getmouseclick(WM_LBUTTONDOWN, xc, yc);
			if(!ib.isInside(xc,yc)) {
				setfillstyle(SOLID_FILL, 15);
				bar(x + char_width*strlen(input[ib.id].content) +10, y+height/2-5,x + char_width*strlen(input[ib.id].content)+36,y+height/2+5);
				return;
			}
		}
	}	
	
	clearmouseclick(WM_LBUTTONDOWN);
	clearmouseclick(WM_RBUTTONDOWN);
}

char* removeTrailingSpace(const char* str) {
    int length = strlen(str);
    
    char* result = new char[length + 1];
    
    strcpy(result, str);
    

    int i = length - 1;
    while (i >= 0 && result[i] == ' ') {
        result[i] = '\0'; 
        i--;
    }
    
    return result;
}

int which_checkBox(int x, int y) {
	for(int i = 0; i < max_cb; i++) {
		if(checkbox[i].isInside(x,y)) { 
			if(checkbox[i].isClicked == false) {
				choose_box(checkbox[i]);
				checkbox[i].isClicked = true;
				for(int j = 0; j < max_cb; j++) {
					if( i != j && checkbox[j].isClicked == true) {
						unchoose_box(checkbox[j]);
						checkbox[j].isClicked = false;
					}
				}
		}
	}
}
}

void which_hovered_row(int x, int y, int &page, int &pageMax, int &NodeCounter) {
	bool condition; 
	
	static int hovered_row = NULL;
	
	if(page != pageMax) { 
		condition = (x >= X1_TABLE && x <= X2_TABLE && y >= Y1_TABLE+50 && y <= Y2_TABLE);
	}else {
		if(NodeCounter % 10 == 0 && NodeCounter != 0) {
			condition = (x >= X1_TABLE && x <= X2_TABLE && y >= Y1_TABLE+50 && y <= (Y1_TABLE + 45 + LINE_HEIGHT*10));
		}else if(NodeCounter == 0){
			condition = false;
		}
		else {
			condition = (x >= X1_TABLE && x <= X2_TABLE && y >= Y1_TABLE+50 && y <= (Y1_TABLE + 45 + LINE_HEIGHT*(NodeCounter%10)));
		}	
		
	}
	
	int index;
	
	if(condition) {
		index = round((y-180-50)/42);
		if(hovered_row != index && hovered_row >= 0 && hovered_row <= 9 && index <= 9 ) {
			row_hightlight(index, displayed_passengers[index]);
			draw_row(Y_FIRSTROW+LINE_HEIGHT*hovered_row, displayed_passengers[hovered_row]);
			hovered_row = index;
		}
	}else {
		if(hovered_row != NULL){
			draw_row(Y_FIRSTROW+LINE_HEIGHT*hovered_row, displayed_passengers[hovered_row]);
			hovered_row = NULL;
		}
	}	
}


int which_rclicked_row(int x, int y, int &page, int &pageMax, int& NodeCounter) {
	bool condition; 
	
	if(page != pageMax) { 
		condition = (x >= X1_TABLE && x <= X2_TABLE && y >= Y1_TABLE+50 && y <= Y2_TABLE);
	}else {
		if(NodeCounter % 10 == 0) {
			condition = (x >= X1_TABLE && x <= X2_TABLE && y >= Y1_TABLE+50 && y <= (Y1_TABLE + 47 + LINE_HEIGHT*10));
		}else {
			condition = (x >= X1_TABLE && x <= X2_TABLE && y >= Y1_TABLE+50 && y <= (Y1_TABLE + 47 + LINE_HEIGHT*(NodeCounter%10)));
		}	
		
	}
	
	int index;
	
	if(condition) {
		index = round((y-180-50)/42);		
	}
}

void dropDownOption(int x, int y, int &NodeCounter, int &page, int& pageMax, PNode *&root, PNode **&Plist,PTR_FLIGHT &flight_list, DSMayBay &plane_list, char *ticket_list[]) {
	drawDropDown(x, y);
	int cx, cy;
	int op;
	int index;
	index = round((y-180-50)/42);
	while(1) {
		if(ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, cx, cy);
			if(cx > x && cx < x + 110 && cy > y && cy < y + 150) {
				op = (cy - y) / 30; 
				switch(op) {
					case 0:
						viewLogic(index, flight_list, plane_list, ticket_list, NodeCounter, page, pageMax,Plist );
						return;
						break;
					case 1:
						edit_passenger_logic(index, page, root, Plist, NodeCounter, pageMax, flight_list, plane_list);			
						return;		
						break;														
				}
			}else {
				print_workspace();		
				draw_customer_workspace(NodeCounter, pageMax, page, Plist);
				return;
			}
		}else if(ismouseclick(WM_MOUSEMOVE)) {
			getmouseclick(WM_MOUSEMOVE, cx, cy);
			
			if(cx > x && cx < x + 110 && cy > y && cy < y + 60) {
				op = (cy - y) / 30;
				setfillstyle(SOLID_FILL, 7);
				bar(x, y + op*30, x + 110, y + op*30 + 30);
				setcolor(0);
				setbkcolor(7);
				rectangle(x, y + op*30, x + 110, y + op*30 + 30);
				outtextxy(x + 5, y+5 + 30*(op), option[op] );
				for(int i = 0; i < 2; i++) {
					if(i != op) {
						setfillstyle(SOLID_FILL, 15);
						bar(x, y + i*30, x + 110, y + i*30 + 30);
						setcolor(0);
						setbkcolor(15);
						rectangle(x, y + i*30, x + 110, y + i*30 + 30);
						outtextxy(x + 5, y+5 + 30*(i), option[i] );
					}
					delay(10);
				}
			}			
		}else if(ismouseclick(WM_RBUTTONDOWN)) {
			print_workspace();		
			draw_customer_workspace(NodeCounter, pageMax, page, Plist);	
			return;
		}
	delay(100);
	}

}

void drawDropDown(int x, int y) {
	setfillstyle(SOLID_FILL, 15);
	bar(x, y, x + 110, y +60);
	setcolor(0);
	rectangle(x, y, x + 110, y + 60);
	setbkcolor(15);
	for(int i = 1; i < 3; i++) {
		line(x, y +30*i, x+ 110, y + 30*i);
		outtextxy(x + 5, y+5 + 30*(i-1), option[i-1] );
	}	
}





// edit feature //


void draw_gui() {
	const int xmax = getmaxx();
	const int ymax = getmaxy();	
	
	int height = 400;
	int width = 500;
	int x = xmax/2 - width/2;
	int y = ymax/2 - height/2;
	
	rounded_bar(WORKSPACE_X,WORKSPACE_Y, WORKSPACE_WIDTH, WORKSPACE_HEIGHT, 11);
	
	setfillstyle(SOLID_FILL, 15);
	bar(x , y, x+width, y+height);
	
	addCccdInput.drawInputBox();
	addHoInput.drawInputBox();
	addTenInput.drawInputBox();
	
	fillText(ADD_HO_INPUT, 15);
	fillText(ADD_TEN_INPUT, 15);
	fillText(ADD_CCCD_INPUT, 7);
	
	male.draw_checkBox();
	female.draw_checkBox();
	submitAddButton.draw_button();
	backButton.draw_button();
	setcolor(0);
	rectangle(x , y, x+width, y+height);
	
//	if(strcmp(displayed_passengers[index].getSex(), "Nam") == 0) {
//		checkbox[MALE].isClicked = true;
//		checkbox[FEMALE].isClicked = false;
//		choose_box(male);
//	}else {
//		checkbox[FEMALE].isClicked = true;
//		checkbox[MALE].isClicked = false;
//		choose_box(female);
//	}
}
void draw_edit_gui(int index) {
	const int xmax = getmaxx();
	const int ymax = getmaxy();	
	
	int height = 400;
	int width = 500;
	int x = xmax/2 - width/2;
	int y = ymax/2 - height/2;
	
	rounded_bar(WORKSPACE_X,WORKSPACE_Y, WORKSPACE_WIDTH, WORKSPACE_HEIGHT, 11);
	
	setfillstyle(SOLID_FILL, 15);
	bar(x , y, x+width, y+height);
	
	addCccdInput.drawInputBox();
	addHoInput.drawInputBox();
	addTenInput.drawInputBox();
	
	fillText(ADD_HO_INPUT, 15);
	fillText(ADD_TEN_INPUT, 15);
	fillText(ADD_CCCD_INPUT, 7);
	
	male.draw_checkBox();
	female.draw_checkBox();
	submitAddButton.draw_button();
	backButton.draw_button();
	setcolor(0);
	rectangle(x , y, x+width, y+height);
	
	if(strcmp(displayed_passengers[index].getSex(), "Nam") == 0) {
		checkbox[MALE].isClicked = true;
		checkbox[FEMALE].isClicked = false;
		choose_box(male);
	}else {
		checkbox[FEMALE].isClicked = true;
		checkbox[MALE].isClicked = false;
		choose_box(female);
	}
}

void draw_edit_gui_v2() {
	const int xmax = getmaxx();
	const int ymax = getmaxy();	
	
	int height = 400;
	int width = 500;
	int x = xmax/2 - width/2;
	int y = ymax/2 - height/2;
	
	rounded_bar(WORKSPACE_X,WORKSPACE_Y, WORKSPACE_WIDTH, WORKSPACE_HEIGHT, 11);
	
	setfillstyle(SOLID_FILL, 15);
	bar(x , y, x+width, y+height);
	
	addCccdInput.drawInputBox();
	addHoInput.drawInputBox();
	addTenInput.drawInputBox();
	
	fillText(ADD_HO_INPUT, 15);
	fillText(ADD_TEN_INPUT, 15);
	fillText(ADD_CCCD_INPUT, 15);
	
	if(checkbox[MALE].isClicked == true){
		male.draw_checkBox();
		choose_box(male);
		female.draw_checkBox();
	}
	
	if(checkbox[FEMALE].isClicked == true){
		female.draw_checkBox();
		choose_box(female);
		male.draw_checkBox();
	}
	
	submitAddButton.draw_button();
	backButton.draw_button();
	setcolor(0);
	rectangle(x , y, x+width, y+height);
	
}



void edit_passenger_logic(int index, int& page, PNode*&root, PNode**&Plist, int &NodeCounter, int &pageMax,PTR_FLIGHT &flight_list, DSMayBay &plane_list) {
	strcpy(input[ADD_CCCD_INPUT].content, displayed_passengers[index].getCccd());
	strcpy(input[ADD_HO_INPUT].content, displayed_passengers[index].getHo());
	strcpy(input[ADD_TEN_INPUT].content, displayed_passengers[index].getTen());
	
	draw_edit_gui(index);
	int mx, my;
	int btnVar, inputVar, checkVar, checkboxVar;
	
	char *ten, ho, cccd, sex;
	
		while(1){
			if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, mx, my);
			btnVar = which_button(mx, my);
			inputVar =  which_input(mx, my);
			checkboxVar = which_checkBox(mx, my);
			switch(btnVar) {
				case BACKBUTTON:
					strcpy(input[ADD_CCCD_INPUT].content,"");
					strcpy(input[ADD_HO_INPUT].content,"");
					strcpy(input[ADD_TEN_INPUT].content,"");
					
					checkbox[MALE].isClicked = false;
					checkbox[FEMALE].isClicked = false;
					
					print_workspace();		
					draw_customer_workspace(NodeCounter, pageMax, page, Plist);	
					return;
				case SUBMITBUTTON:
					char * message = check_info_edit();
					if (strcmp(message, "ok") != 0) {
						notification_v3(message);
						
					}else {
						bool re = isCancel("Do you want to update information");
						if (re == true) {
						
							render_table_data(NodeCounter, page, pageMax, Plist);
							draw_edit_gui(index);
						}else {
							edit_passenger(index, page, root, Plist);
							notification_v2("Updated!!!");
							render_table_data(NodeCounter, page, pageMax, Plist);
							draw_edit_gui(index);
						}
					}
					break;
			}	     
			
			switch(inputVar) {
				case ADD_HO_INPUT:
					get_input(input[ADD_HO_INPUT],2,5,Plist, root, NodeCounter, pageMax, page, flight_list, plane_list);
					break;
				case ADD_TEN_INPUT:
					get_input(input[ADD_TEN_INPUT],2,5,Plist, root, NodeCounter, pageMax, page, flight_list, plane_list);
					break;
				case 999:
					break;
			}
			
			
		}
		else if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE, mx, my);
			which_hovered_button(mx, my, 3, 5);
			which_hovered_input(mx, my, 2, 5);											
		};
		delay(50);
	}
}

void edit_passenger(int index, int &page, PNode *&root, PNode**&Plist) {
	int lindex = (page -1) *10 + index;
	char *new_cccd = input[ADD_CCCD_INPUT].content;
	char *new_ho = removeTrailingSpace(input[ADD_HO_INPUT].content);
	strcpy(input[ADD_HO_INPUT].content, new_ho);
	char *new_ten = input[ADD_TEN_INPUT].content;
	char *new_sex;
	
	if(checkbox[MALE].isClicked == true) {
        new_sex = "Nam";
    } else {
        new_sex = "Nu";
    }    
    
    
    Plist[lindex]->pas.setCccd(new_cccd);
    Plist[lindex]->pas.setHo(new_ho);
    Plist[lindex]->pas.setTen(new_ten);
    Plist[lindex]->pas.setSex(new_sex);
    
    checkbox[MALE].isClicked = false;
    checkbox[FEMALE].isClicked = false;
    
    saveData(root);
    
}

void render_table_data(int &NodeCounter, int &page, int &pageMax, PNode **&Plist) {
	int end =  page*10-1;
	int start = end - 9;
	int maxRow = 10;
	
	if(page == pageMax) {
		if(NodeCounter % 10 == 0) {
			maxRow = 10;
			end = (page-1)*10 + maxRow - 1;
		}else {
			maxRow = NodeCounter % 10;
			end = (page-1)*10 + maxRow - 1;
		}	
	}
	
	if(NodeCounter == 0) {
		maxRow =  0;
		end = 0;
		start = 0;
	}
	
	string navi = to_string(page) + "/" + to_string(pageMax);
	setcolor(0);
	setfillstyle(SOLID_FILL, 11);
	bar(630, Y2_TABLE + 10, 750, Y2_TABLE + 50);
	setbkcolor(11);
	
	outtextxy(650, Y2_TABLE + 30, navi);

	if(NodeCounter != 0) {
		for(int i = start; i <= end; i++) {
			displayed_passengers[i-(page-1)*10] = Plist[i]->pas;			
		}
	}
	
	setfillstyle(SOLID_FILL, 11);
	
	bar(X1_TABLE-5, Y1_TABLE+50, X2_TABLE+5, Y2_TABLE+5);
	
	if(NodeCounter != 0) {
		for(int i = 0; i < maxRow; i++) {	
			draw_row(Y_FIRSTROW + LINE_HEIGHT*i, displayed_passengers[i]);
		}
	}
	
//	for(int i = 0; i < NodeCounter; i++) {
//		print(Plist[i]->pas);
//	}
}

bool search_ticket(FlightNode *node, char *cccd, DSMayBay &plane_list) {
	while(node != NULL) {
		
		if(node->flight.status == HETVE || node->flight.status == CONVE) {
			if(strcmp(node->flight.flightID, "A") != 0) {
				int *ar = getRCnum(node->flight.planeID, plane_list);		
				for(int i = 0; i < ar[0]; i++) {
					for(int j  = 0; j < ar[1]; j++) {
						if(strcmp(cccd, node->flight.ticket[i][j]) == 0) {
							return true;
						}
					}
				}
				delete []ar;
			}
			
		} 
		
		node = node->next;
	}
	return false;
}

//====== pop up to cancle or continute

void drawCancle(){
	setfillstyle(SOLID_FILL, 15);
	bar(X_FORM, Y_FORM, X_FORM + 500, Y_FORM + 500);
	
}

bool isCancel(char *text) {
	settextstyle(0, HORIZ_DIR, 2);
	int textw = textwidth(text);
	
	int width = textw + 50;
	int height = 300;
	
	const int xmax = getmaxx();
	const int ymax = getmaxy();	
	
	int x = xmax/2 - width/2;
	int y = ymax/2 - height/2;
	
	setfillstyle(SOLID_FILL, 15);
	bar(x , y, x+width, y+height);
	
	setbkcolor(15);
	setcolor(0);
	outtextxy(x + width/2 - textw/2, y+120, text);
	
	cancelButton.draw_button();
	yesButton.draw_button();
	
	setcolor(0);
	rectangle(x , y, x+width, y+height);
	int cx, cy;
	
	while(1) {
		if(ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, cx, cy);
			if(cancelButton.isInside(cx, cy)) {
				return true;
			}else if(yesButton.isInside(cx, cy)) {
				return false;
			}
		}
		
		delay(50);
	}
}


int notification(char *alert) {
	const int xmax = getmaxx();
	const int ymax = getmaxy();	
	
	int height = 300;
	int width = 500;
	int x = xmax/2 - width/2;
	int y = ymax/2 - height/2;
	
	setfillstyle(SOLID_FILL, 15);
	bar(x , y, x+width, y+height);
	
	outtextxy(x+60, y+50, alert);
	
	xButton.draw_button();
	
	setcolor(0);
	rectangle(x , y, x+width, y+height);
	
	int cx, cy;
	
	while(1) {
		if(ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, cx, cy);
			if(xButton.isInside(cx, cy)) {
				return HANHKHACH;
			}
		}		
		delay(50);
	}
}



// View Feature 

void drawViewFlightGUI(int index, PTR_FLIGHT &flight_list) {
	rounded_bar(WORKSPACE_X,WORKSPACE_Y, WORKSPACE_WIDTH, WORKSPACE_HEIGHT, 11);
	
	char *cccd = displayed_passengers[index].getCccd();
	char *name = displayed_passengers[index].getTen();
	char *ho = displayed_passengers[index].getHo();
	
	char* ke[3] = {cccd, name, ho};
	char* ti[3] = {"CCCD: ", "TEN: ", "HO: "};
	char* tt[4] = {"MA CHUYEN BAY", "NOI DEN", "THOI GIAN", "SO VE"};
	
	
	setbkcolor(11);
	for(int i = 1; i <= 3; i++) {
		outtextxy(WINDOW_WIDTH/2 - 200, 30 + 40*i, ti[i - 1]);
	}
		
	for(int i = 1; i <= 3; i++) {
		outtextxy(WINDOW_WIDTH/2 - 60, 30 + 40*i, ke[i - 1]);
	}
	
	viewBackButton.draw_button();
	
	setcolor(0);
	rectangle(X_TABLE, Y_TABLE, X_TABLE + 1000, Y_TABLE + 50);
	
	setbkcolor(11);
	for(int i = 0; i <= 3; i++) {
		line(X_TABLE+250*(i+1), Y_TABLE, X_TABLE+250*(i+1), Y_TABLE +50);
		outtextxy(X_TABLE+250*(i) + 15 , Y_TABLE + 17, tt[i]);
	}
	
	previousButton.draw_button();
	nextButton.draw_button();
}

char* concatenateStrings(const char* prefix, const char* suffix) {
    size_t prefix_len = strlen(prefix);
    size_t suffix_len = strlen(suffix);
    size_t new_len = prefix_len + suffix_len + 1; 

    char* new_str = new char[new_len];

    strcpy(new_str, prefix);
    strcat(new_str, suffix);

    return new_str;
}
void viewLogic(int index, PTR_FLIGHT &flight_list, DSMayBay &plane_list, char *ticket_list[], int &NodeCounter, int &page, int &pageMax, PNode **&Plist) {	
	Flight as[100];
	bool ok = true;
	int i;
	int maxRow;
	int vpage = 1;
	int counter = load_ticket(flight_list, displayed_passengers[index].getCccd(), as, plane_list, ticket_list);
	int vpageMax;

	if(counter % 10 == 0) {
		if(counter == 0) {
			vpageMax = 1;
		}else {
			vpageMax = counter/ 10;
		}
	}else {
		vpageMax = counter/10 + 1;
	}
		 
	drawViewFlightGUI(index, flight_list);
	
	render_s_table(as, counter, vpage, vpageMax, ticket_list, maxRow);
	
	int x, y;
	while(1) {
		if(ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if(viewBackButton.isInside(x, y)) {
				print_workspace();		
				draw_customer_workspace(NodeCounter, pageMax, page, Plist);
				return;
			}else if(x > X_TABLE +1010  && x < X_TABLE + 1080 && y > Y1_TABLE + 50 && y < Y1_TABLE+50 + 42*maxRow){
				i = (y - 50 - Y1_TABLE) / 42;
				int id = vpage*10 - 10 + i;
				char *alert = concatenateStrings("Do you want to cancel ", as[id].flightID);
				if(as[id].status != HOANTAT) {
					if(isCancel(alert)) {
						drawViewFlightGUI(index, flight_list);
						render_s_table(as, counter, vpage, vpageMax, ticket_list, maxRow);
					}else {
						cancelSticket(as[id].flightID, plane_list,  displayed_passengers[index].getCccd(), flight_list);
						counter = load_ticket(flight_list, displayed_passengers[index].getCccd(), as, plane_list, ticket_list);
						vpage = 1;
						if(counter % 10 == 0) {
							if(counter == 0) {
								vpageMax=1;
							}else {
								vpageMax = counter/ 10;
							}
						}else {
							vpageMax = counter/10 + 1;
						}
							
						drawViewFlightGUI(index, flight_list);
						render_s_table(as, counter, vpage, vpageMax, ticket_list, maxRow);
					}					
				} 
						
				delete [] alert;
			}else if(previousButton.isInside(x, y)) {
				if (vpage > 1) {
					vpage--;
					render_s_table(as, counter, vpage, vpageMax, ticket_list, maxRow);
				}
			}else if(nextButton.isInside(x,y)) {
				if(vpage != vpageMax) {
					vpage++;
					render_s_table(as, counter, vpage, vpageMax, ticket_list, maxRow);
				}
			}
			
		}else if(ismouseclick(WM_MOUSEMOVE)){
			if(counter != 0){
				getmouseclick(WM_MOUSEMOVE, x, y);
				if(x > X_TABLE +1010  && x < X_TABLE + 1080 && y > Y1_TABLE + 50 && y < Y1_TABLE+50 + 42*maxRow) {
					ok = true;
					i = (y - 50 - Y1_TABLE) / 42;
					setfillstyle(SOLID_FILL, 10);
					bar(X_TABLE + 1010, Y_TABLE+42*i + 52, X_TABLE + 1010 + 70, Y_TABLE+42*i+52+38);
					setcolor(0);
					rectangle(X_TABLE + 1010, Y_TABLE+42*i + 52, X_TABLE + 1010 + 70, Y_TABLE+42*i+52+38);
					setbkcolor(10);
					setcolor(15);
					settextstyle(10, HORIZ_DIR, 1);
					outtextxy(X_TABLE + 1010 + 35 - textwidth("cancel")/2, Y_TABLE+42*i + 52 + 20 - textheight("cancel")/2, "cancel");
					
					for(int j = 0; j < maxRow; j++) {
						if(i != j) {
							fake_btn(X_TABLE + 1010, Y_TABLE+42*j + 52, 70, 38,2, "cancel");
						}
					}
				}else {
					if(ok) {
						for(int j = 0; j < maxRow; j++) {	
							fake_btn(X_TABLE + 1010, Y_TABLE+42*j + 52, 70, 38,2, "cancel");
						}
						ok = false;
					}
				}
			}		
			which_hovered_button(x, y,1,3);
			which_hovered_button(x, y,8,9);
		}
		
		delay(50);
	}
	
	for(int i = 0;i < counter; i++) {
		delete []ticket_list[i];
	}
}

void cancelSticket(char* mcb, DSMayBay &plane_list, char *cccd, PTR_FLIGHT &flight_list) {
    PTR_FLIGHT node = flight_list;
    while (node != NULL) {
        if (strcmp(node->flight.flightID, mcb) == 0) {
        	node->flight.status = CONVE;
            int *n = getRCnum(node->flight.planeID, plane_list);
            for (int i = 0; i < n[0]; i++) {
                for (int j = 0; j < n[1]; j++) {
                    if (strcmp(node->flight.ticket[i][j], cccd) == 0) {
                        strcpy(node->flight.ticket[i][j], "none");
                    }
                }
            }
            break;
        }
        node = node->next;
    }
    
    save_flight_to_file("Data\\Flights.dat", flight_list, plane_list);
}

int load_ticket(FlightNode *node, char *cccd, Flight as[], DSMayBay &plane_list, char* ticket_list[]) {
	int counter = 0;
	while(node != NULL) {
		if(node->flight.status == CONVE || node->flight.status == HETVE) {
			int *ar = getRCnum(node->flight.planeID, plane_list);
			for(int i = 0; i < ar[0]; i++) {
				for(int j  = 0; j < ar[1]; j++) {
					if(strcmp(cccd, node->flight.ticket[i][j]) == 0) {
						as[counter] = node->flight;
						string str = get_ticket_name(i, j);
						char *charPtr = new char[str.length() + 1]; 

   	 					strcpy(charPtr, str.c_str());
   	 					
   	 					ticket_list[counter] = charPtr;
   	 					
						counter ++;
					}
				}
			}
			delete[] ar;	
		} 		    
		node = node->next;
	}
	return counter;
} 

void render_s_table(Flight as[], int counter,int page, int pageMax, char *ticket_list[], int& maxRow) {
	int start = (page * 10) - 10 ;
	int end = start + 9;
	maxRow = 10;
	
	setfillstyle(SOLID_FILL, 11);
	bar(X_TABLE, Y_TABLE + 51, X_TABLE+1100, Y_TABLE+471);
	
	if(page == pageMax) {
		if(counter % 10 == 0) {
			if(counter == 0) {
				end = 0;
				maxRow = 10;
				start = 10;
			}		
		}else{
			end = (counter % 10) + start - 1;
			maxRow = counter % 10;
		}
	}
		
	char *dt[4];
	settextstyle(10, HORIZ_DIR, 1);
	if(counter != 0) {
		for(int i = start; i <= end; i++) {
			int id = i - (page - 1)*10;
			if(as[id].status == HOANTAT) {
				fake_btn(X_TABLE + 1010, Y_TABLE+42*id + 52, 70, 38,7, "cancel");
			}
			fake_btn(X_TABLE + 1010, Y_TABLE+42*id + 52, 70, 38,2, "cancel");
			setcolor(0);
			setfillstyle(SOLID_FILL, 15);
			rectangle(X_TABLE, Y_TABLE, X_TABLE + 1000, Y_TABLE + 50 + 42*(id+1));
			setbkcolor(11);
			
			dt[0] = as[i].flightID;
			dt[1] = as[i].arrive;
			string str = as[i].date.to_string();
			char *temp = new char[str.length() + 1];
			strcpy(temp, str.c_str());
			dt[2] = temp;
			delete[] temp;		  
			dt[3] = ticket_list[i];
			
			for(int j = 0; j <= 3; j++) {
				line(X_TABLE+250*(j), Y_TABLE +52 + 42*id, X_TABLE+250*(j), Y_TABLE + 92 + 42*(id));
				outtextxy(X_TABLE+250*(j) + 15, Y_TABLE +52 + 42*id + 10, dt[j]);
			}
		}
	}
		
	string navi = to_string(page) + "/" + to_string(pageMax);
	setcolor(0);
	setbkcolor(11);
	settextstyle(0, HORIZ_DIR, 2);
	outtextxy(670, Y2_TABLE + 30, navi);
}

void fake_btn(int x, int y, int width, int height, int color, char* placeholder) {
	settextstyle(10, HORIZ_DIR, 1);
	setfillstyle(SOLID_FILL, color);
	setcolor(0);
	
	bar(x,y,x+width, y+height);
	rectangle(x,y,x+width, y+height);
	
	setbkcolor(color);
	outtextxy(x+(width/2) - textwidth(placeholder)/2, y +(height/2) - textheight(placeholder)/2, placeholder);	
}

int *getRCnum(char *mmb, DSMayBay &plane_list) {
	int* arr = new int[2];	
	for(int i = 0; i < plane_list.SoMayBay; i++) {
		if(strcmp(plane_list.n[i]->SoHieuMB, mmb) ==  0) {
			arr[0] = plane_list.n[i]->SoDay;
			arr[1] = plane_list.n[i]->SoDong;
			
			return arr;
		}
	}
	
}

void notification_v2(char *alert) {
	setfillstyle(SOLID_FILL, 15);
	setcolor(0);
	setbkcolor(15);
	
	bar(20, 70, 25+255, 70 + 150);
	rectangle(25, 70, 25+250, 70 + 150);
	
	
	outtextxy(25 + 125 - textwidth(alert)/2, 70 +  75 - textheight(alert)/2, alert);
	delay(1500);
	setfillstyle(SOLID_FILL, 11);
	bar(20, 70, 25+278, 70 + 160);
}

void notification_v3(char *alert) {
	setfillstyle(SOLID_FILL, 15);
	setcolor(0);
	setbkcolor(15);
	
	
	
	int width = textwidth(alert)+50;
	int height = 60;
	
	int x = 700 - width/2;
	int y = 600;
	
	bar(x, y, x + width, y + height);
	rectangle(x, y, x + width, y + height);
		
	outtextxy(x + width/2 - textwidth(alert)/2, y +30 - textheight(alert)/2, alert);
	delay(1500);
	setfillstyle(SOLID_FILL, 11);
	bar(x-2, y-2, x + width+2, y + height + 2);
}

//void render_table_data(int &NodeCounter, int &page, int &pageMax, PNode **&Plist)
void filter_by_cccd(char *cccd, PNode **&Plist, PNode *root, int &NodeCounter, int &pageMax, int &page) {
		PNode *node = findByCccd(root, cccd);
		if(node == NULL) {
			delete []Plist;
			page = 1;
			pageMax = 1;
			NodeCounter = 0;
			render_table_data(NodeCounter,page,pageMax,Plist);
			notification_v2("User Not Found!!");
		}else {
			delete []Plist;
			Plist = new PNode*[1];
			Plist[0] = node;
		
			page = 1;
			pageMax = 1;
			NodeCounter = 1;
		}
}

void cccd_array_filter(char *cccd, PNode **&Plist, int &page, int &pageMax, int &NodeCounter) {
	for(int i = 0; i < NodeCounter; i++){
		if(strcmp(cccd,Plist[i]->pas.getCccd()) == 0){
			PNode *node = Plist[i];
			delete []Plist;
			Plist = new PNode*[1];
			Plist[0] = node;

			page = 1;
			pageMax = 1;
			NodeCounter = 1;
			
			return;
		}
	}
	
	delete []Plist;
	page = 1;
	pageMax = 1;
	NodeCounter = 0;
	render_table_data(NodeCounter,page,pageMax,Plist);
	notification_v2("User Not Found!!");
}

void filter_by_flightID(FlightNode *node, char *flightID, PNode **&Plist, PNode *root, int &pageMax, int &page, int &NodeCounter, DSMayBay &plane_list) {			
		PTR_FLIGHT nod = SerchFlight(node, flightID);
		
		if(nod == NULL || nod->flight.status == HUYCHUYEN || nod->flight.status == HOANTAT) {
			delete []Plist;
			page = 1;
			pageMax = 1;
			NodeCounter = 0;
			render_table_data(NodeCounter,page,pageMax,Plist);
			notification_v2("Flight Not Found!!");
		}else {
			
			int *ar = getRCnum(nod->flight.planeID, plane_list);
			
			PNode *temp[9999];
			
			int counter  = 0;
			
			for(int i = 0; i < ar[0]; i++) {
				for(int j = 0; j < ar[1]; j++) {
					if(strcmp(nod->flight.ticket[i][j], "none") != 0) {
						temp[counter] = findByCccd(root, nod->flight.ticket[i][j]);
						counter++;
					}
				}
			}
			
			delete [] Plist;
			
			Plist = new PNode *[counter];
			
			for(int i = 0; i < counter; i++) {
				Plist[i] = temp[i];
			}
			
			page = 1;
			NodeCounter = counter;
			if(counter % 10 == 0) {
				if(counter == 0) {
					pageMax = 1;
				}else {
					pageMax = counter / 10;
				}
			}else {
				pageMax = counter/10 + 1;
			}
			
			delete []ar;
		} 		
}

void ultimateFilter(PNode **&Plist, PNode *&root, FlightNode *node,int &pageMax, int &page, int &NodeCounter, DSMayBay &plane_list) {
	if(strcmp(input[0].content, "") == 0 && strcmp(input[1].content, "") == 0) {
		NodeCounter = countNodes(root);
		if(NodeCounter % 10 == 0) {
			if(NodeCounter == 0) {
				pageMax = 1;
			}else {
				pageMax = NodeCounter / 10;
			}
		}else {
			pageMax = NodeCounter / 10 + 1;
		}
		
		delete []Plist;
		Plist = new PNode*[NodeCounter];
		int n = 0;
		traverTree_ltl(root, Plist, n);
		int page = 1;
		render_table_data(NodeCounter,page,pageMax, Plist);
	}else if(strcmp(input[0].content, "") != 0 && strcmp(input[1].content, "") == 0) {
		filter_by_cccd(input[0].content, Plist, root, NodeCounter, pageMax, page);
	}else if(strcmp(input[0].content, "") == 0 && strcmp(input[1].content, "") != 0) {
		filter_by_flightID(node, input[1].content, Plist, root, pageMax, page, NodeCounter, plane_list);
	}else {
		filter_by_flightID(node, input[1].content, Plist, root, pageMax, page, NodeCounter, plane_list);
		cccd_array_filter(input[0].content, Plist, page, pageMax, NodeCounter);
	}
	
	if(NodeCounter != 0){
		render_table_data(NodeCounter,page,pageMax,Plist);
	}
}


	


// THIS IS END OF LOGIC SECTION
