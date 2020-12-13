//
// Created by Ilinca on 12/13/2020.
//
#include "draw.h"

void drawaxes (int lgx, int lgy)
{

///axele de coordonate
    line(lgx/2, 0, lgx/2, lgy);
    line(0, lgy/2, lgx, lgy/2);

///impartirea axelor
    for(int i=lgx/2; i<=lgx; i+=unitaxpx)
        line(i, (lgy/2-3), i, lgy/2+3);

    for(int i=lgx/2; i>=0; i-=unitaxpx)
        line(i, (lgy/2-3), i, lgy/2+3);

    for(int i=lgy/2; i<=lgy; i+=unitaxpx)
        line(lgx/2-3, i, lgx/2+3, i);

    for(int i=lgy/2; i>=0; i-=unitaxpx)
        line(lgx/2-3, i, lgx/2+3, i);

}
///Functie temporara pentru teste
double func(double n)
{
    return n*n+n;
}

///Deseneaza functie pe intervalul [a, b] intr-o fereastra de dimensiuni lgx, lgy
void drawf (int a, int b, int unitax, int lgx, int lgy)
{

    /// initwindow(lgx, lgy);

    drawaxes (lgx, lgy);

    ///desenarea graficului
    double x1=lgx/2 + (a/unitax) * unitaxpx;
    double y1=lgy/2 - (func(a)/unitax) * unitaxpx;
    double x2=lgx/2 + ((a+unitf)/unitax) * unitaxpx;
    double y2=lgy/2 - (func(a+unitf)/unitax) * unitaxpx;

    for(double j=a+2*unitf; j<=b; j+=unitf)
    {
        double x3=(j/unitax) * unitaxpx + lgx/2;
        double y3=lgy/2 - (func(j)/unitax) * unitaxpx;
        if(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))<50) ///in cazul in care segmentul este prea mare
            line(x1, y1, x2, y2);
        line(x2, y2, x3, y3);

        if(y2<y1 && y2<y3)
            circle(x2, y2, 3);
        if(y2>y1 && y2>y3)
            circle(x2, y2, 3);

        x1=x2;
        y1=y2;
        x2=x3;
        y2=y3;

    }

}
