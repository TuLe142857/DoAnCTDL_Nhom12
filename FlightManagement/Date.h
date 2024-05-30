#pragma once
#include<iostream>
#include<ctime>
#include<string>
#include<cstring>
using namespace std;

const int MAX_DAY_IN_MONTH[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
struct Date{
    int minute = 0;
    int hour = 0;
    int day = 1;
    int month = 1;
    int year = 1;

    Date (){}
    Date (int minute, int hour, int day, int month, int year) 
        : minute(minute), hour(hour), day(day), month(month), year(year){}

    //return: "hh:mm-dd/mm/yyy"
    string to_string();

    //tra ve tong so phut ke tu 00:00-01/01/0001
    long long total_minute();
};

//nam nhuan
bool isleapyear(int year);

bool checkdate(Date date);

Date today();

//so sanh
bool operator > (Date date1, Date date2);
bool operator < (Date date1, Date date2);
bool operator == (Date date1, Date date2);
bool operator != (Date date1, Date date2);
bool operator >= (Date date1, Date date2);
bool operator <= (Date date1, Date date2);

//tru
long long operator - (Date date1, Date date2);

Date operator + (Date date, long long added_minute);

void operator += (Date &date, long long added_minute);


//===================================================

string Date::to_string(){
    string s;

    if(hour < 10) s += '0';
    s += std::to_string(hour) + ':';

    if(minute < 10) s += '0';
    s += std::to_string(minute) + '-';
    
    if(day < 10) s += '0';
    s += std::to_string(day) + '/';

    if(month < 10) s += '0';
    s += std::to_string(month) + '/';

    s += std::to_string(year);

    return s;
}

long long Date::total_minute(){
    long long sum = 0;

    sum += minute + hour*60 + (day-1)*24*60;
    for(int i = 1; i < month; i++){
        sum += MAX_DAY_IN_MONTH[i]*24*60;
    }
    if(isleapyear(year) && month > 2) sum += 24*60;

    sum += 365*24*60*((long long)(year-1));
    int so_nam_nhuan = 0;
    so_nam_nhuan = ((year-1)/4 - (year-1)/100 + (year-1)/400);

    sum += (long long)(so_nam_nhuan)*24*60;

    return sum;
}

bool isleapyear(int year){
    return((year%4 == 0 && year % 100 != 0) || (year%400 == 0));
}

bool checkdate(Date date){
    if(!(date.minute >= 0 && date.minute < 60)) return false;
    if(!(date.hour >= 0 && date.hour < 24)) return false;
    if(!(date.month >= 1 && date.month <= 12)) return false;
    if(!(date.year >= 1)) return false;

    if(isleapyear(date.year) && date.month == 2){
        if(!(date.day >= 1 && date.day <= 29)) return false;
    }else{
        if(!(date.day >= 1 && date.day <= MAX_DAY_IN_MONTH[date.month])) return false;
    }

    return true;
}

Date today(){
    Date date;
    time_t total_second = time(0);
    tm *now = localtime(&total_second);
    
    date.minute = now->tm_min;
    date.hour = now->tm_hour;
    date.day = now->tm_mday;
    date.month = now->tm_mon + 1;   // tm_mon return months since January - [0, 11]
    date.year = now->tm_year + 1900;// tm_year return years since 1900

    return date;
}

//so sanh
bool operator > (Date date1, Date date2){
    if(date1.year > date2.year) return true;
    if(date1.year < date2.year) return false;

    if(date1.month > date2.month) return true;
    if(date1.month < date2.month) return false;

    if(date1.day > date2.day) return true;
    if(date1.day < date2.day) return false;

    if(date1.hour > date2.hour) return true;
    if(date1.hour < date2.hour) return false;

    if(date1.minute > date2.minute) return true;
    if(date1.minute < date2.minute) return false;

    return false;
}

bool operator < (Date date1, Date date2){
    if(date1.year < date2.year) return true;
    if(date1.year > date2.year) return false;

    if(date1.month < date2.month) return true;
    if(date1.month > date2.month) return false;

    if(date1.day < date2.day) return true;
    if(date1.day > date2.day) return false;

    if(date1.hour < date2.hour) return true;
    if(date1.hour > date2.hour) return false;

    if(date1.minute < date2.minute) return true;
    if(date1.minute > date2.minute) return false;

    return false;
}

bool operator == (Date date1, Date date2){
    return ((date1.minute == date2.minute) &&
            (date1.hour == date2.hour) &&
            (date1.day == date2.day) &&
            (date1.month == date2.month) &&
            (date1.year == date2.year));
}

bool operator != (Date date1, Date date2){
    return ((date1.minute != date2.minute) ||
            (date1.hour != date2.hour) ||
            (date1.day != date2.day) ||
            (date1.month != date2.month) ||
            (date1.year != date2.year));
}

bool operator >= (Date date1, Date date2){
    if(date1.year > date2.year) return true;
    if(date1.year < date2.year) return false;

    if(date1.month > date2.month) return true;
    if(date1.month < date2.month) return false;

    if(date1.day > date2.day) return true;
    if(date1.day < date2.day) return false;

    if(date1.hour > date2.hour) return true;
    if(date1.hour < date2.hour) return false;

    if(date1.minute > date2.minute) return true;
    if(date1.minute < date2.minute) return false;

    return true;
}

bool operator <= (Date date1, Date date2){
    if(date1.year < date2.year) return true;
    if(date1.year > date2.year) return false;

    if(date1.month < date2.month) return true;
    if(date1.month > date2.month) return false;

    if(date1.day < date2.day) return true;
    if(date1.day > date2.day) return false;

    if(date1.hour < date2.hour) return true;
    if(date1.hour > date2.hour) return false;

    if(date1.minute < date2.minute) return true;
    if(date1.minute > date2.minute) return false;

    return true;
}

//tru
long long operator - (Date date1, Date date2){
    return date1.total_minute() - date2.total_minute();
}

Date operator + (Date date, long long added_minute){
    while(added_minute > 0){
        added_minute -= 1;
        date.minute += 1;

        if(date.minute == 60){
            date.minute = 0;
            date.hour ++;
        
            if(date.hour == 24){
                date.hour = 0;
                date.day ++;
                if(date.day > MAX_DAY_IN_MONTH[date.month]){
                    if(!isleapyear(date.year)){
                        date.day = 1;
                        date.month++;
                    }
                    else {
                        if(date.month == 2 ){
                            if(date.day > 29){
                                date.day = 1;
                                date.month++;
                            }
                        }else {
                            date.day = 1;
                            date.month++;
                        }
                    }
                    
                    if(date.month == 13){
                        date.month = 1;
                        date.year ++;
                    }
                }
            }
        }
    }

    return date;
}

void operator += (Date &date, long long added_minute){
    date = date+added_minute;
}
