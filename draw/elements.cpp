//
// Created by zabogdan on 12/29/20.
//

#include "elements.h"
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
            if(DEBUG==true)
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
    int trasholdX=400;
    int trasholdY=30;
    settextstyle(0,0,2);
    if(strlen(input))
        outtextxy(start.x-trasholdX+10, start.y, input);
    settextstyle(0,0,0);
    char enter_input[100], warning_input[100],explain_input[100];
    strcpy(enter_input, language["enter_input"].c_str());
    strcpy(warning_input, language["warning_input"].c_str());
    strcpy(explain_input, language["explain_input"].c_str());

    rectangle(start.x-trasholdX, start.y-trasholdY,start.x+trasholdX,start.y+trasholdY);
    if(inFocus(start,mouse,800,60) && (ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_RBUTTONDOWN)))
    {
        setfillstyle(XHATCH_FILL, BLACK);
        bar(start.x-textwidth(enter_input)/2-20,start.y-70,start.x+textwidth(enter_input)/2+20, start.y-45);
        setcolor(WHITE);
        outtextxy(start.x-textwidth(warning_input)/2,start.y-70, warning_input);
        outtextxy(start.x-textwidth(explain_input)/2,start.y-60, explain_input);
    }
    else
    {
        outtextxy(start.x-textwidth(enter_input)/2,start.y-60, enter_input);
        return;
    }


    setcolor(WHITE);
    settextstyle(0,0,2);
    if(strlen(input)<i)
        i=0;

    char ch='0';
    while((int)ch!=27)
    {
         ch = getch();
        if((int)ch==27)
        {
            clearviewport();
            outtextxy(start.x-trasholdX+10, start.y, input);
            break;
        }
        if (ch == -31 || ch == -27)
            ch = 15;
        if(ch==13)
        {
            if(i)
                needsModified=true;
            return;
        }

        if(i>maxLength)
            return;
        //backspace check
        if(ch==8)
        {
            input[--i]='\0';
            setfillstyle(XHATCH_FILL, BLACK);
            bar(start.x-trasholdX+10, start.y-20, start.x+trasholdX-10,start.y+20);
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
        if(DEBUG==true)
        {
            cout << "[INPUT] Shift is now: " << isShiftUp << endl;
            cout << "[INPUT] Your string is: "<< input << endl;
        }
        outtextxy(start.x-trasholdX+10, start.y, input);
    }
}
