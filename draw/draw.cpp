//
// Created by Ilinca on 12/13/2020.
//
#include "draw.h"
#include "main.h"
#include "pages.h"
bool modified=false;


void nrsir (double n, char s[])
{
    bool sign = 0;
    if(n < 0) sign = 1;
    n = abs(n);

    int i = (int)n;
    double f = n - (int)n;

    f *= 10;

    char frac[100] = {};
    int k = 0;

    while(1){
        frac[k++] = (int)f % 10 + '0';
        f *= 10;
        if(k == 4) break;
    }


    while(frac[k - 1] == '0' && k > 0) k--;
    frac[k] = 0;



    k = 0;
    if(i == 0){
        s[k++] = '0';
    }

    while(i > 0){
        s[k++] = i % 10 + '0';
        i/=10;
    }

    if(sign == 1){
        s[k++] = '-';
    }

    reverse(s, s + k);
    s[k] = 0;

    if(strlen(frac) > 0){
        strcat(s, ".");
        strcat(s, frac);
    }
}

double tr(int coord, int translare)
{
    return coord+translare;
}

pair<double, double> drawaxes (int lgx, int lgy,  double &unitax, int &unitaxpx, int tx, int ty)
{
    char sir[1000] = {};
    double k=unitax;
    pair<double, double> interval;

    if(unitaxpx >= 80){
        unitaxpx = 40;
        unitax /= 2;
    }

    if(unitaxpx <= 20){
        unitaxpx = 40;
        unitax *= 2;
    }

///axele de coordonate
    interval.first = -(tr(lgx/2, tx) / unitaxpx * unitax + 1);
    interval.second = (lgx - tr(lgx/2, tx))/unitaxpx * unitax + 1;

    if(userSettings.axis_arrows) {
        line(tr(lgx / 2, tx), 0, tr(lgx / 2, tx), lgy);
        line(0, tr(lgy / 2, ty), lgx, tr(lgy / 2, ty));

///impartirea si notarea axelor
        for (int i = lgx / 2 + unitaxpx; tr(i, tx) <= lgx; i += unitaxpx) {
            line(tr(i, tx), tr(lgy / 2 - 3, ty), tr(i, tx), tr(lgy / 2 + 3, ty));
            if (userSettings.axis_numbers) {
                nrsir(k, sir);
                outtextxy(tr(i, tx), tr(lgy / 2 + 3, ty), sir);

            }
            k += unitax;
        }


        k = -unitax;
        for (int i = lgx / 2 - unitaxpx; tr(i, tx) >= 0; i -= unitaxpx) {
            line(tr(i, tx), tr(lgy / 2 - 3, ty), tr(i, tx), tr(lgy / 2 + 3, ty));
            if (userSettings.axis_numbers) {
                nrsir(k, sir);
                outtextxy(tr(i, tx), tr(lgy / 2 + 3, ty), sir);

            }
            k -= unitax;
        }


        k = -unitax;
        for (int i = lgy / 2 + unitaxpx; tr(i, ty) <= lgy; i += unitaxpx) {
            line(tr(lgx / 2 - 3, tx), tr(i, ty), tr(lgx / 2 + 3, tx), tr(i, ty));
            if (userSettings.axis_numbers) {
                nrsir(k, sir);
                outtextxy(tr(lgx / 2 + 3, tx), tr(i, ty), sir);

            }
            k -= unitax;
        }
        k = unitax;
        for (int i = lgy / 2 - unitaxpx; tr(i, ty) >= 0; i -= unitaxpx) {
            line(tr(lgx / 2 - 3, tx), tr(i, ty), tr(lgx / 2 + 3, tx), tr(i, ty));
            if (userSettings.axis_numbers) {
                nrsir(k, sir);
                outtextxy(tr(lgx / 2 + 3, tx), tr(i, ty), sir);

            }
            k += unitax;
        }
        if (userSettings.axis_numbers) outtextxy(tr(lgx / 2 + 3, tx), tr(lgy / 2 + 3, ty), "0");
    }

    return interval;

}

double func(double n, vector<string> postfix)
{
    return getValueFromPostfix(postfix,n);
}

///Deseneaza functie pe intervalul [a, b] intr-o fereastra de dimensiuni lgx, lgy
void drawf (double &unitax, int &unitaxpx, int lgx, int lgy, int tx, int ty,vector<string> postfix) {

    clearviewport();
    pair<double, double> aux = drawaxes(lgx, lgy, unitax, unitaxpx, tx, ty);
    int a = (int)aux.first;
    int b = (int)aux.second;


    ///desenarea graficului
    double x1 = lgx / 2 + (a / unitax) * unitaxpx;
    double y1 = lgy / 2 - (func(a,postfix) / unitax) * unitaxpx;
    double x2 = lgx / 2 + ((a + unitf) / unitax) * unitaxpx;
    double y2 = lgy / 2 - (func(a + unitf,postfix) / unitax) * unitaxpx;

    outtextxy(20, 700, "Press x to go back");
    outtextxy(20, 710, "Press i to zoom in");
    outtextxy(20, 720, "Press o to zoom out");
    outtextxy(20, 730, "Move with w - up, a - left, s - down, d - right");


    for (double j = a + 2 * unitf; j <= b; j += unitf) {
        double x3 = (j / unitax) * unitaxpx + lgx / 2;
        double y3 = lgy / 2 - (func(j,postfix) / unitax) * unitaxpx;

        if (!((y1 > lgy && y2 < 0) || (y2 > lgy && y1 < 0))) {
            line(tr(x1, tx), tr(y1, ty),
                 tr(x2, tx), tr(y2, ty));

            if (y2 < y1 && y2 < y3)
                circle(tr(x2, tx), tr(y2, ty), 5);
            if (y2 > y1 && y2 > y3)
                circle(tr(x2, tx), tr(y2, ty), 5);
        }

        x1 = x2;
        y1 = y2;
        x2 = x3;
        y2 = y3;

    }
}
void drawGraph(vector<string> postfix)
{
    cleardevice();
    char ch;
    double unitax = 1;
    int unitaxpx = 40;
    int tx = 0, ty = 0;

    drawf(unitax, unitaxpx, maxWidth, maxHeigh,  tx, ty, postfix);
    do
    {
        ch=getch();
        if(ch=='x')
            break;
        switch(ch)
        {
            case 'i':
                unitaxpx += 5;
                modified=true;
                break;
            case 'o':
                unitaxpx -= 5;
                modified=true;
                break;
            case 'w':
                ty=ty-30;
                break;
            case 's':
                ty=ty+30;
                break;
            case 'a':
                tx=tx-30;
                break;
            case 'd':
                tx=tx+30;
                break;
        }
        drawf(unitax, unitaxpx, maxWidth, maxHeigh,  tx, ty, postfix);
        modified=false;
    } while(ch!='x');
    cout << "EXECUTING THIS!!!" << endl;

//    closegraph();

}