#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <fstream>
using namespace std;


string red = "";
string blue = "";
string reset = "";
int main()
{
    system("cls");
    cout << "Playground\n\nenter map name: ";
    string mapname;
    cin >> mapname;
    ifstream mapfile("Maps/"+mapname+".txt");
    int m,n;
    mapfile >> m >> n;
    vector<vector<int>> mapvalues;
    vector<vector<bool>> mapcrossed;
    for(int i=0; i<m ;i++)
    {
        vector<int> temp;
        for(int j=0; j<n;j++)
        {
            int value;
            mapfile >> value;
            temp.push_back(value);
        }
        mapvalues.push_back(temp);
    }
    mapfile.close();
    cout << "enter your name: ";
    string username;
    cin >> username;
    int sum = 0;
    int x=0, y=0;
    bool win = true;
    while(1)
    {
        system("cls");
        for(int i=0;i<m;i++)
        {
            for(int j=0;i<n;j++)
            {
                if(x==i && y==j)
                {
                    cout << red << setw(4) << mapvalues[i][j] << reset << ' ';
                }
                else if(mapcrossed[i][j]== true)
                {
                    cout << blue << setw(4) << mapvalues[i][j] << reset << ' ';
                }
            }
            cout << endl;
        }
        if(x == m-1 && y == n-1)
        {
            if(sum == mapvalues[x][y])
            {
                win = true;
            }
            else
            {
                win = false;
            }
            break;
        }

        int ch = getch();
        bool breakthewhile = false;
        switch(ch)
        {
        case 119://up
            if(mapcrossed[x-1][y] == false)
                {sum += mapvalues[x][y];
                x--;}
            break;
        case 115://down
            if(mapcrossed[x+1][y] == false)
                {sum += mapvalues[x][y];
                x++;}
            break;
        case 97://left
            if(mapcrossed[x][y-1] == false)
                {sum += mapvalues[x][y];
                y--;}
            break;
        case 100://right
            if(mapcrossed[x][y+1] == false)
                {sum += mapvalues[x][y];
                y++;}
            break;
        case 27://escape
            breakthewhile = true;
            win = false;
            break;
        }
        if(breakthewhile== true)
        {
            break;
        }

        mapcrossed[x][y] = true;
    }



}

