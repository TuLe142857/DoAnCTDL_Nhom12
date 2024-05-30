#ifndef PASSENGER_H
#define PASSENGER_H

#include <cstring>

class Passenger {
private:
    char cccd[13];
    char ho[20];
    char ten[20];
    char sex[4];
public:
    Passenger(char *cccd, char *ho, char *ten, char *sex) {
        strcpy(this->cccd, cccd);
        strcpy(this->ho, ho);
        strcpy(this->ten, ten);
        strcpy(this->sex, sex);
    }
    
    Passenger() {
		strcpy(this->cccd, "");
        strcpy(this->ho, "");
        strcpy(this->ten, "");
        strcpy(this->sex, "");
	}
    
    char *getCccd() {
        return cccd;
    }
    
    char *getHo() {
        return ho;
    }
    
    char *getTen() {
        return ten;
    }
    
    char *getSex() {
        return sex;
    }
    
    
    void setCccd(char* cccd) {
        strcpy(this->cccd, cccd);
    }
    
    void setTen(char *ten) {
        strcpy(this->ten, ten);
    }
    
    void setHo(char *ho) {
        strcpy(this->ho, ho);
    }
    
    void setSex(char *sex) {
        strcpy(this->sex, sex);
    }
    
};

#endif
