#pragma once
#include"Random.h"
#include"E:\\DoAnCTDL_Nhom12\\FlightManagement\\Flight.h"

void CreateFlight(PTR_FLIGHT &flight_list, DSMayBay &plane_list, int n){
    Flight flight;
    int index; //plane index
    Date date(00, 6, 1, 1, 2024);
    for(int i =0; i < n; i++){ 
        //flight ID 
        string id = "CB" + to_string(i+1);
        strcpy(flight.flightID, id.c_str());

        //date
        flight.date = date;
        date += 3*60;

        //arrive
        string arrive = (rand()%2 == 0) ? ("Ha Noi") : ("TP Ho Chi Minh");
        strcpy(flight.arrive, arrive.c_str());

        //status
        flight.status = CONVE;

        //plane ID && ticket
        index = random(0, plane_list.SoMayBay - 1);
        strcpy(flight.planeID, plane_list.n[index]->SoHieuMB);

        int numcol = plane_list.n[index]->SoDay,
            numrow = plane_list.n[index]->SoDong;
        flight.ticket = new char**[numcol];
        for(int j = 0; j < numcol; j++){
            flight.ticket[j] = new char*[numrow];
            for(int k = 0; k < numrow; k++){
                flight.ticket[j][k] = new char[MAX_PASSENGERID + 1];
                strcpy(flight.ticket[j][k], "none");
            }
        }

        //Insert
        InsertOrder(flight_list, flight);
    }
}