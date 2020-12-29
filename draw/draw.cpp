//
// Created by Ilinca on 12/13/2020.
//
#include "draw.h"

void nrsir (int n, char s[])
{
    int c, nr=0, cn;
    int k=0;

    cn=n;
    while(cn!=0)
    {
        nr++;
        cn/=10;
    }
    if(n<0)
    {   s[0]='-';
        nr++;
        n=-n;
    }
    while(n!=0)
    {
        c=n%10;
        s[nr-k-1]=c+'0';
        k++;
        n/=10;
    }
    s[nr]='\0';
}

void drawaxes (int a, int b, int lgx, int lgy, double zoom, int tx, int ty)
{
    char sir[1000];
    int k=0;

///axele de coordonate
    line(lgx/2*zoom + tx, 0, lgx/2*zoom + tx, lgy);
    line(0, lgy/2*zoom + ty, lgx, lgy/2*zoom + ty);

///impartirea si notarea axelor
    for(int i=lgx/2+unitaxpx; i*zoom + tx<=lgx; i+=unitaxpx)
    {
        line(i*zoom + tx, (lgy/2-3)*zoom+ty, i*zoom + tx, (lgy/2+3)*zoom+ty);
        nrsir(k, sir);
        outtextxy((i-unitaxpx)*zoom + tx, (lgy/2+3)*zoom+ty, sir);
        k++;
    }
    k=0;
    for(int i=lgx/2; i*zoom + tx>=0; i-=unitaxpx)
    {   line(i*zoom + tx, (lgy/2-3)*zoom+ty, i*zoom + tx, (lgy/2+3)*zoom+ty);
        nrsir(k, sir);
        outtextxy(i*zoom + tx, (lgy/2+3)*zoom+ty, sir);
        k--;
    }
    k=0;
    for(int i=lgy/2; i*zoom+ty<=lgy; i+=unitaxpx)
    {   line((lgx/2-3)*zoom+tx, i*zoom+ty, (lgx/2+3)*zoom+tx, i*zoom+ty);
        nrsir(k, sir);
        outtextxy((lgx/2+3)*zoom+tx, i*zoom+ty, sir);
        k--;
    }
    k=0;
    for(int i=lgy/2; i*zoom+ty>=0; i-=unitaxpx)
    {   line((lgx/2-3)*zoom+tx, i*zoom+ty, (lgx/2+3)*zoom+tx, i*zoom+ty);
        nrsir(k, sir);
        outtextxy((lgx/2 +3)*zoom+tx, i*zoom+ty, sir);
        k++;
    }


    strcat(sir, "0\0");

    outtextxy((lgx/2+3)*zoom+tx, (lgy/2+3)*zoom+ty, sir);

}

double tr(int coord, double zoom, int translare)
{
    return coord*zoom+translare;
}

///Functie temporara pentru teste
double func(double n, vector<string> postfix)
{
    return getValueFromPostfix(postfix,n);
}

///Deseneaza functie pe intervalul [a, b] intr-o fereastra de dimensiuni lgx, lgy
void drawf (int a, int b, double unitax, int lgx, int lgy, double zoom, int tx, int ty,vector<string> postfix) {

//    cleardevice();
    drawaxes(a, b, lgx, lgy, zoom, tx, ty);


    ///desenarea graficului
    double x1 = lgx / 2 + (a / unitax) * unitaxpx;
    double y1 = lgy / 2 - (func(a,postfix) / unitax) * unitaxpx;
    double x2 = lgx / 2 + ((a + unitf) / unitax) * unitaxpx;
    double y2 = lgy / 2 - (func(a + unitf,postfix) / unitax) * unitaxpx;

    for (double j = a + 2 * unitf; j <= b; j += unitf) {
        double x3 = (j / unitax) * unitaxpx + lgx / 2;
        double y3 = lgy / 2 - (func(j,postfix) / unitax) * unitaxpx;

        if (!((y1 > lgy && y2 < 0) || (y2 > lgy && y1 < 0))) {
            line(tr(x1, zoom, tx), tr(y1, zoom, ty),
                 tr(x2, zoom, tx), tr(y2, zoom, ty));

            if (y2 < y1 && y2 < y3)
                circle(tr(x2, zoom, tx), tr(y2, zoom, ty), 5 * zoom);
            if (y2 > y1 && y2 > y3)
                circle(tr(x2, zoom, tx), tr(y2, zoom, ty), 5 * zoom);
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
    int a, b;
    char ch;
    double unitax, zoom;
    int tx, ty;
    tx=0;
    ty=0;
    unitax=1;  ///distanta dintre 2 pct pe axa in unitati
    zoom=1;
    a=-10;
    b=10;
//    cout<<"Marginea inferioara a intervalului:";
//    cin>>a;
//    cout<<"Marginea superioara a intervalului:";
//    cin>>b;
//    drawf(a, b, unitax, maxWidth, maxHeigh, zoom, tx, ty,postfix);
    drawf(a, b, unitax, 800, 1000, zoom, tx, ty,postfix);

//    do
//    {
//        drawf(a, b, unitax, 800, 1000, zoom, tx, ty,postfix);
//        ch=getch();
//        switch(ch)
//        {
//            case '+': zoom=zoom+0.1; break;
//            case '-': zoom=zoom-0.1; break;
//            case 'w':
//            case 72 : ty=ty-5; break;
//            case 's':
//            case 80 : ty=ty+5; break;
//            case 'a':
//            case 75 : tx=tx-5; break;
//            case 'd':
//            case 77 : tx=tx+5; break;
//        }
//    } while(ch!='x');



//    closegraph();
}