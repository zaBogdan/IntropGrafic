//
// Created by zabogdan on 12/29/20.
//

#include "menu.h"
coord mouseC;
int activePage = 0;
int alreadyRenderedGraph = 0;
char input[]=" \0";

void  inputPage()
{
    setactivepage(1);
    //back button
    drawButton(maxWidth-30, 20, "<",0);
    inputText(100,100);
}


void mainLoop(vector<string> postfix)
{

    /* select driver and mode that supports multiple pages */
    int gdriver = EGA, gmode = EGAHI, errorcode;
    int x, y, ht;
    initgraph(&gdriver,&gmode, "test");
    cleardevice();
    clearviewport();

    inputPage();
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

            inputPage();
            alreadyRenderedGraph=1;
            //drawGraph(postfix);
        }
        if(activePage==2)
        {
            activePage=2;
            secondaryPage();
        }
        if(activePage==3)
        {
            activePage=3;
            thirdPage();
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
        //when we need to get input we can't have delay!
        if(activePage!=1)
        delay(1000/frames);
    }
    while (true);
    quit();
}

void quit()
{
    closegraph();
}
void secondaryPage()
{
    setactivepage(2);
    drawButton(30, 20, "<",0);
    char title[] = "This are your settings";
    settextstyle(0,0,4);
    outtextxy(maxWidth/2-textwidth(title)/2,100, title);
    settextstyle(0,0,0);

}
void thirdPage()
{
    setactivepage(3);
    drawButton(30, 20, "<",0);
    char title[] = "Drawing a graph";
    settextstyle(0,0,4);
    outtextxy(maxWidth/2-textwidth(title)/2,100, title);
    settextstyle(0,0,0);
    char basic[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas a ex sodales, facilisis justo ut, blandit metus. Nunc non efficitur justo. Vestibulum at dictum libero. Maecenas placerat libero quis purus dapibus, id laoreet mauris sodales. Pellentesque et auctor sapien, vitae eleifend mi. Nullam massa enim, placerat a nunc in, eleifend facilisis nisl. Proin sit amet placerat leo. Vestibulum sit amet leo id dolor egestas congue.";
    outtextxy(50,400, basic);
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
    drawButton(maxWidth/2,400,set,2);
    drawButton(maxWidth/2,500,inf,3);
    drawButton(maxWidth/2,600,quit,-1);

    char buildVersion[] = "Debug build 0.5";
    settextstyle(0,0,0);
    outtextxy(maxWidth-textwidth(buildVersion)-30,maxHeigh-30, buildVersion);
}