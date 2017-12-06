// Playball !!!
// UVa ID: 10357
// Verdict: Accepted
// Submission Date: 2017-12-06
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

struct player
{
    double x, y, v;
}players[21];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string tplayers, tballs;
    int np, nb;
    double a, b, c, d, e, f, g;

    while (cin >> tplayers)
    {
        np = 0;
        for (auto c : tplayers)
            if (isdigit(c))
                np = np * 10 + c - '0';

        for (int i = 0; i < np; i++)
        {
            cin >> players[i].x >> players[i].y >> players[i].v;
        }

        cin >> tballs;
        nb = 0;
        for (auto c : tballs)
            if (isdigit(c))
                nb = nb * 10 + c - '0';

        for (int i = 1; i <= nb; i++)
        {
            cin >> a >> b >> c >> d >> e >> f >> g;

            double travelTime;
            double root = b * b - 4.0 * a * c;
            if (root < 0)
            {
                travelTime = 1;
            }
            else
            {
                int root1 = (-b + sqrt(root)) / (2 * a);
                int root2 = (-b - sqrt(root)) / (2 * a);
                
                travelTime = max(root1, root2);
                while (a * travelTime * travelTime + b * travelTime + c > 0)
                    travelTime++;
            }

            cout << "Ball " << i << " was ";
            int x = d * travelTime + e, y = f * travelTime + g;
            if (x < 0 || y < 0)
            {
                cout << "foul";
            }
            else
            {
                bool caught = false;
                for (int j = 0; j < np; j++)
                {
                    double arrivedTime = sqrt(pow(players[j].x - x, 2) + pow(players[j].y - y, 2)) / players[j].v;
                    if (arrivedTime <= travelTime)
                    {
                        cout << "caught";
                        caught = true;
                        break;
                    }
                }
                if (!caught)
                {
                    cout << "safe";
                }
            }
            cout << " at (" << x << ',' << y << ")\n";
        }
    }

    return 0;
}
