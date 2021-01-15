//
// Created by Bogdan Zavadovschi on 07.01.2021.
//

#include "pages.h"


void mainMenuPage(coord mouse)
{
    char imagePath[100] = "../assets/logo.bmp";

    setactivepage(0);

    char title[100],projectSubtitle[100],draw[100];
    char set[100],inf[100],quit[100],buildVersion[100];

    strcpy(projectSubtitle, language["projectSubtitle"].c_str());
    strcpy(draw, language["draw"].c_str());
    strcpy(set, language["settings"].c_str());
    strcpy(inf, language["information"].c_str());
    strcpy(quit, language["quit"].c_str());
    strcpy(buildVersion, language["buildVersion"].c_str());
    strcpy(title, language["projectTitle"].c_str());

    //draw title and subtitle
    settextstyle(0,0,5);
    outtextxy(maxWidth/2-textwidth(title)/2,100, title);
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
    char pageName[100], draw_function[100];
    strcpy(pageName, language["input_title"].c_str());
    strcpy(draw_function, language["draw_function"].c_str());

    pageInit(1, pageName, mouse);
    setvisualpage(1);
    //input this and then compute the postfix version and print the c++ header
    textInputBar(coord{maxWidth/2,400}, mouse);
    //back button
    drawButton(maxWidth/2,500,mouse,draw_function,10);
    if(activePage==10)
    {
        needsModified=true;
        activePage=1;
    }
}
void drawPage(coord mouse)
{
    char pageName[100] = "Draw";
    pageInit(5, pageName, mouse);
    cleardevice();
    drawGraph();
    delay(1000);
    cleardevice();
    activePage=1;
}

void settingsPage(coord mouse)
{
    char pageName[100],lang[100],axis_arrows[100],axis_numbers[100];
    char minor_gridlines[100],measure[100],english[100],romanian[100];
    char yes[100],no[100],radians[100],degrees[100],save[100];
    char failedToSave[100],savedSuccessfull[100];

    strcpy(pageName, language["settingsPage"].c_str());
    pageInit(2, pageName, mouse);

    strcpy(lang, language["your_language"].c_str());
    strcpy(axis_arrows, language["draw_axis_arrows"].c_str());
    strcpy(axis_numbers, language["draw_axis_numbers"].c_str());
    strcpy(minor_gridlines, language["draw_minor_gridlines"].c_str());
    strcpy(measure, language["measure_in"].c_str());
    strcpy(yes, language["yes"].c_str());
    strcpy(no, language["no"].c_str());
    strcpy(romanian, language["lang_romanian"].c_str());
    strcpy(english, language["lang_english"].c_str());
    strcpy(save, language["save"].c_str());
    strcpy(failedToSave, language["error_save"].c_str());
    strcpy(savedSuccessfull, language["success_save"].c_str());

    strcpy(radians, language["radians"].c_str());
    strcpy(degrees, language["degrees"].c_str());

    settextstyle(0,0,2);
    //settings
    outtextxy(50,300, lang);
    outtextxy(50,370, axis_arrows);
    outtextxy(50,440, axis_numbers);
    outtextxy(50,510, minor_gridlines);
    outtextxy(50,580, measure);

    //language settings
    drawButton(400+textwidth(english)/2+10, 300, mouse, english, 10,1, (userSettings.language=="eng"));
    drawButton(600+textwidth(romanian)/2+10, 300, mouse, romanian, 11,1, (userSettings.language=="ro"));

    //axis_arrows
    drawButton(400+textwidth(yes)/2+10, 370, mouse, yes, 12,1, userSettings.axis_arrows);
    drawButton(500+textwidth(no)/2+10, 370, mouse, no, 13,1, !userSettings.axis_arrows);

    //axis_numbers
    drawButton(400+textwidth(yes)/2+10, 440, mouse, yes, 14,1, userSettings.axis_numbers);
    drawButton(500+textwidth(no)/2+10, 440, mouse, no, 15,1, !userSettings.axis_numbers);

    //minor_gridlines
    drawButton(400+textwidth(yes)/2+10, 510, mouse, yes, 16,1, userSettings.minor_gridlines);
    drawButton(500+textwidth(no)/2+10, 510, mouse, no, 17,1, !userSettings.minor_gridlines);

    //measure
    drawButton(400+textwidth(radians)/2+10, 580, mouse, radians, 18,1, (userSettings.measure=="radians"));
    drawButton(600+textwidth(degrees)/2+10, 580, mouse, degrees, 19,1, (userSettings.measure=="degrees"));

    //save
    drawButton(maxWidth/2, maxHeigh-100, mouse, save,20,2,0);
    int copyPage = activePage;


    switch(activePage)
    {
        case 10:
            userSettings.language="eng";
            break;
        case 11:
            userSettings.language="ro";
            break;
        case 12:
            userSettings.axis_arrows=1;
            break;
        case 13:
            userSettings.axis_arrows=0;
            break;
        case 14:
            userSettings.axis_numbers=1;
            break;
        case 15:
            userSettings.axis_numbers=0;
            break;
        case 16:
            userSettings.minor_gridlines=1;
            break;
        case 17:
            userSettings.minor_gridlines=0;
            break;
        case 18:
            userSettings.measure="radians";
            break;
        case 19:
            userSettings.measure="degrees";
            break;
        case 20:
            if(DEBUG==true)
                cout << "[Pages] Saving the configuration\n";
            settextstyle(0,0,1);
            if(!saveConfiguration("config-1"))
                outtextxy(maxWidth/2-textwidth(failedToSave)/2, 200, failedToSave);
            else
            {
                clearviewport();
                outtextxy(maxWidth/2-textwidth(savedSuccessfull)/2, 200, savedSuccessfull);
            }
            settextstyle(0,0,0);
            break;
    }
    if(copyPage==0)
        activePage=copyPage;
    else activePage=2;

}

void informationPage(coord mouse)
{

    char information_title[100];
    strcpy(information_title, language["information_title"].c_str());
    pageInit(3, information_title, mouse);
    char information_project_about[1400];
    char first[300]="In this project we were supposed to draw the graph of any given function. In order to achieve the end goal we had";
    char second[300]="to split the project into two parts: graphics and function evaluator. For the function evaluator we have actually";//
    char third[300]="transform the string into postfix notation in order to remove all parentheses and have a clear path about the priority";//
    char forth[300]="of our operators. Once we had the postfix notation we have just build an evaluator that was reconstructing the whole";
    char fifth[300]="thing and outputting a value. For the graphics part we have used a port for Graphics.h using SDL, so it is also";
    char sixth[300]="cross-platform. We have tried as much as possible to make it 100% live update, but we failed to this while drawing";
    char seven[300]="the graph.";
    outtextxy(60,300,first);
    outtextxy(20,320,second);
    outtextxy(20,340,third);
    outtextxy(20,360,forth);
    outtextxy(20,380,fifth);
    outtextxy(20,400,sixth);
    outtextxy(20,420,seven);

    //TBD
//    drawHugeText(coord{10,300}, language["information_project_about"].c_str());

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