// Logo 2
// UVa ID: 11519
// Verdict: Accepted
// Submission Date: 2017-12-08
// UVa Run Time: 0.010s
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

const double PI = 2.0 * acos(0);
const int LEFT = 0, RIGHT = 1, FORWARD = 2, BACK = 3;

struct command { int d, u; }commands[1010];

void getNext(int d, double u, double &px, double &py, double &angle)
{
    if (d == FORWARD)
    {
        px += u * cos(angle);
        py += u * sin(angle);
    }
    else if (d == LEFT)
    {
        angle += (u / 180.0) * PI;
    }
    else if (d == RIGHT)
    {
        angle -= (u / 180.0) * PI;
    }
    else if (d == BACK)
    {
        px += u * cos(angle - PI);
        py += u * sin(angle - PI);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    string direction, units;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        int mark = -1;
        for (int i = 0; i < n; i++)
        {
            cin >> direction >> units;
            if (units.front() == '?')
            {
                commands[i].u = -1;
                mark = i;
            }
            else
            {
                int u = 0;
                for (int j = 0; j < units.length(); j++)
                    u = u * 10 + units[j] - '0';
                commands[i].u = u;
            }

            if (direction.front() == 'l')
            {
                commands[i].d = LEFT;
            }
            else if (direction.front() == 'r')
            {
                commands[i].d = RIGHT;
            }
            else if (direction.front() == 'f')
            {
                commands[i].d = FORWARD;
            }
            else if (direction.front() == 'b')
            {
                commands[i].d = BACK;
            }
        }

        if (commands[mark].d <= RIGHT)
        {
            double px1 = 0, py1 = 0, angle1 = 0;
            for (int i = 0; i < mark; i++)
                getNext(commands[i].d, 1.0 * commands[i].u, px1, py1, angle1);

            double minD = 1e9;
            int bestDegree = 0;
            for (int degree = 0; degree <= 359; degree++)
            {
                commands[mark].u = degree;

                double px2 = px1, py2 = py1, angle2 = angle1;
                for (int i = mark; i < n; i++)
                    getNext(commands[i].d, 1.0 * commands[i].u, px2, py2, angle2);
                
                double d = sqrt(px2 * px2 + py2 * py2);
                
                if (d < minD)
                {
                    minD = d;
                    bestDegree = degree;
                }
            }
            cout << bestDegree << '\n';
        }
        else
        {
            // 求移动后相对于原始坐标系的坐标值。
            double px1 = 0, py1 = 0, angle1 = 0;
            for (int i = 0; i < mark; i++)
                getNext(commands[i].d, 1.0 * commands[i].u, px1, py1, angle1);
            
            // 从最后一个指令开始，进行相反的移动后相对于原始坐标系的坐标。
            double px2 = 0, py2 = 0, angle2 = angle1;
            for (int i = mark + 1; i < n; i++)
                getNext(commands[i].d, 1.0 * commands[i].u, px2, py2, angle2);

            double d = sqrt(pow(px1 + px2, 2) + pow(py1 + py2, 2));

            cout << fixed << setprecision(0) << d << '\n';
        }
    }

    return 0;
}
