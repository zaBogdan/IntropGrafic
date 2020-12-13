//
// Created by Ilinca on 12/13/2020.
//
#pragma once
#include <graphics.h>
#include <math.h>

const int  unitaxpx=30;
const double unitf=0.01;

void drawaxes (int lgx, int lgy);
void drawf (int a, int b, int unitax, int lgx, int lgy); ///Deseneaza functie pe intervalul [a, b] intr-o fereastra de dimensiuni lgx, lgy
double func(double n); ///Functie temporara pentru teste
