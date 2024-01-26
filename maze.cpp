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

