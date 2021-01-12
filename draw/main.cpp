//
// Created by Bogdan Zavadovschi on 07.01.2021.
//

#include "main.h"
int activePage=0;
int isShiftUp=0;
settings userSettings;
vector<string> postfix;

int gameLoop(coord mouse, char key, vector<string> postfix)
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
        inputFunction(mouse, key);
    if(activePage==4)
        drawPage(mouse, postfix);

    //handle the exit logic
    if(activePage==-1)
        return -1;
    return 0;
}

void graphic(vector<string> postfix)
{
    initialSetup();
    loadSettings("default");

    if(!userSettings.initialized)
    {
        cout << "[Graphics] Failed to initialize settings! Exiting...\n";
        return;
    }
    string lang = userSettings.language;
    loadLanguage(userSettings.language);

    coord mouseInput;
    char keyBoardInput=' ';
    while(true)
    {
        //get mouse input
        mouseInput= coord{mousex(),mousey()};
        if(ismouseclick(WM_LBUTTONDOWN))
        {
//            IDK WHY THIS MUST BE HERE????
        }
        //get keyboard input
        keyBoardInput=kbhit();

        //we re-render only when necessary.
        if(gameLoop(mouseInput, keyBoardInput, postfix)==-1)
            break;
        //handle the settings
        if(userSettings.isModified)
        {
            cout << "[Settings] A modification has occured! Changes must happen!\n";
            if(lang!=userSettings.language)
            {
                cout << "[Settings] Changing the language!\n";
                for(int i=0;i<=5;i++)
                {
                    setactivepage(i);
                    clearviewport();
                    setvisualpage(i);
                }
                setvisualpage(activePage);
                if(!loadLanguage(userSettings.language))
                {
                    userSettings.language=lang;
                    cout << "[Language] Couldn't load the file `" << userSettings.language << ".lang` switching back to last language!\n";
                }
                loadLanguage(userSettings.language);
                lang = userSettings.language;
            }
            userSettings.isModified = false;
        }
        setvisualpage(activePage);
        delay(1000/frames);
    }
    exitGraphic();
}
void initialSetup()
{
    /* select driver and mode that supports multiple pages */
    int gdriver = EGA, gmode = EGAHI, errorcode;
    char t[] = "test";
    initgraph(&gdriver,&gmode, t);
    cleardevice();
    clearviewport();
}
void exitGraphic()
{
    closegraph();
}
