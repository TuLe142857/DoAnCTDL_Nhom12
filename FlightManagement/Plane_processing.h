#pragma once
#include"Plane.h"
#include"DefaultGraphic.h"
#include <iostream>
#include <iomanip> 
#include "Flight.h" 
#include <graphics.h> 
#include <windows.h>
#include <fstream>
#define MAX 300 
//moi sua
#define CN 2//(1: Nhap lien tuc phai co gia tri, 2: Nhap don le ko can co gia tri)
using namespace std;
struct ThongKe{
	char soHieuMB[16]; 
	int dem; 
};

void dondep(){
	while(kbhit()){
		char d=getch(); 
	} 
}

void Turn(){
	clearmouseclick(WM_RBUTTONDOWN);
	setfillstyle(1,15);
	bar(10,50,1390,740);
	setfillstyle(1,0); 
	bar(100,100,1300,665); 
	setcolor(14);
	setbkcolor(0);
}

void drawCenteredText(int x, int y, char* text) {
    int textWidth = textwidth(text); 
    int textHeight = textheight(text); 
    outtextxy(x - textWidth / 2, y - textHeight / 2, text); 
}

char* itochar(int n){
	char *c=new char[5];
	if(n==0){
		c[0]='0';
		c[1]='\0';
		return c; 
	} 
	int tam=0; 
	for(int i=1;i<=n;i*=10){
		tam++; 
	} 
	c[tam]='\0';
	while(n>0){
		tam--;
		int m=n%10;
		c[tam]='0'+m;
		n/=10; 
	} 
	return c; 
} 

void outtoxy(int x,int y, int n) {
	char *c = itochar(n);
	outtextxy(x, y, c);
	delete[]c;
}

void nhap(char* n, int l, int x, int y){

	char tm = 0;
	int i = 0;
	for(i=0;i<l;i++){
		if(n[i]=='\0'){
			break;
		}
	}
	n[i] = '\0';
	outtextxy(x, y, n);
	if(n[0]=='\0'){
    	outtextxy(x,y,"_");
	}
	else
	outtextxy(x+textwidth(n),y,"_");
	char A[]="      ";
	while(1){
		while ((tm = getch()) != 13) {
			if (i < l) {
				if ((('Z' >= tm) && (tm >= 'A')) || (('9' >= tm) && (tm >= '0'))) {
					n[i] = tm;
					n[i + 1] = '\0'; 
					outtextxy(x, y, n);
					i++;
				}
				if (('z' >= tm) && (tm >='a')){
					n[i] = tm-32;
					n[i + 1] = '\0'; 
					outtextxy(x, y, n);
					i++;
				}
			}
			if (tm == 8 && i > 0) { 
				outtextxy(x + (textwidth(n) - textwidth(&n[i - 1])), y, A); 
				i--;
				n[i] = '\0'; 
				outtextxy(x, y, n); 
			}
			if(n[0]=='\0'){
		    	outtextxy(x,y,"_");
			}
			else
			outtextxy(x+textwidth(n),y,"_");
		}
//moi sua
		if(CN==1){
			if(i>0){
				setbkcolor(8);
				outtextxy(x, y, n); 
				outtextxy(x+textwidth(n),y,"  ");
				break;
			}
		}
		else{
			break;
		}
	}
	outtextxy(x + textwidth(n), y, A); 
}

int nhapso2(int &m, int l, int x, int y) {
	char tm = 0;
	int n=m;
	int i=0;
	while(n>0){
		n/=10;
		i++;
	}
	outtoxy(x,y,m);
	char c[10];
    sprintf(c, "%d", m);
    if(c[0]=='0'){
    	outtextxy(x,y,"_");
	}
	else
	outtextxy(x+textwidth(c),y,"_");

	while(1){//
		while ((tm=getch()) != 13) {
			if (i < l) {
				if (('9' >= tm) && (tm >= '0')) {
					if(i==0&&tm=='0'){
						continue;
					}
					m=m*10+(tm - '0'); 
					outtoxy(x,y,m);
					i++;
				}
			}
			if (tm == 8&& i > 0) {
				outtextxy(x,y,"                     ");
				m=m/10; 
				i--;
				outtoxy(x,y,m);
			}
			memset(c, 1, sizeof(c)); 
			sprintf(c, "%d", m);
			if(c[0]=='0'){
		    	outtextxy(x,y,"_");
			}
			else
			outtextxy(x+textwidth(c),y,"_");
		}
		//moi sua
		if(CN==1){
			if(m>0){//
				break;
			}
		}
		else{
			break;
		}	
	}//
	setbkcolor(8);
	if(m!=0){
		outtoxy(x,y,m);
		outtextxy(x+textwidth(c),y,"   ");
	}
	else{
		outtextxy(x,y,"   ");
	}
	return m;
}

void graphic(){
	setfillstyle(1,0); 
	settextstyle(10, 0, 2);
	bar(100,100,1300,665); 
	outtextxy(100,690,"*Chuot phai de xoa"); 
	outtextxy(100,710,"Chuot trai de sua ");
	setcolor(14); 
	bar(615,690,665,720);
	bar(735,690,785,720);
	drawCenteredText(640,705,"<");
	drawCenteredText(760,705,">");
} 

void Chucnang1(int x,int y,DSMayBay maybay, int n){
	setbkcolor(0); 
	setcolor(11);
	setlinestyle(SOLID_LINE, 0, 2);
	rectangle(200,100,450,665); 
	rectangle(100,100,1300,150); 
	rectangle(100,150,1300,665); 
	rectangle(1000,100,1150,665); 
	setcolor(15);
	settextstyle(0, 0, 4);
	setcolor(15);
	rectangle(498,59,910,84);
	setcolor(0);
	setbkcolor(15); 
	outtextxy(450,60,"DANH SACH MAY BAY");
	settextstyle(10, 0, 2);
	setcolor(14);
	setbkcolor(0); 
	drawCenteredText(150,125,"STT");
	drawCenteredText(320,125,"So Hieu May Bay"); 
	drawCenteredText(725,125,"Loai May Bay"); 
	drawCenteredText(1075,125,"So Dong");
	drawCenteredText(1225,125,"So Day");
	bar(1150,60,1300,90);
	drawCenteredText(1225,75,"THONG KE");
	setbkcolor(15); 
	setcolor(4);
	outtoxy(675,695,(n+10)/10);
	outtextxy(693,695,"/");
	outtoxy(712,695,(maybay.SoMayBay+9)/10);
	bar(1200,680,1300,720);
	setbkcolor(0); 
	setcolor(14);
	drawCenteredText(1250,700,"ADD+");
	//Xuat danh sach may bay MENU chinh 
	for(int i=n;i<n+10;i++){
		if(i<=maybay.SoMayBay){
			if(x>=100&&x<=1300&&y>100+50*(i-n+1)&&y<=150+50*(i-n+1)){
				setcolor(4); 
				drawCenteredText(320,130+50*(i-n+1),maybay.n[i-1]->SoHieuMB); 
				outtoxy(135,122+50*(i-n+1),i);
				drawCenteredText(725,130+50*(i-n+1),maybay.n[i-1]->LoaiMB);
				outtoxy(1060,122+50*(i-n+1),maybay.n[i-1]->SoDong); 
				outtoxy(1210,122+50*(i-n+1),maybay.n[i-1]->SoDay); 
				setcolor(14);
			} 
			else if(x!=-1&&y!=-1){
				drawCenteredText(320,130+50*(i-n+1),maybay.n[i-1]->SoHieuMB); 
				outtoxy(135,122+50*(i-n+1),i);
				drawCenteredText(725,130+50*(i-n+1),maybay.n[i-1]->LoaiMB);
				outtoxy(1060,122+50*(i-n+1),maybay.n[i-1]->SoDong); 
				outtoxy(1210,122+50*(i-n+1),maybay.n[i-1]->SoDay); 
			} 
		}
	} 
	delay(50);
} 

void xoa(DSMayBay &maybay, int i){
	delete maybay.n[i-1];
	for(int j=i-1;j<maybay.SoMayBay;j++){
		maybay.n[j]=maybay.n[j+1]; 
	}
	maybay.SoMayBay--;
	setbkcolor(15);
	setcolor(4);
	setfillstyle(1,15); 
	bar(550,300,850,450); 
	settextstyle(10, 0, 1);
	drawCenteredText(700,350,"BAN XOA THANH CONG"); 
	setfillstyle(1,7); 
	bar(580,380,830,420); 
	settextstyle(10, 0, 2);
	setbkcolor(7);
	drawCenteredText(705,400,"OK"); 
	int mx,my; 
	while(1){
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE, mx, my);
			if(mx>=580&&mx<=830&&my>=380&&my<=420){
				setcolor(4); 
				rectangle(580,380,830,420);
			}
			else{
				setcolor(15); 
				rectangle(580,380,830,420);
			} 
		}

		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, mx, my);
			if(mx>=580&&mx<=830&&my>=380&&my<=420){
				return; 
			}
		}
	}
}

void them(DSMayBay &maybay){
	setfillstyle(1,15);
	bar(10,50,1390,740);
	setfillstyle(1,14);
	bar(15,55,1385,735);
	setbkcolor(14);
	setcolor(4);
	char MENU[4][30]={"So Hieu May Bay",
						"Loai May Bay",
						"So Dong",
						"So Day",

	};
	char MENU2[4][30]={"Nhap toi da 15 ki tu!",
						"Nhap toi da 40 ki tu!",
						"Nhap toi da 2 chu so!",
						"Nhap toi da 2 chu so!",
	};

	int m=0;
	setfillstyle(1,7);
	bar(20,100,80,160);
	settextstyle(10, 0, 1);
	setbkcolor(7);
	drawCenteredText(50,130,"<BACK");
	settextstyle(0, 0, 3);
	setbkcolor(14);
	drawCenteredText(700,100,"ADD PLANE"); 
	settextstyle(10, 0, 2);
	setfillstyle(1,15);
	bar(1100,185,1350,235); 

	//NOTE 

	drawCenteredText(1225,210,"*NOTE");
	setfillstyle(1,7);
	setbkcolor(7);
	bar(1100,235,1350,400); 
	setcolor(1); 
	bar(1190,660,1300,700); 
	drawCenteredText(1245,680,"SAVE");
	drawCenteredText(1225,250,"So hieu may bay"); 
	drawCenteredText(1225,280,"Loai may bay"); 
	drawCenteredText(1225,310,"Nhap tu 0-9, A-Z");
	drawCenteredText(1225,340,"So dong*So day >= 20");
	drawCenteredText(1225,370,"Nhap tu 0-9");
	setfillstyle(1,7);
	//Man hinh ban dau 
	for(int i=0;i<4;i++){
		setcolor(1);
		setbkcolor(14);
		rectangle(399,184+100*i,1001,236+100*i);
		outtextxy(150,200+100*i,MENU[i]);
		bar(400,185+100*i,1000,235+100*i);
		setcolor(15);
		setbkcolor(7);
		outtextxy(420,200+100*i,MENU2[i]);

	} 
	int ok=0; 
	int mx,my;
	MayBay *A= new MayBay;

	//Cai dat rong cho may bay moi tao 

	A->SoDay=0;
	A->SoDong=0;
	memset(A->LoaiMB , '\0', sizeof(A->LoaiMB));
	memset(A->SoHieuMB , '\0', sizeof(A->SoHieuMB ));
	int bo=0;
	while(1){
		setbkcolor(8);
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, mx, my);
			//Don dep bo nho dem 
			dondep();
			setcolor(11);
			for(int i=0;i<=3;i++){
				if(mx>=400&&mx<=1000&&my>=185+100*i&&my<=235+100*i){
					setfillstyle(1,8);
					bar(400,185+100*i,1000,235+100*i);
					if(i==0){
						//bien check trung hay k 
						int Check;
						while(1){
							Check=0;
							setbkcolor(8); 
							nhap(A->SoHieuMB,15,420,200); 
							for(int j=0;j<maybay.SoMayBay;j++){
								if(strcmp(A->SoHieuMB,maybay.n[j]->SoHieuMB)==0){
									setfillstyle(1,14);
									bar(400,120,1000,180);
									delay(50);
									setbkcolor(14); 
									setcolor(4);
									outtextxy(405,130,"Ma May Bay nay da ton tai!"); 
									outtextxy(405,150,"Moi tiep tuc nhap         "); 
									setcolor(11);

									Check=1;
									break;
								} 
							}

							if(Check==1){
								continue;
							}
							setfillstyle(1,14);
							bar(400,120,1000,180);
							outtextxy(420,200,A->SoHieuMB);
//							Chuc nang bo xung cho phep nhap lien tuc 
							if(bo==0&&CN==1){
								setfillstyle(1,8);
								setcolor(4);
								setbkcolor(7); 
								setfillstyle(1,7);
								bar(400,185,1000,235);
								outtextxy(420,200,A->SoHieuMB);
								for(int i=1;i<4;i++){//CHUC NANG BO XUNG
									if(i==1){
										setcolor(11);
										setbkcolor(8); 
										setfillstyle(1,8);
										bar(400,185+100*i,1000,235+100*i);
										nhap(A->LoaiMB,40,420,300);
									}
									else{
										setcolor(4);
										setbkcolor(7); 
										setfillstyle(1,7);
										bar(400,185+100*1,1000,235+100*1);
										if(A->LoaiMB[0]!='\0')
										outtextxy(420,300,A->LoaiMB);
										else{
											setcolor(15);
											outtextxy(420,300,MENU2[1]);
										}
									}
									if(i==2){
										setcolor(11);
										setbkcolor(8); 
										setfillstyle(1,8);
										bar(400,185+100*i,1000,235+100*i);
										nhapso2(A->SoDong,2,420,400);
									}
									else {
										setcolor(4);
										setbkcolor(7); 
										setfillstyle(1,7);
										bar(400,185+100*2,1000,235+100*2);
										outtoxy(420,400,A->SoDong);
									}
									if(i==3){
										setcolor(11);
										setbkcolor(8); 
										setfillstyle(1,8);
										bar(400,185+100*i,1000,235+100*i);
										while(1){
											if(nhapso2(A->SoDay,2,420,500)*A->SoDong<20){
												setbkcolor(14); 
												setfillstyle(1,14); 
												bar(400,440,1000,470); 
												delay(50); 
												setcolor(4);
												outtextxy(405,450,"Khong hop le,moi tiep tuc nhap!"); 
												setbkcolor(8); 
												setcolor(11);
												continue;
											}
											setfillstyle(1,14); 
											bar(400,440,1000,470); 
											break;
										}
										setcolor(4);
										setbkcolor(7); 
										setfillstyle(1,7);
										bar(400,185+100*3,1000,235+100*3);
										outtoxy(420,500,A->SoDay);
									}
								}//END
								bo=1;
							}
							delay(50); 

							break; 
						}
						//moi sua 
						setcolor(15);
						if(A->SoHieuMB[0]=='\0'){
							outtextxy(420,200,MENU2[0]);
						} 
					}
//					if(CN==1){
//						if(i==1&&A->SoHieuMB[0]=='\0'){
//							setcolor(15);
//							outtextxy(420,300,MENU2[1]);
//						}
//						if(i==2&&A->SoHieuMB[0]=='\0'){
//							setcolor(15);
//							outtextxy(420,400,MENU2[2]);
//						}
//						if(i==3&&A->SoHieuMB[0]=='\0'){
//							setcolor(15);
//							outtextxy(420,500,MENU2[3]);
//						}
//					}
					if(CN==1){
						if(i==1&&A->SoHieuMB[0]!='\0'){
							nhap(A->LoaiMB,40,420,300);
						}
						if(i==2){
							while(1){
								if(A->SoDay!=0&&nhapso2(A->SoDong,2,420,400)*A->SoDay<20){
									setbkcolor(14); 
									setfillstyle(1,14); 
									bar(400,340,1000,370); 
									delay(50); 
									setcolor(4);
									outtextxy(405,350,"Khong hop le,moi tiep tuc nhap!"); 
									setcolor(11);
									setbkcolor(8); 
									delay(20); 
									continue;
								}
								setfillstyle(1,14); 
								bar(400,340,1000,370); 
	
								break;
							}
						}
						if(i==3){
							while(1){
								if(A->SoDong!=0&&nhapso2(A->SoDay,2,420,500)*A->SoDong<20){
									setbkcolor(14); 
									setfillstyle(1,14); 
									bar(400,440,1000,470); 
									delay(50); 
									setcolor(4);
									outtextxy(405,450,"Khong hop le,moi tiep tuc nhap!"); 
									setbkcolor(8); 
									setcolor(11);
									continue;
								}
								setfillstyle(1,14); 
								bar(400,440,1000,470); 
								break;
							}
						}
					}
					else{
						if(i==1){
							nhap(A->LoaiMB,40,420,300);
							//moi sua
							if(A->LoaiMB[0]=='\0'){
								setcolor(15);
								outtextxy(420,300,MENU2[1]);
							} 
						}
						if(i==2){
							while(1){
								if(A->SoDay!=0&&nhapso2(A->SoDong,2,420,400)*A->SoDay<20){
									setbkcolor(14); 
									setfillstyle(1,14); 
									bar(400,340,1000,370); 
									delay(50); 
									setcolor(4);
									outtextxy(405,350,"Khong hop le,moi tiep tuc nhap!"); 
									setcolor(11);
									setbkcolor(8); 
									delay(20); 
									continue;
								}
								else if(A->SoDay==0){
									nhapso2(A->SoDong,2,420,400);
								}
								//moi sua 
								if(A->SoDong==0){
									setcolor(15);
									outtextxy(420,400,MENU2[2]);
								} 
								setfillstyle(1,14); 
								bar(400,340,1000,370); 
	
								break;
							}
						}
						if(i==3){
							while(1){
								if(A->SoDong!=0&&nhapso2(A->SoDay,2,420,500)*A->SoDong<20){
									setbkcolor(14); 
									setfillstyle(1,14); 
									bar(400,440,1000,470); 
									delay(50); 
									setcolor(4);
									outtextxy(405,450,"Khong hop le,moi tiep tuc nhap!"); 
									setbkcolor(8); 
									setcolor(11);
									continue;
								}
								else if(A->SoDong==0){
									nhapso2(A->SoDay,2,420,500);
								}
								//moi sua 
								if(A->SoDay==0){
									setcolor(15);
									outtextxy(420,500,MENU2[2]);
								} 
								setfillstyle(1,14); 
								bar(400,440,1000,470); 
								break;
							}
						}
					}
				}
			}
			if(mx>=1190&&mx<=1300&&my>=660&&my<=700){
				if(A->SoHieuMB[0]!='\0'&&A->LoaiMB[0]!='\0'&&A->SoDay!=0&&A->SoDong!=0){

					//Luu may bay 
					maybay.n[maybay.SoMayBay]=new MayBay;
					strcpy(maybay.n[maybay.SoMayBay]->SoHieuMB, A->SoHieuMB); 
            		strcpy(maybay.n[maybay.SoMayBay]->LoaiMB, A->LoaiMB); 
            		maybay.n[maybay.SoMayBay]->SoDay = A->SoDay; 
            		maybay.n[maybay.SoMayBay]->SoDong = A->SoDong; 
            		delete A;

					maybay.SoMayBay++;
					ok=1; 
				}
				if(ok==1){

					setcolor(4);
					setfillstyle(1,15); 
					bar(550,300,850,450); 
					settextstyle(10, 0, 1);
					setbkcolor(15);

					drawCenteredText(700,350,"LUU THANH CONG!"); 
					setfillstyle(1,7); 
					bar(580,380,680,420); 
					settextstyle(0, 0, 2);
					setbkcolor(7);

					drawCenteredText(630,400,"THOAT"); 
					bar(720,380,820,420); 
					drawCenteredText(770,400,"THEM"); 
					while(1){
						if(ismouseclick(WM_MOUSEMOVE)){
							getmouseclick(WM_MOUSEMOVE, mx, my);
							for(int i=0;i<=1;i++){
								if(mx>=580+140*i&&mx<=680+140*i&&my>=380&&my<=420){
									setcolor(4); 
									rectangle(580+140*i,380,680+140*i,420);
								}
								else{
									setcolor(15); 
									rectangle(580+140*i,380,680+140*i,420);
								} 
							}
						}
						int OK=0; 
						if(ismouseclick(WM_LBUTTONDOWN)){
							getmouseclick(WM_LBUTTONDOWN, mx, my);
							for(int z=0;z<=1;z++){
								if(mx>=580+140*z&&mx<=680+140*z&&my>=380&&my<=420){
									if(z==0){

										OK=1; 
										//Luu va quay lai Man Hinh Chinh 
										Turn();

										return; 
									} 
									else if(z==1){
										//Luu va Tiep tuc nhap 

										them(maybay); 

										return;
									} 
								}
							}
							clearmouseclick(WM_LBUTTONDOWN);
						}
						delay(50); 
					}
				} 
				if(ok==0){
					setbkcolor(15);
					setcolor(4);

					setfillstyle(1,15); 
					bar(550,300,850,450); 
					settextstyle(10, 0, 1);
					drawCenteredText(700,350,"BAN CHUA NHAP XONG"); 
					setfillstyle(1,7); 
					bar(580,380,830,420); 
					settextstyle(10, 0, 2);

					setbkcolor(7);

					drawCenteredText(705,400,"OK TOI HIEU ROI"); 
					while(1){
						if(ismouseclick(WM_MOUSEMOVE)){
							getmouseclick(WM_MOUSEMOVE, mx, my);
							if(mx>=580&&mx<=830&&my>=380&&my<=420){
								setcolor(4); 
								rectangle(580,380,830,420);
							}
							else{
								setcolor(15); 
								rectangle(580,380,830,420);
							} 
						}

						//Quay lai de tiep tuc nhap 

						if(ismouseclick(WM_LBUTTONDOWN)){
							getmouseclick(WM_LBUTTONDOWN, mx, my);
							if(mx>=580&&mx<=830&&my>=380&&my<=420){
								settextstyle(10, 0, 2);
								setfillstyle(1,14);
								bar(200,200,900,735);

								setfillstyle(1,7);
								for(int i=0;i<4;i++){
									setcolor(1);
									setbkcolor(14); 
									rectangle(399,184+100*i,1001,236+100*i);
									outtextxy(150,200+100*i,MENU[i]);
									bar(400,185+100*i,1000,235+100*i);
									setbkcolor(7);
									setcolor(4);
									if(i==0&&A->SoHieuMB[0]!='\0'){
										outtextxy(420,200,A->SoHieuMB);
									}
									else if(i==0&&A->SoHieuMB[0]=='\0'){
										setcolor(15); 
										outtextxy(420,200,MENU2[i]);
									} 
									if(i==1&&A->LoaiMB[0]!='\0'){
										outtextxy(420,300,A->LoaiMB);
									}
									else if(i==1&&A->LoaiMB[0]=='\0'){
										setcolor(15); 
										outtextxy(420,300,MENU2[i]);
									}
									if(i==2&&A->SoDong!=0){
										outtoxy(420,400,A->SoDong);
									}
									else if(i==2&&A->SoDong==0){
										setcolor(15); 
										outtextxy(420,400,MENU2[i]);
									} 
									if(i==3&&A->SoDay!=0){
										outtoxy(420,500,A->SoDay);
									}
									else if(i==3&&A->SoDay==0){
										setcolor(15); 
										outtextxy(420,500,MENU2[i]);
									} 
								}
							break;
							}
							clearmouseclick(WM_LBUTTONDOWN);
						}
						delay(50); 

					}
				}
			}
			if(mx>=20&&mx<=80&&my>=100&&my<=160){
				if(ok==1){
					Turn();

					return;
				} 
				else{
					setfillstyle(1,15); 
					bar(550,300,850,450); 
					settextstyle(10, 0, 1);

					setbkcolor(15);
					setcolor(4);

					drawCenteredText(700,350,"DO YOU WANT TO CANCEL?"); 
					setfillstyle(1,7); 
					bar(580,380,680,420); 
					settextstyle(10, 0, 2);

					setbkcolor(7);

					drawCenteredText(630,400,"YES"); 
					bar(720,380,820,420); 
					drawCenteredText(770,400,"NO"); 
					while(1){
						if(ismouseclick(WM_MOUSEMOVE)){
							getmouseclick(WM_MOUSEMOVE, mx, my);
							for(int i=0;i<=1;i++){
								if(mx>=580+140*i&&mx<=680+140*i&&my>=380&&my<=420){
									setcolor(4); 
									rectangle(580+140*i,380,680+140*i,420);
								}
								else{
									setcolor(15); 
									rectangle(580+140*i,380,680+140*i,420);
								} 
							}
						}
						int tam=0; 
						if(ismouseclick(WM_LBUTTONDOWN)){
							getmouseclick(WM_LBUTTONDOWN, mx, my);
							for(int z=0;z<=1;z++){
								if(mx>=580+140*z&&mx<=680+140*z&&my>=380&&my<=420){
									if(z==0){

										Turn();

										return; 
									} 
									else if(z==1){
										tam=1; 
										setfillstyle(1,14);
										bar(200,200,900,735);

										setfillstyle(1,7);
										
										for(int i=0;i<4;i++){
											setcolor(1);
											setbkcolor(14); 
											rectangle(399,184+100*i,1001,236+100*i);
											outtextxy(150,200+100*i,MENU[i]);
											bar(400,185+100*i,1000,235+100*i);
											setbkcolor(7); 
											setcolor(4);
											if(i==0&&A->SoHieuMB[0]!='\0'){
												outtextxy(420,200,A->SoHieuMB);
											}
											else if(i==0&&A->SoHieuMB[0]=='\0'){
												setcolor(15);
												outtextxy(420,200+100*i,MENU2[i]);
											}
											if(i==1&&A->LoaiMB[0]!='\0'){
												outtextxy(420,300,A->LoaiMB);
											}
											else if(i==1&&A->LoaiMB[0]=='\0'){
												setcolor(15);
												outtextxy(420,200+100*i,MENU2[i]);
											}
											if(i==2&&A->SoDong!=0){
												outtoxy(420,400,A->SoDong);
											}
											else if(i==2&&A->SoDong==0){
												setcolor(15);
												outtextxy(420,200+100*i,MENU2[i]);
											}
											if(i==3&&A->SoDay!=0){
												outtoxy(420,500,A->SoDay);
											} 
											else if(i==3&&A->SoDay==0){
												setcolor(15);
												outtextxy(420,200+100*i,MENU2[i]);
											}

										}
									} 
								}
							}
							clearmouseclick(WM_LBUTTONDOWN);

						}
						if(tam==1){
							break;
						}

						delay(50);
					}
				} 
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}
		else if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE, mx, my);
			for(int i=0;i<4;i++){
				if(mx>=400&&mx<=1000&&my>=185+100*i&&my<=235+100*i){
					setcolor(11);
					setbkcolor(8);
					setfillstyle(1,8);
					bar(400,185+100*i,1000,235+100*i);
				}
				else if(mx!=-1&&my!=-1){
					setcolor(4);
					setbkcolor(7);
					setfillstyle(1,7);
					bar(400,185+100*i,1000,235+100*i);
				}
				if(i==0&&A->SoHieuMB[0]!='\0'){
					outtextxy(420,200,A->SoHieuMB);
				}
				else if(i==0&&A->SoHieuMB[0]=='\0'){
					setcolor(15);
					outtextxy(420,200+100*i,MENU2[i]);
				}
				if(i==1&&A->LoaiMB[0]!='\0'){
					outtextxy(420,300,A->LoaiMB);
				}
				else if(i==1&&A->LoaiMB[0]=='\0'){
					setcolor(15);
					outtextxy(420,200+100*i,MENU2[i]);
				}
				if(i==2&&A->SoDong!=0){
					outtoxy(420,400,A->SoDong);
				}
				else if(i==2&&A->SoDong==0){
					setcolor(15);
					outtextxy(420,200+100*i,MENU2[i]);
				}
				if(i==3&&A->SoDay!=0){
					outtoxy(420,500,A->SoDay);
				} 
				else if(i==3&&A->SoDay==0){
					setcolor(15);
					outtextxy(420,200+100*i,MENU2[i]);
				}

			}
			if(mx>=20&&mx<=80&&my>=100&&my<=160){
				setcolor(4);
				rectangle(20,100,80,160);
			}
			else{
				setcolor(14);
				rectangle(20,100,80,160);
			}
			if(mx>=1190&&mx<=1300&&my>=660&&my<=700){
				setcolor(4);
				rectangle(1190,660,1300,700);
			}
			else{
				setcolor(14);
				rectangle(1190,660,1300,700);
			}
			setcolor(4);
		}

		delay(100);

	} 
}

void sua(DSMayBay &maybay, int x, int y,int n,int CK,FlightNode* &CB){
	setfillstyle(1,15);
	bar(10,50,1390,740);
	setfillstyle(1,14);
	bar(15,55,1385,735);
	setbkcolor(14);
	setcolor(4);
	char MENU[4][30]={"So Hieu May Bay",
						"Loai May Bay",
						"So Dong",
						"So Day",
					};
	int m=0;
	setfillstyle(1,7);
	bar(20,100,80,160);
	settextstyle(10, 0, 1);
	setbkcolor(7);
	drawCenteredText(50,130,"<BACK");
	settextstyle(0, 0, 3);
	setbkcolor(14);
	drawCenteredText(700,100,"ADJUST PLANE"); 
	setfillstyle(1,15);
	bar(1100,185,1350,235); 
	drawCenteredText(1225,210,"*NOTE");
	setfillstyle(1,7);
	setbkcolor(7);
	bar(1100,235,1350,430); 
	setcolor(1); 
	settextstyle(10, 0, 2);
	drawCenteredText(1225,250,"So hieu may bay"); 
	drawCenteredText(1225,280,"Loai may bay"); 
	drawCenteredText(1225,310,"Nhap tu 0-9, A-Z");
	drawCenteredText(1240,340," > So dong >= ");
	drawCenteredText(1240,370," > So day  >= ");
	drawCenteredText(1225,400,"So dong*So day >= 20");
	setbkcolor(14);
	for(int i=0;i<4;i++){
		outtextxy(150,200+100*i,MENU[i]);
		rectangle(399,184+100*i,1001,236+100*i);
	}
	setfillstyle(1,7);
	setcolor(4);
	setbkcolor(7);
	for(int i=n;i<n+10;i++){
		if(x>=100&&x<=1300&&y>=100+50*(i-n+1)&&y<=150+50*(i-n+1)){
			bar(400,185,1000,235);
			outtextxy(420,200,maybay.n[i-1]->SoHieuMB);
			bar(400,285,1000,335);
			outtextxy(420,300,maybay.n[i-1]->LoaiMB);
			bar(400,385,1000,435);
			outtoxy(420,400,maybay.n[i-1]->SoDong);
			bar(400,485,1000,535);
			outtoxy(420,500,maybay.n[i-1]->SoDay);

			m=i-1;
		}
	}
	int mx,my;

	//Bien TAM de luu lai cau hinh cu phong khi nguoi nhap doi y 

	MayBay TAM;
	strcpy(TAM.LoaiMB,maybay.n[m]->LoaiMB);
	strcpy(TAM.SoHieuMB,maybay.n[m]->SoHieuMB);
	TAM.SoDay=maybay.n[m]->SoDay;
	TAM.SoDong=maybay.n[m]->SoDong; 
	setcolor(1);
	bar(1085,95,1370,150); 
	rectangle(1085,95,1370,150);
	setcolor(4);
	if(CK==0){
		outtoxy(1315,330,1);
		outtoxy(1315,360,1);
		outtextxy(1100,100," May bay nay chua duoc");
		outtextxy(1100,125,"cai dat cho chuyen bay");
	}
	else{
		outtoxy(1315,330,TAM.SoDong);
		outtoxy(1315,360,TAM.SoDay);
		outtextxy(1100,100," May bay nay da duoc");
		outtextxy(1100,125,"cai dat cho chuyen bay");
	}

	outtoxy(1120,330,100);
	outtoxy(1120,360,100);
	int OK=0;
	while(1){
		setbkcolor(14);
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, mx, my);
			dondep();
			setbkcolor(8);
			for(int i=0;i<=3;i++){
				if(mx>=400&&mx<=1000&&my>=185+100*i&&my<=235+100*i){
					setcolor(11);
					if(i==0){
						//if(CB->flight.ticket==NULL){
							int ok;//Bien check trung ten 
							//CHECK trung ten 
							while(1){
								ok=0;
								setbkcolor(8); 
								nhap(maybay.n[m]->SoHieuMB,15,420,200); 
								for(int i=0;i<maybay.SoMayBay;i++){
									if(strcmp(maybay.n[m]->SoHieuMB,maybay.n[i]->SoHieuMB)==0&&i!=m){
										setfillstyle(1,14);
										bar(400,120,1000,180);
										delay(50);
										setbkcolor(14); 
										setcolor(4);
										outtextxy(405,130,"Ma May Bay nay da ton tai!"); 
										outtextxy(405,150,"Moi tiep tuc nhap         "); 
										setcolor(11);
										setbkcolor(8); 
										ok=1;
										break;
									} 
								}
	
								delay(20); 
	
								if(ok==1){
									continue;
								}
								setfillstyle(1,14);
	
								bar(400,120,1000,180);
	
								break; 
							}
						//}
					}
					if(i==1){
						nhap(maybay.n[m]->LoaiMB,40,420,300);
					}
					if(i==2){
						if(CK==1){
							while(1){
								if(nhapso2(maybay.n[m]->SoDong,2,420,400)<TAM.SoDong){
									setbkcolor(14); 
									setfillstyle(1,14); 
									bar(400,340,1000,370); 
									delay(50); 
									setcolor(4);
									outtextxy(405,350,"Khong hop le,moi tiep tuc nhap!"); 
									setcolor(11);
									setbkcolor(8); 
									delay(20); 
									continue;
								}
								setfillstyle(1,14); 
								bar(400,340,1000,370); 
								break;
							}
						}
						else{
							while(1){
								if(nhapso2(maybay.n[m]->SoDong,2,420,400)*maybay.n[m]->SoDay<20){
									setbkcolor(14); 
									setfillstyle(1,14); 
									bar(400,340,1000,370); 
									delay(50); 
									setcolor(4);
									outtextxy(405,350,"Khong hop le,moi tiep tuc nhap!"); 
									setcolor(11);
									setbkcolor(8); 
									delay(20); 
									continue;
								}
								setfillstyle(1,14); 
								bar(400,340,1000,370); 
	
								break;
							}
						}
					}
					if(i==3){
						if(CK==1){
							while(1){
								if(nhapso2(maybay.n[m]->SoDay,2,420,500)<TAM.SoDay){
									setbkcolor(14); 
									setfillstyle(1,14); 
									bar(400,440,1000,470); 
									delay(50); 
									setcolor(4);
									outtextxy(405,450,"Khong hop le,moi tiep tuc nhap!"); 
									setbkcolor(8); 
									setcolor(11);
									continue;
								}
								setfillstyle(1,14); 
								bar(400,440,1000,470); 
	
								break;
							}
						}
						else{
							while(1){
								if(nhapso2(maybay.n[m]->SoDay,2,420,500)*maybay.n[m]->SoDong<20){
									setbkcolor(14); 
									setfillstyle(1,14); 
									bar(400,440,1000,470); 
									delay(50); 
									setcolor(4);
									outtextxy(405,450,"Khong hop le,moi tiep tuc nhap!"); 
									setbkcolor(8); 
									setcolor(11);
									continue;
								}
								setfillstyle(1,14); 
								bar(400,440,1000,470); 
								break;
							}
						}
						
					}
					OK=1;
				}
			}
			if(mx>=20&&mx<=80&&my>=100&&my<=160){
				if(OK==0){

					Turn();
					return; 
				}
				setbkcolor(15);

				setfillstyle(1,15); 
				bar(550,300,850,450); 
				settextstyle(10, 0, 1);
				drawCenteredText(700,350,"DO YOU WANT TO APPLY?"); 
				setfillstyle(1,7); 
				bar(580,380,680,420); 
				settextstyle(10, 0, 2);

				setbkcolor(7);

				drawCenteredText(630,400,"YES"); 
				bar(720,380,820,420); 
				drawCenteredText(770,400,"NO"); 
				while(1){
					if(ismouseclick(WM_MOUSEMOVE)){
						getmouseclick(WM_MOUSEMOVE, mx, my);
						for(int i=0;i<=1;i++){
							if(mx>=580+140*i&&mx<=680+140*i&&my>=380&&my<=420){
								setcolor(4); 
								rectangle(580+140*i,380,680+140*i,420);
							}
							else{
								setcolor(15); 
								rectangle(580+140*i,380,680+140*i,420);
							} 
						}
					}
					int ok=0; 
					if(ismouseclick(WM_LBUTTONDOWN)){
						getmouseclick(WM_LBUTTONDOWN, mx, my);
						for(int z=0;z<=1;z++){
							if(mx>=580+140*z&&mx<=680+140*z&&my>=380&&my<=420){
								if(z==0){
									Turn();
									FlightNode* P=CB;
									while(P!=NULL){
										if(strcmp(TAM.SoHieuMB,P->flight.planeID)==0){
											strcpy(P->flight.planeID,maybay.n[m]->SoHieuMB);
											char ***newticket = newTicket(maybay.n[m]->SoDay,maybay.n[m]->SoDong);
											for(int i=0;i<TAM.SoDay;i++){
												for(int j=0;j<TAM.SoDong;j++){
													strcpy(newticket[i][j],P->flight.ticket[i][j]);
												}
											}
											deleteTicket(P->flight.ticket,TAM.SoDay,TAM.SoDong);
											P->flight.ticket=newticket;
											if(P->flight.status==HETVE)
												P->flight.status=CONVE;
										}
										P=P->next;
									}
									if(!save_flight_to_file("Data\\Flights.dat", CB, maybay)){
										cout<<"Luu khong thanh cong!"<<'\n';
									}
									delete P; 
									return; 
								} 
								else if(z==1){
									strcpy(maybay.n[m]->LoaiMB,TAM.LoaiMB);
									strcpy(maybay.n[m]->SoHieuMB,TAM.SoHieuMB);
									maybay.n[m]->SoDay=TAM.SoDay;
									maybay.n[m]->SoDong=TAM.SoDong; 
									Turn();
									return; 
								} 
							}
						}
					}

					delay(50); 
				}
			}
			clearmouseclick(WM_LBUTTONDOWN);

		}
		else if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE, mx, my);
			for(int i=0;i<4;i++){

				if(mx>=400&&mx<=1000&&my>=185+100*i&&my<=235+100*i){
					setcolor(11);
					setbkcolor(8);
					setfillstyle(1,8);
					bar(400,185+100*i,1000,235+100*i);
				}
				else if(x!=-1&&y!=-1){
					setcolor(4);
					setbkcolor(7);
					setfillstyle(1,7);
					bar(400,185+100*i,1000,235+100*i);
				}
				if(i==0){
					outtextxy(420,200,maybay.n[m]->SoHieuMB);
				}
				if(i==1){
					outtextxy(420,300,maybay.n[m]->LoaiMB);
				}
				if(i==2){
					outtoxy(420,400,maybay.n[m]->SoDong);
				}
				if(i==3){
					outtoxy(420,500,maybay.n[m]->SoDay);

				} 
			}
			if(mx>=20&&mx<=80&&my>=100&&my<=160){
				setcolor(4);
				rectangle(20,100,80,160);
			}
			else{
				setcolor(14);
				rectangle(20,100,80,160);
			}
			setcolor(4);
		}
		delay(50);
	}
}

void CurrentTime(Date &a) {
     time_t currentTime =  time(nullptr);
     tm* localTime =  localtime(&currentTime);
     a.year=(localTime->tm_year + 1900);
	 a.month=(localTime->tm_mon + 1);
	 a.day= localTime->tm_mday;
	 a.hour= localTime->tm_hour;
	 a.minute=localTime->tm_min;
}

bool Time(Flight A){
	Date HT;
    CurrentTime(HT); 
    if (A.date.year<HT.year) {
        return 1;
    } 
    else if (A.date.year==HT.year&&A.date.month<HT.month) {
        return 1;
    }
    else if (A.date.year==HT.year&&A.date.month==HT.month&&A.date.day<HT.day) {
        return 1;
    } 
    else if (A.date.year==HT.year&&A.date.month==HT.month&&A.date.day==HT.day&&A.date.hour<HT.hour) {
        return 1;
    } 
    else if (A.date.year==HT.year&& A.date.month==HT.month && A.date.day == HT.day&&A.date.hour==HT.hour&&A.date.minute<HT.minute) {
        return 1;
    } 
    else {
        return 0;
    } 
}

void swap(ThongKe* a, ThongKe* b) {
    ThongKe temp = *a;
    *a = *b;
    *b = temp;
}

void Sort(ThongKe* L[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (L[j]->dem < L[j + 1]->dem) {
                swap(L[j], L[j + 1]);
            }
        }
    }
}

void THONGKE(DSMayBay &maybay, FlightNode *A){
	ThongKe *LIST[maybay.SoMayBay]; 
    for (int i = 0; i < maybay.SoMayBay; i++) {
    	LIST[i] = new ThongKe();
        strcpy(LIST[i]->soHieuMB, maybay.n[i]->SoHieuMB); 
        LIST[i]->dem=0; 
    } 
    while (A != nullptr) {
        if (A->flight.status == 3){
            for (int i = 0; i < maybay.SoMayBay; i++) {
                if (strcmp(A->flight.planeID, LIST[i]->soHieuMB) == 0) {
                    LIST[i]->dem++; 
                    break; 
                }    
            }
        } 
        A = A->next; 
    } 
    Sort(LIST, maybay.SoMayBay);
	setfillstyle(1,15);
	bar(10,50,1390,740);
	setfillstyle(1,14);
	bar(15,55,1385,735);
	setfillstyle(1,7);
	bar(20,100,80,160);
	settextstyle(10, 0, 1);
	setbkcolor(7);
	setcolor(4); 
	drawCenteredText(50,130,"<BACK");
	setbkcolor(14);
	setcolor(4);
	settextstyle(0,0, 5);
	drawCenteredText(700,100,"THONG KE MAY BAY"); 
	settextstyle(10,0, 2);
	setlinestyle(0,0,2); 
	setfillstyle(1,0);
	bar(450,175,950,225);
	setbkcolor(0);
	setcolor(11);
	rectangle(449,174,951,176+50);
	rectangle(550,174,770,225); 
	setcolor(14); 
	bar(615,690,665,720);
	bar(735,690,785,720);
	drawCenteredText(640,705,"<");
	drawCenteredText(760,705,">");
	drawCenteredText(500,200,"STT"); 
	drawCenteredText(655,200,"SO HIEU MAY BAY"); 
	drawCenteredText(855,200,"SO LAN BAY"); 
	int x=0; 
	char d; 
	while(kbhit()){
		char d=getch(); 
	} 
	int ok=1; 
	while(1){
		int a,b; 
		setcolor(0);
		setbkcolor(14); 
		outtoxy(675,695,(x+9)/9);
		outtextxy(693,695,"/");
		outtoxy(712,695,(maybay.SoMayBay+8)/9);
		setbkcolor(0); 
		for(int i=x;i<x+9;i++){
			if(i==maybay.SoMayBay){
				break; 
			} 
			setfillstyle(1,0); 
			bar(450,175+50*(i-x+1),950,225+50*(i-x+1));
			setcolor(11); 
			rectangle(449,175+50*(i-x+1),951,225+50*(i-x+1));
			rectangle(550,175+50*(i-x+1),770,225+50*(i-x+1)); 
			setcolor(14); 
			drawCenteredText(655,250+50*(i-x),LIST[i]->soHieuMB); 
			outtoxy(850,240+50*(i-x),LIST[i]->dem); 
			outtoxy(490,240+50*(i-x),i+1); 
		} 
		while(1){
			int Ko=0; 
			if(ismouseclick(WM_MOUSEMOVE)){
				getmouseclick(WM_MOUSEMOVE, a, b);
				if(a>=20&&a<=80&&b>=100&&b<=160){
	
					setcolor(4);
					rectangle(20,100,80,160);
				}
				else{
					setcolor(14);
					rectangle(20,100,80,160);
				}
				for(int i=0;i<=1;i++){
					if(a>=615+120*i&&a<=665+120*i&&b>=690&&b<=720){
						setcolor(4);
						rectangle(615+120*i,690,665+120*i,720);
					}
					else{
						setcolor(3);
						rectangle(615+120*i,690,665+120*i,720);
					}
				}
			}
			else if(ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN, a, b);
				if(a>=20&&a<=80&&b>=100&&b<=160){
					clearmouseclick(WM_RBUTTONDOWN);
					Turn();
					for(int j=0;j<maybay.SoMayBay;j++){
						delete LIST[j]; 
					} 
					return; 
				} 
				for(int i=0;i<=1;i++){
					if(a>=615+120*i&&a<=665+120*i&&b>=690&&b<=720){
						if(i==0&&x>1){
							setfillstyle(1,14); 
							bar(100,225,1300,680); 
							x-=9;
						}
						else if(i==1&&x+9<maybay.SoMayBay){
							setfillstyle(1,14); 
							bar(100,225,1300,680); 
							x+=9;
						}
						Ko=1; 
					}
				}
				if(Ko==1){
					break; 
				} 
			}
			delay(50); 
		}
	} 
}

int Plane_processing(DSMayBay &maybay,FlightNode* CB){
    print_workspace();
	int start = 1; 
    int mx, my;
    setfillstyle(1,15);
	bar(10,50,1390,740);
	setfillstyle(1,0); 
	bar(100,100,1300,665); 
	settextstyle(10, 0, 2);
	setcolor(14);
	setbkcolor(0); 
	outtextxy(100,690,"*Chuot phai de xoa"); 
	outtextxy(100,710,"Chuot trai de sua "); 
	bar(615,690,665,720);
	bar(735,690,785,720);
	drawCenteredText(640,705,"<");
	drawCenteredText(760,705,">");
    while(true){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            for(int i = 0; i < MAX_TAB; i++){
                if(tab_button[i].inside(mx, my)){
                    unclick_tab(PLANE_TAB);
                    if(i == PLANE_TAB) return MAIN_MENU;
                    click_tab(i);
                    setfillstyle(1,3);
					bar(10,50,1390,740);
                    return i;
                }
            }
            int Check=0;
			for(int i=start;i<start+10;i++){
				if(i<=maybay.SoMayBay){
					if(mx>=100&&mx<=1300&&my>=100+50*(i-start+1)&&my<=150+50*(i-start+1)){
						MayBay Temp;
						strcpy(Temp.SoHieuMB,maybay.n[i-1]->SoHieuMB); 
						setfillstyle(1,15);
						bar(10,50,1390,740);
						FlightNode* P=CB;
						int check=0;
						while(P!=NULL){
							if(strcmp(maybay.n[i-1]->SoHieuMB,P->flight.planeID)==0){
								check=1;
							}
							P=P->next;
						}
						delete P;
						sua(maybay,mx,my,start,check,CB);
						graphic(); 
	
					}
				}
			}
			for(int i=0;i<=1;i++){
				if(mx>=615+120*i&&mx<=665+120*i&&my>=690&&my<=720){
					if(i==0&&start>1){
						start-=10;
						setfillstyle(1,0); 
						bar(100,100,1300,665); 
					}
					else if(i==1&&start+10<=maybay.SoMayBay){
						start+=10;
						setfillstyle(1,0); 
						bar(100,100,1300,665);  
					}
				}
			}
			if(mx>=1200&&mx<=1300&&my>=680&&my<=720){
				them(maybay);

				graphic(); 

			}
			if(mx>=1150&&mx<=1300&&my>=60&&my<=90){
				THONGKE(maybay,CB); 
				graphic(); 

			} 
        }
        else if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, mx, my);
            for(int i = 0; i < MAX_TAB; i++){
                if(tab_button[i].inside(mx, my))
                    tab_button[i].hover();
                else 
                    tab_button[i].unhover();
    
            }
            for(int i=0;i<=1;i++){
				if(mx>=615+120*i&&mx<=665+120*i&&my>=690&&my<=720){
					setcolor(4);
					rectangle(615+120*i,690,665+120*i,720);
				}
				else{
					setcolor(3);
					rectangle(615+120*i,690,665+120*i,720);
				}
			}
			setlinestyle(0, 0, 2);
			if(mx>=1200&&mx<=1300&&my>=680&&my<=720){
				setcolor(4);
				rectangle(1199,679,1301,721);
			}
			else{
				setcolor(11);
				rectangle(1199,679,1301,721);
			}
			if(mx>=1150&&mx<=1300&&my>=60&&my<=90){
				setcolor(4);
				rectangle(1149,59,1301,91);
			} 
			else{
				setcolor(11);
				rectangle(1149,59,1301,91);
			} 
		}
		else  if (ismouseclick(WM_RBUTTONDOWN)) {
            getmouseclick(WM_RBUTTONDOWN, mx, my); 
            for(int i=start;i<start+10;i++){
            	if(i<=maybay.SoMayBay){
					if(mx>=100&&mx<=1300&&my>100+50*(i-start+1)&&my<=150+50*(i-start+1)){
						FlightNode* P=CB;
						int check=0;
						while(P!=NULL){
							if(strcmp(maybay.n[i-1]->SoHieuMB,P->flight.planeID)==0){
								check=1;
							}
							P=P->next;
						}
						delete P;
						int ok=0; 
						if(check==0){
							setbkcolor(15); 
							setcolor(4); 
							setfillstyle(1,15); 
							bar(550,300,850,450); 
							settextstyle(10, 0, 1);
							drawCenteredText(700,350,"DO YOU WANT TO DELETE?"); 
							setfillstyle(1,7); 
							bar(580,380,680,420); 
							settextstyle(0, 0, 2);
							setbkcolor(7); 
							drawCenteredText(630,400,"Cancel"); 
							bar(720,380,820,420); 
							drawCenteredText(770,400,"Ok"); 
							while(1){
								if(ismouseclick(WM_MOUSEMOVE)){
									getmouseclick(WM_MOUSEMOVE, mx, my);
									for(int i=0;i<=1;i++){
										if(mx>=580+140*i&&mx<=680+140*i&&my>=380&&my<=420){
											setcolor(4); 
											rectangle(580+140*i,380,680+140*i,420);
										}
										else{
											setcolor(15); 
											rectangle(580+140*i,380,680+140*i,420);
										} 
									}
								}
								
								if(ismouseclick(WM_LBUTTONDOWN)){
									getmouseclick(WM_LBUTTONDOWN, mx, my);
									for(int z=0;z<=1;z++){
										if(mx>=580+140*z&&mx<=680+140*z&&my>=380&&my<=420){
											if(z==0){
												ok=1; 
												setfillstyle(1,0); 
												bar(100,100,1300,665); 
											}
											if(z==1){
												ok=1; 
												xoa(maybay,i);
												Turn();
												graphic();
											}
										}
									}
								}
								if(ok==1){
									break;
								}
							}
						}
						else{
							setcolor(4);
							setbkcolor(15);
							setfillstyle(1,15); 
							bar(550,300,850,450); 
							settextstyle(10, 0, 1);
							drawCenteredText(700,350,"XOA KHONG THANH CONG"); 
							setfillstyle(1,7); 
							bar(580,380,640,420); 
							settextstyle(10, 0, 1);
							setbkcolor(7); 
							drawCenteredText(605,400,"OK"); 
							bar(655,380,820,420); 
							drawCenteredText(740,400,"Xem chi tiet"); 
							while(1){
								if(ismouseclick(WM_MOUSEMOVE)){
									getmouseclick(WM_MOUSEMOVE, mx, my);
									if(mx>=580&&mx<=640&&my>=380&&my<=420){
											setcolor(4); 
											rectangle(580,380,640,420);
									}
									else{
										setcolor(15); 
										rectangle(580,380,640,420);
									} 
									if(mx>=655&&mx<=820&&my>=380&&my<=420){
											setcolor(4); 
											rectangle(655,380,820,420);
									}
									else{
										setcolor(15); 
										rectangle(655,380,820,420);
									} 
								}
								int oK=0; 
								if(ismouseclick(WM_LBUTTONDOWN)){
									getmouseclick(WM_LBUTTONDOWN, mx, my);
									if(mx>=580&&mx<=640&&my>=380&&my<=420){
										setfillstyle(1,0); 
										bar(100,100,1300,665); 
										setcolor(14);
										setbkcolor(0);
										break; 
									}
									if(mx>=655&&mx<=820&&my>=380&&my<=420){
										char MENU[5][50]={	"STT",
														"MA CHUYEN BAY",
														"NGAY GIO KHOI HANH",
														"NOI DEN",
														"TRANG THAI",
										}; 
										setfillstyle(1,15);
										bar(10,50,1390,740);
										setfillstyle(1,14);
										bar(15,55,1385,735);
										settextstyle(10,0,2); 
										setbkcolor(14); 
										outtextxy(250,100,"VI MA MAY BAY       DA DUOC THIET LAP CHO CAC CHUYEN BAY SAU, NEN KHONG THE XOA");
										setcolor(1); 
										outtextxy(420,100,maybay.n[i-1]->SoHieuMB); 
										FlightNode* PP=CB;
										int k=0; 
										setcolor(14); 
										setbkcolor(0);
										setfillstyle(1,0);
										bar(50,150,1350,200);
										while(PP!=NULL){
											if(strcmp(maybay.n[i-1]->SoHieuMB,PP->flight.planeID)==0){
												bar(50,150+50*(k+1),1350,200+50*(k+1));
												outtoxy(100,215+50*k,k+1); 
												drawCenteredText(285,225+50*k,PP->flight.flightID); 
												if(PP->flight.date.hour>9){
													outtoxy(490,215+50*k,PP->flight.date.hour);
												} 
												else{
													outtoxy(490,215+50*k,0);
													outtoxy(500,215+50*k,PP->flight.date.hour);
												} 
												outtextxy(520,215+50*k,":");
												if(PP->flight.date.minute>9) {
													outtoxy(535,215+50*k,PP->flight.date.minute);
												}
												else{
													outtoxy(535,215+50*k,0);
													outtoxy(545,215+50*k,PP->flight.date.minute);
												} 
												if(PP->flight.date.day>9){
													outtoxy(575,215+50*k,PP->flight.date.day);
												} 
												else{
													outtoxy(575,215+50*k,0);
													outtoxy(585,215+50*k,PP->flight.date.day);
												} 
												outtextxy(600,215+50*k,"/");
												if(PP->flight.date.month>9){
													outtoxy(617,215+50*k,PP->flight.date.month);
												} 
												else{
													outtoxy(617,215+50*k,0);
													outtoxy(627,215+50*k,PP->flight.date.month);
												} 
												outtextxy(645,215+50*k,"/");
												outtoxy(660,215+50*k,PP->flight.date.year);
												drawCenteredText(1000,225+50*k,PP->flight.arrive);
												if(PP->flight.status==0){
													drawCenteredText(1275,225+50*k,"HUY CHUYEN");
												} 
												if(PP->flight.status==1){
													drawCenteredText(1275,225+50*k,"CON VE");
												} 
												if(PP->flight.status==2){
													drawCenteredText(1275,225+50*k,"HET VE");
												} 
												if(PP->flight.status==3){
													drawCenteredText(1275,225+50*k,"HOAN TAT");
												} 
												k++; 
											}
											PP=PP->next;
										}
										delete PP; 
										drawCenteredText(110,175,MENU[0]);
										drawCenteredText(285,175,MENU[1]);
										drawCenteredText(600,175,MENU[2]);
										drawCenteredText(1000,175,MENU[3]);
										drawCenteredText(1275,175,MENU[4]);
										setcolor(11);
										rectangle(50,150,1350,200); 
										rectangle(50,150,170,200+50*k); 
										rectangle(170,150,400,200+50*k); 
										rectangle(400,150,800,200+50*k); 
										rectangle(800,150,1200,200+50*k); 
										rectangle(1200,150,1350,200+50*k); 
										setbkcolor(14); 
										setcolor(4); 
									//	outtextxy(100,230+50*k,"Trang Thai( 0: Huy chuyen, 1: Con ve, 2: het ve, 3: hoan tat )");
										setfillstyle(1,7); 
										bar(20,80,80,140);
										settextstyle(10, 0, 1);
										setbkcolor(7);
										setcolor(4); 
										drawCenteredText(50,110,"<BACK");
										while(1){
											int a,b; 
											if(ismouseclick(WM_MOUSEMOVE)){
												getmouseclick(WM_MOUSEMOVE, a, b);
												if(a>=20&&a<=80&&b>=80&&b<=140){ 
													setcolor(4);
												} 
												else{
													setcolor(14);
												} 
												rectangle(19,79,81,141); 
											}
											else if(ismouseclick(WM_LBUTTONDOWN)){
												getmouseclick(WM_LBUTTONDOWN, a, b);
												if(a>=20&&a<=80&&b>=80&&b<=140){
													Turn();
													graphic(); 
													oK=1; 
													break; 
												} 
											}
											delay(50); 
										}
										if(oK==1){
											break; 
										} 
									}
								}
								delay(50); 
							}
							clearmouseclick(WM_LBUTTONDOWN);
	//						if(ok==1){
	//							break; 
	//						} 
							delay(50); 
						} 
						break; 
					}
				}
			}
			clearmouseclick(WM_RBUTTONDOWN);
        }
        savedata(maybay); 
		Chucnang1(mx,my,maybay,start); 
		delay(30);
	}
}
