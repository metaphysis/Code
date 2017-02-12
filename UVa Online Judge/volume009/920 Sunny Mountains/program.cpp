// Sunny Mountains
// UVa ID: 920
// Verdict: Accepted
// Submission Date: 2017-02-12
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

const int MAXN = 110;

struct point
{
    int x, y;
    
    bool operator<(const point &b) const
    {
        return x < b.x;
    }
};

point points[MAXN];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int C;
    cin >> C;
    
    for (int i = 1; i <= C; i++)
    {
        int N;
        cin >> N;
        for (int j = 0; j < N; j++)
        {
            cin >> points[j].x >> points[j].y;
        }
        
        sort(points, points + N);
        
        double sides = 0.0;
        int highestY = 0;

        for (int j = N - 1; j >= 0; j -= 2)
        {
            if (j >= 1)
            {
                if (points[j - 1].y > highestY)
                {
                    double arc = sqrt(pow(points[j].x - points[j - 1].x, 2) + pow(points[j].y - points[j - 1].y, 2));
                    sides += arc * (double)(points[j - 1].y - highestY) / (double)(points[j - 1].y - points[j].y);
                    highestY = points[j - 1].y;
                }
            }
        }

        cout << fixed << setprecision(2) << sides << '\n';
    }

    return 0;
}
