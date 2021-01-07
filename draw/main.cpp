//
// Created by Bogdan Zavadovschi on 07.01.2021.
//

#include "main.h"
int activePage=0;

int gameLoop(coord mouse, char key)
{
    //main page
    if(activePage==0)
        mainMenuPage(mouse);
    //settings page
    if(activePage==2)
        settingsPage(mouse);
    //information page
    if(activePage==3)
        informationPage(mouse);
    //go to input function(s) page
    if(activePage==1)
        inputFunction(mouse);

    //handle the exit logic
    if(activePage==-1)
        return -1;
    return 0;
}

void graphic()
{
    initialSetup();
    coord mouseInput;
    char keyBoardInput=' ';
    while(true)
    {
        mouseInput= coord{mousex(),mousey()};
        if(ismouseclick(WM_LBUTTONDOWN))
        {
//            IDK WHY THIS MUST BE HERE????
        }

        if(keyBoardInput==0)
            break;
        //we re-render only when necessary.
        if(gameLoop(mouseInput, keyBoardInput)==-1)
            break;

        setvisualpage(activePage);
        delay(1000/frames);
    }
    exitGraphic();
}
void initialSetup()
{
    /* select driver and mode that supports multiple pages */
    int gdriver = EGA, gmode = EGAHI, errorcode;
    int x, y, ht;
    initgraph(&gdriver,&gmode, "test");
    cleardevice();
    clearviewport();
}
void exitGraphic()
{
    closegraph();
}