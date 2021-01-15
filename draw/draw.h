//
// Created by Ilinca on 12/13/2020.
//
#pragma once
#include "../setup.h"
const double unitf=0.1;

void nrsir (double, char s[]);
double func(double,double,double);
pair<double, double> drawaxes(int, int,double&, int&, int, int);
void drawf (double&, int&, int, int, int, int);
double tr(int, int);
void drawGraph();

