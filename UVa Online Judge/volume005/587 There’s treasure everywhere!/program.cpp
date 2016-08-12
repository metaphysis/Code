// There’s treasure everywhere!
// UVa ID: 587
// Verdict: Accepted
// Submission Date: 2016-08-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    cout << fixed << setprecision(3);
    
    map<string, pair<int, int>> offset = {
        {"N", {0, 1}}, {"NE", {1, 1}}, {"E", {1, 0}}, {"SE", {1, -1}},
        {"S", {0, -1}}, {"SW", {-1, -1}}, {"W", {-1, 0}}, {"NW", {-1, 1}}, 
    };
    
    int cases = 0;
    string line;
    while (getline(cin, line), line != "END")
    {
        if (line.back() == '.')
            line.erase(line.end() - 1);
            
        pair<int, int> x = {0, 0}, y = {0, 0};

        istringstream iss(line);
        string block;
        while (getline(iss, block, ','))
        {
            int number = 0;
            for (int i = 0; i < block.length() && isdigit(block[i]); i++)
                number = number * 10 + block[i] - '0';
            string direction;
            for (int i = block.length() - 1; i >= 0 && isalpha(block[i]); i--)
                direction.insert(direction.begin(), block[i]);
                
            if (direction == "NE" || direction == "SE" || direction == "SW" || direction == "NW")
            {
                x.second += offset[direction].first * number;
                y.second += offset[direction].second * number;
            }
            else
            {
                x.first += offset[direction].first * number;
                y.first += offset[direction].second * number;
            }
        }
        
        double xx = x.first + x.second * sqrt(2) / 2, yy = y.first + y.second * sqrt(2) / 2;
        double distances = sqrt(xx * xx + yy * yy);
        
        cout << "Map #" << ++cases << '\n';
        cout << "The treasure is located at (" << xx << "," << yy << ").\n";
        cout << "The distance to the treasure is " << distances << ".\n";
        cout << '\n';
    }
    
	return 0;
}
