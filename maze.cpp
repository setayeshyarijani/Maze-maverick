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

void createmap() 
{
    system("cls");
    cout << "create map" << endl;
    int difficulty, n, m, min_num, max_num, min_zero, max_zero, step;
    
    cout << "1.easy" << endl << "2.hard" << endl;
    cin >> difficulty;
    
    if(difficulty == 1)
	{
        cout << "height: " << endl;
        cin >> n;
        cout << "width: " << endl;
        cin >> m;
        min_num = -3;
        max_num = 3;
        min_zero = 2;
        max_zero = min(5 , m * n - m - n + 1);
        step = m + n - 2;
    }
    else
	{
        cout << "height: " << endl;
        cin >> n;
        cout << "width: " << endl;
        cin >> m;
        cout << "block min value: " << endl;
        cin >> min_num;
        cout << "block max value: " << endl;
		cin >> max_num;
        cout << "block min zero: " << endl;
        cin >> min_zero; 
        cout << "block max zero: " << endl;
        cin >> max_zero;
        cout << "PathLength: " << endl;
        cin >> step;
        max_zero = min(max_zero , m * n - step - 1);
    }

    bool pathfound=false;
    vector<vector<int>> a(n, vector<int>(m));
        for(int i = 0; i < n; i++)
          {
            for(int j = 0; j < m; j++)
             {
                a[i][j] = 2;
             }
          }
    int pathLength = 0;
    int flag = 1;
    findPath(0 , 0 , n, m, pathLength, step ,a , flag);
    random_device rd;
    mt19937 gen(rd());
    int num_zeros = min_zero + rand() % (max_zero - min_zero + 1);
    vector<vector<int>> backup_a = a;
    bool validMatrix = true;
    int sum = 0;
    int zeros_placed = 0;
    do {
        validMatrix = true;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) 
             {
                if (zeros_placed < num_zeros && rand()% max_zero == 0 && (a[i][j] != 1) && (a[i][j] != 0)) 
                 {
                    a[i][j] = 0;
                    zeros_placed++;
                 }
                if (zeros_placed != num_zeros) 
                {
                    validMatrix = false;
                }
            }
    } 
    while (!validMatrix);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
        {
            if((a[i][j] == 1) && !(i == n - 1 && j == m - 1))
            {
                do
                 {
                    a[i][j] = rand() % (max_num - min_num + 1) + min_num;
                 }
                while (a[i][j] == 0);
                sum += a[i][j];
            }
            else if(a[i][j] != 0)
            {
               do
                {
                  a[i][j] = rand() % (max_num - min_num + 1) + min_num;
                }
               while (a[i][j] == 0);
            }
        }
    a[n - 1][m - 1] = sum;
    for (int i = 0; i < n; i++) 
    {
            for (int j = 0; j < m; j++) 
              {

                cout << left << setw(4) << to_string(a[i][j]) << " ";
              }
            cout << endl;
    }
    savemap(n, m, step, a);
    cout << "press enter to continue";
    getch();
}

