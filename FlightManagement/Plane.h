/*
-Tui coppy struct va cac ham load file trong file AD.H qua day
-File nay co bo sung ham  "int SerchPlane(DSMayBay &ds, char* planeid)"
*/
#pragma once
#include <iostream>
#include <iomanip> 
#include <windows.h>
#include <fstream>
#define MAX 300 
#define MaMayBay 15
#define LoaiMayBay 40 
using namespace std;

struct MayBay {
    char SoHieuMB[MaMayBay+1];
    char LoaiMB[LoaiMayBay+1];
    int SoDay;
    int SoDong; 
};

struct DSMayBay{
	MayBay* n [MAX];
	int SoMayBay=0; 
}; 

int SerchPlane(DSMayBay &ds, char* planeid){
    int index = -1;
    for(int i = 0; i < ds.SoMayBay; i++){
        if(strcmp(ds.n[i]->SoHieuMB, planeid) == 0){
            index = i;
            break;
        }
    }
    return index;
}

int readfile(DSMayBay &c) {
    ifstream f("Data\\Planes.txt");
    if (!f.is_open()) {
        cout << "Khong the mo file" << endl;
        return 0;
    }

    string line;
    while (getline(f, line)) {
        MayBay *newMayBay = new MayBay;
        sscanf(line.c_str(), "%[^|]|%[^|]|%d|%d", newMayBay->SoHieuMB, newMayBay->LoaiMB, &newMayBay->SoDong, &newMayBay->SoDay);
        for(int i=0;i<c.SoMayBay;i++){
        	if(strcmp(newMayBay->SoHieuMB,c.n[i]->SoHieuMB)==0){
        		cout<<"Load file may bay khong thanh cong!"<<endl;
        		return 0;
			}
		}
        c.n[c.SoMayBay++] = newMayBay;
    }
    f.close();
}

void savedata(DSMayBay &c) {
    ofstream f("Data\\Planes.txt");
    if (!f.is_open()) {
        cout << "Khong the mo file" << endl;
        return;
    }
    for(int i = 0; i < c.SoMayBay; i++) {
        f << c.n[i]->SoHieuMB << "|" << c.n[i]->LoaiMB << "|" << c.n[i]->SoDong << "|" << c.n[i]->SoDay << "\n";
    }
    f.close();
}

void freeing_plane(DSMayBay &c){
	for(int i=0;i<c.SoMayBay;i++){
		delete c.n[i]; 
		c.n[i]==nullptr; 
	} 
	c.SoMayBay=0;
	cout<<"Giai phong bo nho may bay hoan tat!"<<endl; 
}