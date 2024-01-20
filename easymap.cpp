#include <iostream>   
#include <vector>   
#include <random>   
#include <algorithm>   
using namespace std;   
bool isValid(int x, int y, int n, int m, const vector<vector<int>>& a);
bool findPath(int x, int y, int end_x, int end_y, int n, int m, int &pathLength, vector<vector<int>>& a);
int main(){   
    int n, m;   
    cin >> n >> m;   
    bool pathfound=false;  
    vector<vector<int>> a(n, vector<int>(m));   
    while (!pathfound) {  
    random_device rd;  
    mt19937 gen(rd());  
    uniform_int_distribution<> dis(-3, 3);  
    int num_zeros = 2 + rand()%4;  
    bool validMatrix = true;  
    do {  
        validMatrix = true;
        a[0][0] = dis(gen); 
        int zeros_placed = 0; 
        for (int i = 0; i < n; i++) {  
            for (int j = 0; j < m; j++) {  
                if (i == 0 && j == 0) continue;  
                if (zeros_placed < num_zeros && rand()%5 == 0 && a[i][j] != a[0][0]) {  
                    a[i][j] = 0;  
                    zeros_placed++;  
                } else {  
                    do {  
                        a[i][j] = dis(gen);  
                    } while (a[i][j] == 0);  
                }  
            }  
        }  
        if (zeros_placed != num_zeros) {  
            validMatrix = false;  
        }  
    } while (!validMatrix);  
    int start_x = 0, start_y = 0, end_x = n - 1, end_y = m - 1;   
    int pathLength = 0;   
    for (int i = 0; i < n; ++i) {   
        for (int j = 0; j < m; ++j) {   
            cout << a[i][j] << " ";   
        }   
        cout << endl;   
    }   
    cout << "Path: ";   
    if (findPath(start_x, start_y, end_x, end_y, n, m, pathLength, a)) {   
        cout << "Path Length: " << pathLength << endl;   
        pathfound=true;  
    } else {   
        cout << "No valid path found!" << endl;   
    }   
}  
    return 0;   
}