#include"FlightTabGraphic.h"
#include"SortFlight.h"
/*
                CAC CHUC NANG
-Loc, sort chuyen bay
-Them/Chinh chuyen bay
-Dat/Huy ve
-In danh sach hanh khach trong chuyen bay
-Huy chuyen
*/

//=============== FUNCTION PROTOTYPE ==================
//Ham xu ly chinh dung trong main.cpp
    int Flight_processing(PTR_FLIGHT &flight_list, DSMayBay &plane_list, PNode *&root);   

//Filter
    void filter(PTR_FLIGHT flight_list, Flight **array,  int &n);

//Them/chinh chuyen bay
    bool AddFlight(PTR_FLIGHT &flight_list, DSMayBay &plane_list);//Tra ve true neu co them chuyen bay moi
    bool AdjustFlight(Flight &flight,PTR_FLIGHT &flight_list, DSMayBay &plane_list);//Tra ve true neu co dieu chinh chuyen bay

//Dat/Huy ve trong chuyen bay, in danh sach ghe da dat/chua dat
    //Tra ve true neu thay doi flight status
    bool ManageBookingTicket(Flight &flight, PTR_FLIGHT flight_list, DSMayBay &plane_list, PNode *&root);  
    //Tra ve true neu dat ve thanh cong
    bool BookTicketForSeat(Flight &flight, int column, int row, PTR_FLIGHT flight_list, DSMayBay &plane_list, PNode *&root);
    void AddPassenger(PNode *&root); 
    
//In danh sach hanh khach
    void ShowPassengerList(Flight flight, DSMayBay &plane_list, PNode *root);

//=============== FUNCTION DEFINITION =================

int Flight_processing(PTR_FLIGHT &flight_list, DSMayBay &plane_list, PNode *&root){
    print_workspace();
    PrintToolBar();


    int n = CountFlight(flight_list);
    if(n == 0) n++; //tranh truong hop n = 0 cap phat dong loi(FLight **arr = new Flight*[0])
    Flight **array = new Flight*[n];
    
    
    int mx, my;//Luu toa do chuot
    int start_flight = 0,   //start_flight: index cua flights hien thi dau tien trong bang
        current_row = -1;   //current_row: dong(trong bang flights) ma chuot dang tro toi
    bool need_to_save = false,
         need_to_filter = true,
         need_to_print = true; //print flights table
    while(true){
        if(need_to_save){
            if(!save_flight_to_file("Data\\Flights.dat", flight_list, plane_list)){
                Notification("Save du lieu chuyen bay that bai!");
                delete[]array;
                return EXIT;
            }
            need_to_save = false;
        }
        if(need_to_filter){
            need_to_print = true;
            filter(flight_list, array, n);
            need_to_filter = false;
        }
        if(need_to_print){
            start_flight = 0;
            current_row = -1;
            PrintFlightTable(array, n, start_flight);
            need_to_print = false;
        }
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);

            //===================== RETURN =====================
            for(int i = 0; i < MAX_TAB; i++){
                if(tab_button[i].inside(mx, my)){
                    //Giai phong bo nho mang 
                    delete[]array;
                    unclick_tab(FLIGHT_TAB);
                    if(i == FLIGHT_TAB) return MAIN_MENU;
                    click_tab(i);
                    return i;
                }
            }

            //======================== FILTER ==========================
            if(FilterFlightBox[FLIGHTID].inside(mx, my))
                if(FilterFlightBox[FLIGHTID].Insert(Insert_number_and_capital_letter))
                    need_to_filter = true;

            if(FilterFlightBox[PLANEID].inside(mx, my))
                if(FilterFlightBox[PLANEID].Insert(Insert_number_and_capital_letter))
                    need_to_filter = true;
            
            if(FilterFlightBox[HOUR].inside(mx, my))
                if(FilterFlightBox[HOUR].Insert(Insert_hour))
                    need_to_filter = true;
            
            if(FilterFlightBox[MINUTE].inside(mx, my))
                if(FilterFlightBox[MINUTE].Insert(Insert_minute))
                    need_to_filter = true;
            
            if(FilterFlightBox[DAY].inside(mx, my))
                if(FilterFlightBox[DAY].Insert(Insert_day))
                    need_to_filter = true;
            
            if(FilterFlightBox[MONTH].inside(mx, my))
                if(FilterFlightBox[MONTH].Insert(Insert_month))
                    need_to_filter = true;
                
            if(FilterFlightBox[YEAR].inside(mx, my))
                if(FilterFlightBox[YEAR].Insert(Insert_number_only))
                    need_to_filter = true;
            
            if(FilterFlightBox[ARRIVE].inside(mx, my))
                if(FilterFlightBox[ARRIVE].Insert(Insert_normal_text))
                    need_to_filter = true;
            
            if(StatusCheckBox[CONVE].inside(mx, my)){
                StatusCheckBox[CONVE].click();
                need_to_filter = true;
            }

            if(StatusCheckBox[HETVE].inside(mx, my)){
                StatusCheckBox[HETVE].click();
                need_to_filter = true;
            }

            if(StatusCheckBox[HUYCHUYEN].inside(mx, my)){
                StatusCheckBox[HUYCHUYEN].click();
                need_to_filter = true;
            }

            if(StatusCheckBox[HOANTAT].inside(mx, my)){
                StatusCheckBox[HOANTAT].click();
                need_to_filter = true;
            }
            //================== Sort ===========================
            if(SortType_button.inside(mx, my)){
                if(SortType_button.getcontent() == "Tang dan")
                    SortType_button.setcontent("Giam dan");
                else 
                    SortType_button.setcontent("Tang dan");
                SortType_button.print();
                reverse_arr(array, n);
                need_to_print = true;
            }
            if(SortField.inside(mx, my)){
                int oldchoice = SortField.getchoice();
                if(SortField.choose() != oldchoice){
                    QuickSortFlight(array, n, SortField.getchoice(), (SortType_button.getcontent() == "Tang dan")?(INCREASE):(DECREASE));
                    need_to_print = true;
                }
            }

            //=================== CAC CHUC NANG CHINH =======================
            //ADD FLIGHT
            if(add_flight_button.inside(mx, my)){
                add_flight_button.setstatus(NORMAL);
                if(AddFlight(flight_list, plane_list)){
                    //xoa mang array, tao mang moi 
                    delete []array;
                    n = CountFlight(flight_list);
                    array = new Flight*[n];
                    need_to_filter = true;
                    need_to_save = true;
                    print_workspace();
                    PrintToolBar();
                }else{
                    print_workspace();
                    PrintToolBar();
                    PrintFlightTable(array, n, start_flight);
                    current_row = -1;
                }   
            }

            //ADJUST, BOOKING TICKET, CANCEL FLIGHT, SHOW PASSENGER LIST
            for(int i = 0; i < FlightTable.getnumrow() - 1; i++){
                if(start_flight + i >= n) break; //for(i)
                if(FlightTable.insiderow(i+1, mx, my)){
                    int x = mx, y = my;
                    if(x + popupmenu.getwidth() > FlightTable.getx() + FlightTable.getwidth())
                        x -= popupmenu.getwidth();
                    if(y + popupmenu.getheight() > FlightTable.gety() + FlightTable.getheight())
                        y -= popupmenu.getheight();

                    popupmenu.unactive_alloption();
                    switch(array[start_flight + i]->status){
                        case CONVE:
                        case HETVE:{
                            popupmenu.active_alloption();
                            break;
                        }
                        case HUYCHUYEN:
                        case HOANTAT:{
                            popupmenu.active_option(SHOW_PASSENGER_IN_FLIGHT);
                            break;
                        }
                    }

                    switch(popupmenu.choose(x, y)){
                        //MANAGE_TICKET, ADJUST_FLIGHT, CANCEL_FLIGHT, SHOW_PASSENGER_LIST
                        case MANAGE_TICKET:{
                            if(ManageBookingTicket(*array[start_flight + i], flight_list, plane_list, root)){
                                need_to_filter = true;
                                need_to_save = true;
                            }
                                
                            print_workspace();
                            PrintToolBar();
                            break;
                        }
                        case ADJUST_FLIGHT:{
                            if(AdjustFlight(*array[start_flight + i], flight_list, plane_list)){
                                need_to_filter = true;
                                need_to_save = true;
                                print_workspace();
                                PrintToolBar();
                            }else{
                                print_workspace();
                                PrintToolBar();
                                current_row = -1;
                            }
                            break;
                        }
                        case CANCEL_FLIGHT:{
                            if(Confirm("Ban co xac nhan muon huy chuyen bay?","Ma so chuyen bay: "  + string(array[start_flight+i]->flightID)))
                            {
                                array[start_flight + i]->status = HUYCHUYEN;
                                need_to_save = true;
                                need_to_filter = true;
                            }
                            break;
                        }
                        case SHOW_PASSENGER_IN_FLIGHT:{
                            ShowPassengerList(*array[start_flight+i], plane_list, root);
                            print_workspace();
                            PrintToolBar();
                            break;
                        }
                    }
                    PrintFlightTable(array, n, start_flight);
                    break;//for(i)
                }//end if(inside row)
            }//end for(i)

            //Chuyen trang
            if(prev_page_button.inside(mx, my) && prev_page_button.isactive()){
                start_flight -= FlightTable.getnumrow() -1;
                current_row = -1;
                PrintFlightTable(array, n, start_flight);
            }
            if(next_page_button.inside(mx, my) && next_page_button.isactive()){
                start_flight += FlightTable.getnumrow() -1;
                current_row = -1;
                PrintFlightTable(array, n, start_flight);
            }
            //Reset filter & sort
            if(reset_button.inside(mx, my)){
                reset_button.setstatus(NORMAL);
                for(int i = 0; i < MAX_FLIGHT_FIELD; i++)
                    FilterFlightBox[i].setcontent("");
                for(int i = 0; i < MAX_FLIGHT_STATUS; i++)
                    StatusCheckBox[i].setclick(false);
                StatusCheckBox[CONVE].setclick(true);
                SortType_button.setcontent("Tang dan");
                SortField.setchoice(SORTBY_DATE);
                PrintToolBar();
                need_to_filter = true;
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

            //hover trong flight table
            if((!FlightTable.inside(mx, my) || FlightTable.insiderow(0, mx, my)) && current_row != -1){
                FlightTable.outtext(current_row+1, 0, array[start_flight+current_row]->flightID);
                FlightTable.outtext(current_row+1, 1, array[start_flight+current_row]->planeID);
                FlightTable.outtext(current_row+1, 2, array[start_flight+current_row]->date.to_string());
                FlightTable.outtext(current_row+1, 3, array[start_flight+current_row]->arrive);
                FlightTable.outtext(current_row+1, 4, status_to_string[array[start_flight+current_row]->status]);
                current_row = -1;
            }
            for(int i = 0; i < FlightTable.getnumrow() - 1; i++){
                if(start_flight + i >= n) break;//for(i)
                if(FlightTable.insiderow(i+1, mx, my) && current_row != i){
                    FlightTable.outtext(i+1, 0, array[start_flight+i]->flightID, RED, LIGHTCYAN);
                    FlightTable.outtext(i+1, 1, array[start_flight+i]->planeID, RED, LIGHTCYAN);
                    FlightTable.outtext(i+1, 2, array[start_flight+i]->date.to_string(), RED, LIGHTCYAN);
                    FlightTable.outtext(i+1, 3, array[start_flight+i]->arrive, RED, LIGHTCYAN);
                    FlightTable.outtext(i+1, 4, status_to_string[array[start_flight+i]->status], RED, LIGHTCYAN);
                    if(current_row != -1){
                        FlightTable.outtext(current_row+1, 0, array[start_flight+current_row]->flightID);
                        FlightTable.outtext(current_row+1, 1, array[start_flight+current_row]->planeID);
                        FlightTable.outtext(current_row+1, 2, array[start_flight+current_row]->date.to_string());
                        FlightTable.outtext(current_row+1, 3, array[start_flight+current_row]->arrive);
                        FlightTable.outtext(current_row+1, 4, status_to_string[array[start_flight+current_row]->status]);
                    }
                    current_row = i;
                    break;//for(i);
                }
            }

            if(SortType_button.inside(mx, my))
                SortType_button.hover();
            else SortType_button.unhover();

            if(add_flight_button.inside(mx, my))
                add_flight_button.hover();
            else add_flight_button.unhover();

            if(reset_button.inside(mx, my))
                reset_button.hover();
            else reset_button.unhover();


            if(prev_page_button.inside(mx, my))
                prev_page_button.hover();
            else prev_page_button.unhover();

            if(next_page_button.inside(mx, my))
                next_page_button.hover();
            else next_page_button.unhover();
        }
        delay(100);
    }
}

void filter(PTR_FLIGHT flight_list, Flight **array,  int &n){
    n = 0;
    PTR_FLIGHT p = flight_list;

    //Dieu kien loc
    Flight filter;
    strcpy(filter.flightID, FilterFlightBox[FLIGHTID].getcontent().c_str());
    strcpy(filter.planeID, FilterFlightBox[PLANEID].getcontent().c_str());
    strcpy(filter.arrive, FilterFlightBox[ARRIVE].getcontent().c_str());

    if(FilterFlightBox[HOUR].getcontent().size() != 0){
        filter.date.hour = stoi(FilterFlightBox[HOUR].getcontent());
    }else filter.date.hour = -1;

    if(FilterFlightBox[MINUTE].getcontent().size() != 0){
        filter.date.minute = stoi(FilterFlightBox[MINUTE].getcontent());
    }else filter.date.minute = -1;

    if(FilterFlightBox[DAY].getcontent().size() != 0){
        filter.date.day = stoi(FilterFlightBox[DAY].getcontent());
    }else filter.date.day = -1;

    if(FilterFlightBox[MONTH].getcontent().size() != 0){
        filter.date.month = stoi(FilterFlightBox[MONTH].getcontent());
    }else filter.date.month = -1;

    if(FilterFlightBox[YEAR].getcontent().size() != 0){
        filter.date.year = stoi(FilterFlightBox[YEAR].getcontent());
    }else filter.date.year = -1;

    while(p != NULL){
        //flightID
        if(strlen(filter.flightID) != 0){
            //Vi danh sach tang dan theo flightID nen stop khi p.id > filer.id
            if(strncmp(p->flight.flightID, filter.flightID, strlen(filter.flightID)) > 0)
                break;
            if(strncmp(p->flight.flightID, filter.flightID, strlen(filter.flightID)) != 0){
                p = p->next;
                continue;
            }
        }

        //planeID
        if(strlen(filter.planeID) != 0){
            if(strncmp(p->flight.planeID, filter.planeID, strlen(filter.planeID)) != 0){
                p = p->next;
                continue;
            }
        }

        //arrive
        if(strlen(filter.arrive) != 0){
            if(strncmp(p->flight.arrive, filter.arrive, strlen(filter.arrive)) != 0){
                p = p->next;
                continue;
            }
        }

        //Date
        if(filter.date.hour != -1){
            if(p->flight.date.hour != filter.date.hour){
                p = p->next;
                continue;
            }
        }

        if(filter.date.minute != -1){
            if(p->flight.date.minute != filter.date.minute){
                p = p->next;
                continue;
            }
        }

        if(filter.date.day != -1){
            if(p->flight.date.day != filter.date.day){
                p = p->next;
                continue;
            }
        }

        if(filter.date.month != -1){
            if(p->flight.date.month != filter.date.month){
                p = p->next;
                continue;
            }
        }

        if(filter.date.year != -1){
            if(p->flight.date.year != filter.date.year){
                p = p->next;
                continue;
            }
        }

        //Status
        if( !StatusCheckBox[CONVE].isclicked() && p->flight.status == CONVE){
            p = p->next;
            continue;
        }

        if(!StatusCheckBox[HETVE].isclicked() && p->flight.status == HETVE){
            p = p->next;
            continue;
        }

        if(!StatusCheckBox[HUYCHUYEN].isclicked() && p->flight.status == HUYCHUYEN){
            p = p->next;
            continue;
        }

        if(!StatusCheckBox[HOANTAT].isclicked() && p->flight.status == HOANTAT){
            p = p->next;
            continue;
        }

        //pass tat ca cac filter
        array[n++] = &(p->flight);
        p = p->next;
    }
    //sort.......
    int sortype = (SortType_button.getcontent() == "Tang dan")?(INCREASE):(DECREASE);
    int sortby = SortField.getchoice();

    //Vi danh sach co san thu tu theo flightID ne
    if(sortby == SORTBY_FLIGHTID){
        //Thu tu mac dinh la tang dan, neu thu tu la giam dan=>dao day
        if(sortype = DECREASE)
            reverse_arr(array, n);
    }else{
        QuickSortFlight(array, n, sortby, sortype);
    }
}

bool AddFlight(PTR_FLIGHT &flight_list, DSMayBay &plane_list){
    PrintAddFlightDialog();

    int mx, my;
    int index;  //chi so may bay
    Date now;   //thoi gian hien tai
    Flight newflight; 
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            
            //an nut apply
            if(apply_button.inside(mx, my)){
                //=============== Check dieu kien: du lieu khong duoc bo trong ===============
                //flightID
                if(InsertFlightBox[FLIGHTID].getcontent().size() == 0 ){
                    Notification("Khong duoc de trong ma chuyen bay!");
                    PrintAddFlightDialog();
                    continue;//while(true)
                }
                //PlaneID
                if(InsertFlightBox[PLANEID].getcontent().size() == 0){
                    Notification("Khong duoc de trong  ma chuyen bay!");
                    PrintAddFlightDialog();
                    continue;//while(true)
                }
                //Date
                if( (InsertFlightBox[HOUR].getcontent().size() == 0) ||
                    (InsertFlightBox[MINUTE].getcontent().size() == 0) ||
                    (InsertFlightBox[DAY].getcontent().size() == 0) ||
                    (InsertFlightBox[MONTH].getcontent().size() == 0) ||
                    (InsertFlightBox[YEAR].getcontent().size() == 0))
                {
                    Notification("Khong duoc de trong thoi gian!");
                    PrintAddFlightDialog();
                    continue;//while(true)
                }
                //Arrive
                if(InsertFlightBox[ARRIVE].getcontent().size() == 0){
                    Notification("Khong duoc de trong noi den");
                    PrintAddFlightDialog();
                    continue;//while(true)
                }

                //Du lieu day du, load vao newflight
                strcpy(newflight.flightID, InsertFlightBox[FLIGHTID].getcontent().c_str());
                strcpy(newflight.planeID, InsertFlightBox[PLANEID].getcontent().c_str());
                strcpy(newflight.arrive, InsertFlightBox[ARRIVE].getcontent().c_str());
                newflight.date.hour = stoi( InsertFlightBox[HOUR].getcontent());
                newflight.date.minute = stoi( InsertFlightBox[MINUTE].getcontent());
                newflight.date.day = stoi( InsertFlightBox[DAY].getcontent());
                newflight.date.month = stoi( InsertFlightBox[MONTH].getcontent());
                newflight.date.year = stoi( InsertFlightBox[YEAR].getcontent());

                //=============== Check dieu kien:  du lieu phai chinh xac ===================
                
                //FlightID da ton tai
                if(SerchFlight(flight_list, newflight.flightID) != NULL){
                    Notification("Ma so chuyen bay da ton tai!");
                    PrintAddFlightDialog();
                    continue;//while(true)
                }

                //PlaneID khong ton tai
                index = SerchPlane(plane_list, newflight.planeID);
                if(index == -1){
                    Notification("Khong ton tai may bay ma so: " + InsertFlightBox[PLANEID].getcontent());
                    PrintAddFlightDialog();
                    continue;//while(true)
                }       

                //Date khong hop le(khong ton tai, o trong qua khu, cach hien tai it nhat 3h, trung lich bay)
                now = today();
                if(!checkdate(newflight.date)){
                    Notification("Khoang thoi diem khong ton tai!");
                    PrintAddFlightDialog();
                    continue;//while(true)
                }

                if(newflight.date < now){
                    Notification("Khong duoc nhap thoi gian trong qua khu");
                    PrintAddFlightDialog();
                    continue;//while(true)
                }

                if(newflight.date - now < 3*60){
                    Notification("Thoi diem phai cach hien tai it nhat 3h");
                    PrintAddFlightDialog();
                    continue;//while(true)
                }

                PTR_FLIGHT p =flight_list;
                bool check = true;
                while(p != NULL){
                    if(strcmp(p->flight.planeID, newflight.planeID) == 0){
                        if((p->flight.status == CONVE || p->flight.status == HETVE) && (abs(p->flight.date - newflight.date) < 3*60)){
                            check = false;
                            break;//while(p!=NULL)
                        }
                    }
                    p = p->next;
                }
                if(!check){
                    Notification("May bay da co chuyen luc: " +  p->flight.date.to_string(), 
                                 "Ma chuyen bay: " + string(p->flight.flightID),
                                 "Khoang cach toi thieu giua 2 chuyen bay la 3h");
                    PrintAddFlightDialog();
                    continue;//while(true)
                }

                //=============== Xac nhan lai, them chuyen bay ==============================
                if(Confirm("Ban co xac nhan them chuyen bay nay?")){
                    int numcol = plane_list.n[index]->SoDay,
                        numrow = plane_list.n[index]->SoDong;
                    newflight.status = CONVE;
                    newflight.ticket = new char**[numcol];
                    for(int i = 0; i < numcol; i++){
                        newflight.ticket[i] = new char*[numrow];
                        for(int j = 0; j < numrow; j++){
                            newflight.ticket[i][j] = new char[MAX_PASSENGERID + 1];
                            strcpy(newflight.ticket[i][j], "none");
                        }
                    }
                    InsertOrder(flight_list, newflight);
                    Notification("Them chuyen bay thanh cong!");

                    apply_button.setstatus(NORMAL);
                    for(int i = 0; i < MAX_FLIGHT_FIELD; i++)
                        InsertFlightBox[i].setcontent("");
                    return true;
                }else{
                    PrintAddFlightDialog();
                    continue;//while(true)
                }

            }

            //an nut cancel
            if(cancel_button.inside(mx, my)){
                if(Confirm("Ban co xac nhan thoat?")){
                    cancel_button.setstatus(NORMAL);
                    for(int i = 0; i < MAX_FLIGHT_FIELD; i++)
                        InsertFlightBox[i].setcontent("");
                    return false;
                }else PrintAddFlightDialog();
            }

            //Nhap du lieu
            if(InsertFlightBox[FLIGHTID].inside(mx, my))
                InsertFlightBox[FLIGHTID].Insert(Insert_number_and_capital_letter);

            if(InsertFlightBox[PLANEID].inside(mx, my))
                InsertFlightBox[PLANEID].Insert(Insert_number_and_capital_letter);
            
            if(InsertFlightBox[HOUR].inside(mx, my))
                InsertFlightBox[HOUR].Insert(Insert_hour);

            if(InsertFlightBox[MINUTE].inside(mx, my))
                InsertFlightBox[MINUTE].Insert(Insert_minute);

            if(InsertFlightBox[DAY].inside(mx, my))
                InsertFlightBox[DAY].Insert(Insert_day);

            if(InsertFlightBox[MONTH].inside(mx, my))
                InsertFlightBox[MONTH].Insert(Insert_month);

            if(InsertFlightBox[YEAR].inside(mx, my))
                InsertFlightBox[YEAR].Insert(Insert_number_only);
            
            if(InsertFlightBox[ARRIVE].inside(mx, my))
                InsertFlightBox[ARRIVE].Insert(Insert_normal_text);
            
            if(choose_plane_button.inside(mx, my)){
                index = ChoosePlane(plane_list);
                if(index != -1){
                    InsertFlightBox[PLANEID].setcontent(plane_list.n[index]->SoHieuMB);
                    InsertFlightBox[PLANEID].print();
                }
                PrintAddFlightDialog();
            }

            if(reset_button.inside(mx, my)){
                for(int i = 0; i < MAX_FLIGHT_FIELD; i++)
                    InsertFlightBox[i].setcontent("");
                reset_button.setstatus(NORMAL);
                PrintAddFlightDialog();
            }

        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(apply_button.inside(mx, my))
                apply_button.hover();
            else apply_button.unhover();

            if(cancel_button.inside(mx, my))
                cancel_button.hover();
            else cancel_button.unhover();

            if(choose_plane_button.inside(mx, my))
                choose_plane_button.hover();
            else choose_plane_button.unhover();

            if(reset_button.inside(mx, my))
                reset_button.hover();
            else reset_button.unhover();
        }
        delay(100);
    }
}

bool AdjustFlight(Flight &flight,PTR_FLIGHT &flight_list, DSMayBay &plane_list){
    InsertFlightBox[PLANEID].settitle(flight.planeID);
    InsertFlightBox[ARRIVE].settitle(flight.arrive);
    InsertFlightBox[HOUR].settitle((flight.date.hour < 10) ?("0" + to_string(flight.date.hour)):(to_string(flight.date.hour)));
    InsertFlightBox[MINUTE].settitle((flight.date.minute < 10) ?("0" + to_string(flight.date.minute)):(to_string(flight.date.minute)));
    InsertFlightBox[DAY].settitle((flight.date.day < 10) ?("0" + to_string(flight.date.day)):(to_string(flight.date.day)));
    InsertFlightBox[MONTH].settitle((flight.date.month < 10) ?("0" + to_string(flight.date.month)):(to_string(flight.date.month)));
    InsertFlightBox[YEAR].settitle(to_string(flight.date.year));
    PrintAdjustFlightDialog(flight);

    Flight newflight;   //luu cac thong tin thay doi
    int new_index,      //chi so may bay moi
        old_index;      //chi so may bay cu

    old_index = SerchPlane(plane_list, flight.planeID);
    if(old_index == -1) {
        Notification("Loi du lieu!");
        return false;
    }

    bool change_plane = false,
         change_date = false,
         change_arrive = false;
    int mx, my;
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            //an nut apply
            if(apply_button.inside(mx, my)){
                
                //=============== Check su thay doi cac thong tin
                change_plane = (InsertFlightBox[PLANEID].   getcontent().size() != 0);

                change_date = ( (InsertFlightBox[HOUR].     getcontent().size() != 0)||
                                (InsertFlightBox[MINUTE].   getcontent().size() != 0)||
                                (InsertFlightBox[DAY].      getcontent().size() != 0)||
                                (InsertFlightBox[MONTH].    getcontent().size() != 0)||
                                (InsertFlightBox[YEAR].     getcontent().size() != 0)  );

                change_arrive = (InsertFlightBox[ARRIVE].  getcontent().size() != 0);

                //Neu khong thay doi thong tin
                if(!(change_plane || change_date || change_arrive)){
                    if(Confirm("Ban khong thay doi thong tin nao",
                                "An OK de tiep tuc chinh sua thong tin",
                                "An Cancel de quay ve man hinh chinh"))
                    {
                        PrintAdjustFlightDialog(flight);
                        continue;//white(true)
                    }else{
                        break;//while(true)
                    }
                }
                //=============== Check thong tin
                newflight = flight;
                new_index = old_index;
                //check plane
                if(change_plane){
                    strcpy(newflight.planeID, InsertFlightBox[PLANEID].getcontent().c_str());

                    //Khong ton tai may bay
                    new_index = SerchPlane(plane_list, newflight.planeID);
                    if(new_index == -1){
                        Notification("May bay khong ton tai!");
                        PrintAdjustFlightDialog(flight);
                        continue;//white(true)
                    }

                    //May bay co so cho it hon may bay cu
                    if(plane_list.n[new_index]->SoDay < plane_list.n[old_index]->SoDay){
                        Notification("May bay moi co so day it hon may bay cu!");
                        PrintAdjustFlightDialog(flight);
                        continue;//white(true)
                    }
                    if(plane_list.n[new_index]->SoDong < plane_list.n[old_index]->SoDong){
                        Notification("May bay moi co so dong it hon may bay cu!");
                        PrintAdjustFlightDialog(flight);
                        continue;//white(true)
                    }
                }

                //check date
                if(change_date){
                    if(InsertFlightBox[HOUR].getcontent().size() != 0)
                        newflight.date.hour = stoi(InsertFlightBox[HOUR].getcontent());

                    if(InsertFlightBox[MINUTE].getcontent().size() != 0)
                        newflight.date.minute = stoi(InsertFlightBox[MINUTE].getcontent());

                    if(InsertFlightBox[DAY].getcontent().size() != 0)
                        newflight.date.day = stoi(InsertFlightBox[DAY].getcontent());

                    if(InsertFlightBox[MONTH].getcontent().size() != 0)
                        newflight.date.month = stoi(InsertFlightBox[MONTH].getcontent());

                    if(InsertFlightBox[YEAR].getcontent().size() != 0)
                        newflight.date.year = stoi(InsertFlightBox[YEAR].getcontent());
                    
                    //thoi gian khong ton tai
                    if(!checkdate(newflight.date)){
                        Notification("Thoi gian khong ton tai!");
                        PrintAdjustFlightDialog(flight);
                        continue;//white(true)
                    }

                    //Chi duoc lui thoi gian tre hon thoi gian ban dau
                    if(newflight.date < flight.date){
                        Notification("Khong duoc doi thoi gian bay som hon!");
                        PrintAdjustFlightDialog(flight);
                        continue;//white(true)
                    }

                    //chech lech gio bay cua may bay < 3h
                    bool check = true;
                    PTR_FLIGHT p = flight_list;

                    while(p != NULL){
                        if(strcmp(p->flight.planeID, newflight.planeID) == 0 && strcmp(p->flight.flightID, newflight.flightID) != 0){
                            if( (p->flight.status == CONVE || p->flight.status == HETVE) && 
                                (abs(p->flight.date - newflight.date) < 3*60))
                            {
                                check = false;
                                break; //while(p!=NULL)
                            }
                        }
                        p = p->next;
                    }
                    if(!check){
                        Notification("May bay da co chuyen bay luc: " + p->flight.date.to_string(),
                                    "Ma chuyen bay: " + string(p->flight.flightID),
                                    "Khoang cach toi thieu giua 2 chuyen bay la 3h!");
                        PrintAdjustFlightDialog(flight);
                        continue;//white(true)
                    }

                    //hanh khach bi trung thoi gian bay
                    check = true;
                    string pass_id;
                    int numcol = plane_list.n[old_index]->SoDay,
                        numrow = plane_list.n[old_index]->SoDong;
                    for(int i = 0; i < numcol; i++){
                        for(int j = 0; j < numrow; j++){
                            if(strcmp(flight.ticket[i][j], "none") != 0){
                                p = flight_list;
                                while(p != NULL){
                                    //Tim trong tat cac cac chuyen bay co thoi gian bay chenh lech < 3h voi "thoi gian moi"
                                    if((p->flight.status == CONVE || p->flight.status == HETVE) && 
                                        (abs(p->flight.date - newflight.date) < 3*60) && (strcmp(p->flight.flightID, flight.flightID) != 0))
                                    {
                                        int index = SerchPlane(plane_list, p->flight.planeID);
                                        if(index == -1) continue;  //while(p!=NULL)
                                        int c = plane_list.n[index]->SoDay,  //column
                                            r = plane_list.n[index]->SoDong; //row
                                        for(int a = 0; a < c; a++){ 
                                            for(int b = 0; b < r; b++){
                                                if(strcmp(p->flight.ticket[a][b], flight.ticket[i][j]) == 0){
                                                    pass_id = string(flight.ticket[i][j]);
                                                    check = false;
                                                    break;//for(b)
                                                }     
                                            }
                                            if(!check) break;//for(a)
                                        }
                                            
                                    }
                                    if(!check) break;//while(p!=NULL)
                                    p = p->next;
                                }
                            }
                            if(!check) break;//for(j)
                        }//end for(j)
                        if(!check) break;//for(i)

                    }//end for(i)

                    if(!check){
                        Notification("Hanh khach ma so: " + pass_id +  " trong chuyen bay nay",
                                     "Da dat ve trong  chuyen bay: " + string(p->flight.flightID),
                                     "Luc: " + p->flight.date.to_string());
                        PrintAdjustFlightDialog(flight);
                        continue;//white(true)
                    }

                }//end if(change date)

                

                //=============== Xac nhan thay doi
                if(Confirm("Ban co xac nhan thay doi ?")){
                    
                    if(change_plane){
                        strcpy(flight.planeID, newflight.planeID);
                        //Neu thay doi kich thuoc may bay
                        if( (plane_list.n[new_index]->SoDay != plane_list.n[old_index]->SoDay)||
                            (plane_list.n[new_index]->SoDong != plane_list.n[old_index]->SoDong ))
                        {   

                            //Tao danh sach ve moi
                            char ***newticket = newTicket(plane_list.n[new_index]->SoDay, plane_list.n[new_index]->SoDong);

                            //Copy thong tin danh sach ve cu vao
                            for (int i = 0; i < plane_list.n[old_index]->SoDay; i++)
                                for(int j = 0; j < plane_list.n[old_index]->SoDong; j++)
                                    strcpy(newticket[i][j], flight.ticket[i][j]);
                                    
                            //xoa danh sach ve cu
                            deleteTicket(flight.ticket, plane_list.n[old_index]->SoDay, plane_list.n[old_index]->SoDong);

                            //Gan ticket moi
                            flight.ticket = newticket;
                            
                            //cap nhat status
                            if(flight.status == HETVE)
                                flight.status = CONVE;
                            
                        }
                    }

                    if(change_date){
                        flight.date = newflight.date;
                    }
                    
                    if(change_arrive){
                        strcpy(flight.arrive, InsertFlightBox[ARRIVE].getcontent().c_str());
                    }
                    
                    Notification("Thay doi thanh cong!");
                    break;//while(true)
                }else{
                    PrintAdjustFlightDialog(flight);
                    continue;//white(true)
                }
            }

            //an nut cancel
            if(cancel_button.inside(mx, my)){
                if(Confirm("Ban co xac nhan thoat?")){
                    change_plane = false,
                    change_date = false,
                    change_arrive = false;
                    break;//while(true)
                }else{
                    PrintAdjustFlightDialog(flight);
                    continue;//while(true)
                }
            }

            //Nhap thong tin
            if(InsertFlightBox[PLANEID].inside(mx, my)){
                InsertFlightBox[PLANEID].Insert(Insert_number_and_capital_letter);
                if(strcmp(flight.planeID, InsertFlightBox[PLANEID].getcontent().c_str() ) == 0){
                    InsertFlightBox[PLANEID].setcontent("");
                    InsertFlightBox[PLANEID].print();
                }        
            }
                
            
            if(InsertFlightBox[HOUR].inside(mx, my)){
                InsertFlightBox[HOUR].Insert(Insert_hour);
                if(InsertFlightBox[HOUR].getcontent().size() == 0) continue;//while(true)
                if(flight.date.hour == stoi( InsertFlightBox[HOUR].getcontent())){
                    InsertFlightBox[HOUR].setcontent("");
                    InsertFlightBox[HOUR].print();
                }
            }
                

            if(InsertFlightBox[MINUTE].inside(mx, my)){
                InsertFlightBox[MINUTE].Insert(Insert_minute);
                if(InsertFlightBox[MINUTE].getcontent().size() == 0) continue;//while(true)
                if(flight.date.minute == stoi(InsertFlightBox[MINUTE].getcontent())){
                    InsertFlightBox[MINUTE].setcontent("");
                    InsertFlightBox[MINUTE].print();
                }
            }
                

            if(InsertFlightBox[DAY].inside(mx, my)){
                InsertFlightBox[DAY].Insert(Insert_day);
                if(InsertFlightBox[DAY].getcontent().size() == 0) continue;//while(true)
                if(flight.date.day == stoi(InsertFlightBox[DAY].getcontent())){
                    InsertFlightBox[DAY].setcontent("");
                    InsertFlightBox[DAY].print();
                }
            }
                

            if(InsertFlightBox[MONTH].inside(mx, my)){
                InsertFlightBox[MONTH].Insert(Insert_month);
                if(InsertFlightBox[MONTH].getcontent().size() == 0) continue;//while(true)
                if(flight.date.month == stoi(InsertFlightBox[MONTH].getcontent())){
                    InsertFlightBox[MONTH].setcontent("");
                    InsertFlightBox[MONTH].print();
                }
            }
                

            if(InsertFlightBox[YEAR].inside(mx, my)){
                InsertFlightBox[YEAR].Insert(Insert_number_only);
                if(InsertFlightBox[YEAR].getcontent().size() == 0) continue;//while(true)
                if(flight.date.year == stoi(InsertFlightBox[YEAR].getcontent())){
                    InsertFlightBox[YEAR].setcontent("");
                    InsertFlightBox[YEAR].print();
                }
            }
                
            
            if(InsertFlightBox[ARRIVE].inside(mx, my)){
                InsertFlightBox[ARRIVE].Insert(Insert_normal_text);
                if(strcmp(flight.arrive, InsertFlightBox[ARRIVE].getcontent().c_str()) == 0){
                    InsertFlightBox[ARRIVE].setcontent("");
                    InsertFlightBox[ARRIVE].print();
                }
            }
                
            
            if(choose_plane_button.inside(mx, my)){
                int k = ChoosePlane(plane_list);
                if(k != -1 && k!= old_index){
                    InsertFlightBox[PLANEID].setcontent(plane_list.n[k]->SoHieuMB);
                    InsertFlightBox[PLANEID].print();
                }
                PrintAdjustFlightDialog(flight);
            }

            //an nut reset
            if(reset_button.inside(mx, my)){
                reset_button.setstatus(NORMAL);
                for(int i = PLANEID; i < MAX_FLIGHT_FIELD; i++){
                    InsertFlightBox[i].setcontent("");
                }
                PrintAdjustFlightDialog(flight);
            }
            
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            //hover
            if(apply_button.inside(mx, my))
                apply_button.hover();
            else apply_button.unhover();

            if(cancel_button.inside(mx, my))
                cancel_button.hover();
            else cancel_button.unhover();

            if(choose_plane_button.inside(mx, my))
                choose_plane_button.hover();
            else choose_plane_button.unhover();

            if(reset_button.inside(mx, my))
                reset_button.hover();
            else reset_button.unhover();
        }
        delay(100);
    }
    
    apply_button.setstatus(NORMAL);
    cancel_button.setstatus(NORMAL);
    for(int i = PLANEID; i < MAX_FLIGHT_FIELD; i++)
        InsertFlightBox[i].setcontent("");
    InsertFlightBox[PLANEID].   settitle("MAX 15 ky tu");
    InsertFlightBox[HOUR].      settitle("hh");
    InsertFlightBox[MINUTE].    settitle("mm");
    InsertFlightBox[DAY].       settitle("dd");
    InsertFlightBox[MONTH].     settitle("mm");
    InsertFlightBox[YEAR].      settitle("yyyy");
    InsertFlightBox[ARRIVE].    settitle("MAX 30 ky tu");

    //Co thay doi => return true
    return (change_plane || change_date || change_arrive);
}

bool ManageBookingTicket(Flight &flight, PTR_FLIGHT flight_list, DSMayBay &plane_list, PNode *&root){
    int index, num_col, num_row, bookedticket = 0, start_col = 0, start_row = 0;
    index = SerchPlane(plane_list, flight.planeID);
    if(index == -1){
        Notification("Loi du lieu");
        return false;
    }
    num_col = plane_list.n[index]->SoDay;
    num_row = plane_list.n[index]->SoDong;
    for(int i = 0; i < num_col; i++)
        for(int j = 0; j < num_row; j++)
            if(strcmp(flight.ticket[i][j], "none") != 0)
                bookedticket++;

    PrintManageTicketDialog(flight);
    PrintSeat(flight, num_col, num_row, start_col, start_row);

    int mx, my;
    bool ischange = false;
    int i, j;//bien vong lap
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            //press backbutton
            if(back_button.inside(mx, my)){
                back_button.setstatus(NORMAL);
                return(ischange);
            }

            //An vao vi tri Seat
            bool choose_seat = false;
            for(i = 0; i < MAX_SEAT_COLUMN; i++){
                for(j = 0; j < MAX_SEAT_ROW; j++){
                    if(Seat[i][j].inside(mx, my) && Seat[i][j].isactive()){
                        choose_seat = true;
                        break;//for(j) 
                    }      
                }
                if(choose_seat) break;//for(i)
            }
            
            if(choose_seat){
                if(strcmp(flight.ticket[i + start_col][j + start_row], "none") == 0){
                    //Ve chua dat
                    if(Confirm("Ban co muon dat ve " + get_ticket_name(start_col + i,start_row +  j) + "?")){
                        //Dat ve
                        if(BookTicketForSeat(flight, i + start_col, j + start_row, flight_list, plane_list, root)){
                            ischange = true;
                            bookedticket++;
                            if(bookedticket == num_col*num_row) flight.status = HETVE;
                        }
                            
                    }
                    PrintManageTicketDialog(flight);
                    PrintSeat(flight, num_col, num_row, start_col, start_row);
                }
                else{
                    //ve da dat
                    if(Confirm("Ve " + get_ticket_name(i + start_col, j + start_row) + " da duoc dat",
                                "CCCD cua hanh khach: " + string(flight.ticket[i][j]), 
                                "Ban co muon huy khong?" ))
                    {
                        //Huy ve
                        ischange = true;
                        strcpy(flight.ticket[i][j], "none");
                        bookedticket --;
                        if(flight.status == HETVE)
                            flight.status = CONVE;
                        
                    }
                    PrintSeat(flight, num_col, num_row, start_col, start_row);
                }
            }
            

            //press buttonup/down/left/right
            if(up_button.inside(mx, my) && up_button.isactive()){
                start_row -= MAX_SEAT_ROW;
                PrintSeat(flight, num_col, num_row, start_col, start_row);
            }
            if(down_button.inside(mx, my) && down_button.isactive()){
                start_row += MAX_SEAT_ROW;
                PrintSeat(flight, num_col, num_row, start_col, start_row);
            }
            if(left_button.inside(mx, my) && left_button.isactive()){
                start_col -= MAX_SEAT_COLUMN;
                PrintSeat(flight, num_col, num_row, start_col, start_row);
            }
            if(right_button.inside(mx, my) && right_button.isactive()){
                start_row += MAX_SEAT_COLUMN;
                PrintSeat(flight, num_col, num_row, start_col, start_row);
            }

        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            for(i = 0; i < MAX_SEAT_COLUMN; i++)
                for(j = 0; j < MAX_SEAT_ROW; j++)
                    if(Seat[i][j].inside(mx, my))
                        Seat[i][j].hover();
                    else Seat[i][j].unhover();
            
            if(back_button.inside(mx, my))
                back_button.hover();
            else back_button.unhover();

            if(up_button.inside(mx, my))
                up_button.hover();
            else up_button.unhover();

            if(down_button.inside(mx, my))
                down_button.hover();
            else down_button.unhover();

            if(left_button.inside(mx, my))
                left_button.hover();
            else left_button.unhover();

            if(right_button.inside(mx, my))
                right_button.hover();
            right_button.unhover();
        }
        delay(100);
    }
}

bool BookTicketForSeat(Flight &flight, int column, int row, PTR_FLIGHT flight_list, DSMayBay &plane_list, PNode *&root){
    PrintBookingTicketDialog(get_ticket_name(column, row));
    
    int mx, my;
    int i, j;//bien vong lap
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);

            //press apply button
            if(mediumdialog::apply_button.inside(mx, my)){
                //=============== Check du lieu
                //Khong duoc de trong CCCD
                if(mediumdialog::InsertPassID.getcontent().size() == 0){
                    Notification("Khong duoc de trong CCCD");
                    PrintBookingTicketDialog(get_ticket_name(column, row));
                    continue;//while(1);
                }

                //CCCD phai du 12 so
                if(mediumdialog::InsertPassID.getcontent().size() != 12){
                    Notification("CCCD phai du 12 so");
                    PrintBookingTicketDialog(get_ticket_name(column, row));
                    continue;//while(1);
                }

                //CCCD phai ton tai, neu khong ton tai thi them vao
                PNode *node = search(root, mediumdialog::InsertPassID.getcontent_char());
                if(node == NULL){
                    if(Confirm("CCCD khong ton tai", "Ban co muon them hanh khach moi?")){
                        AddPassenger(root);
                        
                    }
                    PrintBookingTicketDialog(get_ticket_name(column, row));
                    continue;//while(1);

                }

                //Hanh khach khong duoc dat 2 ve tren 1 chuyen bay/dat 2 chuyen bay chenh lech < 3h
                    //cung chuyen bay khong duoc dat 2 ve
                    int index = SerchPlane(plane_list, flight.planeID);
                    if(index == -1){
                        Notification("Loi du lieu!");
                        return false;
                    }
                    bool check = true;
                    for(i = 0; i < plane_list.n[index]->SoDay; i++){
                        for(j = 0; j < plane_list.n[index]->SoDong; j++){
                            if(strcmp(flight.ticket[i][j], mediumdialog::InsertPassID.getcontent().c_str()) == 0){
                                check = false;
                                break;//for(j)
                            }
                        }
                        if(!check) break;//for(i)
                    }
                    if(!check){
                        Notification("Hanh khach da dat ve trong chuyen bay nay!", "Ma ve: " + get_ticket_name(i, j));
                        PrintBookingTicketDialog(get_ticket_name(column, row));
                        continue;//while(1);
                    }
                        
                    
                    //khong duoc dat chuyen bay khach chenh lech < 3h
                    check = true;
                    PTR_FLIGHT p = flight_list;
                    while(p != NULL){
                        if(abs(p->flight.date - flight.date) < 3*60){
                            if((p->flight.status == CONVE || p->flight.status == HETVE) && (strcmp(p->flight.flightID, flight.flightID)!=0)){
                                int k = SerchPlane(plane_list, p->flight.planeID);
                                if(k == -1) continue;
                                int col = plane_list.n[k]->SoDay,
                                    row = plane_list.n[k]->SoDong;
                                for(i = 0; i < col; i++){
                                    for(j = 0; j < row; j++){
                                        if(strcmp(p->flight.ticket[i][j], mediumdialog::InsertPassID.getcontent().c_str()) == 0){
                                            check = false;
                                            break;//for(j)
                                        }
                                    }
                                    if(!check) break;//for(i)
                                }
                            }
                        }
                        if(!check) break;//while(p!=null)
                        p = p->next;
                    }
                    if(!check){
                        Notification("Hanh khach da dat ve trong chuyen bay: " + string(p->flight.flightID),
                                    "Luc: " + p->flight.date.to_string());
                        PrintBookingTicketDialog(get_ticket_name(column, row));
                        continue;//while(1);
                    }

                //=============== Xac nhan dat ve
                if(Confirm("Ban co xac nhan dat ve?")){
                    //book ve
                    strcpy(flight.ticket[column][row], mediumdialog::InsertPassID.getcontent_char());
                    Notification("Dat ve thanh cong!");
                    mediumdialog::InsertPassID.setcontent("");
                    return true;;
                }
                PrintBookingTicketDialog(get_ticket_name(column, row));
            }
            //press cancel button
            if(mediumdialog::cancel_button.inside(mx, my)){
                mediumdialog::cancel_button.setstatus(NORMAL);
                if(Confirm("Ban co xac nhan thoat?")){
                    mediumdialog::InsertPassID.setcontent("");
                    return false;
                }
                    
                PrintBookingTicketDialog(get_ticket_name(column, row));
            }

            //Nhap du lieu
            if(mediumdialog::InsertPassID.inside(mx, my))
                mediumdialog::InsertPassID.Insert(Insert_number_only);
            if(mediumdialog::choose_passenger_button.inside(mx, my)){
                Passenger *ptr = ChoosePassenger(root);
                if(ptr != NULL)
                    mediumdialog::InsertPassID.setcontent(ptr->getCccd());

                rounded_bar(bigdialog::x, bigdialog::y, bigdialog::width, bigdialog::height, WHITE);
                rounded_rect(bigdialog::x, bigdialog::y, bigdialog::width, bigdialog::height, WHITE);
                PrintBookingTicketDialog(get_ticket_name(column, row));
            }
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(mediumdialog::choose_passenger_button.inside(mx, my))
                mediumdialog::choose_passenger_button.hover();
            else mediumdialog::choose_passenger_button.unhover();

            if(mediumdialog::apply_button.inside(mx, my))
                mediumdialog::apply_button.hover();
            else mediumdialog::apply_button.unhover();

            if(mediumdialog::cancel_button.inside(mx, my))
                mediumdialog::cancel_button.hover();
            else mediumdialog::cancel_button.unhover();
        }
        delay(100);
    }
    return false;
}

void AddPassenger(PNode *&root){
    PrintAddPassengerDialog();
    mediumdialog::InsertFirstname.setcontent("");
    mediumdialog::InsertLastname.setcontent("");
    mediumdialog::male.setclick(false);
    mediumdialog::female.setclick(false);

    int mx, my;
    Passenger newpassenger;
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            //press apply button
            if(mediumdialog::apply_button.inside(mx, my)){
                //=============== check du lieu
                //Khong duoc de trong thong tin
                if(mediumdialog::InsertPassID.getcontent().size() == 0){
                    Notification("Khong duoc de trong CCCD!");
                    PrintAddPassengerDialog();
                    continue;//while(true)
                }
                if(mediumdialog::InsertPassID.getcontent().size() != 12){
                    Notification("CCCD phai co 12 chu so!");
                    PrintAddPassengerDialog();
                    continue;//while(true)
                }
                if(mediumdialog::InsertFirstname.getcontent().size() == 0){
                    Notification("Khong duoc de trong ho");
                    PrintAddPassengerDialog();
                    continue;//while(true)
                }
                if(mediumdialog::InsertLastname.getcontent().size() == 0){
                    Notification("Khong duoc de trong ten");
                    PrintAddPassengerDialog();
                    continue;//while(true)
                }
                if(!mediumdialog::female.isclicked() && !mediumdialog::male.isclicked()){
                    Notification("Chua ghi nhan gioi tinh!");
                    PrintAddPassengerDialog();
                    continue;//while(true)
                }

                //CCCD khong duoc trung
                if(search(root, mediumdialog::InsertPassID.getcontent_char()) != NULL){
                    Notification("CCCD da ton tai");
                    PrintAddPassengerDialog();
                    continue;//while(true)
                }

                //=============== Load du lieu vao newpassenger
                newpassenger.setCccd(mediumdialog::InsertPassID.getcontent_char());
                newpassenger.setHo(mediumdialog::InsertFirstname.getcontent_char());
                newpassenger.setTen(mediumdialog::InsertLastname.getcontent_char());
                if(mediumdialog::male.isclicked())
                    newpassenger.setSex("Nam");
                else 
                    newpassenger.setSex("Nu");
                //=============== xac nhan them hanh khach
                if(Confirm("Ban co xac nhan them hanh khach")){
                    root = insert(root, NULL, newpassenger);
                    saveData(root);
                    Notification("Them thanh cong!");
                    break;
                }else{
                    PrintAddPassengerDialog();
                    continue;//while(true)
                }
            }

            //press cancel button
            if(mediumdialog::cancel_button.inside(mx, my)){
                
                if(Confirm("Ban co xac nhan thoat?")){
                    break;
                }
                PrintAddPassengerDialog();
            }

            //nhap du lieu
            if(mediumdialog::InsertPassID.inside(mx, my))
            mediumdialog::InsertPassID.Insert(Insert_number_only);

            if(mediumdialog::InsertFirstname.inside(mx, my))
                mediumdialog::InsertFirstname.Insert(Insert_firstname);
            
            if(mediumdialog::InsertLastname.inside(mx, my))
                mediumdialog::InsertLastname.Insert(Insert_lastname);
            
            if(mediumdialog::male.inside(mx, my)){
                mediumdialog::male.click();
                if(mediumdialog::male.isclicked() && mediumdialog::female.isclicked()){
                    mediumdialog::female.click();
                }
            }

            if(mediumdialog::female.inside(mx, my)){
                mediumdialog::female.click();
                if(mediumdialog::male.isclicked() && mediumdialog::female.isclicked()){
                    mediumdialog::male.click();
                }
            }

        }
        if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(mediumdialog::apply_button.inside(mx, my))
                mediumdialog::apply_button.hover();
            else mediumdialog::apply_button.unhover();

            if(mediumdialog::cancel_button.inside(mx, my))
                mediumdialog::cancel_button.hover();
            else mediumdialog::cancel_button.unhover();
        }
        delay(100);
    }
}

void ShowPassengerList(Flight flight, DSMayBay &plane_list, PNode *root){
    int index = SerchPlane(plane_list, flight.planeID);
    if(index == -1){
        Notification("Loi du lieu", "Khong tim thay may bay tuong ung");
        return ;
    }

    int num_col = plane_list.n[index]->SoDay,
        num_row = plane_list.n[index]->SoDong,
        bookedticket = 0;
    //Tinh so ve da dat
    for(int i = 0; i < num_col; i++){
        for(int j = 0; j < num_row; j++){
            if(strcmp(flight.ticket[i][j], "none") != 0)
                bookedticket ++;
        }
    }

    //Cap phat dong
    Passenger **pass_arr = new Passenger*[bookedticket];
    string *ticketname = new string[bookedticket];
    //Loc danh sach hanh khach vao mang tam
    int n = 0;
    for(int i = 0; i < num_col; i++){
        for(int j = 0; j < num_row; j++){
            if(strcmp(flight.ticket[i][j], "none") != 0){
                PNode *p = search(root, flight.ticket[i][j]);
                if(p == NULL){
                    Notification("Loi du lieu", "Khong tim thay hanh khach co CCCD: ", string(flight.ticket[i][j]));
                    return;
                }
                pass_arr[n] = &(p->pas);
                ticketname[n] = get_ticket_name(i, j);
                n++;
            }   
        }
    }
    //In
    print_workspace();
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    setcolor(BLACK);
    setbkcolor(WORKSPACE_COLOR);
    settextstyle(3, HORIZ_DIR, 1);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    outtextxy(WORKSPACE_X + WORKSPACE_WIDTH/2, WORKSPACE_Y + 20, "DANH SACH HANH KHACH THUOC CHUYEN BAY:  " + string(flight.flightID));
    outtextxy(WORKSPACE_X + WORKSPACE_WIDTH/2, WORKSPACE_Y + 50, "Ngay khoi hanh: " + flight.date.to_string() + "    Noi den: " + string(flight.arrive));
    settextstyle(2, HORIZ_DIR, 5);
    settextjustify(LEFT_TEXT, TOP_TEXT);
    outtextxy(WORKSPACE_X + 50, WORKSPACE_Y + 70, "Da dat: " + to_string(n) + "/" + to_string(num_col*num_row) + " ve");
    back_button.print();


    int start_pass = 0;
    PrintPassengerTable(pass_arr, ticketname, n, start_pass);
    int mx, my;
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(back_button.inside(mx, my)){
                back_button.setstatus(NORMAL);
                break;
            }
            
            if(prev_page_button.inside(mx, my) && prev_page_button.isactive()){
                start_pass -= (PassengerTable.getnumrow() - 1);
                PrintPassengerTable(pass_arr, ticketname, n, start_pass);
            }

            if(next_page_button.inside(mx, my) && next_page_button.isactive()){
                start_pass += (PassengerTable.getnumrow() - 1);
                PrintPassengerTable(pass_arr, ticketname, n, start_pass);
            }

        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            if(back_button.inside(mx, my))
                back_button.hover();
            else back_button.unhover();

            if(next_page_button.inside(mx, my))
                next_page_button.hover();
            else next_page_button.unhover();

            if(prev_page_button.inside(mx, my))
                prev_page_button.hover();
            else prev_page_button.unhover();
        }
        delay(100);
    }

    //Xoa bo nho
    delete []pass_arr;
    delete [] ticketname;
    setgraphicsettings(&currentsettings);

}
