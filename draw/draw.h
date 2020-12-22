//
// Created by Ilinca on 12/13/2020.
//
#pragma once
#include <graphics.h>
#include <math.h>
#include <string.h>

const int  unitaxpx=30;
const double unitf=0.01;

void nrsir (int n, char s[]);
void drawaxes (int a, int b, int lgx, int lgy, double zoom, int tx, int ty);
void drawf (int a, int b, double unitax, int lgx, int lgy, double zoom, int tx, int ty); ///Deseneaza functie pe intervalul [a, b] intr-o fereastra de dimensiuni lgx, lgy
double func(double n); ///Functie temporara pentru teste
double tr(int coord, double zoom, int translare); /// translate for a point with a zoom


