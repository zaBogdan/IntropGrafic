//
// Created by zabogdan on 12/29/20.
//

#include "menu.h"
coord mouseC;
int activePage = 0;

void  drawPage()
{
    setactivepage(1);
//    drawButton(maxWidth-200, 100, "Back", 0);
}


void secondaryPage()
{
    setactivepage(2);
    drawButton(300,300,"Small",0);
}

void mainLoop(vector<string> postfix)
{

    /* select driver and mode that supports multiple pages */
    int gdriver = EGA, gmode = EGAHI, errorcode;
    int x, y, ht;
    initgraph(&gdriver,&gmode, "test");
    cleardevice();
    clearviewport();

    secondaryPage();
    primaryPage();

    do
    {
        mouseC.x=mousex();
        mouseC.y=mousey();
        if(ismouseclick(WM_LBUTTONDOWN))
        {
//            IDK WHY THIS MUST BE HERE????
        }

        if(activePage==1)
        {
            activePage=1;
            drawPage();
            drawGraph(postfix);
        }
        if(activePage==2)
        {
            activePage=2;
            secondaryPage();
        }
        if(activePage==0)
        {
            activePage = 0;
            primaryPage();
        }
        if(activePage==-1)
        {
            quit();
            break;
        }
        setvisualpage(activePage);
        delay(1000/frames);
    }
    while (true);
    quit();
}

void quit()
{
    closegraph();
}
void primaryPage()
{
    setactivepage(0);
    char projectTitle[] = "Grafic";
    char projectSubtitle[] = "We are the new Desmos";
    char imagePath[] = "../assets/logo.bmp";
    settextstyle(0,0,5);
    outtextxy(maxWidth/2-textwidth(projectTitle)/2,100, projectTitle);
    settextstyle(0,0,2);
    outtextxy(maxWidth/2-textwidth(projectSubtitle)/2+25,150, projectSubtitle);
    readimagefile(imagePath,200,50,350,200);

    char draw[] = "Draw";
    char set[] = "Settings";
    char inf[] = "Information";
    char quit[] = "Quit";
    drawButton(maxWidth/2,300,draw,1);
    drawButton(maxWidth/2,400,set,0);
    drawButton(maxWidth/2,500,inf,2);
    drawButton(maxWidth/2,600,quit,-1);

    char buildVersion[] = "Debug build 0.5";
    settextstyle(0,0,0);
    outtextxy(maxWidth-textwidth(buildVersion)-30,maxHeigh-30, buildVersion);
}