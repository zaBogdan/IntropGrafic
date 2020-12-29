//
// Created by zabogdan on 12/29/20.
//

#include "menu.h"

void loadingPage()
{
//    int gdriver=DETECT,gmode;
//    initgraph(&gdriver,&gmode);
    cleardevice();
}
void primaryPage()
{
//    cleardevice();
    setactivepage(0);
    drawButton(150,150,"Small",1);
    drawButton(450,450,"Medium",2);
    drawButton(850,550,"Big",3);
}
void secondaryPage()
{
//    cleardevice();
    setactivepage(1);
    drawButton(300,300,"Small",1);
}

void mainLoop()
{

    /* select driver and mode that supports multiple pages */
    int gdriver = EGA, gmode = EGAHI, errorcode;
    int x, y, ht;
    initgraph(&gdriver,&gmode, "test");
    cleardevice();
    clearviewport();

    secondaryPage();
    primaryPage();
    int activePage = 0;

//    setvisualpage(activePage);
    do
    {
        x=mousex();
        y=mousey();
        cout << "COORD X: " << x << " COORD Y: " << y << '\n';
        if(ismouseclick(WM_LBUTTONDOWN))
        {
//            IDK WHY THIS MUST BE HERE????
        }
        if((x<=180 && x>=140) && (y>=130 && y<=170))
        {
            activePage = 1;
        }
        else
            activePage = 0;
        setvisualpage(activePage);
        delay(1000/frames);
    }
    while (true);



    /* clean up */
    getch();
    closegraph();
}