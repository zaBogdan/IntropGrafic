//
// Created by Ilinca on 12/13/2020.
//
#pragma once
#include "../setup.h"
#include "main.h"
//int  unitaxpx=30;
const double unitf=0.1;

void nrsir (double n, char s[]);
void drawaxes (int a, int b, int lgx, int lgy,  double &unitax, int &unitaxpx, int tx, int ty);
void drawf (int a, int b, double &unitax, int &unitaxpx, int lgx, int lgy, int tx, int ty,vector<string> postfix); ///Deseneaza functie pe intervalul [a, b] intr-o fereastra de dimensiuni lgx, lgy
double tr(int coord, int translare); /// translate for a point with a zoom
void drawGraph(vector<string> postfix);

