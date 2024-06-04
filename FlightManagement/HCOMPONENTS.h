#ifndef HCOMPONENTS_H
#define HCOMPONENTS_H

class H_Button {
public:
    int x1, y1, x2, y2, height, width, color; bool hover_status;
    char *button_type;
    
    H_Button(int x1, int y1, int width, int height, char *type, int color);
    void draw_button();
    bool isInside(int x, int y);
};

H_Button::H_Button(int x1, int y1, int width, int height, char *type, int color) : 
    x1(x1), y1(y1), width(width), height(height), button_type(type), color(color), hover_status(false) {
    x2 = x1 + width;
    y2 = y1 + height;
}

bool H_Button::isInside(int x, int y) {
	return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

void H_Button::draw_button() {
	settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    rounded_bar(x1, y1, width, height, color, 5);
        setcolor(15);
        char *text = button_type;
        
        int h = textheight(text);
        int w = textwidth(text);
        
        moveto(x1 + width/2 - w/2, y1 + height/2 - h/2);
        
        setcolor(15);
        setbkcolor(color);
        outtext(text);
}

	
// end of button


// <--- input Box --->


class InputBox {
public:
	int x, y, width, height, color;
	char *type;
	char content[20];
	bool hover_status;
	int id;
	InputBox(int x, int y, int width, int height, int color, char *type,int id);
	void drawInputBox();
	bool isInside(int x, int y);
	
};

bool InputBox::isInside(int xp, int yp) {
	return (xp >= x && xp <=x+width && yp >= y && yp <= y + height );
}

InputBox::InputBox(int x, int y, int width, int height, int color, char *type, int id) : 
    x(x), y(y), width(width*16+10), height(height), color(color), type(type), hover_status(false), id(id) {
    	strcpy(content, "");
	}

void InputBox::drawInputBox() {
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); 
	setfillstyle(SOLID_FILL, color);
	bar(x, y, x + width, y + height);
	
	int h = textheight(type);
	int w = textwidth(type);
	
	setcolor(0);
	rectangle(x,y,x + width, y + height);
	
	moveto(x + width/2 - w/2, y + height/2 - h/2);
	
	
	setcolor(7);
	setbkcolor(color);
	
	outtext(type);
}


// <--- end input box --->


// <--- this start of checkbox --->
//char *content, int x, int y, int width, int height

class H_CheckBox {
public:
	int x, y, width, height, cx, cy;
	char *content;
	bool isClicked;
	
	H_CheckBox(int x, int y, int width, int height, char *content);
	void draw_checkBox();
	bool isInside(int x, int y);
		
};

H_CheckBox::H_CheckBox(int x, int y, int width, int height, char *content):
	x(x), y(y), width(width), height(height), content(content), isClicked(false),cx(x+width + 5), cy(y + 15){}
	
void H_CheckBox::draw_checkBox() {
	int h = textheight(content);
	int w = textwidth(content);
	
	setcolor(0);
	setbkcolor(15);
	moveto(x + width/2 - w/2, y + height/2 - h/2);
	outtext(content);
	
	circle(cx, cy, 15);
	
}


bool H_CheckBox::isInside(int xp, int yp) {
	return (xp >= cx - 15  && xp <= cx + 15 && yp >= cy - 15 && yp <= cy + 15);
}
//<--- End of checkbox --->



#endif
