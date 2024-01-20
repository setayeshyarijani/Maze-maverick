#include <iostream>   
#include <vector>   
#include <random>   
#include <algorithm>   
  
using namespace std;   
  
bool isValid(int x, int y, int n, int m, const vector<vector<int>>& a) {   
    return x >= 0 && x < n && y >= 0 && y < m && a[x][y] != 0;   
}   
     
  bool findPath(int x, int y, int end_x, int end_y, int n, int m, int &pathLength, vector<vector<int>>& a) {
    if (x == end_x && y == end_y) {
        pathLength++;
        return true;
    }

    if (isValid(x, y, n, m, a)) {
        cout << a[x][y] << " ";
        pathLength++;

        a[x][y] = 0;

        vector<pair<int, int>> moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        random_shuffle(moves.begin(), moves.end());

        for (const auto& move : moves) {
            int new_x = x + move.first;
            int new_y = y + move.second;

            if (isValid(new_x, new_y, n, m, a) && findPath(new_x, new_y, end_x, end_y, n, m, pathLength, a)) {
                return true;
            }
        }

        a[x][y] = numeric_limits<int>::max();
    }

    return false;
}
