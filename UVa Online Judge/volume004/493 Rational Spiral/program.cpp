// Rational Spiral
// UVa ID: 493
// Verdict: Accepted
// Submission Date: 2016-07-29
// UVa Run Time: 0.580s
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

    vector<pair<int, int>> offset = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    set<long long> produced = {100001, 1};
    map<int, pair<int, int>> rational = {{0, {1, 1}}, {1, {0, 1}}};
    
    int number, max_number = 0;
    vector<int> numbers;
    
    while (cin >> number)
    {
        numbers.push_back(number);
        max_number = max(max_number, number);
    }
        
    int direction = 0, counter = 2, startx = 0, starty = 0;
    queue<int> step;
    step.push(1), step.push(1);
    
    while (counter <= max_number)
    {
        int lengthOfStep = step.front();
        step.pop();
        
        for (int i = 1; i <= lengthOfStep; i++)
        {
            startx += offset[direction].first;
            starty += offset[direction].second;
            
            if (startx == 0 || starty == 0) continue;
            
            int sign = 1;
            if (starty < 0) sign *= -1;
            if (startx < 0) sign *= -1;
            
            int nexty = abs(starty), nextx = abs(startx);
            int a = nexty, b = nextx, t;
            while (a % b) t = a, a = b, b = t % b;
            
            if (b > 0) nexty /= b, nextx /= b;
            if (produced.find(sign * (nexty * 100000 + nextx)) == produced.end())
            {
                produced.insert(sign * (nexty * 100000 + nextx));
                rational[counter] = make_pair(sign * nexty, nextx);
                counter++;
            }
        }
        
        direction += 1;
        direction %= 4;
        
        step.push(lengthOfStep + 1);
    }
    
    for (auto aNumber : numbers)
    {
        pair<int, int> resutl = rational[aNumber];
        cout << resutl.first << " / " << resutl.second << '\n';
    }
    
	return 0;
}
