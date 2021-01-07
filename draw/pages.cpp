//
// Created by Bogdan Zavadovschi on 07.01.2021.
//

#include "pages.h"

void mainMenuPage(coord mouse)
{
    setactivepage(0);
    char projectTitle[] = "Grafic";
    char projectSubtitle[] = "We are the new Desmos";
    char imagePath[] = "../assets/logo.bmp";
    char draw[] = "Draw";
    char set[] = "Settings";
    char inf[] = "Information";
    char quit[] = "Quit";
    char buildVersion[] = "Debug build 0.5";

    //draw title and subtitle
    settextstyle(0,0,5);
    outtextxy(maxWidth/2-textwidth(projectTitle)/2,100, projectTitle);
    settextstyle(0,0,2);
    outtextxy(maxWidth/2-textwidth(projectSubtitle)/2+25,150, projectSubtitle);
    readimagefile(imagePath,200,50,350,200);

    //draw the buttons
    drawButton(maxWidth/2,300,mouse,draw,1);
    drawButton(maxWidth/2,400,mouse,set,2);
    drawButton(maxWidth/2,500,mouse,inf,3);
    drawButton(maxWidth/2,600,mouse,quit,-1);

    //set the version build
    settextstyle(0,0,0);
    outtextxy(maxWidth-textwidth(buildVersion)-30,maxHeigh-30, buildVersion);
}
void inputFunction(coord mouse)
{
    pageInit(1, "Input function", mouse);
    setvisualpage(1);
    //input this and then compute the postfix version and print the c++ header
    textInputBar(coord{100,400}, mouse);
}

void settingsPage(coord mouse)
{
    char language[] = "Your lange is: ";
    char axis_arrows[] = "Arrows to axis: ";
    char axis_numbers[] = "Add numers to axis: ";
    char minor_gridlines[] = "Minor gridlines: ";
    char measure[] = "Measure in: ";

    pageInit(2, "Settings", mouse);

    settextstyle(0,0,2);
    //settings
    outtextxy(50,300, language);
    outtextxy(50,350, axis_arrows);
    outtextxy(50,400, axis_numbers);
    outtextxy(50,450, minor_gridlines);
    outtextxy(50,500, measure);

}

void informationPage(coord mouse)
{

    pageInit(3, "Information", mouse);
    outtextxy(10,300, "I will write this later.");

}

void pageInit(int id, char* name, coord mouse)
{
    setactivepage(id);
    char backButton[] = "<";
    //back button
    drawButton(40,40,mouse,backButton,0);

    //title
    settextstyle(0,0,3);
    outtextxy(maxWidth/2-textwidth(name)/2,100, name);

    //reset to default
    settextstyle(0,0,0);
}