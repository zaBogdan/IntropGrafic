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

bool canZoomOut(int lgx, int lgy, double &unitax, int &unitaxpx, int tx, int ty)
{
    pair<double, double> interval;
    interval.first =  (tr(lgx/2, tx) / unitaxpx * unitax + 1);
    interval.second = (lgx - tr(lgx/2, tx))/unitaxpx * unitax + 1;

    return (interval.second + interval.first) < 80;
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
        strcpy(sir, "0");
        sir[1] = 0;
        if (userSettings.axis_numbers) outtextxy(tr(lgx / 2 + 3, tx), tr(lgy / 2 + 3, ty), sir);
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

enum{
    CONSTANT,
    RISING,
    FALLING
};

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

    int state = CONSTANT;
    bool tmp = 1;
    ///desenarea graficului
    double x1 = (double)lgx / 2 + (a / (double)unitax) * (double)unitaxpx;
    double y1 = (double)lgy / 2 - (func(a,a,b) / (double)unitax) * (double)unitaxpx;
    if(errorFlagDrawing != 0){
        y1 = (double)1/0;
        tmp = 0;
    }
    double x2 = (double)lgx / 2 + ((a + unitf) / (double)unitax) * (double)unitaxpx;
    double y2 = (double)lgy / 2 - (func(a + unitf,a,b) / (double)unitax) * (double)unitaxpx;
    if(errorFlagDrawing != 0){
        y1 = (double)1/0;
        tmp = 0;
    }

    //double dif1 = (y2-y1)/(x2-x1);

    setcolor(WHITE);
    if(tmp) {
        if (y1 < y2) {
            state = FALLING;
        } else if (y1 > y2) {
            state = RISING;
        } else {
            state = CONSTANT;
        }

        x1 = x2;
        y1 = y2;
    }



//    double tmp = func(0,a,b) * 2;
//    cout << tmp << '\n';
    //return;

    for (double j = a + 2 * unitf; j <= b; j += unitf) {

        if(y1 == (double)1/0){
            x1 = (j / (double)unitax) * (double)unitaxpx + (double)lgx / 2;
            y1 = (double)lgy / 2 - (func(j,a,b) / (double)unitax) * (double)unitaxpx;

            if(errorFlagDrawing != 0){
                y1 = (double)1/0;
            }
            continue;
        }

        else {
            x2 = (j / (double) unitax) * (double) unitaxpx + (double) lgx / 2;
            y2 = (double) lgy / 2 - (func(j, a, b) / (double) unitax) * (double) unitaxpx;
        }

        if(errorFlagDrawing != 0){
            continue;
        }

        if(state == RISING){
            if(y1 < y2){
                if(abs( y1 - y2) > lgy/2){
                    if(tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) line(tr(x1, tx), tr(y1, ty), tr(x1, tx), 0);
                    if(tr(y2, ty) >= 0 && tr(y2, ty) <= lgy) line(tr(x2, tx), tr(y2, ty), tr(x2, tx), lgy);
                }

                else{
                    state = FALLING;
                    if(tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) circle(tr(x1, tx), tr(y1, ty), 5);
                    if((tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) || (tr(y2, ty) >= 0 && tr(y2, ty) <= lgy)) line(tr(x1, tx), tr(y1, ty), tr(x2, tx), tr(y2, ty));
                }
            }

            else{
                if((tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) || (tr(y2, ty) >= 0 && tr(y2, ty) <= lgy)) line(tr(x1, tx), tr(y1, ty), tr(x2, tx), tr(y2, ty));
            }
        }

        if(state == FALLING){
            if(y1 > y2){
                if(abs(y1- y2) > lgy/2){
                    if(tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) line(tr(x1, tx), tr(y1, ty), tr(x1, tx), lgy);
                    if(tr(y2, ty) >= 0 && tr(y2, ty) <= lgy) line(tr(x2, tx), tr(y2, ty), tr(x2, tx), 0);
                }

                else{
                    state = RISING;
                    if(tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) circle(tr(x1, tx), tr(y1, ty), 5);
                    if((tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) || (tr(y2, ty) >= 0 && tr(y2, ty) <= lgy)) line(tr(x1, tx), tr(y1, ty), tr(x2, tx), tr(y2, ty));
                }
            }

            else{
                if((tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) || (tr(y2, ty) >= 0 && tr(y2, ty) <= lgy)) line(tr(x1, tx), tr(y1, ty), tr(x2, tx), tr(y2, ty));
            }
        }

        if(state == CONSTANT){
            if(y1 > y2){
                state = RISING;
                if((tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) || (tr(y2, ty) >= 0 && tr(y2, ty) <= lgy)) line(tr(x1, tx), tr(y1, ty), tr(x2, tx), tr(y2, ty));
            }

            else if(y1 < y2){
                state = FALLING;
                if((tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) || (tr(y2, ty) >= 0 && tr(y2, ty) <= lgy)) line(tr(x1, tx), tr(y1, ty), tr(x2, tx), tr(y2, ty));
            }

            else{
                if((tr(y1, ty) >= 0 && tr(y1, ty) <= lgy) || (tr(y2, ty) >= 0 && tr(y2, ty) <= lgy)) line(tr(x1, tx), tr(y1, ty), tr(x2, tx), tr(y2, ty));
            }
        }

        x1 = x2;
        y1 = y2;
        //dif = abs(y1 - y2);
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
        bool redraw = true;
        ch=getch();
        if(ch=='x')
            break;
        switch(ch)
        {
            case 'i':
                unitaxpx += 5;
                break;
            case 'o':
                if(canZoomOut(maxWidth, maxHeigh, unitax, unitaxpx, tx, ty)) unitaxpx -= 5;
                else redraw = false;
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
        if(redraw) drawf(unitax, unitaxpx, maxWidth, maxHeigh,  tx, ty);
    } while(ch!='x');
    postfix.clear();
    values.clear();

}