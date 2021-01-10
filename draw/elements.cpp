//
// Created by zabogdan on 12/29/20.
//

#include "elements.h"
char input[100] = " \0";
int i=0;

bool inFocus(coord center,coord mouseInput,int textW, int textH)
{
    int x1 = center.x-textW/2-2*defaultSizeX; //left
    int x2 = center.x+textW/2+defaultSizeX+10; //right
    int y1 = center.y-textH/2-defaultSizeY; //top
    int y2 = center.y+textH+2*defaultSizeY+10; //bottom
    if(mouseInput.x>=x1 && mouseInput.x<=x2)
        if(mouseInput.y>=y1 && mouseInput.y<=y2)
            return true;
    return false;
}

void drawButton(int x, int y,coord mouseInput, char text[20],int aPage,int font_size, int active)
{
    setcolor(WHITE);
    int font = 0;
    int direction = 0;
    settextstyle(font,direction, 2*font_size);
    coord point;
    point.x=x;
    point.y=y;
    bool focus = inFocus(point,mouseInput,textwidth(text),textheight(text));
    if(focus || active)
    {
        setcolor(buttonFocusColor);
        line(x-textwidth(text)/2-10, y+defaultSizeY+textheight(text), x+textwidth(text)/2+10, y+defaultSizeY+textheight(text));
        if((ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_RBUTTONDOWN)) && focus)
        {
            cout << "[BUTTON] Active page set to: " << aPage << endl;
            activePage = aPage;
        }

    }
    outtextxy(x-textwidth(text)/2, y, text);

    if(!focus && !active)
    {
        setcolor(BLACK);
        line(x-textwidth(text)/2-10, y+defaultSizeY+textheight(text), x+textwidth(text)/2+10, y+defaultSizeY+textheight(text));
    }
    //reset to normal
    setcolor(WHITE);
    settextstyle(0,0, 0);
}

void textInputBar(coord start, coord mouse)
{
//    char warning[] = "Warning! You are in input mode! To leave please press `esc` or if you want to finish press `enter`.";
//    char explain[] = "Being in input mode means that you can't do anything else!";
//    outtextxy(start.x+30,start.y-50, warning);
//    outtextxy(start.x+30,start.y-30, explain);
    rectangle(start.x, start.y, start.x+600, start.y+50);
    setcolor(WHITE);
    settextstyle(0,0,2);
    char ch = kbhit();
    if(ch)
    {
//        char ch = getch();
        cout << "Char: " << ch << " int: " << (int)ch << endl;
        if(ch==-31)
            ch=15;
        if(ch==13)
            return;
        if(i>maxLength)
            return;
        //backspace check
        if(ch==8)
        {
            input[--i]='\0';
            clearviewport();
        }
        //ordinary chars check
        else if(ch!=15)
        {
            //shift check
            if (isShiftUp)
            {
                //for shift+(0-9)
                bool ok = true;
                if (ch - '0' >= 0 && ch - '0' <= 9)
                    ch = ch - '0';
                    //for `=`
                else if (ch == '=')
                    ch = 10;
                    //if we pressed shift but it was a miss match we just skip
                else
                    ok = false;
                if (ok)
                {
                    ch = shiftKeys[ch];
                }
                isShiftUp = 0;
            }
            //adding the input
            input[i++] = ch;
            input[i] = '\0';
        }
        else
        {
            //if we pressed shift we will handle this next time
            isShiftUp=1;
        }
        cout << "Shift is now: " << isShiftUp << endl;
        cout << "[INPUT] Your string is: "<< input << endl;
        outtextxy(start.x+10, start.y+20, input);
    }
}