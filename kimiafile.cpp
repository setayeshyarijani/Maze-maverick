#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

string red = "\033[0;31m";
string blue = "\033[0;36m";
string reset = "\033[0m";

void playground() {
    system("cls");
    int number;
    ifstream mapfile;
    string mapname, addressfile;
    cout << "Playground" << endl;
    cout << "1.choose from existing maps" << endl << "2.import a custom map" << endl;
    cin >> number;
    if (number==1)
    {
        cout << "enter the map name" << endl;
        cin >> mapname;
        mapfile.open("Maps/" + mapname + ".txt");
    }
    else
    {   cout << "enter the map address" << endl;
        cin >> addressfile;
        mapfile.open(addressfile);
    }
    int m, n;
    mapfile >> m >> n;
    vector<vector<int>> mapvalues;
    vector<vector<bool>> mapcrossed;
    for (int i = 0; i < m; i++)
    {
        vector<int> temp;
        vector<bool> falses;
        for (int j = 0; j < n; j++)
        {
            int value;
            mapfile >> value;
            temp.push_back(value);
            falses.push_back(false);
        }
        mapvalues.push_back(temp);
        mapcrossed.push_back(falses);
    }
    mapfile.close();
    cout << "enter your name: ";
    string username;
    cin >> username;
    int sum = 0;
    int x = 0, y = 0;
    bool win = true;
    int start = time(0);
    time_t now = time(0);
    char* date = ctime(&now);
    int end = time(0);
    int gameTime = end - start;
}