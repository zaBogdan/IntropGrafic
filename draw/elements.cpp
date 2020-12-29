//
// Created by zabogdan on 12/29/20.
//

#include "elements.h"

bool inFocus(int startX, int startY, int finishX, int finishY)
{

}

void drawButton(int x, int y,char text[20],int size)
{
    if(size<=0 || size>=4)
    {
        cout << "[GRAPHICS] Failed to draw button! Maximum size is 3!";
        return;
    }
    int font = 0;
    int direction = 0;
    int font_size = size+1;
    line(x-defaultSizeX, y+20, x+defaultSizeX, y+20);
//    rectangle(x-defaultSizeX*size,y-defaultSizeY*size,x+defaultSizeX*size, y+defaultSizeY*size);
    settextstyle(font,direction, 2*font_size);
    outtextxy(x-38, y-8, text);
}