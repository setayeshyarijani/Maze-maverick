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
     while (true)
    {
        system("cls");
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (x == i && y == j)
                {
                    cout << red << setw(4) << mapvalues[i][j] << reset << ' ';
                }
                else if (mapcrossed[i][j] == true)
                {
                    cout << blue << setw(4) << mapvalues[i][j] << reset << ' ';
                }
                else
                {
                    cout << setw(4) << mapvalues[i][j] << ' ';
                }
            }
            cout << endl;
        }
        if (x == m - 1 && y == n - 1)
        {
            if (sum != mapvalues[x][y])
                win = false;
            break;
        }
        mapcrossed[x][y] = true;
        int ch = getch();
        bool breakthewhile = false;
        switch (ch)
        {
        case 119: // up
            if (x > 0 && mapcrossed[x - 1][y] == false && mapvalues[x - 1][y] !=0 )
            {
                sum += mapvalues[x][y];
                x--;
            }
            break;
        case 115: // down
            if (x < m - 1 && mapcrossed[x + 1][y] == false && mapvalues[x + 1][y] !=0)
            {
                sum += mapvalues[x][y];
                x++;
            }
            break;
        case 97: // left
            if (y > 0 && mapcrossed[x][y - 1] == false && mapvalues[x][y - 1] !=0)
            {
                sum += mapvalues[x][y];
                y--;
            }
            break;
        case 100: // right
            if (y < n - 1 && mapcrossed[x][y + 1] == false && mapvalues[x][y + 1] != 0)
            {
                sum += mapvalues[x][y];
                y++;
            }
            break;
        case 27: // escape
            breakthewhile = true;
            win = false;
            break;
        }
        if (breakthewhile == true)
        {
            break;
        }
    }
    string result;
    if(win){
        cout << "you win"<<endl << "press enter to continue";
        getch();
        result = "Win";
    }
    else{
       cout << "you lose"<<endl << "press enter to continue";
       getch();
       result = "Lose";
    }
    int end = time(0);
    int gameTime = end - start;
    updateUser(username , result , gameTime);
    updatehistory(date , username , mapname , gameTime , result);
}

void updateUser(string name , string result , int gameTime){
    ifstream file("Users/" + name + ".txt");
    Player user;
    if(file.is_open()){
        file>>user.totalgames>>user.games;
        file>>user.totalwins>>user.wins;
        file>>user.gametime>>user.lastTime;
        file>>user.totalgametime>>user.totalTime;
        file.close();
        user.games++;
        if(result == "Win"){
            user.wins++;
            user.lastTime = gameTime;
        }
        user.totalTime += gameTime;
        ofstream file("Users/" + name + ".txt");
        if(file.is_open()){
            file<<user.totalgames<<" "<<user.games<<endl<<user.totalwins<<" "<<user.wins<<endl<<user.gametime<<" "<<user.lastTime<<endl<<user.totalgametime<<" "<<user.totalTime;
            file.close();
        }
    }
    else{
        ofstream file("Users/" + name + ".txt");
        if(file.is_open()){
            file<<"Totalgames: "<< 1 <<endl;
            if(result == "Win"){
                file<<"Totalwins: "<< 1 <<endl;
                file<<"Gametime: " << gameTime << endl;
            }
            else{
                file<<"Totalwins: "<< 0 <<endl;
                file<<"Gametime: "<< 0 <<endl;
            }
            file<<"Totalgametime: "<< gameTime;
            file.close();
        }
    }
}