#pragma once
#include"DefaultGraphic.h"
#include"Flight.h"
#include"passenger_tree.h"
#include"SortFlight.h"
#include<math.h>

#define MAX_FLIGHT_FIELD 8
#define MAX_FLIGHT_STATUS 4
#define MAX_SEAT_COLUMN 26  
#define MAX_SEAT_ROW 10
enum FLIGHT_FIELD {FLIGHTID, PLANEID, HOUR,  MINUTE , DAY, MONTH, YEAR, ARRIVE};
enum POPUPMENU_OPTION{MANAGE_TICKET, ADJUST_FLIGHT, CANCEL_FLIGHT, SHOW_PASSENGER_IN_FLIGHT};



//=============== GLOBAL VARIABLE ====================
//Giao dien chinh: toolbar + flight table
    //================ TOOL BAR ================
    
    //Kich thuoc toolbar
    int toolbar_x, toolbar_y, toolbar_width, toolbar_height;
    
    //Nhap thong tin filter; index: {FLIGHTID, PLANEID, MINUTE, HOUR, DAY, MONTH, YEAR, ARRIVE};
    InsertBox FilterFlightBox[MAX_FLIGHT_FIELD];

    //index: enum FLIGHT_STATUS{HUYCHUYEN, CONVE, HETVE, HOANTAT};
    CheckBox StatusCheckBox[MAX_FLIGHT_STATUS]; 
   
    Button add_flight_button,  reset_button, SortType_button;

    //choice = SORTBY_DATE, SORTBY_FLIGHTID, SORTBY_PLANEID, SORTBY_ARRIVE
    SelectionList SortField;

    //================ FLIGHT TABLE ============
    //choice = MANAGE_TICKET, ADJUST_FLIGHT, CANCEL_FLIGHT, SHOW_PASSENGER_LIST
    Table FlightTable;
    Button next_page_button, prev_page_button;
    PopupMenu popupmenu;

//Giao dien add/adjust flight
    Button apply_button, cancel_button, choose_plane_button;
    //Nhap thong tin chuyen bay; index: {FLIGHTID, PLANEID, MINUTE, HOUR, DAY, MONTH, YEAR, ARRIVE};
    InsertBox InsertFlightBox[MAX_FLIGHT_FIELD];

//Giao dien Book ticket
    int SeatBox_x, SeatBox_y, SeatBox_width, SeatBox_height;
    Button Seat[MAX_SEAT_COLUMN][MAX_SEAT_ROW];
    Button back_button, up_button, down_button, left_button, right_button;

   
    


//Giao dien in danh sach hanh khach
    //dung chung back_button voi Giao dien Book ticket
    //dung chung prev_page_button, next_page_button voi giao dien chinh
    Table PassengerTable;

//Cac hop thoai
namespace smalldialog{
    //dung cho ham notification va confirm
    int x, y, width, height;
    Button ok_button, apply_button, cancel_button;
}

namespace mediumdialog{
    //dung cho chuc nang: hien thi/nhap thong tin book ve
    int x, y, width, height;
    Button apply_button, cancel_button, choose_passenger_button;
    InsertBox InsertPassID, InsertFirstname, InsertLastname;
    CheckBox male, female;
}

namespace bigdialog{
    //dung cho ham choose plane, choose passsenger
    int x, y, width, height;
    Button backbutton, next_page_button, prev_page_button;
    Table PlaneTable, PassengerTable;

    void PrintPlaneTable(DSMayBay &plane_list, int start);
    void PrintPassengerTable(Passenger **arr, int n, int start);

    
}


//=============== FUNCTION PROTOTYPE =================
void SetupGraphicFlightTab();

void PrintToolBar();

void PrintFlightTable(Flight **array, int n, int start);

//add/adjust flight
void PrintAddFlightDialog();
void PrintAdjustFlightDialog(Flight flight);

//Manage Booking ticket
void PrintManageTicketDialog(Flight &flight);
void PrintSeat(Flight &flight, int numcol, int numrow, int startcol, int startrow);
    //Dat ve, them hanh khach(TH hanh khach chua co trong danh sach)
    void PrintBookingTicketDialog(string ticketname);
    void PrintAddPassengerDialog();

//Show Passenger Table
void PrintPassengerTable(Passenger **pass, string *ticketname, int n, int start);

//Chon may bay, hanh khach
int  ChoosePlane(DSMayBay &plane_list);
Passenger* ChoosePassenger(PNode *root);
    

//Notification: In ra thong bao, cho den khi nguoi dung an nut "OK" 
void Notification(string s);
void Notification(string s1, string s2);
void Notification(string s1, string s2, string s3);

//Confirm : In ra thong bao, an nut "OK" return true, an nut "Cancel" return false
bool Confirm(string s);
bool Confirm(string s1, string s2);
bool Confirm(string s1, string s2, string s3);

//=============== FUNCTION DEFINITION ================

void PrintToolBar(){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    setbkcolor(WHITE);
    settextstyle(2, HORIZ_DIR, 6);
    rounded_bar(toolbar_x, toolbar_y, toolbar_width, toolbar_height, WHITE);

    for(int i = 0; i < MAX_FLIGHT_FIELD; i++)
        FilterFlightBox[i].print();
    outtextxy(FilterFlightBox[FLIGHTID].getx() - textwidth("Ma chuyen bay") - 10, FilterFlightBox[FLIGHTID].gety() + 5, "Ma chuyen bay");
    outtextxy(FilterFlightBox[PLANEID].getx() - textwidth("Mamay bay") - 10, FilterFlightBox[PLANEID].gety() + 5, "Ma may bay");
    outtextxy(FilterFlightBox[HOUR].getx() - textwidth("Thoi gian") - 10, FilterFlightBox[HOUR].gety() + 5, "Thoi gian");
    outtextxy(FilterFlightBox[ARRIVE].getx() - textwidth("Noi den") - 10, FilterFlightBox[ARRIVE].gety() + 5, "Noi den");

    outtextxy(FilterFlightBox[MINUTE].getx() - 10, FilterFlightBox[MINUTE].gety() + 5, ":" );
    outtextxy(FilterFlightBox[DAY].getx() - 10, FilterFlightBox[DAY].gety() + 5, "-" );
    outtextxy(FilterFlightBox[MONTH].getx() - 10, FilterFlightBox[MONTH].gety() + 5, "/" );
    outtextxy(FilterFlightBox[YEAR].getx() - 10, FilterFlightBox[YEAR].gety() + 5, "/" );

    for(int i = 0; i < MAX_FLIGHT_STATUS; i++)
        StatusCheckBox[i].print();
    outtextxy(StatusCheckBox[CONVE].getx() + StatusCheckBox[CONVE].getsize() + 5, StatusCheckBox[CONVE].gety() + 5, "Con ve");
    outtextxy(StatusCheckBox[HETVE].getx() + StatusCheckBox[HETVE].getsize() + 5, StatusCheckBox[HETVE].gety() + 5, "Het ve");
    outtextxy(StatusCheckBox[HOANTAT].getx() + StatusCheckBox[HOANTAT].getsize() + 5, StatusCheckBox[HOANTAT].gety() + 5, "Hoan tat");
    outtextxy(StatusCheckBox[HUYCHUYEN].getx() + StatusCheckBox[HUYCHUYEN].getsize() + 5, StatusCheckBox[HUYCHUYEN].gety() + 5, "Da huy");

    SortField.print();
    outtextxy(SortField.getx() - textwidth("Sap xep theo:") - 10, SortField.gety() + 5, "Sap xep theo:");

    SortType_button.print();
    outtextxy(SortType_button.getx() - textwidth("Sap xep: ") - 10, SortType_button.gety() + 10, "Sap xep:");

    add_flight_button.print();
    reset_button.print();

    setgraphicsettings(&currentsettings);

    
}

void PrintFlightTable(Flight **array, int n, int start){
    if(n == 0 || !(start >= 0 && start < n) ){
        rounded_bar(FlightTable.getx(), FlightTable.gety(), FlightTable.getwidth(), FlightTable.getheight() + 50, WORKSPACE_COLOR, -1);
        outtextxy(WORKSPACE_X + 100, toolbar_y + toolbar_height + 50, "Khong co chuyen bay nao!");
        return;
    }

    int max_row = FlightTable.getnumrow() - 1;
    FlightTable.print();
    FlightTable.outtext(0, 0, "Ma chuyen bay");
    FlightTable.outtext(0, 1, "Ma may bay");
    FlightTable.outtext(0, 2, "Ngay khoi hanh");
    FlightTable.outtext(0, 3, "Noi den");
    FlightTable.outtext(0, 4, "Trang thai");

    for(int i = 0; i < max_row; i++){
        if(start + i >= n) break;
        FlightTable.outtext(i+1, 0, array[start+i]->flightID);
        FlightTable.outtext(i+1, 1, array[start+i]->planeID);
        FlightTable.outtext(i+1, 2, array[start+i]->date.to_string());
        FlightTable.outtext(i+1, 3, array[start+i]->arrive);
        FlightTable.outtext(i+1, 4, status_to_string[array[start+i]->status]);
    }
    if(start + max_row < n)
        next_page_button.setstatus(NORMAL);
    else    
        next_page_button.setstatus(UNACTIVE);
    
    if(start > 0)
        prev_page_button.setstatus(NORMAL);
    else 
        prev_page_button.setstatus(UNACTIVE);

    next_page_button.print();
    prev_page_button.print();
    int page = ceil(double(start + 1)/max_row);
    int max_page = ceil(double(n)/max_row);
    string page_name = to_string(page) + "/" + to_string(max_page);
    rounded_bar(prev_page_button.getx() + prev_page_button.getwidth(), prev_page_button.gety(), 100, 30, WORKSPACE_COLOR, -1);
    outtextxy(prev_page_button.getx() + prev_page_button.getwidth() + 5, prev_page_button.gety() + 5, page_name);

    int color = getcolor();
    setcolor(RED);
    outtextxy(WORKSPACE_X + 10, WORKSPACE_Y + WORKSPACE_HEIGHT - 30, "*An chuot trai vao chuyen bay trong bang de chon chuc nang");
    setcolor(color);
}

void PrintAddFlightDialog(){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    settextstyle(3, HORIZ_DIR, 1);
    setcolor(BLACK);
    setbkcolor(WORKSPACE_COLOR);

    print_workspace();
    for(int i = 0; i < MAX_FLIGHT_FIELD; i++)
        InsertFlightBox[i].print();

    outtextxy(WORKSPACE_X + WORKSPACE_WIDTH/2 - textwidth("THEM CHUYEN BAY")/2, WORKSPACE_Y + 10, "THEM CHUYEN BAY");
    
    outtextxy(InsertFlightBox[FLIGHTID].getx() - 10 - textwidth("Ma chuyen bay"), InsertFlightBox[FLIGHTID].gety(), "Ma chuyen bay");
    outtextxy(InsertFlightBox[PLANEID].getx() - 10 - textwidth("Ma may bay"), InsertFlightBox[PLANEID].gety(), "Ma may bay");
    outtextxy(InsertFlightBox[HOUR].getx() - 10 - textwidth("Thoi gian"), InsertFlightBox[HOUR].gety(), "Thoi gian");
    outtextxy(InsertFlightBox[ARRIVE].getx() - 10 - textwidth("Noi den"), InsertFlightBox[ARRIVE].gety(), "Noi den");
    
    outtextxy(InsertFlightBox[MINUTE].getx() - 10, InsertFlightBox[MINUTE].gety() + 5, ":"  );
    outtextxy(InsertFlightBox[DAY].getx() - 10, InsertFlightBox[DAY].gety() +5, "-"  );
    outtextxy(InsertFlightBox[MONTH].getx() - 10, InsertFlightBox[MONTH].gety()+5, "/"  );
    outtextxy(InsertFlightBox[YEAR].getx() - 10, InsertFlightBox[YEAR].gety()+5, "/"  );
    apply_button.print();
    cancel_button.print();
    choose_plane_button.print();
    reset_button.print();
    setgraphicsettings(&currentsettings);
}

void PrintAdjustFlightDialog(Flight flight){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    settextstyle(3, HORIZ_DIR, 1);
    setcolor(BLACK);
    setbkcolor(WORKSPACE_COLOR);

    print_workspace();
    for(int i = 1; i < MAX_FLIGHT_FIELD; i++)
        InsertFlightBox[i].print();

    outtextxy(WORKSPACE_X + WORKSPACE_WIDTH/2 - textwidth("CHINH CHUYEN BAY")/2, WORKSPACE_Y + 10, "CHINH CHUYEN BAY");
    outtextxy(WORKSPACE_X + 300, WORKSPACE_Y + 50, "Ma so chuyen bay: " + string(flight.flightID));

    outtextxy(InsertFlightBox[PLANEID].getx() - 10 - textwidth("Ma may bay"), InsertFlightBox[PLANEID].gety(), "Ma may bay");
    outtextxy(InsertFlightBox[HOUR].getx() - 10 - textwidth("Thoi gian"), InsertFlightBox[HOUR].gety(), "Thoi gian");
    outtextxy(InsertFlightBox[ARRIVE].getx() - 10 - textwidth("Noi den"), InsertFlightBox[ARRIVE].gety(), "Noi den");
    
    outtextxy(InsertFlightBox[MINUTE].getx() - 10, InsertFlightBox[MINUTE].gety() + 5, ":"  );
    outtextxy(InsertFlightBox[DAY].getx() - 10, InsertFlightBox[DAY].gety() +5, "-"  );
    outtextxy(InsertFlightBox[MONTH].getx() - 10, InsertFlightBox[MONTH].gety()+5, "/"  );
    outtextxy(InsertFlightBox[YEAR].getx() - 10, InsertFlightBox[YEAR].gety()+5, "/"  );
    apply_button.print();
    cancel_button.print();
    choose_plane_button.print();
    reset_button.print();
    setgraphicsettings(&currentsettings);
}

//Manage Booking ticket
void PrintManageTicketDialog(Flight &flight){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    settextstyle(3, HORIZ_DIR, 1);
    setcolor(BLACK);
    setbkcolor(WORKSPACE_COLOR);
    
    print_workspace();
    back_button.print();
    
    outtextxy(WORKSPACE_X + WORKSPACE_WIDTH/2 - textwidth("QUAN LY VE")/2, WORKSPACE_Y + 10, "QUAN LY VE");
    string outscreen = "Chuyen bay: "+string(flight.flightID) 
            + "   Khoi hanh luc " + flight.date.to_string() 
            + "   Noi den: " + string(flight.arrive);
    outtextxy(WORKSPACE_X + WORKSPACE_WIDTH/2 - textwidth(outscreen)/2, WORKSPACE_Y + 40, outscreen);
    setgraphicsettings(&currentsettings);
}

void PrintSeat(Flight &flight, int numcol, int numrow, int startcol, int startrow){
    if(!(startcol >= 0 && startcol < numcol && startrow >= 0 && startrow < numrow)) return;
    int end_col = (startcol + MAX_SEAT_COLUMN - 1 < numcol) ? (startcol + MAX_SEAT_COLUMN - 1) : (numcol - 1),
        end_row = (startrow + MAX_SEAT_ROW - 1 < numrow) ? (startrow + MAX_SEAT_ROW - 1) : (numrow - 1);

    for(int i = 0; i < MAX_SEAT_COLUMN; i++)
        for(int j = 0; j < MAX_SEAT_ROW; j++)
            Seat[i][j].setstatus(UNACTIVE);

    for(int i  = 0; i < MAX_SEAT_COLUMN; i++){
        if(i + startcol >= numcol) break;//for(i)
        for(int j = 0; j < MAX_SEAT_ROW; j++){
            if(j + startrow >= numrow) break;//for(j)
            Seat[i][j].setstatus(NORMAL);
            if(strcmp(flight.ticket[i][j], "none") == 0){
                //Ve chua dat
                Seat[i][j].setbackground(LIGHTGREEN, GREEN, BLACK, BLACK);
            }else{
                //Ve da dat
                Seat[i][j].setbackground(LIGHTRED, RED, BLACK, BLACK);
            }
        }
    }

    if(startcol > 0)
        left_button.setstatus(NORMAL);
    else left_button.setstatus(UNACTIVE);

    if(startcol + MAX_SEAT_COLUMN < numcol)
        right_button.setstatus(NORMAL);
    else right_button.setstatus(UNACTIVE);

    if(startrow > 0)
        up_button.setstatus(NORMAL);
    else up_button.setstatus(UNACTIVE);

    if(startrow + MAX_SEAT_ROW < numrow)
        down_button.setstatus(NORMAL);
    else down_button.setstatus(UNACTIVE);

    //In ra man hinh
    rounded_bar(SeatBox_x, SeatBox_y, SeatBox_width, SeatBox_height, LIGHTCYAN);
    rounded_rect(SeatBox_x, SeatBox_y, SeatBox_width, SeatBox_height, BLACK);
    

    
    for(int i = 0; i < MAX_SEAT_COLUMN; i++){
        if(startcol + i >= numcol) break;
        outtextxy(SeatBox_x + 45 + i*35 + (30 - textwidth(get_column_name(startcol + i)))/2 , SeatBox_y + 20, get_column_name(startcol + i));
    }
    for(int i = 0; i < MAX_SEAT_ROW; i++){
        if(i + startrow >= numrow) break;
        outtextxy(SeatBox_x + 40 - textwidth(to_string(i + startrow + 1)), SeatBox_y + 50 + i*35, to_string(i + startrow + 1));
    }
    
    for(int i = 0; i < MAX_SEAT_COLUMN; i++) 
        for(int j = 0; j < MAX_SEAT_ROW; j++)
            if(Seat[i][j].isactive())
                Seat[i][j].print();
    
    rounded_bar(SeatBox_x + SeatBox_width - 300, SeatBox_y + SeatBox_height + 30, 30, 30, LIGHTGREEN);
    outtextxy(SeatBox_x + SeatBox_width - 300 + 40, SeatBox_y + SeatBox_height + 30 + 7, "Ve chua dat");
    rounded_bar(SeatBox_x + SeatBox_width - 300, SeatBox_y + SeatBox_height + 80, 30, 30, LIGHTRED);
    outtextxy(SeatBox_x + SeatBox_width - 300 + 40, SeatBox_y + SeatBox_height + 80 + 7, "Ve da dat");

    up_button.print();
    down_button.print();
    left_button.print();
    right_button.print();
}

void PrintBookingTicketDialog(string ticketname){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    
    setcolor(BLACK);
    setbkcolor(WHITE);
    
    
    rounded_bar(mediumdialog::x, mediumdialog::y, mediumdialog::width,mediumdialog::height, WHITE);
    rounded_rect(mediumdialog::x, mediumdialog::y, mediumdialog::width, mediumdialog::height, BLACK);

    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(2, HORIZ_DIR, 7);
    outtextxy(mediumdialog::x + mediumdialog::width/2, mediumdialog::y + 20, "DAT VE");
    settextstyle(2, HORIZ_DIR, 6);
    outtextxy(mediumdialog::x + mediumdialog::width/2, mediumdialog::y + 50, "Ma so ve: " + ticketname);
    outtextxy(mediumdialog::x + mediumdialog::width/2, mediumdialog::y + 80, "Vui long nhap so CCCD cua hanh khach ben duoi");
    
    settextjustify(LEFT_TEXT, TOP_TEXT);
    
    mediumdialog::InsertPassID.print();
    outtextxy(mediumdialog::InsertPassID.getx() - textwidth("CCCD") - 10, mediumdialog::InsertPassID.gety() + 5, "CCCD");
    
    mediumdialog::apply_button.print();
    mediumdialog::cancel_button.print();
    mediumdialog::choose_passenger_button.print();

    setgraphicsettings(&currentsettings);
}

void PrintAddPassengerDialog(){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    rounded_bar(mediumdialog::x, mediumdialog::y, mediumdialog::width,mediumdialog::height, WHITE);
    rounded_rect(mediumdialog::x, mediumdialog::y, mediumdialog::width, mediumdialog::height, BLACK);

    setcolor(BLACK);
    setbkcolor(WHITE);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    

    settextstyle(2, HORIZ_DIR, 7);
    outtextxy(mediumdialog::x + mediumdialog::width/2, mediumdialog::y + 50, "Them Hanh Khach");
    settextstyle(2, HORIZ_DIR, 6);
    settextjustify(LEFT_TEXT, TOP_TEXT);
    
    mediumdialog::InsertPassID.print();
    mediumdialog::InsertFirstname.print();
    mediumdialog::InsertLastname.print();
    mediumdialog::male.print();
    mediumdialog::female.print();
    outtextxy(mediumdialog::InsertPassID.getx() - textwidth("CCCD") - 10, mediumdialog::InsertPassID.gety() + 5, "CCCD");
    outtextxy(mediumdialog::InsertFirstname.getx() - textwidth("Ho") - 10, mediumdialog::InsertFirstname.gety() + 5, "Ho ");
    outtextxy(mediumdialog::InsertLastname.getx() - textwidth("Ten") - 10, mediumdialog::InsertLastname.gety() + 5, "Ten");
    outtextxy(mediumdialog::male.getx() - textwidth("Gioi tinh") - 10, mediumdialog::male.gety() + 5, "Gioi tinh");
    outtextxy(mediumdialog::male.getx() + mediumdialog::male.getsize() + 10, mediumdialog::male.gety() + 5, "Nam");
    outtextxy(mediumdialog::female.getx() + mediumdialog::female.getsize() + 10, mediumdialog::female.gety() + 5, "Nu");
    mediumdialog::apply_button.print();
    mediumdialog::cancel_button.print();
    mediumdialog::choose_passenger_button.print();

    setgraphicsettings(&currentsettings);
}

void PrintPassengerTable(Passenger **pass, string *ticketname, int n, int start){
    if(n == 0 ){
        rounded_bar(PassengerTable.getx(), PassengerTable.gety(), PassengerTable.getwidth(), PassengerTable.getheight(), WORKSPACE_COLOR, -1);
        outtextxy(WORKSPACE_X + 400, WORKSPACE_Y + 200, "DANH SACH HANH KHACH TRONG");
        return ;
    }
    if(!(start >= 0 && start < n)){
        cout << "Loi in bang danh sach hanh khach: start value wrong" << endl;
        Notification("Loi du lieu");
        return;
    }

    int max_row = PassengerTable.getnumrow() - 1;
    PassengerTable.print();
    //cac cot trong bang: stt, mave, cccd, ho, ten, phai=>6 cot
    PassengerTable.outtext(0, 0, "STT");
    PassengerTable.outtext(0, 1, "Ma ve");
    PassengerTable.outtext(0, 2, "CCCD");
    PassengerTable.outtext(0, 3, "Ho");
    PassengerTable.outtext(0, 4, "Ten");
    PassengerTable.outtext(0, 5, "Gioi tinh");

    for(int i = 0; i < max_row; i++){
        if(start + i >= n) break;
        PassengerTable.outtext(i+1, 0, to_string(start + i + 1));
        PassengerTable.outtext(i+1, 1, ticketname[start + i]);
        PassengerTable.outtext(i+1, 2, pass[start + i]->getCccd());
        PassengerTable.outtext(i+1, 3, pass[start + i]->getHo());
        PassengerTable.outtext(i+1, 4, pass[start + i]->getTen());
        PassengerTable.outtext(i+1, 5, pass[start + i]->getSex());
    }
    if(start > 0)
        prev_page_button.setstatus(NORMAL);
    else prev_page_button.setstatus(UNACTIVE);

    if(start + max_row < n)
        next_page_button.setstatus(NORMAL);
    else next_page_button.setstatus(UNACTIVE);

    next_page_button.print();
    prev_page_button.print();
    int page = ceil(double(start+1)/max_row),
        max_page = ceil(double(n)/max_row);


    string page_name = to_string(page) + "/" + to_string(max_page);
    outtextxy(prev_page_button.getx() + prev_page_button.getwidth() + 5, prev_page_button.gety() + 5, page_name);
}

//Chon may bay
int  ChoosePlane(DSMayBay &plane_list){
    if(plane_list.SoMayBay == 0){
        Notification("Danh sach may bay rong");
        return -1;
    }
    rounded_bar(bigdialog::x, bigdialog::y, bigdialog::width, bigdialog::height, WHITE);
    rounded_rect(bigdialog::x, bigdialog::y, bigdialog::width, bigdialog::height, BLACK);
    bigdialog::backbutton.print();

    int start_plane = 0;
    bigdialog::PrintPlaneTable(plane_list, start_plane);

    int mx, my;
    int current_row = -1, 
        max_row = bigdialog::PlaneTable.getnumrow() - 1;
    while(1){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(bigdialog::backbutton.inside(mx, my)){
                bigdialog::backbutton.setstatus(NORMAL);
                return -1;
            }
            for(int i = 0; i < max_row; i++){
                if(start_plane + i >= plane_list.SoMayBay ) break;
                if(bigdialog::PlaneTable.insiderow(i+1, mx, my)){
                    string s1, s2, s3;
                    s1 = "Ban co xac nhan chon may bay nay?";
                    s2 = "So hieu: " + string(plane_list.n[start_plane + i]->SoHieuMB);
                    s3 = "Loai: " + string(plane_list.n[start_plane + i]->LoaiMB) 
                            + "(" + to_string(plane_list.n[start_plane + i]->SoDay) + " * " 
                            + to_string(plane_list.n[start_plane + i]->SoDong) + ")";
                    if(Confirm(s1, s2, s3)){
                        return start_plane + i;
                    }else{
                        bigdialog::PrintPlaneTable(plane_list, start_plane);
                        current_row = -1;
                        break;//for(i)
                    }
                } 
            }
            if(bigdialog::prev_page_button.inside(mx, my) && bigdialog::prev_page_button.isactive()){
                current_row = -1;
                start_plane -= max_row;
                bigdialog::PrintPlaneTable(plane_list, start_plane);
            }
            if(bigdialog::next_page_button.inside(mx, my) && bigdialog::next_page_button.isactive()){
                current_row = -1;
                start_plane += max_row;
                bigdialog::PrintPlaneTable(plane_list, start_plane);
            }
        }

        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            

            //Hover table
            if( (!bigdialog::PlaneTable.inside(mx, my) || bigdialog::PlaneTable.insiderow(0, mx, my)) && current_row != -1){
                bigdialog::PlaneTable.outtext(current_row+1, 0,plane_list.n[start_plane + current_row]->SoHieuMB);
                bigdialog::PlaneTable.outtext(current_row+1, 1, plane_list.n[start_plane + current_row]->LoaiMB);
                bigdialog::PlaneTable.outtext(current_row+1, 2, 
                                              to_string(plane_list.n[start_plane + current_row]->SoDay) + " * " 
                                              + to_string(plane_list.n[start_plane + current_row]->SoDong));
                current_row = -1;
            }
            else{
                for(int i = 0; i < max_row; i++){
                    if (start_plane + i >= plane_list.SoMayBay) break;//for(i)
                    if(bigdialog::PlaneTable.insiderow(i+1, mx, my) && current_row != i){
                        bigdialog::PlaneTable.outtext(i+1, 0,plane_list.n[start_plane + i]->SoHieuMB, RED, LIGHTCYAN);
                        bigdialog::PlaneTable.outtext(i+1, 1, plane_list.n[start_plane + i]->LoaiMB, RED, LIGHTCYAN);
                        bigdialog::PlaneTable.outtext(i+1, 2, 
                                                        to_string(plane_list.n[start_plane + i]->SoDay) + " * " 
                                                        + to_string(plane_list.n[start_plane + i]->SoDong), RED, LIGHTCYAN);
                        if(current_row != -1){
                            bigdialog::PlaneTable.outtext(current_row+1, 0,plane_list.n[start_plane + current_row]->SoHieuMB);
                            bigdialog::PlaneTable.outtext(current_row+1, 1, plane_list.n[start_plane + current_row]->LoaiMB);
                            bigdialog::PlaneTable.outtext(current_row+1, 2, 
                                                            to_string(plane_list.n[start_plane + current_row]->SoDay) + " * " 
                                                            + to_string(plane_list.n[start_plane + current_row]->SoDong));
                        }
                    current_row = i;
                    break;//for(i)
                    }
                }
            }

            //Hover button
            if(bigdialog::prev_page_button.inside(mx, my))
                bigdialog::prev_page_button.hover();
            else bigdialog::prev_page_button.unhover();

            if(bigdialog::next_page_button.inside(mx, my))
                bigdialog::next_page_button.hover();
            else bigdialog::next_page_button.unhover();

            if(bigdialog::backbutton.inside(mx, my))
                bigdialog::backbutton.hover();
            else bigdialog::backbutton.unhover();
        }
        delay(100);
    }
}

void bigdialog::PrintPlaneTable(DSMayBay &plane_list, int start){
    if(plane_list.SoMayBay == 0 || !(start >= 0 && start < plane_list.SoMayBay)){
        Notification("Danh sach may bay rong");
        return;
    }
    bigdialog::PlaneTable.print();
    bigdialog::PlaneTable.outtext(0, 0, "So hieu may bay");
    bigdialog::PlaneTable.outtext(0, 1, "Loai may bay");
    bigdialog::PlaneTable.outtext(0, 2, "So cho( Day * Dong)");

    int max_row = bigdialog::PlaneTable.getnumrow()-1;
    for(int i = 0; i < max_row; i++){
        if(start + i >= plane_list.SoMayBay) break;
        bigdialog::PlaneTable.outtext(i+1, 0,plane_list.n[start + i]->SoHieuMB);
        bigdialog::PlaneTable.outtext(i+1, 1, plane_list.n[start + i]->LoaiMB);
        bigdialog::PlaneTable.outtext(i+1, 2, to_string(plane_list.n[start + i]->SoDay) + " * " + to_string(plane_list.n[start + i]->SoDong));
    }

    if(start > 0)
        bigdialog::prev_page_button.setstatus(NORMAL);
    else    
        bigdialog::prev_page_button.setstatus(UNACTIVE);
    if(start + max_row < plane_list.SoMayBay)
        bigdialog::next_page_button.setstatus(NORMAL);
    else  
        bigdialog::next_page_button.setstatus(UNACTIVE);
    
    bigdialog::prev_page_button.print();
    bigdialog::next_page_button.print();
    int page = ceil(double(start+1)/max_row);
    int max_page = ceil(double(plane_list.SoMayBay)/max_row);
    string page_name = to_string(page) + "/" + to_string(max_page);
    rounded_bar(bigdialog::prev_page_button.getx() + bigdialog::prev_page_button.getwidth(), bigdialog::prev_page_button.gety(), 40, 30, WHITE, -1);
    outtextxy(bigdialog::prev_page_button.getx() + bigdialog::prev_page_button.getwidth() + 5, bigdialog::prev_page_button.gety() + 5, page_name);
    
}

//Chon hanh khach
Passenger* ChoosePassenger(PNode *root){
    //Luu tat cac cac dia chi Passenger cua cay vao array de de duyet
    int totalNode = countNodes(root);
    if(totalNode == 0){
        Notification("Danh sach hanh khach rong!");
        return NULL;
    }
    Passenger **arr = new Passenger*[totalNode];
    PNode **Stack = new PNode*[totalNode],
          *p = root;
    int n = 0, sp = -1;
    while(true){
        while(p != NULL){
            Stack[++sp] = p;
            p = p->left;
        }
        if(sp != -1){
            p = Stack[sp--];
            arr[n++] = &(p->pas);
            p = p->right;
        }else break;
    }
    //xoa Stack
    delete [] Stack;
    
    rounded_bar(bigdialog::x, bigdialog::y, bigdialog::width, bigdialog::height, WHITE);
    rounded_rect(bigdialog::x, bigdialog::y, bigdialog::width, bigdialog::height, BLACK);
    bigdialog::backbutton.print();

    int start_pass = 0,
        current_row = -1,
        max_row = bigdialog::PassengerTable.getnumrow()-1;
    bigdialog::PrintPassengerTable(arr, n, start_pass);
    int mx, my;
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            for(int i = 0; i < max_row; i++){
                if(start_pass + i >= n) break;//for(i)
                if(bigdialog::PassengerTable.insiderow(i+1, mx, my)){
                    //Xac nhan chon hanh khach
                    if(Confirm("Ban co xac nhan chon hanh khach nay?")){
                        Passenger *return_value = arr[start_pass + i];
                        delete[] arr;
                        return return_value;
                    }else{
                        bigdialog::PrintPassengerTable(arr, n, start_pass);
                        current_row = -1;
                        break; //for(i)
                    }
                }
            }

            if(bigdialog::backbutton.inside(mx, my)){
                bigdialog::backbutton.setstatus(NORMAL);
                delete[] arr;
                return NULL;
            }

            if(bigdialog::prev_page_button.inside(mx, my) && bigdialog::prev_page_button.isactive()){
                start_pass -= max_row;
                current_row = -1;
                bigdialog::PrintPassengerTable(arr, n, start_pass);
            }

            if(bigdialog::next_page_button.inside(mx, my) && bigdialog::next_page_button.isactive()){
                start_pass += max_row;
                current_row = -1;
                bigdialog::PrintPassengerTable(arr, n, start_pass);
            }

        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            
            //hover table
            if((!bigdialog::PassengerTable.inside(mx, my) || bigdialog::PassengerTable.insiderow(0, mx, my)) && current_row != -1){
                bigdialog::PassengerTable.outtext(current_row+1, 0, arr[start_pass + current_row]->getCccd());
                bigdialog::PassengerTable.outtext(current_row+1, 1, arr[start_pass + current_row]->getHo());
                bigdialog::PassengerTable.outtext(current_row+1, 2, arr[start_pass + current_row]->getTen());
                bigdialog::PassengerTable.outtext(current_row+1, 3, arr[start_pass + current_row]->getSex());
                current_row = -1;
                
            }
            else{
                for(int i = 0; i < max_row; i++){
                    if(start_pass + i >= n) break;//for(i)
                    if(bigdialog::PassengerTable.insiderow(i+1, mx, my) && current_row != i){
                        bigdialog::PassengerTable.outtext(i+1, 0, arr[start_pass + i]->getCccd(), RED, LIGHTCYAN);
                        bigdialog::PassengerTable.outtext(i+1, 1, arr[start_pass + i]->getHo(), RED, LIGHTCYAN);
                        bigdialog::PassengerTable.outtext(i+1, 2, arr[start_pass + i]->getTen(), RED, LIGHTCYAN);
                        bigdialog::PassengerTable.outtext(i+1, 3, arr[start_pass + i]->getSex(), RED, LIGHTCYAN);
                        if(current_row != -1){
                            bigdialog::PassengerTable.outtext(current_row+1, 0, arr[start_pass + current_row]->getCccd());
                            bigdialog::PassengerTable.outtext(current_row+1, 1, arr[start_pass + current_row]->getHo());
                            bigdialog::PassengerTable.outtext(current_row+1, 2, arr[start_pass + current_row]->getTen());
                            bigdialog::PassengerTable.outtext(current_row+1, 3, arr[start_pass + current_row]->getSex());
                        }
                        current_row = i;
                        break;//for(i)
                    }
                }
            }

            //Hover button
            if(bigdialog::prev_page_button.inside(mx, my))
                bigdialog::prev_page_button.hover();
            else bigdialog::prev_page_button.unhover();

            if(bigdialog::next_page_button.inside(mx, my))
                bigdialog::next_page_button.hover();
            else bigdialog::next_page_button.unhover();

            if(bigdialog::backbutton.inside(mx, my))
                bigdialog::backbutton.hover();
            else bigdialog::backbutton.unhover();
        }
        delay(100);
    }
}

void bigdialog::PrintPassengerTable(Passenger **arr, int n, int start){
    if(!(start >= 0 && start < n)){
        Notification("Danh sach hanh khach rong!");
        return;
    }
    //4 cot: cccd, ten, ho, gioi tinh
    bigdialog::PassengerTable.print();
    bigdialog::PassengerTable.outtext(0, 0, "CCCD");
    bigdialog::PassengerTable.outtext(0, 1, "Ho");
    bigdialog::PassengerTable.outtext(0, 2, "Ten");
    bigdialog::PassengerTable.outtext(0, 3, "Gioi tinh");

    int max_row = bigdialog::PassengerTable.getnumrow()-1;
    for(int i = 0; i < max_row; i++){
        if(start + i >= n ) break;
        bigdialog::PassengerTable.outtext(i+1, 0, arr[start + i]->getCccd());
        bigdialog::PassengerTable.outtext(i+1, 1, arr[start + i]->getHo());
        bigdialog::PassengerTable.outtext(i+1, 2, arr[start + i]->getTen());
        bigdialog::PassengerTable.outtext(i+1, 3, arr[start + i]->getSex());
    
    }

    if(start > 0)
        bigdialog::prev_page_button.setstatus(NORMAL);
    else bigdialog::prev_page_button.setstatus(UNACTIVE);
    if(start + max_row < n)
        bigdialog::next_page_button.setstatus(NORMAL);
    else bigdialog::next_page_button.setstatus(UNACTIVE);

    bigdialog::prev_page_button.print();
    bigdialog::next_page_button.print();

    int maxpage = ceil(double(n)/max_row),
        page = ceil(double(start+1)/max_row);
    string page_name = to_string(page) + "/" + to_string(maxpage);
    rounded_bar(bigdialog::prev_page_button.getx() + bigdialog::prev_page_button.getwidth(), bigdialog::prev_page_button.gety(), 40, 30, WHITE, -1);
    outtextxy(bigdialog::prev_page_button.getx() + bigdialog::prev_page_button.getwidth() + 5, bigdialog::prev_page_button.gety() + 5, page_name);

}

//Notification: In ra thong bao, cho den khi nguoi dung an nut "OK" 
void Notification(string s){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    rounded_bar(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, WHITE);
    rounded_rect(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, BLACK);

    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(2, HORIZ_DIR, 5);
    setcolor(BLACK);
    setbkcolor(WHITE);
    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 100, s);
    smalldialog::ok_button.print();
    int mx, my;
    while(1){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(smalldialog::ok_button.inside(mx, my))
                break;//while(1)
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(smalldialog::ok_button.inside(mx, my))
                smalldialog::ok_button.hover();
            else    
                smalldialog::ok_button.unhover();
        }
        delay(100);
    }
    smalldialog::ok_button.setstatus(NORMAL);
    setgraphicsettings(&currentsettings);
}

void Notification(string s1, string s2){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    rounded_bar(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, WHITE);
    rounded_rect(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, BLACK);

    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(2, HORIZ_DIR, 5);
    setcolor(BLACK);
    setbkcolor(WHITE);

    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 50, s1);
    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 80, s2);
    smalldialog::ok_button.print();
    int mx, my;
    while(1){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(smalldialog::ok_button.inside(mx, my))
                break;//while(1)
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(smalldialog::ok_button.inside(mx, my))
                smalldialog::ok_button.hover();
            else    
                smalldialog::ok_button.unhover();
        }
        delay(100);
    }
    smalldialog::ok_button.setstatus(NORMAL);
    setgraphicsettings(&currentsettings);
}

void Notification(string s1, string s2, string s3){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    rounded_bar(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, WHITE);
    rounded_rect(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, BLACK);

    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(2, HORIZ_DIR, 5);
    setcolor(BLACK);
    setbkcolor(WHITE);

    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 50, s1);
    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 80, s2);
    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 120, s3);
    smalldialog::ok_button.print();
    int mx, my;
    while(1){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(smalldialog::ok_button.inside(mx, my))
                break;//while(1)
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(smalldialog::ok_button.inside(mx, my))
                smalldialog::ok_button.hover();
            else    
                smalldialog::ok_button.unhover();
        }
        delay(100);
    }
    smalldialog::ok_button.setstatus(NORMAL);
    setgraphicsettings(&currentsettings);
}

//Confirm : In ra thong bao, an nut "OK" return true, an nut "Cancel" return false
bool Confirm(string s){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    rounded_bar(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, WHITE);
    rounded_rect(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, BLACK);

    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(2, HORIZ_DIR, 5);
    setcolor(BLACK);
    setbkcolor(WHITE);

    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 100, s);
    smalldialog::apply_button.print();
    smalldialog::cancel_button.print();
    int mx, my;
    while(1){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(smalldialog::apply_button.inside(mx, my)){
                smalldialog::apply_button.setstatus(NORMAL);
                setgraphicsettings(&currentsettings);
                return true;
            }
            if(smalldialog::cancel_button.inside(mx,my)){
                smalldialog::cancel_button.setstatus(NORMAL);
                setgraphicsettings(&currentsettings);
                return false;
            }
               
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(smalldialog::apply_button.inside(mx, my))
                smalldialog::apply_button.hover();
            else    
                smalldialog::apply_button.unhover();

            if(smalldialog::cancel_button.inside(mx, my))
                smalldialog::cancel_button.hover();
            else    
                smalldialog::cancel_button.unhover();
        }
        delay(100);
    }
}

bool Confirm(string s1, string s2){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    rounded_bar(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, WHITE);
    rounded_rect(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, BLACK);

    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(2, HORIZ_DIR, 5);
    setcolor(BLACK);
    setbkcolor(WHITE);

    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 50, s1);
    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 80, s2);
    smalldialog::apply_button.print();
    smalldialog::cancel_button.print();
    int mx, my;
    while(1){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(smalldialog::apply_button.inside(mx, my)){
                smalldialog::apply_button.setstatus(NORMAL);
                setgraphicsettings(&currentsettings);
                return true;
            }
            if(smalldialog::cancel_button.inside(mx,my)){
                smalldialog::cancel_button.setstatus(NORMAL);
                setgraphicsettings(&currentsettings);
                return false;
            }
               
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(smalldialog::apply_button.inside(mx, my))
                smalldialog::apply_button.hover();
            else    
                smalldialog::apply_button.unhover();

            if(smalldialog::cancel_button.inside(mx, my))
                smalldialog::cancel_button.hover();
            else    
                smalldialog::cancel_button.unhover();
        }
        delay(100);
    }
}

bool Confirm(string s1, string s2, string s3){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    rounded_bar(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, WHITE);
    rounded_rect(smalldialog::x, smalldialog::y, smalldialog::width, smalldialog::height, BLACK);

    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(2, HORIZ_DIR, 5);
    setcolor(BLACK);
    setbkcolor(WHITE);

    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 50, s1);
    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 80, s2);
    outtextxy(smalldialog::x + smalldialog::width/2, smalldialog::y + 120, s3);
    smalldialog::apply_button.print();
    smalldialog::cancel_button.print();
    int mx, my;
    while(1){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(smalldialog::apply_button.inside(mx, my)){
                smalldialog::apply_button.setstatus(NORMAL);
                setgraphicsettings(&currentsettings);
                return true;
            }
            if(smalldialog::cancel_button.inside(mx,my)){
                smalldialog::cancel_button.setstatus(NORMAL);
                setgraphicsettings(&currentsettings);
                return false;
            }
               
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(smalldialog::apply_button.inside(mx, my))
                smalldialog::apply_button.hover();
            else    
                smalldialog::apply_button.unhover();

            if(smalldialog::cancel_button.inside(mx, my))
                smalldialog::cancel_button.hover();
            else    
                smalldialog::cancel_button.unhover();
        }
        delay(100);
    }
}

void SetupGraphicFlightTab(){
    //================================== Giao dien chinh ======================================
    //Toolbar
    toolbar_x = WORKSPACE_X + 5;
    toolbar_y = WORKSPACE_Y + 5;
    toolbar_width = WORKSPACE_WIDTH - 10;
    toolbar_height = 200;

    //Cac o insert
    FilterFlightBox[FLIGHTID].  setup(toolbar_x + 200, toolbar_y + 5 + 50*0, MAX_FLIGHT_ID);
    FilterFlightBox[PLANEID].   setup(toolbar_x + 200, toolbar_y + 5 + 50*1, MAX_PLANE_ID);
    FilterFlightBox[HOUR].      setup(toolbar_x + 200, toolbar_y + 5 + 50*2, 2);
    FilterFlightBox[MINUTE].    setup(toolbar_x + 275, toolbar_y + 5 + 50*2, 2);
    FilterFlightBox[DAY].       setup(toolbar_x + 350, toolbar_y + 5 + 50*2, 2);
    FilterFlightBox[MONTH].     setup(toolbar_x + 425, toolbar_y + 5 + 50*2, 2);
    FilterFlightBox[YEAR].      setup(toolbar_x + 500, toolbar_y + 5 + 50*2, 4);
    FilterFlightBox[ARRIVE].    setup(toolbar_x + 200, toolbar_y + 5 + 50*3, MAX_ARRIVE);


    FilterFlightBox[FLIGHTID].  settitle("MAX 15 ky tu");
    FilterFlightBox[PLANEID].   settitle("MAX 15 ky tu");
    FilterFlightBox[HOUR].      settitle("hh");
    FilterFlightBox[MINUTE].    settitle("mm");
    FilterFlightBox[DAY].       settitle("dd");
    FilterFlightBox[MONTH].     settitle("mm");
    FilterFlightBox[YEAR].      settitle("yyyy");
    FilterFlightBox[ARRIVE].    settitle("MAX 30 ky tu");
    for(int i = 0; i < MAX_FLIGHT_FIELD; i++){
        FilterFlightBox[i].setbackgroundcolor(LIGHTGRAY, LIGHTCYAN);
        FilterFlightBox[i].settext(2, HORIZ_DIR , 6);
    }
        
    //checkBox
    StatusCheckBox[CONVE].      setup(toolbar_x + 750, toolbar_y + 5);
    StatusCheckBox[HETVE].      setup(toolbar_x + 750, toolbar_y + 55);
    StatusCheckBox[HOANTAT].    setup(toolbar_x + 750, toolbar_y + 105);
    StatusCheckBox[HUYCHUYEN].  setup(toolbar_x + 750, toolbar_y + 155);
    StatusCheckBox[CONVE].setclick(true);

    //FlightTable
    //Cac cot:flighid, planeid , date, arrive, status
    FlightTable.setup(toolbar_x, toolbar_y + toolbar_height + 10, 
                      toolbar_width, WORKSPACE_Y + WORKSPACE_HEIGHT - 70 - (toolbar_y + toolbar_height + 10),
                       11, 5 );
    FlightTable.setrowheight(0, FlightTable.getrowheight(0) + 20);

    //Button
    add_flight_button.  setup(toolbar_x + toolbar_width - 105, toolbar_y + 10, 100, 30, "Add");
    reset_button.       setup(toolbar_x + toolbar_width - 105, toolbar_y + 50, 100, 30, "Reset");
    add_flight_button.  settext(3, HORIZ_DIR, 1);
    reset_button.       settext(3, HORIZ_DIR, 1);
    prev_page_button.setup(WORKSPACE_X + WORKSPACE_WIDTH/2 - 100, WORKSPACE_Y + WORKSPACE_HEIGHT - 40, 50, 30, "<<");
    next_page_button.setup(WORKSPACE_X + WORKSPACE_WIDTH/2 + 50, WORKSPACE_Y + WORKSPACE_HEIGHT - 40, 50, 30, ">>");
    //PopupMenu
    popupmenu.setbackgroundcolor(LIGHTGRAY, LIGHTCYAN);
    popupmenu.settextcolor(BLACK, RED, DARKGRAY);
    
    popupmenu.add("Dat/Huy ve");            //MANAGE_TICKET
    popupmenu.add("Chinh chuyen bay");      //ADJUST_FLIGHT
    popupmenu.add("Huy chuyen bay");        //CANCEL_FLIGHT
    popupmenu.add("Danh sach hanh khach");  //SHOW_PASSENGER_IN_FLIGHT

    //Selection list
    SortField.setup(toolbar_x + toolbar_width - 300, toolbar_y + 50, 100, 25);
    SortField.settext(2, HORIZ_DIR, 6);
    SortField.add_option("Date");       //SORTBY_DATE
    SortField.add_option("FlightID");   //SORTBY_FLIGHTID
    SortField.add_option("PlaneID");    //SORTBY_PLANEID
    SortField.add_option("Arrive");     //SORTBY_ARRIVE
    SortField.setchoice(SORTBY_DATE);

    //SortType
    SortType_button.setup(toolbar_x + toolbar_width - 300, toolbar_y + 10, 110, 30, "Tang dan");
    SortType_button.settextcolor(BLACK, BLUE, WHITE, BLACK);
    SortType_button.setbackground(LIGHTGREEN, CYAN, LIGHTGREEN, BLACK);
    SortType_button.settext(2, HORIZ_DIR, 6);

    //================================= ADD FLIGHT/ ADJUST FLIGHT =========================
    //Button apply_button, cancel_button, choose_plane_button;
    //InsertBox InsertFlightBox[MAX_FLIGHT_FIELD];
    InsertFlightBox[FLIGHTID].  setup(WORKSPACE_X + 400, WORKSPACE_Y + 100*1, MAX_FLIGHT_ID, 3, 1);
    InsertFlightBox[PLANEID].   setup(WORKSPACE_X + 400, WORKSPACE_Y + 100*2, MAX_PLANE_ID, 3, 1);
    InsertFlightBox[HOUR].      setup(WORKSPACE_X + 400, WORKSPACE_Y + 100*3, 2, 3, 1);
    InsertFlightBox[MINUTE].    setup(WORKSPACE_X + 500, WORKSPACE_Y + 100*3, 2, 3, 1);
    InsertFlightBox[DAY].       setup(WORKSPACE_X + 600, WORKSPACE_Y + 100*3, 2, 3, 1);
    InsertFlightBox[MONTH].     setup(WORKSPACE_X + 700, WORKSPACE_Y + 100*3, 2, 3, 1);
    InsertFlightBox[YEAR].      setup(WORKSPACE_X + 800, WORKSPACE_Y + 100*3, 4, 3, 1);
    InsertFlightBox[ARRIVE].    setup(WORKSPACE_X + 400, WORKSPACE_Y + 100*4, MAX_ARRIVE, 3, 1);

    InsertFlightBox[FLIGHTID].  settitle("MAX 15 ky tu");
    InsertFlightBox[PLANEID].   settitle("MAX 15 ky tu");
    InsertFlightBox[HOUR].      settitle("hh");
    InsertFlightBox[MINUTE].    settitle("mm");
    InsertFlightBox[DAY].       settitle("dd");
    InsertFlightBox[MONTH].     settitle("mm");
    InsertFlightBox[YEAR].      settitle("yyyy");
    InsertFlightBox[ARRIVE].    settitle("MAX 30 ky tu");

    apply_button.setup(WORKSPACE_X + WORKSPACE_WIDTH/2 - 200, WORKSPACE_Y + WORKSPACE_HEIGHT - 100, 100, 40, "Ok");
    cancel_button.setup(WORKSPACE_X + WORKSPACE_WIDTH/2 + 100, WORKSPACE_Y + WORKSPACE_HEIGHT - 100, 100, 40, "Cancel");
    apply_button.settext(3, HORIZ_DIR, 1);
    cancel_button.settext(3, HORIZ_DIR, 1);
    choose_plane_button.setup(InsertFlightBox[PLANEID].getx() + InsertFlightBox[PLANEID].getwidth() + 10, InsertFlightBox[PLANEID].gety(), 30, 30, "+");
    choose_plane_button.settext(3, HORIZ_DIR, 1);

    //================================= MANAGE TICKET =====================================
    // int SeatBox_x, SeatBox_y, SeatBox_width, SeatBox_height;
    // Button Seat[MAX_SEAT_COLUMN][MAX_SEAT_ROW];
    // Button back_button, up_button, down_button, left_button, right_button;
    int seat_size = 30;
    int border_space = 40;
    SeatBox_width = (seat_size+5) * MAX_SEAT_COLUMN + border_space*2 + 10;
    SeatBox_height = (seat_size+5) * MAX_SEAT_ROW + border_space*2;
    SeatBox_x = WORKSPACE_X + WORKSPACE_WIDTH/2 - SeatBox_width/2;
    SeatBox_y = WORKSPACE_Y + 100;
    for(int i = 0; i < MAX_SEAT_COLUMN; i++)
        for(int j = 0; j < MAX_SEAT_ROW; j++){
            Seat[i][j].setup((SeatBox_x + border_space + 5 + i*(seat_size+5)),
                             (SeatBox_y + border_space + j*(seat_size+5)),
                             seat_size, seat_size,"");
            Seat[i][j].setbackground(LIGHTGREEN, GREEN, GREEN, GREEN);
        }
    back_button.setup(WORKSPACE_X + 10, WORKSPACE_Y + 10, 100, 40, "BACK");
    back_button.settext(2, HORIZ_DIR, 6);
    back_button.settextcolor(BLUE, WHITE, WHITE, WHITE);
    up_button.      setup(SeatBox_x + SeatBox_width/2 - 30/2, SeatBox_y + SeatBox_height + 25 , 30, 30, ">>");
	down_button.    setup(SeatBox_x + SeatBox_width/2 - 30/2, SeatBox_y + SeatBox_height + 95 , 30, 30, "<<");
	left_button.    setup(SeatBox_x + SeatBox_width/2 - 55, SeatBox_y + SeatBox_height + 60 , 30, 30, "<<");
	right_button.   setup(SeatBox_x + SeatBox_width/2 + 25, SeatBox_y + SeatBox_height + 60 , 30, 30, ">>");
    
    up_button.settext(2, VERT_DIR, 5);
    down_button.settext(2, VERT_DIR, 5);

    

    //================================= Show passenger in flight ==========================
    //cac cot trong bang: stt, mave, cccd, ho, ten, phai=>6 cot
    // PassengerTable.setup(toolbar_x, toolbar_y + toolbar_height + 10, 
    //                     toolbar_width, WORKSPACE_Y + WORKSPACE_HEIGHT - 70 - (toolbar_y + toolbar_height + 10),
    //                     11, 6 );
    PassengerTable.setup(WORKSPACE_X + 20, WORKSPACE_Y + 100, 
                         WORKSPACE_WIDTH - 20*2, WORKSPACE_HEIGHT - 100 - 100,
                         11, 6);
    PassengerTable.setrowheight(0, FlightTable.getrowheight(0) + 20);
    int width = PassengerTable.getcolwidth(0);
    PassengerTable.setcolwidth(0, 80 );//stt
    PassengerTable.setcolwidth(1, 100 );//mave
    PassengerTable.setcolwidth(5, 200 );//gioi tinh
    
    PassengerTable.setcolwidth(2, width + (width-80 + width - 100 + width - 200)/3 );//CCCD
    PassengerTable.setcolwidth(3, width + (width-80 + width - 100 + width - 200)/3 );//Ho
    PassengerTable.setcolwidth(4, width + (width-80 + width - 100 + width - 200)/3 );//ten


    //================================== Cac hop thoai ====================================
    //Small dialog : notification + confirm
    smalldialog::width = 400;
    smalldialog::height = 200;
    smalldialog::x = WORKSPACE_X + WORKSPACE_WIDTH/2 -smalldialog::width/2;
    smalldialog::y = WORKSPACE_Y + WORKSPACE_HEIGHT/2 - smalldialog::height/2;
    smalldialog::apply_button.setup(smalldialog::x + 100, smalldialog::y + smalldialog::height - 50, 80, 30, "Ok");
    smalldialog::cancel_button.setup(smalldialog::x + smalldialog::width - 180, smalldialog::y + smalldialog::height - 50, 80, 30, "Cancel");
    smalldialog::ok_button.setup(smalldialog::x + smalldialog::width/2 - 40, smalldialog::y + smalldialog::height - 50, 80, 30, "Ok");


    //Medium dialog:hien thi/nhap thong tin book ve, them hanh khach

    mediumdialog::width = 800;
    mediumdialog::height = 400;
    mediumdialog::x = WORKSPACE_X + WORKSPACE_WIDTH/2 - mediumdialog::width/2;
    mediumdialog::y = WORKSPACE_Y + WORKSPACE_HEIGHT/2 - mediumdialog::height/2;

    mediumdialog::InsertPassID.   setup(mediumdialog::x + 200, mediumdialog::y + 130, MAX_PASSENGERID, 2, 6);
    mediumdialog::InsertFirstname.setup(mediumdialog::x + 200, mediumdialog::y + 180, 19, 2, 6);
    mediumdialog::InsertLastname. setup(mediumdialog::x + 200, mediumdialog::y + 230, 19, 2, 6);

    mediumdialog::InsertPassID.   settitle("MAX 12 ky tu");
    mediumdialog::InsertFirstname.settitle("MAX 19 ky tu");
    mediumdialog::InsertLastname. settitle("MAX 19 ky tu");


    mediumdialog::choose_passenger_button.setup(mediumdialog::InsertPassID.getx() + mediumdialog::InsertPassID.getwidth() + 10, mediumdialog::InsertPassID.gety(), 30, 30, "+");
    mediumdialog::male.   setup(mediumdialog::x + 200, mediumdialog::y + 280, 30);
    mediumdialog::female. setup(mediumdialog::x + 400, mediumdialog::y + 280, 30);
    mediumdialog::apply_button.setup(mediumdialog::x + mediumdialog::width/2 - 180, mediumdialog::y + mediumdialog::height - 50, 80, 30, "Ok");
    mediumdialog::cancel_button.setup(mediumdialog::x + mediumdialog::width/2 + 100, mediumdialog::y + mediumdialog::height - 50, 80, 30, "Cancel");

    //Big dialog : chooseplane, choose passenger
    bigdialog::width = (WORKSPACE_WIDTH*4)/5;
    bigdialog::height = (WORKSPACE_HEIGHT*4)/5;
    bigdialog::x = WORKSPACE_X + WORKSPACE_WIDTH/2 - bigdialog::width/2;
    bigdialog::y = WORKSPACE_Y + WORKSPACE_HEIGHT/2 - bigdialog::height/2;

    bigdialog::backbutton.setup(bigdialog::x + 10, bigdialog::y + 10, 75, 30, "BACK");
    bigdialog::prev_page_button.setup(bigdialog::x + bigdialog::width/2 - 50,bigdialog::y + bigdialog::height - 40,30, 30, "<<");
    bigdialog::next_page_button.setup(bigdialog::x + bigdialog::width/2 + 20,bigdialog::y + bigdialog::height - 40,30, 30, ">>");
    //3 cot: id, loai, kich thuoc
    bigdialog::PlaneTable.setup(bigdialog::x + 50, bigdialog::y + 50, bigdialog::width - 100, bigdialog::height - 100, 11, 3);
    //4 cot: cccd, ten, ho, gioi tinh
    bigdialog::PassengerTable.setup(bigdialog::x + 50, bigdialog::y + 50, bigdialog::width - 100, bigdialog::height - 100, 11, 4);
    
}

