//
// Created by zabogdan on 12/29/20.
//

#include "menu.h"

void primaryPage()
{
//    cleardevice();
//    setactivepage(0);
    drawButton(150,150,"Small",1);
    drawButton(450,450,"Medium",2);
    drawButton(850,550,"Big",3);
}
void secondaryPage()
{
    cleardevice();
    setactivepage(1);
    drawButton(100,100,"Small",1);
}

void mainLoop()
{

    /* select driver and mode that supports multiple pages */
    int gdriver = EGA, gmode = EGAHI, errorcode;
    int x, y, ht;

    /* initialize graphics and local variables */






    int xMouse,yMouse;
    initwindow(maxWidth,maxHeigh);
//    primaryPage();
//    setvisualpage(0);
//    clearviewport();
    rectangle(200,320,300,380);
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
//            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            cout << "COORD X: " << x << " COORD Y: " << y;
//            if ((x>=200 && x<=300 && y>=320&&y<=380))
//                gata=true;
        }
    }
    while (true);
//    char ch='0';
//    do {
//        SDL_PumpEvents();
//        SDL_GetMouseState(&xMouse,&yMouse);
//        cout << "MOUSE POSITIONS: " << xMouse << " " << yMouse << endl;
//        if(ch == '0')
//        {
//            primaryPage();
//            setvisualpage(0);
//        }
//        if(ch == '1')
//        {
//            secondaryPage();
//            setvisualpage(1);
//        }
//        delay(10000);
//    }while(ch!='x');


    /* clean up */
    getch();
    closegraph();
}