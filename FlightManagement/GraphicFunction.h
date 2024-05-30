#pragma once
#include<graphics.h>
#include<iostream>
#include<string.h>
#include<cstring>

using namespace std;


struct graphicsettingstype{
    textsettingstype textsettings; // textsettingstype : struct co san trong graphics.h
	fillsettingstype fillsettings; // fillsettingstype : struct co san trong graphics.h
	linesettingstype linesettings; // linesettingstype : struct co san trong graphics.h
	int textcolor;
	int bkcolor;
};

//========== FUNCTION PROTOTYPE ==========

void settextsettings(textsettingstype *textsettings);
void setfillsettings(fillsettingstype *fillsettings);
void setlinesettings(linesettingstype *linesettings);

void getgraphicsettings(graphicsettingstype *graphicsettings);
void setgraphicsettings(graphicsettingstype *graphicsettings);

void outtext(string s);
void outtextxy(int x, int y, string s);
int textwidth(string s);
int textheight(string s);

void rounded_bar(int x, int y, int width, int height, int fillcolor, int r = 5);
void rounded_rect(int x, int y, int width, int height, int linecolor, int r = 5);

//========== FUNCTION DEFINITION =========

void settextsettings(textsettingstype *textsettings){
    settextstyle(textsettings->font, textsettings->direction, textsettings->charsize);
    settextjustify(textsettings->horiz, textsettings->vert);
}

void setfillsettings(fillsettingstype *fillsettings){
    setfillstyle(fillsettings->pattern, fillsettings->color);
}

void setlinesettings(linesettingstype *linesettings){
    setlinestyle(linesettings->linestyle, linesettings->upattern, linesettings->thickness);
}

void getgraphicsettings(graphicsettingstype *graphicsettings){
    gettextsettings(&(graphicsettings->textsettings));
	getfillsettings(&(graphicsettings->fillsettings));
	getlinesettings(&(graphicsettings->linesettings));
	graphicsettings->textcolor = getcolor();
	graphicsettings->bkcolor = getbkcolor();
}

void setgraphicsettings(graphicsettingstype *graphicsettings){
    settextsettings(&(graphicsettings->textsettings));
	setfillsettings(&(graphicsettings->fillsettings));
	setlinesettings(&(graphicsettings->linesettings));
	setcolor(graphicsettings->textcolor);
	setbkcolor(graphicsettings->bkcolor);
}

void outtext(string s){
    int size = s.size() + 1;
    char *c = new char[size];
    strcpy(c, s.c_str());
    c[size-1] = '\0';
    outtext(c);
    delete[] c;
}

void outtextxy(int x, int y, string s){
    int size = s.size() + 1;
    char *c = new char[size];
    strcpy(c, s.c_str());
    c[size-1] = '\0';
    outtextxy(x, y, c);
    delete[] c;
}

int textwidth(string s){
    int size = s.size() + 1;
    char *c = new char[size];
    strcpy(c, s.c_str());
    c[size-1] = '\0';
    int width = textwidth(c);
    delete[] c;
    return width;
}

int textheight(string s){
    int size = s.size() + 1;
    char *c = new char[size];
    strcpy(c, s.c_str());
    c[size-1] = '\0';
    int height = textheight(c);
    delete[] c;
    return height;
}

void rounded_bar(int x, int y, int width, int height, int fillcolor, int r){
    graphicsettingstype current_settings;
	getgraphicsettings(&current_settings);

	setfillstyle(SOLID_FILL, fillcolor);
	setlinestyle(SOLID_LINE, 0, 1);
	setcolor(fillcolor);
	if (r <= 0)
	{
		bar(x, y, x + width, y + height);
	}
	else
	{
		circle(x + width - r, y + r, r);
		floodfill(x + width - r, y + r, fillcolor);

		circle(x + r, y + r, r);
		floodfill(x + r, y + r, fillcolor);

		circle(x + r, y + height - r, r);
		floodfill(x + r, y + height - r, fillcolor);
		
		circle(x + width - r, y + height - r, r);
		floodfill(x + width - r, y + height - r, fillcolor);

		bar(x + r, y, x + width - r, y + height);
		bar(x, y + r, x + width, y + height - r);
	}

	setgraphicsettings(&current_settings);
}

void rounded_rect(int x, int y, int width, int height, int linecolor, int r){
    graphicsettingstype current_settings;
	getgraphicsettings(&current_settings);

	setcolor(linecolor);
	if (r <= 0)
	{
		rectangle(x, y, x + width, y + height);
	}
	else
	{	
		arc(x + width - r, y + r, 0, 90, r);
		arc(x + r, y + r, 90, 180, r);
		arc(x + r, y + height - r, 180, 270, r);
		arc(x + width - r, y + height - r, 270, 360, r);

		line(x + r, y, x + width - r, y);
		line(x + r, y + height, x + width - r, y + height);
		line(x, y + r, x, y + height - r);
		line(x + width, y + r, x + width, y + height - r);
	}
	setgraphicsettings(&current_settings);
}
