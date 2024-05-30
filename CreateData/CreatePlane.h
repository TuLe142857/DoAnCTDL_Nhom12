#pragma once
#include"Random.h"
#include"E:\\DoAnCTDL_Nhom12\\FlightManagement\\Plane.h"

string PlaneType[] = {"BOEING123", "BOEING456", "BOEING789", "AIRBUS123", "AIRBUS456", "AIRBUS789"};
void CreatePlane(DSMayBay &plane_list, int n){
    if(!(n > 0 && n <= MAX)) return;
    plane_list.SoMayBay = n;
    
    for(int i = 0; i < n; i++){
        plane_list.n[i] = new MayBay;

        //id
        string id = "MB" + to_string(i+1);
        strcpy(plane_list.n[i]->SoHieuMB, id.c_str());

        //type
        int k = random(0, (sizeof(PlaneType)/sizeof(string) - 1));
        strcpy(plane_list.n[i]->LoaiMB, PlaneType[k].c_str());

        //kich thuoc
        plane_list.n[i]->SoDay = random(10, 20);
        plane_list.n[i]->SoDong = random(10, 20);
    }
}