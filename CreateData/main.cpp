#include"..\\FlightManagement\\Plane.h"
#include"..\\FlightManagement\\Flight.h"
#include"CreatePassenger.h"
#include"CreatePlane.h"
#include"CreateFlight.h"
#include<windows.h>
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
    //Tao folder(code tao folde loot tren chatCPT :)) )
    LPCWSTR folderName = L"Data";
    if (!(CreateDirectoryW(folderName, NULL) || ERROR_ALREADY_EXISTS == GetLastError())) {
        cout << "Tao folder loi!" << endl;
        return 0;
    }
        
	//Tao file
	fstream file1("Data\\Flights.dat", ios::out);
	fstream file2("Data\\Planes.txt", ios::out);
	fstream file3("Data\\Passengers.dat", ios::out);
	if(!(file1 && file2 && file3)){
		cout << "Error creating file" << endl;
		return 0;
	}
	file1.close();
	file2.close();
	file3.close();    
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
    
    system("pause");
    return 0;
}




