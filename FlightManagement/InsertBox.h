#pragma once
#include"GraphicObject.h"

#define MAX_CHAR_INSERT 100 //insert toi da 100 ky tu

class InsertBox:public GraphicObject{
private:
    char content[MAX_CHAR_INSERT + 1];
    int contentsize = 0;
    int maxchar = 0;

    char title[MAX_CHAR_INSERT + 1] = "_type here";

    int background_normal = LIGHTGRAY;
    int background_active = WHITE;
    int textcolor_normal = DARKGRAY;
    int textcolor_active = BLACK;
public:
    void setup(int x, int y, int maxchar, int textfont = 10, int textsize = 2);

    void setcontent(string content);
    void setcontent(char *content);

    void settitle(string title);
    void settitle(char *title);

    void settextcolor(int normal, int active);
    void setbackgroundcolor(int normal, int active);

    string getcontent();
    char* getcontent_char();

    void print();
    bool Insert(bool (*check)(InsertBox*, char&));//tra ve true neu co thay doi noi dung

    //Cac ham kiem tra dieu kien nhap 
    friend bool autotrue(InsertBox *ib, char &c); // return true
    friend bool Insert_normal_text(InsertBox *ib, char &c);
    friend bool Insert_number_only(InsertBox *ib, char &c);
    friend bool Insert_capital_letter_only(InsertBox *ib, char &c);
    friend bool Insert_number_and_capital_letter(InsertBox *ib, char &c);

    friend bool Insert_minute(InsertBox *ib, char &c);
    friend bool Insert_hour(InsertBox *ib, char &c);
    friend bool Insert_day(InsertBox *ib, char &c);
    friend bool Insert_month(InsertBox *ib, char &c);
    //Insert year: Insert_number_only

    friend bool Insert_firstname(InsertBox *ib, char &c);
    friend bool Insert_lastname(InsertBox *ib, char &c);
};

void InsertBox::setup(int x, int y, int maxchar, int textfont , int textsize ){
    this->x = x;
    this->y = y;
    if(maxchar > 0 && maxchar <= MAX_CHAR_INSERT)
        this->maxchar = maxchar;
    this->textfont = textfont;
    this->textsize = textsize;

    contentsize = 0;
    content[contentsize] = '\0';
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    settextstyle(this->textfont, HORIZ_DIR, this->textsize);
    this->height = textheight("QWERTYUIOPASDFGHJKLZXCVBNM|") + 10;
    int maxwidth = (textwidth("W") > textwidth("_")) ? textwidth("W") : textwidth("_");
    this->width = maxwidth*(this->maxchar + 1) + 10;

    setgraphicsettings(&currentsettings);
}


void InsertBox::setcontent(string content){
    if(content.size() <= maxchar){
        strcpy(this->content, content.c_str());
        contentsize = content.size();
        this->content[contentsize] = '\0';
    }
}

void InsertBox::setcontent(char *content){
    if(strlen(content) <= maxchar){
        strcpy(this->content, content);
        contentsize = strlen(content);
        this->content[contentsize] = '\0';
    }
}

void InsertBox::settitle(string title){
    if(title.size() <= maxchar){
        strcpy(this->title, title.c_str());
        this->title[title.size()] = '\0';
    }
}

void InsertBox::settitle(char *title){
    if(strlen(title) <= maxchar){
        strcpy(this->title, title);
        this->title[strlen(title)] = '\0';
    }
}

void InsertBox::settextcolor(int normal, int active){
    this->textcolor_normal = normal;
    this->textcolor_active = active;
}

void InsertBox::setbackgroundcolor(int normal, int active){
    this->background_normal = normal;
    this->background_active = active;
}

string InsertBox::getcontent(){
    return string(content);
}

char* InsertBox::getcontent_char(){
    return content;
}

void InsertBox::print(){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    settextstyle(textfont, HORIZ_DIR, textsize);
    setcolor((contentsize == 0) ? (textcolor_normal) : (textcolor_active));
    setbkcolor(background_normal);
    settextjustify(LEFT_TEXT, TOP_TEXT);
    rounded_bar(x, y, width, height, background_normal);

    string outscreen = string((contentsize == 0)?(title):(content));
    outtextxy(x+5, y + (height - textheight(outscreen))/2, outscreen);

    setgraphicsettings(&currentsettings);
}

bool autotrue(InsertBox *ib, char &c){
    return true;
}

bool InsertBox::Insert(bool (*check)(InsertBox*, char&) = autotrue){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);
    string before_insert = string(content);

    settextstyle(textfont, HORIZ_DIR, textsize);
    setcolor(textcolor_active);
    setbkcolor(background_active);
    settextjustify(LEFT_TEXT, TOP_TEXT);
    string outscreen = string(content);
    rounded_bar(x, y, width, height, background_active);
    outtextxy(x + 5, y + (height - textheight(outscreen))/2, outscreen);

    int mx, my;
    int count = 0;
    char key;

    //Xoa tat ca ky tu trong bo nho dem
    while(kbhit()){
        getch();
    }

    while(1){
        if(kbhit()){
            key = getch();
            //ENTER thi ket thuc
            if(key == 13)
                break;

            //BLACKSPACE
            if(key == 8 && contentsize > 0){
                contentsize--;
                content[contentsize] = '\0';
                outscreen = string(content);
                rounded_bar(x, y, width, height, background_active);
                //outtextxy(x + 5, y + (height - textheight(outscreen))/2, outscreen);
                outtextxy(x + 5, y + (height - textheight(outscreen + "_"))/2, outscreen + "_");
                continue;//while(1)
            }

            if(contentsize < maxchar && check(this, key)){
                content[contentsize] = key;
                contentsize++;
                content[contentsize] = '\0';
                outscreen = string(content);
                rounded_bar(x, y, width, height, background_active);
                //outtextxy(x + 5, y + (height - textheight(outscreen))/2, outscreen);
                outtextxy(x + 5, y + (height - textheight(outscreen + "_"))/2, outscreen + "_");
            }
        }
        //Click chuot ra ngoai thi ket thuc
        else if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(!inside(mx, my))
                break;//while(1)
        }

        delay(10);//10 mili second = 0,01 second => toc do doc toi da 100 char/s
        
        count ++;
        if(count == 1){
            outtextxy(x + 5, y + (height - textheight(outscreen + "_"))/2, outscreen + "_");
        }else if(count == 35){
            rounded_bar(x, y, width, height, background_active);
            outtextxy(x + 5, y + (height - textheight(outscreen))/2, outscreen);
        }else if(count == 70){
            count  = 0;      
        }
    }

    print();
    setgraphicsettings(&currentsettings);
    //Bo khoang trang cuoi chuoi
    if(content[contentsize-1] == ' '){
        content[contentsize-1] = '\0';
        contentsize --;
    }
    string after_insert = string(content);
    return (before_insert != after_insert); 
}

bool Insert_normal_text(InsertBox *ib, char &c){
    if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
    if(c == ' '){
        //Khong cho khoang trang o vi tri dau tien
        if(ib->contentsize == 0){
             return false;
        } 
        else if(ib->contentsize > 0){
            //khong de 2 khoang trang lien tiep
            if(ib->content[ib->contentsize-1] == ' ') return false;
        }
        return true;
    }
    return false;
}

bool Insert_number_only(InsertBox *ib, char &c){
    return(c >= '0' && c <= '9');
}

bool Insert_capital_letter_only(InsertBox *ib, char &c){
    if(c >= 'a' && c <= 'z') c -= 32;
    return (c >= 'A' && c <= 'Z');
}

bool Insert_number_and_capital_letter(InsertBox *ib, char &c){
    if(c >= 'a' && c <= 'z') c -= 32;
    return ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}


bool Insert_minute(InsertBox *ib, char &c){
    //minute: 00-59
    if(!(c >= '0' && c <= '9')) return false;
    if(ib->contentsize == 0 && c >= '6'){
        ib->content[0] = '0';
        ib->contentsize = 1;
        ib->content[1] = '\0';
    }
    return true;
}

bool Insert_hour(InsertBox *ib, char &c){
    //hour: 00-23 (24h => 00h)
    if(!(c >= '0' && c <= '9')) return false;
    if(ib->contentsize == 0 && c >= '3'){
        ib->content[0] = '0';
        ib->contentsize = 1;
        ib->content[1] = '\0';
    }
    else if(ib->contentsize == 1 && ib->content[0] == '2'){
        if(c == '4'){
            c = '0';
            ib->content[0] = '0';
            return true;
        }
        if(c > '4') return false;
    } 
    return true;
}

bool Insert_day(InsertBox *ib, char &c){
    //day: 1-31
    if(!(c >= '0' && c <= '9')) return false;
    if(ib->contentsize == 0 && c >= '4'){
        ib->content[0] = '0';
        ib->contentsize = 1;
        ib->content[1] = '\0';
    }
    else if(ib->contentsize == 1 && ib->content[0] == '3' && c > '1')
        return false;
    return true;
}

bool Insert_month(InsertBox *ib, char &c){
    //month: 1-12
    if(!(c >= '0' && c <= '9')) return false;
    if(ib->contentsize == 0 && c >= '2'){
        ib->content[0] = '0';
        ib->contentsize = 1;
        ib->content[1] = '\0';
    }
    else if(ib->contentsize == 1 && ib->content[0] == '1' && c > '2')
        return false;

    return true;
}

//Ho + ten dem
bool Insert_lastname(InsertBox *ib, char &c){
    // if( !( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||(c == ' ')) ) 
    //     return false;

    // if(c == ' '){
    //     //Khong cho khoang trang o vi tri dau tien
    //     if(ib->contentsize == 0){
    //          return false;
    //     } 
    //     else if(ib->contentsize > 0){
    //         //khong de 2 khoang trang lien tiep
    //         if(ib->content[ib->contentsize-1] == ' ') return false;
    //     }
    //     return true;
    // }


    // if(c >= 'a' && c <= 'z'){
    //     //Viet hoa chu cai dau tien
    //     if(ib->contentsize == 0){
    //         c -= 32;
    //         return true;
    //     }
    //     //Tu dong viet hoa sau khoang trang
    //     else if(ib->content[ib->contentsize-1] == ' '){
    //         c -= 32;
    //         return true;
    //     }
    // }
    // return true;
    if(c >= 'a' && c <= 'z') c-= 32;
    if(c == ' '){
        //Khong de khoang trang vi tri dau tien
        if(ib->contentsize == 0)
            return false;
        
        //Khong de hai khoang trang lien tiep
        else if(ib->content[ib->contentsize-1] == ' ')
            return false;
        return true;
    }
    if(c >= 'A' && c <= 'Z')
        return true;
    return false;
}

//Ten 
bool Insert_firstname(InsertBox *ib, char &c){
    // if( !( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
    //     return false;
    
    // //viet hoa chu dau tien
    // if(ib->contentsize == 0 && (c >= 'a' && c <= 'z'))
    //     c -= 32;

    // return true;
    if(c >= 'a' && c <= 'z') c-= 32;
    if(c >= 'A' && c <= 'Z') return true;
    return false;

}
