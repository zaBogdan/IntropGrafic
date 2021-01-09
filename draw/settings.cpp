//
// Created by Bogdan Zavadovschi on 09.01.2021.
//

#include "settings.h"
langCore language;

void loadSettings(string name)
{
    string path = "../settings/"+name+".conf";
    ifstream f(path);
    if(!f.is_open())
    {
        cout << "[Settings] This file doesn't exist! Please check again! Aboarding...\n";
        return;
    }
    string line;
    while(getline(f,line))
    {
        string name = line.substr(0, line.find("="));
        string value = line.substr(line.find("=")+1, line.length());

        //check for cases like =test or test=
        if(name.empty() || value.empty())
            continue;
        if(name == "language")
            userSettings.language = value;
        else if(name == "axis_arrows")
            userSettings.axis_arrows = (value!="0");
        else if(name ==  "axis_numbers")
            userSettings.axis_numbers = (value!="0");
        else if(name == "minor_gridlines")
            userSettings.minor_gridlines = (value!="0");
        else if(name == "measure")
            userSettings.measure = value; //we can only have radians/degree
        else
        {
            cout << "[Settings] Setting " << name << " couldn't be found! Skipping.\n";
        }
    }
    userSettings.initialized=true;
    f.close();
}
bool saveConfiguration(string name)
{
    string path = "../settings/"+name+".conf";
    ofstream g(path);
    if(!g.is_open())
    {
        cout << "[Settings] This file couldn't be open! Please check again! Aboarding...\n";
        return false;
    }
    string settingsFormat = "";
    settingsFormat = settingsFormat + "language=" + userSettings.language+"\n";
    settingsFormat = settingsFormat + "axis_arrows=" + (userSettings.axis_arrows ? "1" : "0")+"\n";
    settingsFormat = settingsFormat + "axis_numbers=" + (userSettings.axis_numbers? "1": "0")+"\n";
    settingsFormat = settingsFormat + "minor_gridlines=" + (userSettings.minor_gridlines? "1":"0")+"\n";
    settingsFormat = settingsFormat + "measure=" + userSettings.measure+"\n";
    g << settingsFormat;
    g.close();
    userSettings.isModified=true;
    return true;
}
bool loadLanguage(string name) {
    string path = "../lang/" + name + ".lang";
    ifstream f(path);
    if (!f.is_open()) {
        cout << "[Language] Couldn't find the file with path " << path << "! Exiting...";
        return false;
    }
    string line;
    while (getline(f, line)) {
        string name = line.substr(0, line.find("="));
        string value = line.substr(line.find("=") + 1, line.length());
        name = sanitizeString(name);
        value = sanitizeString(value);
        language[name] = value;
    }

    return true;
}
string sanitizeString(string name)
{
    bool insideQuotes = false;
    string newString = "";

    for(int i=0;i<name.length();i++)
    {
        if(name[i]=='"')
            insideQuotes=!insideQuotes;
        if(name[i]==' ' && insideQuotes)
        {
            newString+=name[i];
        }
        if(name[i]!=' ' && name[i]!=';' && name[i]!='"')
            newString+=name[i];
    }
    return newString;
}