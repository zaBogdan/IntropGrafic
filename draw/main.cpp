//
// Created by Bogdan Zavadovschi on 07.01.2021.
//

#include "main.h"
int activePage=0;
int isShiftUp=0;
settings userSettings;
vector<string> postfix;
bool needsModified=false;
char input[100]= " \0";
string cppVersion;

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
    if(activePage==4)
        drawPage(mouse);

    //handle the exit logic
    if(activePage==-1)
        return -1;
    return 0;
}

void graphic()
{
    initialSetup();
    loadSettings("config-1");
    if(!userSettings.initialized)
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
        if(needsModified && activePage==1)
        {
            needsModified=false;
            string func = readFunction(input);
            postfix = buildAndValidatePostfix(func);
            if(postfix.empty())
            {
                postfix.clear();
                char error_postfix[100];
                strcpy(error_postfix, language["error_postfix"].c_str());
                clearviewport();
                outtextxy(maxWidth/2-textwidth(error_postfix)/2, 450,error_postfix);
                activePage=1;
            }
            else
            {
                if(DEBUG==true)
                    cout << "[MAIN] The C/C++ notation of this function is: ";
                cppVersion=getCPPNotation(postfix);
                cout << cppVersion << endl;
                activePage=4;
                strcpy(input, " \0");
                clearviewport();
            }
        }
        //we re-render only when necessary.
        if(gameLoop(mouseInput, keyBoardInput)==-1)
            break;
        //handle the settings
        if(userSettings.isModified)
        {
            if(DEBUG==true)
                cout << "[Settings] A modification has occured! Changes must happen!\n";
            if(lang!=userSettings.language)
            {
                if(DEBUG==true)
                    cout << "[Settings] Changing the language!\n";
                for(int i=0;i<6;i++)
                {
                    //5th is valid but 4 isn't.
                    if(i==4)
                        continue;
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
    int gdriver = EGA, gmode = EGAHI;
    char t[] = "test";
    initgraph(&gdriver,&gmode, t);
    cleardevice();
    clearviewport();
}
void exitGraphic()
{
    closegraph();
}
string readFunction(char* input)
{
    string s;
    for(int i=0;i<strlen(input);i++)
        s+=input[i];
    return s;
}
