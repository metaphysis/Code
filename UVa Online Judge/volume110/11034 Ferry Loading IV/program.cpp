// Ferry Loading IV
// UVa ID: 11034
// Verdict: Accepted
// Submission Date: 2017-02-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

    int c, lane_length, car_length, m;
    queue<int> left_bank, right_bank;
    string bank;

    cin >> c;
    for (int i = 0; i < c; i++)
    {
        cin >> lane_length >> m;
        
        lane_length *= 100;
        
        for (int j = 0; j < m; j++)
        {
            cin >> car_length >> bank;
            if (bank == "left") left_bank.push(car_length);
            else right_bank.push(car_length);
        }
        
        int times = 0, at_left = 1;
        while (true)
        {
            if (left_bank.empty() && right_bank.empty()) break;

            int loaded_length = 0;
            if (at_left)
            {
                while (!left_bank.empty() && loaded_length < lane_length)
                {
                    if (left_bank.front() + loaded_length > lane_length)
                        break;
                    loaded_length += left_bank.front();
                    left_bank.pop();
                }
                at_left = 0;
            }
            else
            {
                while (!right_bank.empty() && loaded_length < lane_length)
                {
                    if (right_bank.front() + loaded_length > lane_length)
                        break;
                    loaded_length += right_bank.front();
                    right_bank.pop();
                }
                at_left = 1;
            }
            
            times++;
        }
        
        cout << times << '\n';
    }

    return 0;
}
