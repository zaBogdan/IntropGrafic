//
// Created by Bogdan Zavadovschi on 09.01.2021.
//
#pragma once
#include "../setup.h"
extern langCore language;

void loadSettings(string);
bool saveConfiguration(string);
bool loadLanguage(string);
string sanitizeString(string);