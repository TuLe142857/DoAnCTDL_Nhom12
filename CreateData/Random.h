#pragma once

#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;

int random(int a, int b);
int* random_arr(int a, int b, int n);

//===============================================


int random(int a, int b){
    if(b < a) return random(b, a);
    return a + rand()%(b - a + 1);
}

int* random_arr(int a, int b, int n){
    int n1 = b-a+1,
        *arr1 = new int[n1],
        n2 = n,
        *arr2 = new int[n2];
    for(int i = 0; i < n1; i++)
        arr1[i] = a + i;
    
    int k, temp;
    for(int i = 0; i < n2; i++){
        k = rand()%n1;
        arr2[i] = arr1[k];

        //swap arr1[k] va arr1[n1-1]
        temp = arr1[k];
        arr1[k] = arr1[n1 - 1];
        arr1[n1 - 1] = temp;
        n1 --;
    }

    delete[] arr1;
    return arr2;
}


