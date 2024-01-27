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

// function for creating easy and hard map //
void createmap() 
{
    system("cls");
    cout << red << "Create map" << reset << endl;
    int number, n, m, min_num, max_num, min_zero, max_zero, step;
    cout << "1.Easy" << endl << "2.Hard" << endl << "3.Back to menu" <<endl;
    cin >> number;
    // easy map //
    if(number == 1)
	{
        cout << "Height: " << endl;
        cin >> n;
        cout << "Width: " << endl;
        cin >> m;
        min_num = -3;
        max_num = 3;
        min_zero = 2;
        max_zero = min(5 , m * n - m - n + 1);
        step = m + n - 2;
    }
    //hard map
    else if(number == 2)
	{
        cout << "Height: " << endl;
        cin >> n;
        cout << "Width: " << endl;
        cin >> m;
        cout << "Block min value: " << endl;
        cin >> min_num;
        cout << "Block max value: " << endl;
		cin >> max_num;
        cout << "Block min zero: " << endl;
        cin >> min_zero; 
        cout << "Block max zero: " << endl;
        cin >> max_zero;
        cout << "PathLength: " << endl;
        cin >> step;
        max_zero = min(max_zero , m * n - step - 1);
    }
    else if(number == 3)
	return;
    bool pathfound = false;
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
    // finding maze path //
    findPath(0 , 0 , n, m, pathLength, step ,a , flag);
    // generate random number //
    random_device rd;
    mt19937 gen(rd());
    int num_zeros = min_zero + rand() % (max_zero - min_zero + 1);
    vector<vector<int>> backup_a = a;
    bool validMatrix = true;
    int sum = 0;
    int zeros_placed = 0;
    do {
        validMatrix = true;
	// place block (0) in map //
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
    // filling the rest blocks randomly //
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
    // put sum in the last block //
    a[n - 1][m - 1] = sum;
    // show the created map in terminal //
    for (int i = 0; i < n; i++) 
    {
            for (int j = 0; j < m; j++) 
              {

                cout << left << setw(4) << to_string(a[i][j]) << " ";
              }
            cout << endl;
    }
    // saving created map in map file //
    savemap(n, m, step, a);
    cout << "Press enter to continue";
    getch();
}
// function for make move and find path //
void findPath(int x, int y, int n, int m, int &pathLength, int step ,vector<vector<int>>& a, int& flag) 
{
    a[x][y] = 1;
    if (x == n - 1 && y == m - 1 && pathLength == step ) 
      {
        flag = 0;
        return;
      }
    if(pathLength > step - 1)
    {
        a[x][y] = 2;
        return;
    }
    pathLength++;
    vector<pair<int, int>> moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    random_device rd;
    mt19937 gen(rd());
    // finding the path randomly //
    shuffle(moves.begin() ,moves.end() ,gen);
    for (const auto& move : moves) {
        int new_x = x + move.first;
        int new_y = y + move.second;
        if (isValid(new_x, new_y, n, m, a)) {
            findPath(new_x, new_y, n , m , pathLength, step, a, flag);
            if(flag == 0)
                return;
        }
    }
    // can go in it agaian later //
    a[x][y] = 2;
    pathLength--;
}
// function for solving maps and showing the path // 
void solvemaze() {
    system("cls");
    cout << red << "Solve maze" << reset <<endl;
    int number;
    int whileflag = 1;
    ifstream mapfile;
    string mapname, addressfile;
    // get the player choice //
    cout << "1.Choose from existing maps" << endl << "2.Import a custom map" << endl <<  "3.Back to menu" <<endl;
    cin >> number;
    // for exist map //
    if (number == 1)
    {   
	// showing mapslist for user to choose from them //
	cout << "mapslist: " << endl;
        string line;
        ifstream mapslist("Maps/mapslist.txt");
        while(getline(mapslist, line)){
            cout << line << endl;
        }
        mapslist.close();
	// get the player map name //
        while ( whileflag == 1){
            cout << "Enter the map name" << endl;
            cin >> mapname;
            mapfile.open("Maps/" + mapname + ".txt");
	    // if the map exists //
            if(mapfile.is_open())
                whileflag = 0;
	    // if the map doesn't exist //	    
            else
                cout << "No map found!" << endl;
        }
    }
    // new custom map importing from user //
    else if(number == 2)
    {   cout << "Enter the map address" << endl;
        cin >> addressfile;
        mapfile.open(addressfile);
    }
    // back to menu //
    else if(number == 3)
	return;
    // reading mapfile //
    int m, n;
    mapfile >> m >> n;
    vector<vector<int>> mapvalues;
    vector<vector<int>> b(m , vector<int>(n));
    int pathlength = 0 , flag = 1 , sum = 0;
    for (int i = 0; i < m; i++)
    {
        vector<int> temp;
        for (int j = 0; j < n; j++)
        {
            int value;
            mapfile >> value;
            temp.push_back(value);
        }
        mapvalues.push_back(temp);
    }
    int step;
    mapfile >> step;
    mapfile.close();
    // creating vector<vector<int>>b //
    for(int i = 0 ; i < m; i++){
		for(int j = 0; j < n ; j++)
		{
			b[i][j] = 2;
		}
	}
    // show maze path //
    resultpath(0, 0, m, n, pathlength, step, b, flag, sum, mapvalues);
    for(int i = 0 ; i < m; i++){
		for(int j = 0; j < n ; j++)
		{
			if(b[i][j] == 1){
				cout << blue << setw(4) <<mapvalues[i][j] << reset << " ";
			}
			else{
				cout << setw(4) << mapvalues[i][j] << " ";
			}
		}
		cout << endl;
	}
    cout << "Press enter to continue";
    getch();
}
// function for finding maze solving path //
void resultpath(int x, int y, int n, int m, int &pathLength, int step ,vector<vector<int>>& a, int& flag, int &sum , vector<vector<int>>b) {
    a[x][y] = 1;
    sum += b[x][y];
    if (x == n - 1 && y == m - 1 && pathLength == step && sum == 2 * b[n-1][m-1]) {
        flag = 0;
        return;
    }
    if(pathLength > step - 1 ){
        a[x][y] = 2;
        sum -= b[x][y];
        return;
    }
    pathLength++;
    // condition for move and path //
    vector<pair<int, int>> moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        if (isValid(x+1, y, n, m, a) && b[x+1][y] != 0) {
            resultpath(x+1, y, n, m, pathLength, step, a, flag, sum, b);
            if(flag == 0)
                return;
        }
        if (isValid(x-1, y, n, m, a)&&b[x-1][y] != 0) {
            resultpath(x-1, y, n, m, pathLength, step, a, flag, sum, b);
            if(flag == 0)
                return;
        }
        if (isValid(x, y+1, n, m, a)&&b[x][y+1] != 0) {
            resultpath(x, y+1, n , m , pathLength, step, a, flag, sum, b);
            if(flag == 0)
                return;
        }
         if (isValid(x,y-1, n, m, a) &&b[x][y-1] != 0) {
            resultpath(x, y-1, n, m, pathLength, step, a, flag, sum, b);
            if(flag == 0)
                return;
         }
    a[x][y] = 2;
    sum -=b[x][y];
    pathLength--;
}
// function for valid blocks //
bool isValid(int x, int y, int n, int m, vector<vector<int>> a) 
{
    return x >= 0 && x < n && y >= 0 && y < m && a[x][y] != 1;
}
