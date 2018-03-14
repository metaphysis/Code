// Logo
// UVa ID: 11505
// Verdict: Accepted
// Submission Date: 2017-12-07
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    string command;
    double units, px, py, angle;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        px = 0, py = 0, angle = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> command >> units;
            if (command.front() == 'f')
            {
                px += units * cos(angle);
                py += units * sin(angle);
            }
            else if (command.front() == 'l')
            {
                angle += (units / 180) * PI;
            }
            else if (command.front() == 'r')
            {
                angle -= (units / 180) * PI;
            }
            // Just move back, the turtle DO NOT trun its head back.
            else if (command.front() == 'b')
            {
                px += units * cos(angle - PI);
                py += units * sin(angle - PI);
            }
        }
        cout << fixed << setprecision(0) << sqrt(px * px + py * py) << '\n';
    }

    return 0;
}
