// Counting Weekend Days
// UVa ID: 1727
// Verdict: Accepted
// Submission Date: 2019-03-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<string, int> weekday = {
        {"SUN", 1}, {"MON", 2}, {"TUE", 3}, {"WED", 4},
        {"THU", 5}, {"FRI", 6}, {"SAT", 7}
    };
    map<string, int> months = {
        {"JAN", 0}, {"FEB", 1}, {"MAR", 2}, {"APR", 3},
        {"MAY", 4}, {"JUN", 5}, {"JUL", 6}, {"AUG", 7},
        {"SEP", 8}, {"OCT", 9}, {"NOV", 10}, {"DEC", 11}
    };
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int cases;
    cin >> cases;
    string MTH, DAY;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> MTH >> DAY;
        int weekend = 0;
        for (int i = 1, j = weekday[DAY]; i <= daysInMonth[months[MTH]]; i++, j++)
        {
            if (j >= 6) weekend++;
            j %= 7;
        }
        cout << weekend << '\n';
    }

    return 0;
}
