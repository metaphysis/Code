// Leap Birthdays
// UVa ID: 13275
// Verdict: Accepted
// Submission Date: 2021-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool isLeapYear(int year)
{
    return !(year % 400) || (!(year % 4) && (year % 100));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int D, M, Y, QY;
        cin >> D >> M >> Y >> QY;
        int birthdays = 0;
        if (D == 29 && M == 2)
        {
            for (int y = Y + 4; y <= QY; y += 4)
                if (isLeapYear(y))
                    birthdays++;
        }
        else birthdays = QY - Y;
        cout << "Case " << cs << ": " << birthdays << '\n';
    }

    return 0;
}
