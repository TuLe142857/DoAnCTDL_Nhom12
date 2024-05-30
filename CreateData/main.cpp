#include"E:\\DoAnCTDL_Nhom12\\FlightManagement\\Plane.h"
#include"E:\\DoAnCTDL_Nhom12\\FlightManagement\\Flight.h"
#include"CreatePassenger.h"
#include"CreatePlane.h"
#include"CreateFlight.h"

#include<iostream>
using namespace std;

int main(){    
    system("cls");
    srand(time(0));
    DSMayBay plane_list;
    PTR_FLIGHT flight_list = NULL; 
    PNode *root;
    
    //Create data
    CreatePlane(plane_list, 29);
    CreateFlight(flight_list, plane_list, 20);
    //CreatePassenger(root, 10); 
	
    //Save data
    save_flight_to_file("Data\\Flights.dat", flight_list, plane_list);
    freeing_flight_memory(flight_list, plane_list);
    savedata(plane_list);
    //...save passenger

    cout << "OK" << endl;
    return 0;
}




