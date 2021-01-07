//
// Created by zabogdan on 12/29/20.
//

#include "elements.h"

bool inFocus(int x,int y,int textW, int textH)
{
    coord center;
    center.x = x;
    center.y = y;
    int x1 = x-textW/2-2*defaultSizeX; //left
    int x2 = x+textW/2+defaultSizeX+10; //right
    int y1 = y-textH/2-defaultSizeY; //top
    int y2 = y+textH+2*defaultSizeY+10; //bottom
    if(mouseC.x>=x1 && mouseC.x<=x2)
        if(mouseC.y>=y1 && mouseC.y<=y2)
            return true;
    return false;
}

void drawButton(int x, int y,char text[20],int aPage)
{
    setcolor(WHITE);
    int font = 0;
    int direction = 0;
    int font_size = 2;
    settextstyle(font,direction, 2*font_size);
    bool focus = inFocus(x,y,textwidth(text),textheight(text));
    if(focus)
    {
        setcolor(COLOR(104, 137, 255));
        line(x-textwidth(text)/2-10, y+defaultSizeY+textheight(text), x+textwidth(text)/2+10, y+defaultSizeY+textheight(text));
        if(ismouseclick(WM_LBUTTONDOWN) || ismouseclick((WM_RBUTTONDOWN)))
        {
            cout << "[BUTTON] Active page set to: " << aPage << endl;
            activePage = aPage;
        }

    }
    outtextxy(x-textwidth(text)/2, y, text);

    if(!focus)
    {
        setcolor(BLACK);
        line(x-textwidth(text)/2-10, y+defaultSizeY+textheight(text), x+textwidth(text)/2+10, y+defaultSizeY+textheight(text));
    }
    //reset to normal
    setcolor(WHITE);
    settextstyle(0,0, 0);
}

void inputText(int x, int y, int maxLength)
{
    int isShiftUp = 0;
    setcolor(WHITE);
    settextstyle(0,0,2);
    rectangle(x,y-20, x+500, y+20);
    int i=0;
    char input[]=" \0";
    //cout << "[Input] Starting the input module!\n";
    int curr = 0;


}


void inputTextOLD(int x, int y)
{



    int isShiftUp = 0;
    setcolor(WHITE);
    int font = 0;
    int direction = 0;
    int font_size = 2;
    settextstyle(font,direction, font_size);
    rectangle(x,y-20, x+500, y+20);
    char ch = getch();
    //enter -> 13
    //backspace -> 8
    char input[100]=" \0";
    int i=0;
    while(ch != 13 && i<100)
    {
        if(ch==8)
        {
            input[--i]='\0';
            clearviewport();
        }else if(ch!=15)
        {
            if(isShiftUp)
            {
                bool ok=true;
                if(ch-'0'>=0 && ch-'0'<=9)
                    ch = ch-'0';
                else if(ch=='=')
                    ch = 10;
                else
                    ok = false;
                if(ok)
                {
                    ch = shiftKeys[ch];
                }
                isShiftUp=0;
            }
            input[i++]=ch;
            input[i]='\0';

        }
        else
        {
            isShiftUp=1;
        }
        cout << "Shift is now: " << isShiftUp << endl;
        cout << "[INPUT] Your string is: "<< input << endl;
        outtextxy(100, 100, input);

        ch = getch();
    }
}