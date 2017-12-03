// Camel Trading
// UVa ID: 10700
// Verdict: Accepted
// Submission Date: 2017-12-03
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    string text;
    for (int c = 1; c <= cases; c++)
    {
        cin >> text;

        vector<long long> r1, r2;
        int n = 0;

        for (int i = 0; i < text.length(); i++)
        {
            if (isdigit(text[i]))
            {
                n = n * 10 + text[i] - '0';
            }
            else
            {
                r1.push_back(n);
                r1.push_back(text[i] == '+' ? -1 : -2);
                
                r2.push_back(n);
                r2.push_back(text[i] == '+' ? -1 : -2);
                n = 0;
            }
        }
        r1.push_back(n);
        r2.push_back(n);
        
        long long maxv = 1;
        while (r1.size() > 1)
        {
            bool flag = false;
            for (int i = 0; i < r1.size(); i++)
            {
                if (r1[i] == -1)
                {
                    r1[i - 1] += r1[i + 1];
                    r1.erase(r1.begin() + i, r1.begin() + i + 2);
                    flag = true;
                    break;
                }
                
            }
            if (!flag) break;
        }
        for (int i = 0; i < r1.size(); i += 2)
            maxv *= r1[i];

        long long minv = 0;
        while (r2.size() > 1)
        {
            bool flag = false;
            for (int i = 0; i < r2.size(); i++)
            {
                if (r2[i] == -2)
                {
                    r2[i - 1] *= r2[i + 1];
                    r2.erase(r2.begin() + i, r2.begin() + i + 2);
                    flag = true;
                    break;
                }
            }
            if (!flag) break;
        }
        for (int i = 0; i < r2.size(); i += 2)
            minv += r2[i];

        cout << "The maximum and minimum are " << maxv << " and " << minv << ".\n";
    }

    return 0;
}
