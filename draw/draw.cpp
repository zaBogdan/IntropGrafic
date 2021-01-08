//
// Created by Ilinca on 12/13/2020.
//
#include "draw.h"

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

void drawaxes (int a, int b, int lgx, int lgy,  double &unitax, int &unitaxpx, int tx, int ty)
{
    char sir[1000] = {};
    double k=unitax;

    if(unitaxpx >= 80){
        unitaxpx = 40;
        unitax /= 2;
    }

    if(unitaxpx <= 20){
        unitaxpx = 40;
        unitax *= 2;
    }

///axele de coordonate
    line(tr(lgx/2, tx), 0, tr(lgx/2,tx), lgy);
    line(0, tr(lgy/2,   ty), lgx, tr(lgy/2,ty));

///impartirea si notarea axelor
    for(int i=lgx/2+unitaxpx; tr(i,   tx)<=lgx; i+=unitaxpx)
    {
        line(tr(i,   tx), tr(lgy/2-3,   ty), tr(i,   tx), tr(lgy/2+3, ty));
        nrsir(k, sir);
        outtextxy(tr(i, tx), tr(lgy/2+3, ty), sir);
        k += unitax;
    }
    k=-unitax;
    for(int i=lgx/2-unitaxpx; tr(i,   tx)>=0; i-=unitaxpx)
    {   line(tr(i,   tx), tr(lgy/2-3,   ty), tr(i,   tx), tr(lgy/2+3,   ty));
        nrsir(k, sir);
        outtextxy(tr(i,   tx), tr(lgy/2+3,   ty), sir);
        k -= unitax;
    }
    k=-unitax;
    for(int i=lgy/2+unitaxpx; tr(i,   ty)<=lgy; i+=unitaxpx)
    {   line(tr(lgx/2-3, tx), tr(i,   ty), tr(lgx/2+3, tx), tr(i,   ty));
        nrsir(k, sir);
        outtextxy(tr(lgx/2+3, tx), tr(i,   ty), sir);
        k -= unitax;
    }
    k=unitax;
    for(int i=lgy/2-unitaxpx; tr(i,   ty)>=0; i-=unitaxpx)
    {   line(tr(lgx/2-3, tx), tr(i,   ty), tr(lgx/2+3, tx), tr(i,   ty));
        nrsir(k, sir);
        outtextxy(tr(lgx/2+3, tx), tr(i,   ty), sir);
        k += unitax;
    }
    outtextxy(tr(lgx/2+3, tx), tr(lgy/2+3,   ty), "0");

}

///Functie temporara pentru teste
double func(double n, vector<string> postfix)
{
    return getValueFromPostfix(postfix,n);
}

///Deseneaza functie pe intervalul [a, b] intr-o fereastra de dimensiuni lgx, lgy
void drawf (int a, int b, double &unitax, int &unitaxpx, int lgx, int lgy, int tx, int ty,vector<string> postfix) {

    cleardevice();
    drawaxes(a, b, lgx, lgy, unitax, unitaxpx, tx, ty);


    ///desenarea graficului
    double x1 = lgx / 2 + (a / unitax) * unitaxpx;
    double y1 = lgy / 2 - (func(a,postfix) / unitax) * unitaxpx;
    double x2 = lgx / 2 + ((a + unitf) / unitax) * unitaxpx;
    double y2 = lgy / 2 - (func(a + unitf,postfix) / unitax) * unitaxpx;

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

    /**
     * TODO: Inputul trebuie mutat pe partea grafica
     * TODO: Trebuie realizata desenarea functiei dupa modelul cu initgraph
     * BUG: Butonu de back e inutil momentan.
     */
    int a = -100, b = 100;
    char ch;
    double unitax = 1;
    int unitaxpx = 40;
    int tx = 0, ty = 0;
//    cout<<"Marginea inferioara a intervalului:"; cin>>a;
//    cout<<"Marginea superioara a intervalului:"; cin>>b;

    initwindow(850, 850);
    drawf(a, b, unitax, unitaxpx, 850, 850,  tx, ty, postfix);
    do
    {
        ch=getch();
        cout << (int)ch << '\n';
        switch(ch)
        {
            case 'n':
                //zoom=zoom+0.1;
                unitaxpx += 5;
                drawf(a, b, unitax, unitaxpx, 850, 850,  tx, ty, postfix);
                break;
            case 'm':
                unitaxpx -= 5;
                //zoom=zoom-0.1;
                drawf(a, b, unitax, unitaxpx, 850, 850,  tx, ty, postfix);
                break;
            case 'w':
            case KEY_UP://72 :
                ty=ty-30;
                drawf(a, b, unitax, unitaxpx, 850, 850,  tx, ty, postfix);
                break;
            case 's':
            case KEY_DOWN://80 :
                ty=ty+30;
                drawf(a, b, unitax, unitaxpx, 850, 850,  tx, ty, postfix);
                break;
            case 'a':
            case KEY_LEFT://75 :
                tx=tx-30;
                drawf(a, b, unitax, unitaxpx, 850, 850,  tx, ty, postfix);
                break;
            case 'd':
            case KEY_RIGHT://77 :
                tx=tx+30;
                drawf(a, b, unitax, unitaxpx, 850, 850,  tx, ty, postfix);
                break;
        }
    } while(ch!='x');
    closegraph();


//    closegraph();
}