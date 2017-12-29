// February 29
// UVa ID: 12439
// Verdict: Accepted
// Submission Date: 2017-12-29
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

bool isLeapYear(int y)
{
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int getLeapDays(int y, int m, int d)
{
    int leadYearOf4Years = 1, leapYearOf100Years = 24, leapYearOf400Years = 97;
    int y1 = y, leapDays;

    leapDays = y1 / 400 * leapYearOf400Years, y1 %= 400;
    leapDays += y1 / 100 * leapYearOf100Years, y1 %= 100;
    leapDays += y1 / 4 * leadYearOf4Years, y1 %= 4;

    return leapDays;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    string m;
    char comma;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int m1, d1, y1, m2, d2, y2;
        cin >> m >> d1 >> comma >> y1;
        m1 = find(months, months + 12, m) - months + 1;
        cin >> m >> d2 >> comma >> y2;
        m2 = find(months, months + 12, m) - months + 1;
        
        int days1 = getLeapDays(y1, m1, d1), days2 = getLeapDays(y2, m2, d2);

        if (isLeapYear(y1) && (m1 < 2 || (m1 == 2 && d1 <= 29))) days1--;
        if (isLeapYear(y2) && (m2 < 2 || (m2 == 2 && d2 <= 28))) days2--;
   
        cout << "Case " << c << ": " << (days2 - days1) << '\n';
    }

    return 0;
}
