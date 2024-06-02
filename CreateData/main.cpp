#include"E:\\DoAnCTDL_Nhom12\\FlightManagement\\Plane.h"
#include"E:\\DoAnCTDL_Nhom12\\FlightManagement\\Flight.h"
#include"CreatePassenger.h"
#include"CreatePlane.h"
#include"CreateFlight.h"

#include<iostream>
using namespace std;
void print_pas(PNode *root){
    if(root != NULL){
        print_pas(root->left);
        cout << root->pas.getCccd() << endl
             << "\t"<< root->pas.getHo() << "-" << root->pas.getTen() << "-" << root->pas.getSex() << endl << endl;
        print_pas(root->right);
    }
}
int main(){    
    system("cls");
    srand(time(0)); 
    DSMayBay plane_list;
    PTR_FLIGHT flight_list = NULL; 
    PNode *root = NULL;
      
    //Create data
    CreatePlane(plane_list, 29);
    CreateFlight(flight_list, plane_list, 20);
    root = CreatePassenger(100); 
      
	 
    //Save data 
    save_flight_to_file("Data\\Flights.dat", flight_list, plane_list);
    freeing_flight_memory(flight_list, plane_list);
    savedata(plane_list);
    saveData(root);

      
    PNode **list, *load;
    loadData(load, list);
    
    cout << "test lai du lieu hanh khach trong ram" << endl << endl;
    print_pas(load);
    cout << "so sanh voi du lieu truoc khi save" << endl;
    print_pas(root);

    cout << "OK" << endl;
    return 0;
}




