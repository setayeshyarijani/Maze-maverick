#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

// define colors //
string red = "\033[0;31m";
string blue = "\033[0;36m";
string reset = "\033[0m";

// struct for users and games information //
struct Player
{
    int games;
    int wins;
    int lastTime;
    int totalTime;
    string totalgames;
    string totalwins;
    string gametime;
    string totalgametime;
};

// function for playing game //
void playground() {
    system("cls");
    int number;
    // define mapfile for choosing a map //
    ifstream mapfile;
    string mapname, addressfile;
    cout << "Playground" << endl;
    cout << "1.choose from existing maps" << endl << "2.import a custom map" << endl;
    // get the player choice //
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
    // reading mapfile //
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
    // calculate the Date //
    time_t now = time(0);
    char* date = ctime(&now);
    while (true)
    {
        system("cls");
        // show status of map //
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
        // define and make movements //
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
    // show the game result //
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
    // calculate the gametime //
    int gameTime = end - start;
    // update user and history files //
    updateUser(username , result , gameTime);
    updatehistory(date , username , mapname , gameTime , result);
}

// function for updating users game information //
void updateUser(string name , string result , int gameTime){
    ifstream file("Users/" + name + ".txt");
    Player user;
    // if user has played before //
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
    // new user //
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

// updating users game history //
void updatehistory(char* date , string username , string mapname , int gametime , string result) {
    ifstream file ("History/history.txt");
    int num = 0;
    string newdate = date; 
    string a = "date : " + newdate + "username : " + username + "\n" +"mapname : " + mapname + "\n" + "game time : " + to_string(gametime) + "\n" + "result : "+ result + "\n" + "---------------------" + "\n";
    string b;
    // updating game history for 10 last games //
    if(file.is_open())
    {
        while (getline(file , b) &&  num < 9)
        {
            a += b + "\n";
            getline(file , b);
            a += b + "\n";
            getline(file , b);
            a += b + "\n";
            getline(file , b);
            a += b + "\n";
            getline(file , b);
            a += b + "\n";
            getline(file , b);
            a += b + "\n";
            num++;
        }
    file.close();
    }
    ofstream historyfile ("History/history.txt");
    historyfile << a;
}

// function for showing user information //
void user() {
    string username;
    string totalgames,totalwins,gametime,totalgametime;
    cout<<"enter your name: ";
    cin>>username;
    ifstream userfile("Users/" + username + ".txt");
    // if user exists //
    if(userfile.is_open()){
        getline(userfile,totalgames);
        getline(userfile,totalwins);
        getline(userfile,gametime);
        getline(userfile,totalgametime);
    }
    // if user doesn't exist //
    else
    {
        cout<<"no user found";
    }
    cout<<totalgames<<endl<<totalwins<<endl<<gametime<<endl<<totalgametime<<endl;
    cout<<"press enter to continue";
    getch();
}

// function for showing games history //
void history() {
    string line;
    ifstream historyfile("History/history.txt");
    while(getline(historyfile, line)){
        cout<<line<<endl;
    }
    historyfile.close();
    cout<<"press enter to continue";
    getch();
}

// function for saving created map as file //
void savemap(int n , int m , int step , vector<vector<int>> mazemap) {
    string mapsname;
    // getting map name from user //
    cout << "enter the map name: ";
    cin >> mapsname;
    ofstream map("Maps/" + mapsname + ".txt");
    // write map in file //
    if (map.is_open())
    {
        map << n << " " << m << endl;
        for (int i=0 ; i<n ; i++)
        {
            for (int j=0 ; j<m ; j++)
            {
                map <<left << setw(4) << mazemap[i][j] << " ";   
            }
            map << endl;
        }
        map << step << endl;
        map.close();
    }
}