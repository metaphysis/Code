// Frogger
// UVa ID: 534
// Verdict: Accepted
// Submission Date: 2016-08-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, distances[201][201], cases = 0;
    pair<int, int> points[201];
    
    while (cin >> n, n)
    {
        for (int i = 1; i <= n; i++)
            cin >> points[i].first >> points[i].second;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                distances[i][j] = distances[j][i] =
                    (points[j].first - points[i].first) * (points[j].first - points[i].first) +
                    (points[j].second - points[i].second) * (points[j].second - points[i].second);
                
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    distances[i][j] = min(distances[i][j], max(distances[i][k], distances[k][j]));
                
        cout << "Scenario #" << ++cases << '\n';
        cout << "Frog Distance = " << fixed << setprecision(3) << sqrt(distances[1][2]) << '\n';
        cout << '\n';
    }
    
	return 0;
}
