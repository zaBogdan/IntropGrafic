//
// Created by Bogdan Zavadovschi on 07.01.2021.
//

#include "pages.h"

void mainMenuPage(coord mouse)
{
    setactivepage(0);
    char title[100] = "Grafic";
    char projectSubtitle[100] = "We are the new Desmos";
    char imagePath[100] = "../assets/logo.bmp";
    char draw[100] = "Draw";
    char set[100] = "Settings";
    char inf[100] = "Information";
    char quit[100] = "Quit";
    char buildVersion[100] = "Debug build 0.5";
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
    char pageName[100] = "Input function";

    pageInit(1, pageName, mouse);
    setvisualpage(1);
    //input this and then compute the postfix version and print the c++ header
    textInputBar(coord{100,400}, mouse);
}
void drawPage(coord mouse, vector<string> postfix)
{
    char pageName[100] = "Draw";
    pageInit(5, pageName, mouse);
    //setactivepage(1);
    //setactivepage(4);
    //cleardevice();
    cleardevice();
    drawGraph(postfix);
    //line(100, 0, 100, 100);
    delay(1000);
    cleardevice();

    activePage=0;
}

void settingsPage(coord mouse)
{
    char pageName[100] = "Settings";
    char lang[100] = "Your lange is: ";
    char axis_arrows[100] = "Arrows to axis: ";
    char axis_numbers[100] = "Add numers to axis: ";
    char minor_gridlines[100] = "Minor gridlines: ";
    char measure[100] = "Measure in: ";
    char english[100] = "English";
    char romanian[100] = "Romanian";
    char yes[100] = "Yes";
    char no[100] = "No";
    char radians[100] = "Radians";
    char degrees[100] = "Degrees";
    char save[100] = "Save";
    char failedToSave[100] = "There was an error while trying to save the configuration! Please try again!";
    char savedSuccessfull[100] = "Your settings have been saved successfully!";

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