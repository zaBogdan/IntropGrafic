//
// Created by Ilinca on 12/13/2020.
//
#include "draw.h"
#include "main.h"
#include "pages.h"

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



    if(userSettings.minor_gridlines || userSettings.axis_arrows) {
///impartirea si notarea axelor
        for (int i = lgx / 2 + unitaxpx; tr(i, tx) <= lgx; i += unitaxpx) {
            if(userSettings.axis_arrows)
                line(tr(i, tx), tr(lgy / 2 - 3, ty), tr(i, tx), tr(lgy / 2 + 3, ty));
            if(userSettings.minor_gridlines) {
                setcolor(COLOR(96, 69, 69));
                line(tr(i, tx), 0, tr(i, tx), lgy);
                setcolor(WHITE);
            }
            if (userSettings.axis_numbers) {
                nrsir(k, sir);
                outtextxy(tr(i, tx), tr(lgy / 2 + 3, ty), sir);

            }
            k += unitax;
        }


        k = -unitax;
        for (int i = lgx / 2 - unitaxpx; tr(i, tx) >= 0; i -= unitaxpx) {
            if(userSettings.axis_arrows)
                line(tr(i, tx), tr(lgy / 2 - 3, ty), tr(i, tx), tr(lgy / 2 + 3, ty));
            if(userSettings.minor_gridlines) {
                setcolor(COLOR(96, 69, 69));
                line(tr(i, tx), 0, tr(i, tx), lgy);
                setcolor(WHITE);
            }
            if (userSettings.axis_numbers) {
                nrsir(k, sir);
                outtextxy(tr(i, tx), tr(lgy / 2 + 3, ty), sir);

            }
            k -= unitax;
        }


        k = -unitax;
        for (int i = lgy / 2 + unitaxpx; tr(i, ty) <= lgy; i += unitaxpx) {
            if(userSettings.axis_arrows)
                line(tr(lgx / 2 - 3, tx), tr(i, ty), tr(lgx / 2 + 3, tx), tr(i, ty));
            if(userSettings.minor_gridlines) {
                setcolor(COLOR(96, 69, 69));
                line(0, tr(i, ty), lgx, tr(i, ty));
                setcolor(WHITE);
            }
            if (userSettings.axis_numbers) {
                nrsir(k, sir);
                outtextxy(tr(lgx / 2 + 3, tx), tr(i, ty), sir);

            }
            k -= unitax;
        }
        k = unitax;
        for (int i = lgy / 2 - unitaxpx; tr(i, ty) >= 0; i -= unitaxpx) {
            if(userSettings.axis_arrows)
                line(tr(lgx / 2 - 3, tx), tr(i, ty), tr(lgx / 2 + 3, tx), tr(i, ty));
            if(userSettings.minor_gridlines) {
                setcolor(COLOR(96, 69, 69));
                line(0, tr(i, ty), lgx, tr(i, ty));
                setcolor(WHITE);
            }
            if (userSettings.axis_numbers) {
                nrsir(k, sir);
                outtextxy(tr(lgx / 2 + 3, tx), tr(i, ty), sir);

            }
            k += unitax;
        }
        if (userSettings.axis_numbers) outtextxy(tr(lgx / 2 + 3, tx), tr(lgy / 2 + 3, ty), "0");
    }

    if(userSettings.axis_arrows) {
        line(tr(lgx / 2, tx), 0, tr(lgx / 2, tx), lgy);
        line(tr(lgx / 2, tx) + 1, 0, tr(lgx / 2, tx) + 1, lgy);
        line(tr(lgx / 2, tx) - 1, 0, tr(lgx / 2, tx) - 1, lgy);

        line(0, tr(lgy / 2, ty), lgx, tr(lgy / 2, ty));
        line(0, tr(lgy / 2, ty) + 1, lgx, tr(lgy / 2, ty) + 1);
        line(0, tr(lgy / 2, ty) - 1, lgx, tr(lgy / 2, ty) - 1);
    }

    return interval;

}


double func(double n, double start,double finish)
{
    if(userSettings.measure=="degrees")
        n = n*(180.0/M_PI);
    return getValueFromPostfix(postfix,n,start, finish);
}

///Deseneaza functie pe intervalul [a, b] intr-o fereastra de dimensiuni lgx, lgy
void drawf (double &unitax, int &unitaxpx, int lgx, int lgy, int tx, int ty) {
    char go_back[100],zoom_in[100],zoom_out[100],controls[100];
    strcpy(go_back, language["go_back"].c_str());
    strcpy(zoom_in, language["zoom_in"].c_str());
    strcpy(zoom_out, language["zoom_out"].c_str());
    strcpy(controls, language["controls"].c_str());

    clearviewport();
    pair<double, double> aux = drawaxes(lgx, lgy, unitax, unitaxpx, tx, ty);
    int a = (int)aux.first;
    int b = (int)aux.second;


    ///desenarea graficului
    double x1 = lgx / 2 + (a / unitax) * unitaxpx;
    double y1 = lgy / 2 - (func(a,a,b) / unitax) * unitaxpx;
    double x2 = lgx / 2 + ((a + unitf) / unitax) * unitaxpx;
    double y2 = lgy / 2 - (func(a + unitf,a,b) / unitax) * unitaxpx;
    setcolor(WHITE);

    for (double j = a + 2 * unitf; j <= b; j += unitf) {
        double x3 = (j / unitax) * unitaxpx + lgx / 2;
        double y3 = lgy / 2 - (func(j,a,b) / unitax) * unitaxpx;

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
    setcolor(COLOR(104, 137, 255));
    char func[100]="f(x)=";
    strcat(func, cppVersion.c_str());
    outtextxy(20,690, func);
    setcolor(RED);
    outtextxy(20, 700, go_back);
    outtextxy(20, 710, zoom_in);
    outtextxy(20, 720, zoom_out);
    outtextxy(20, 730, controls);
    setcolor(WHITE);
}
void drawGraph()
{
    cleardevice();
    char ch;
    double unitax = 1;
    int unitaxpx = 40;
    int tx = 0, ty = 0;

    //settextstyle(10, 0, 0);

    drawf(unitax, unitaxpx, maxWidth, maxHeigh,  tx, ty);
    do
    {
        ch=getch();
        if(ch=='x')
            break;
        switch(ch)
        {
            case 'i':
                unitaxpx += 5;
                break;
            case 'o':
                unitaxpx -= 5;
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
            default:
                continue;
        }
        drawf(unitax, unitaxpx, maxWidth, maxHeigh,  tx, ty);
    } while(ch!='x');
    postfix.clear();
    values.clear();

}