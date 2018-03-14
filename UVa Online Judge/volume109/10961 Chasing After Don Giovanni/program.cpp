// Chasing After Don Giovanni
// UVa ID: 10961
// Verdict: Accepted
// Submission Date: 2018-01-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int row, col;
};

inline int diff(int a, int b)
{
    if (a == b) return 0;
    return a < b ? 1 : -1;
}

int main(int argc, char *argv[])
{
    int cases, n;
    point leporello, villagers, tmp, nextL, nextV;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> villagers.row >> villagers.col;
        cin >> leporello.row >> leporello.col;

        nextL = leporello, nextV = villagers;

        cin >> n;
        queue<point> routeL, routeV;

        while (n--)
        {
            cin >> tmp.row >> tmp.col;
            routeL.push(tmp);
        }

        cin >> n;
        while (n--)
        {
            cin >> tmp.row >> tmp.col;
            routeV.push(tmp);
        }

        bool safe = true;
        while (true)
        {
            if (villagers.row == leporello.row && villagers.col == leporello.col)
            {
                safe = routeL.empty() && leporello.row == nextL.row && leporello.col == nextL.col;
                break;
            }

            if (nextL.row == leporello.row && nextL.col == leporello.col)
            {
                if (routeL.empty()) break;
                else { nextL = routeL.front(); routeL.pop(); }
            }

            if (nextV.row == villagers.row && nextV.col == villagers.col)
            {
                if (routeV.empty()) break;
                else { nextV = routeV.front(); routeV.pop(); }
            }

            leporello.row += diff(leporello.row, nextL.row);
            leporello.col += diff(leporello.col, nextL.col);

            villagers.row += diff(villagers.row, nextV.row);
            villagers.col += diff(villagers.col, nextV.col);
        }
        if (c > 1) cout << '\n';
        cout << (safe ? "Yes" : "No") << '\n';
    }

    return 0;
}
