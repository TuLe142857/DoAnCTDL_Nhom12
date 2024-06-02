#pragma once

#include"Flight.h"

enum SORTTYPE{INCREASE, DECREASE};
enum SORTBY{SORTBY_DATE, SORTBY_FLIGHTID, SORTBY_PLANEID, SORTBY_ARRIVE};

void reverse_arr(Flight **arr, int n);

void QuickSortFlight(Flight**arr, int n, int sortby, int sorttype);

//date incre
void QuickSortFlight_byDate_Incre(Flight**arr, int low, int high);
//data decre
void QuickSortFlight_byDate_Decre(Flight**arr, int low, int high);

//flightid incre
void QuickSortFlight_byFID_Incre(Flight**arr, int low, int high);
//flightid decre
void QuickSortFlight_byFID_Decre(Flight**arr, int low, int high);

//planeid incre
void QuickSortFlight_byPLID_Incre(Flight**arr, int low, int high);

//planeid decre
void QuickSortFlight_byPLID_Decre(Flight**arr, int low, int high);

//arrive incre
void QuickSortFlight_byAR_Incre(Flight**arr, int low, int high);
//arrive decre
void QuickSortFlight_byAR_Decre(Flight**arr, int low, int high);

// //================================================================
void reverse_arr(Flight **arr, int n){
    if(n <= 0) return;
    int i = 0, j = n-1;
    Flight *temp;
    while(i < j){
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

void QuickSortFlight(Flight**arr, int n, int sortby, int sorttype){
    if(n <= 0) return ;
    switch(sortby){
        case SORTBY_DATE:{
            cout << "sdate";
            if(sorttype == INCREASE)
                QuickSortFlight_byDate_Incre(arr, 0, n-1);
            else    
                QuickSortFlight_byDate_Decre(arr, 0, n-1);
            break;
        }
        case SORTBY_FLIGHTID:{
            cout << "sfli";
            if(sorttype == INCREASE)
                QuickSortFlight_byFID_Incre(arr, 0, n-1);
            else    
                QuickSortFlight_byFID_Decre(arr, 0, n-1);
            break;
        }
        //SORTBY_DATE, SORTBY_FLIGHTID, SORTBY_PLANEID, SORTBY_ARRIVE
        case SORTBY_PLANEID:{
            cout << "spl";
            if(sorttype == INCREASE){
                cout << "-incr";
                QuickSortFlight_byPLID_Incre(arr, 0, n-1);
            }
                
            else
                QuickSortFlight_byPLID_Decre(arr, 0, n-1);
            break;
        }
        case SORTBY_ARRIVE:{
            cout << "sar";
            if(sorttype == INCREASE)
                QuickSortFlight_byAR_Incre(arr, 0, n-1);
            else
                QuickSortFlight_byAR_Decre(arr, 0, n-1);
            break;
        }
    }
}

void QuickSortFlight_byDate_Incre(Flight**arr, int low, int high){
    int i = low, j = high;
    Date pivot = arr[(i+j)/2]->date;
    Flight* temp;

    do{
        while(arr[i]->date < pivot) i++;
        while(arr[j]->date > pivot) j--;
        if(i <= j){
            //swap dia chi
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }while(i <= j);
    if(j > low && j != high) QuickSortFlight_byDate_Incre(arr, low, j);
    if(i < high && i != low) QuickSortFlight_byDate_Incre(arr, i, high);
}

void QuickSortFlight_byDate_Decre(Flight**arr, int low, int high){
    int i = low, j = high;
    Date pivot = arr[(i+j)/2]->date;
    Flight* temp;

    do{
        while(arr[i]->date > pivot) i++;
        while(arr[j]->date < pivot) j--;
        if(i <= j){
            //swap dia chi
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }while(i <= j);
    if(j > low && j != high) QuickSortFlight_byDate_Decre(arr, low, j);
    if(i < high && i != low) QuickSortFlight_byDate_Decre(arr, i, high);
}

void QuickSortFlight_byFID_Incre(Flight**arr, int low, int high){
    int i = low, j = high;
    char pivot[MAX_FLIGHT_ID+1];
    Flight* temp;
    strcpy(pivot, arr[(i+j)/2]->flightID);

    do{
        while(strcmp(arr[i]->flightID, pivot) < 0) i++;
        while(strcmp(arr[j]->flightID, pivot) > 0) j--;
        if(i <= j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }while(i <= j);
    if(j > low && j != high) QuickSortFlight_byFID_Incre(arr, low, j);
    if(i < high && i != low) QuickSortFlight_byFID_Incre(arr, i, high);
}

void QuickSortFlight_byFID_Decre(Flight**arr, int low, int high){
    int i = low, j = high;
    char pivot[MAX_FLIGHT_ID+1];
    Flight* temp;
    strcpy(pivot, arr[(i+j)/2]->flightID);

    do{
        while(strcmp(arr[i]->flightID, pivot) > 0) i++;
        while(strcmp(arr[j]->flightID, pivot) < 0) j--;
        if(i <= j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }while(i <= j);
    if(j > low && j != high) QuickSortFlight_byFID_Decre(arr, low, j);
    if(i < high && i != low) QuickSortFlight_byFID_Decre(arr, i, high);
}

//planeid incre
void QuickSortFlight_byPLID_Incre(Flight**arr, int low, int high){
    cout << "called" << endl;
    int i = low, j = high;
    char pivot[MAX_PLANE_ID+1];
    Flight* temp;
    strcpy(pivot, arr[(i+j)/2]->planeID);
    do{ 
        while(strcmp(arr[i]->planeID, pivot) < 0) i++;
        while(strcmp(arr[j]->planeID, pivot) > 0) j--;
        if(i <= j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }

    }while(i <= j);
    if(j > low && j != high) QuickSortFlight_byPLID_Incre(arr, low, j);
    if(i < high && i != low) QuickSortFlight_byPLID_Incre(arr, i, high);
}

//planeid decre
void QuickSortFlight_byPLID_Decre(Flight**arr, int low, int high){
    int i = low, j = high;
    char pivot[MAX_PLANE_ID+1];
    Flight* temp;
    strcpy(pivot, arr[(i+j)/2]->planeID);
    do{ 
        while(strcmp(arr[i]->planeID, pivot) > 0) i++;
        while(strcmp(arr[j]->planeID, pivot) < 0) j--;
        if(i <= j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }

    }while(i <= j);
    if(j > low && j != high) QuickSortFlight_byPLID_Decre(arr, low, j);
    if(i < high && i != low) QuickSortFlight_byPLID_Decre(arr, i, high);
}

//arrive incre
void QuickSortFlight_byAR_Incre(Flight**arr, int low, int high){
   
    int i = low, j = high;
    char pivot[MAX_ARRIVE + 1];
    Flight *temp;
    strcpy(pivot, arr[(i+j)/2]->arrive);
        
    do{
        while(strcmp(arr[i]->arrive, pivot) < 0) i++;
        while(strcmp(arr[j]->arrive, pivot) > 0) j--;
        if(i <= j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }

    }while(i <= j);
    if(j > low && j != high) QuickSortFlight_byAR_Incre(arr, low, j);
    if(i < high && i != low) QuickSortFlight_byAR_Incre(arr, i, high);
}
//arrive decre
void QuickSortFlight_byAR_Decre(Flight**arr, int low, int high){
     int i = low, j = high;
    char pivot[MAX_ARRIVE + 1];
    Flight *temp;
    strcpy(pivot, arr[(i+j)/2]->arrive);
        
    do{
        while(strcmp(arr[i]->arrive, pivot) > 0) i++;
        while(strcmp(arr[j]->arrive, pivot) < 0) j--;
        if(i <= j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }

    }while(i <= j);
    if(j > low && j != high) QuickSortFlight_byAR_Decre(arr, low, j);
    if(i < high && i != low) QuickSortFlight_byAR_Decre(arr, i, high);
}