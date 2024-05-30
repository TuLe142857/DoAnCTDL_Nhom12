#pragma once

#include"Date.h"
#include"Plane.h"

#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;

#define MAX_FLIGHT_ID 15
#define MAX_PLANE_ID 15
#define MAX_ARRIVE 30
#define MAX_PASSENGERID 12

//=============== STRUCT ==========================

enum FLIGHT_STATUS{HUYCHUYEN, CONVE, HETVE, HOANTAT};
struct Flight{
    char flightID[MAX_FLIGHT_ID+1];   // key
    char planeID[MAX_PLANE_ID+1];
    Date date;
    char arrive[MAX_ARRIVE+1];
    int status = CONVE;

    //ticket[day][dong] (ticket[column][row])
    //ve [i][j] chua dat => ticket[i][j] = "none"
    char ***ticket;
};

//ds lien ket don tang dan theo key
struct FlightNode{
    Flight flight;
    FlightNode *next = NULL;
};
typedef FlightNode* PTR_FLIGHT;

//============ FUNTION PROTOTYPE =================

PTR_FLIGHT newFlightNode();
PTR_FLIGHT newFlightNode(Flight flight);

int CountFlight(PTR_FLIGHT First);
void InsertOrder(PTR_FLIGHT &First, Flight flight);
PTR_FLIGHT SerchFlight(PTR_FLIGHT First, char *flightID);

string get_column_name(int column);
string get_ticket_name(int column, int row);

bool load_flight_from_file(string file_path, PTR_FLIGHT &flight_list, DSMayBay &plane_list);
bool save_flight_to_file(string file_path, PTR_FLIGHT flight_list, DSMayBay &plane_list);

bool freeing_ticket_memory(Flight &flight, DSMayBay &plane_list);
bool freeing_flight_memory(PTR_FLIGHT &flight_list, DSMayBay &plane_list);

//============ FUNCTION DEFINITION ===============

PTR_FLIGHT newFlightNode(){
    PTR_FLIGHT newnode = new FlightNode;
    newnode->next = NULL;
    return newnode;
}

PTR_FLIGHT newFlightNode(Flight flight){
    PTR_FLIGHT newnode = new FlightNode;
    newnode->flight = flight;
    newnode->next = NULL;
    return newnode;
}

int CountFlight(PTR_FLIGHT First){
    int count = 0;
    PTR_FLIGHT p = First;
    while(p != NULL){
        p = p->next;
        count ++;
    }
    return count;
}

void InsertOrder(PTR_FLIGHT &First, Flight flight){

    PTR_FLIGHT newnode = newFlightNode(flight),
               prev_node = NULL,
               next_node = First;

    //Vi danh sach tang dan theo flight ID nen stop khi next_node == NULL || next_node.flightID >= newnode.flightID
    while( next_node != NULL && (strcmp(next_node->flight.flightID, newnode->flight.flightID) < 0)){
        prev_node = next_node;
        next_node = next_node->next;
    }

    //Insert
    if(next_node == First){
        //prev_node == NULL
        newnode->next = First;
        First = newnode;
    }else{
        //prev_node != NULL
        prev_node->next = newnode;
        newnode->next = next_node;
    }
    
}

PTR_FLIGHT SerchFlight(PTR_FLIGHT First, char *flightID){
    PTR_FLIGHT p = First;

    //list tang dan theo flightID nen stop khi (p ==NULL || p.id >= flight ID)
    while(p != NULL && (strcmp(p->flight.flightID, flightID) < 0) ){
        p = p->next;
    }

    if(p == NULL) return NULL;
    if(strcmp(p->flight.flightID, flightID) == 0) return p;
    return NULL;
}

//{0, 1, 2, ... 25} => 'A', 'B', 'C', ... 'Z'
// 26, 27, ... => 'AA', 'AB' , ...
string get_column_name(int column){
    string s = "";
    while(column >= 0){
        s = char('A' + column%26) + s;
        column = (column/26) - 1;
    }
    return s;
}

string get_ticket_name(int column, int row){
    return get_column_name(column) + to_string(row+1);
}

bool load_flight_from_file(string file_path, PTR_FLIGHT &flight_list, DSMayBay &plane_list){
    cout << "==============================================================================================" << endl
         << "\t\t\tLoad danh sach chuyen bay tu file: " << file_path << endl;

    fstream file(file_path, ios::in | ios::binary);
    if(!file){
        cout << "\tKhong mo duoc file" << endl
             << "\t\t\tLoad danh sach chuyen bay that bai !" << endl
             << "==============================================================================================" << endl << endl;
        return false;
    }
    
    //Vi trong file da co san thu tu nen khong can insert order
    //De bo qua truong hop insert first, dung node fake_first => insert last
    PTR_FLIGHT fake_first = newFlightNode();
    PTR_FLIGHT lastnode = fake_first;

    Flight record;                  //bien doc file

    int index, num_col, num_row,    //index: chi so may bay tuong ung; 
        count = 0,                  //dem so chuyen bay doc duoc
        i, j;                       //bien vong lap for
    Date now = today();

    while(file.read(reinterpret_cast<char*>(&record), sizeof(Flight))){
        //check du lieu co khop voi planelist khong
        index = SerchPlane(plane_list, record.planeID);
        if(index == -1){
            cout << "Loi: Khong tim thay may bay ma so: " << record.planeID 
                 << " tuong ung voi chuyen bay: " << record.flightID << endl
                 << "\t\t\tLoad danh sach chuyen bay that bai !" << endl
                 << "==============================================================================================" << endl << endl;
            return false;  
        }

        //Neu da qua thoi gian khoi hanh && status == CONVE || status == HETVE thi status = HOANTAT
        if((record.date < now) && (record.status == CONVE || record.status == HETVE))
            record.status = HOANTAT;

        //doc danh sach ve
        num_col = plane_list.n[index]->SoDay;
        num_row = plane_list.n[index]->SoDong;

        record.ticket = new char**[num_col];
        for(i = 0; i < num_col; i++){
            record.ticket[i] = new char*[num_row];
            for(j = 0; j < num_row; j++){
                record.ticket[i][j] = new char[MAX_PASSENGERID + 1];
                file.read(record.ticket[i][j], sizeof(char)*(MAX_PASSENGERID + 1));
            }
        }

        //insert
        PTR_FLIGHT newnode = newFlightNode(record);
        lastnode->next = newnode;
        lastnode = lastnode->next;
        
        //in ra man hinh de check
        cout << newnode->flight.flightID << "-" 
             << newnode->flight.date.to_string() << "-" 
             << newnode->flight.planeID << "-" 
             << newnode->flight.status << endl;
        
        count ++;
    }

    flight_list = fake_first->next;
    delete fake_first;

    cout << "\t\t\tLoad danh sach chuyen bay thanh cong!(load duoc: " << count << " chuyen bay)" << endl
         << "==============================================================================================" << endl << endl;
    file.close();
    return true;
}

bool save_flight_to_file(string file_path, PTR_FLIGHT flight_list, DSMayBay &plane_list){
    cout << "==============================================================================================" << endl
         << "\t\t\tLuu danh sach chuyen bay vao file: " << file_path << endl;

    fstream file(file_path, ios::out | ios::binary);
    if(!file){
        cout << "\tKhong mo duoc file!" << endl
             << "\t\t\tLuu danh sach chuyen bay thai bai!" << endl
             << "==============================================================================================" << endl << endl;
        return false;
    }

    PTR_FLIGHT p = flight_list;
    int count = 0, 
        index, num_col, num_row, 
        i, j;
    while(p != NULL){
        index = SerchPlane(plane_list, p->flight.planeID);
        if(index == -1){
            cout << "Loi: Khong tim thay may bay ma so: " << p->flight.planeID 
                 << " tuong ung voi chuyen bay: " << p->flight.flightID << endl 
                 << "\t\t\tLuu danh sach chuyen bay thai bai!" << endl
                 << "==============================================================================================" << endl << endl;
            return false;
        }

        //Luu struct flight
        file.write(reinterpret_cast<char*>(&(p->flight)), sizeof(Flight));

        //Luu ticket[][]
        num_col = plane_list.n[index]->SoDay;
        num_row = plane_list.n[index]->SoDong;
        for(i = 0; i < num_col; i++)
            for(j = 0; j < num_row; j++)    
                file.write(p->flight.ticket[i][j], sizeof(char)*(MAX_PASSENGERID + 1));

        //In ra man hinh de check
        cout << p->flight.flightID << "-" 
             << p->flight.date.to_string() << "-" 
             << p->flight.planeID << "-" 
             << p->flight.status << endl;
        count ++;
        p = p->next;
    }

    cout << "\t\t\tLuu danh sach chuyen bay thanh cong!(Luu duoc " << count << " chuyen bay)" << endl
         << "==============================================================================================" << endl << endl;
    file.close();
    return true;
}

bool freeing_ticket_memory(Flight &flight, DSMayBay &plane_list){
    int index = SerchPlane(plane_list, flight.planeID);
    if(index == -1){
        return false;
    }

    int num_col = plane_list.n[index]->SoDay,
        num_row = plane_list.n[index]->SoDong;
    for(int i = 0; i < num_col; i++){
        for(int j = 0; j < num_row; j++){
            delete[] flight.ticket[i][j];
        }
        delete[] flight.ticket[i];
    }
    delete[] flight.ticket;

    return true;
}

bool freeing_flight_memory(PTR_FLIGHT &flight_list, DSMayBay &plane_list){
    cout << "==============================================================================================" << endl
         << "\t\t\tGiai phong bo nho danh sach chuyen bay" << endl;
    PTR_FLIGHT p = flight_list,
               q;

    while(p != NULL){
        q = p;
        p = p->next;

        if(!freeing_ticket_memory(q->flight, plane_list)){
            cout << "Loi khi giai phong bo nho danh sach ve: "
                 << "Khong tim thay may bay ma so: " << q->flight.planeID 
                 << " tuong ung voi chuyen bay: " << q->flight.flightID << endl   
                 << "\t\t\tGiai phong bo nho danh sach chuyen bay thai bai!" << endl
                 << "==============================================================================================" << endl << endl;
            return false; 
        }

        delete q;
    }

    cout << "\t\t\tGiai phong bo nho danh sach chuyen bay thanh cong!" << endl
         << "==============================================================================================" << endl << endl;
    return true;
}