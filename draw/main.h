//
// Created by Bogdan Zavadovschi on 07.01.2021.
//
#pragma once
#include "../setup.h"
#include "settings.h"
#include "pages.h"
#include "draw.h"
using namespace std;
const int maxWidth = 1024;
const int maxHeigh = 768;
const int frames=80;
extern int activePage;
extern settings userSettings;
extern int isShiftUp;
extern vector<string> postfix;


void initialSetup();
void graphic(vector<string> postfix);
void exitGraphic();
int gameLoop(coord, char, vector <string> postfix);
void mainMenuPage(coord);