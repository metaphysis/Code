// Leap Year or Not Leap Year and ...
// UVa ID: 10070
// Verdict: Accepted
// Submission Date: 2017-03-02
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

int bigmod(string& line, int n)
{
    int m = 0;
    for (int i = 0; i < line.length(); i++)
    {
        m = m * 10 + (line[i] - '0');
        m %= n;
    }
    return m;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    string year;

    while (cin >> year)
    {
        if (cases++ > 0) cout << '\n';
        
        int outputed = 0;
        bool is_leap_year = false;
        
        if ((bigmod(year, 4) == 0 && bigmod(year, 100) != 0) || (bigmod(year, 400) == 0))
        {
            cout << "This is leap year.\n";
            is_leap_year = true;
            outputed++;
        }
        
        if (bigmod(year, 15) == 0)
        {
            cout << "This is huluculu festival year.\n";
            outputed++;
        }
        
        if (bigmod(year, 55) == 0 && is_leap_year)
        {
            cout << "This is bulukulu festival year.\n";
            outputed++;
        };
        
        if (outputed == 0)
        {
            cout << "This is an ordinary year.\n";
        }
    }
    
    return 0;
}
