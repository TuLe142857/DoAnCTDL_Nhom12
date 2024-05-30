#pragma once
#include"GraphicObject.h"

#define MAX_ROW 20
#define MAX_COL 10
//toi da 20 dong, 10 cot
class Table:public GraphicObject{
private:
    int numcol;
    int numrow;
    int colwidth[MAX_COL];
    int rowheight[MAX_ROW];
public:
    void setup(int x, int y, int width, int height, int numrow, int numcol);
    void setcolwidth(int column, int width);
    void setrowheight(int row, int height);

    int getnumcol();
    int getnumrow();
    int getrowheight(int row);
    int getcolwidth(int column);
    int getrow_y(int row);
    int getcol_x(int column);

    int print(int backgroundcolor = WHITE);
    void outtext(int row, int column, string s, int textcolor = BLACK, int backgroundcolor = WHITE);
    void outtext(int row, int column, char *c, int textcolor = BLACK, int backgroundcolor = WHITE);

    bool insiderow(int row, int mx, int my);
    bool insidecol(int column, int mx, int my);
    bool insidecell(int row, int column, int mx, int my);
};

void Table::setup(int x, int y, int width, int height, int numrow, int numcol){
    GraphicObject::setup(x, y, width, height);
    if(numrow > 0 && numrow <= MAX_ROW)
        this->numrow = numrow;
    if(numcol > 0 && numcol <= MAX_COL)
        this->numcol = numcol;
    for(int i = 0; i < this->numrow; i++){
        rowheight[i] = height/(this->numrow);
    }
    for(int i = 0; i < this->numcol; i++){
        colwidth[i] = width/(this->numcol);
    }
}

void Table::setcolwidth(int column, int width){
    if(width <= 0 || !(column >= 0 && column < numcol)) return;
    this->width += (width - colwidth[column]);
    colwidth[column] = width;
}

void Table::setrowheight(int row, int height){
    if(height <= 0 || !(row >= 0 && row < numrow)) return;
    this->height += (height - rowheight[row]);
    rowheight[row] = height;
}

int Table::getnumcol(){
    return numcol;
}

int Table::getnumrow(){
    return numrow;
}

int Table::getrowheight(int row){
    if(!(row >= 0 && row < numrow)) return -1;
    return rowheight[row];
}

int Table::getcolwidth(int column){
    if(!(column >= 0 && column < numcol)) return -1;
    return colwidth[column];
}

int Table::getrow_y(int row){
    if(!(row >= 0 && row < numrow)) return -1;
    int coords_y = y;
    for(int i = 0; i < row; i++)
        coords_y += rowheight[i];
    return coords_y;
}

int Table::getcol_x(int column){
    if(!(column >= 0 && column < numcol)) return -1;
    int coords_x = x;
    for(int i = 0; i < column; i++)
        coords_x += colwidth[i];
    return coords_x;
}

int Table::print(int backgroundcolor){
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, backgroundcolor);

    bar(x, y, x + width, y + height);
    rectangle(x, y, x + width, y + height);

    int coords_x = x, coords_y = y;

    //ve duong ngang
    for(int i = 0; i < numrow - 1; i++){
        coords_y += rowheight[i];
        line(x, coords_y, x + width, coords_y);
    }

    //ve duong doc
    for(int i = 0; i < numcol - 1; i++){
        coords_x += colwidth[i];
        line(coords_x, y, coords_x, y+height);
    }


    setgraphicsettings(&currentsettings);
}

void Table::outtext(int row, int column, string s, int textcolor, int backgroundcolor){
    if(!(row >= 0 && row < numrow) && (column >= 0 && column < numcol)) return;
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    setcolor(textcolor);
    setbkcolor(backgroundcolor);
    setfillstyle(SOLID_FILL, backgroundcolor);
    settextstyle(textfont, HORIZ_DIR, textsize);
    settextjustify(CENTER_TEXT, TOP_TEXT);

    int coords_x = getcol_x(column), coords_y = getrow_y(row);
    bar(coords_x+1, coords_y+1,coords_x + colwidth[column], coords_y + rowheight[row]);
    char *c = new char[s.size()+1];
    strcpy(c, s.c_str());
    c[s.size()] = '\0';
    outtextxy(coords_x + colwidth[column]/2, coords_y + (rowheight[row] - textheight(c))/2, c);
    delete[]c;

    setgraphicsettings(&currentsettings);
}

void Table::outtext(int row, int column, char *c, int textcolor, int backgroundcolor){
    if(!(row >= 0 && row < numrow) && (column >= 0 && column < numcol)) return;
    graphicsettingstype currentsettings;
    getgraphicsettings(&currentsettings);

    setcolor(textcolor);
    setbkcolor(backgroundcolor);
    setfillstyle(SOLID_FILL, backgroundcolor);
    settextstyle(textfont, HORIZ_DIR, textsize);
    settextjustify(CENTER_TEXT, TOP_TEXT);

    int coords_x = getcol_x(column), coords_y = getrow_y(row);
    bar(coords_x+1, coords_y+1,coords_x + colwidth[column], coords_y + rowheight[row]);
    outtextxy(coords_x + colwidth[column]/2, coords_y + (rowheight[row] - textheight(c))/2, c);
    
    setgraphicsettings(&currentsettings);
}

bool Table::insiderow(int row, int mx, int my){
    if(!(row >= 0 && row < numrow)) return false;
    int coords_y = getrow_y(row);
    return ((mx >= x && mx <= (x + width)) && ( my >= coords_y && my <= (coords_y + rowheight[row])));
}

bool Table::insidecol(int column, int mx, int my){
    if(!(column >= 0 && column < numcol)) return false;
    int coords_x = getcol_x(column);
    return ((mx >= coords_x && mx <= (coords_x + colwidth[column])) && (my >= y && my <= (y + height)));
}

bool Table::insidecell(int row, int column, int mx, int my){
    if(!((row >= 0 && row < numrow) && (column >= 0 && column < numcol))) return false;
    int coords_x = getcol_x(column), coords_y = getrow_y(row);
    return ((mx >= coords_x && (mx <= coords_x + colwidth[column])) && (my >= coords_y && my <= (coords_y + rowheight[row])));
}