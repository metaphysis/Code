// Highways
// UVa ID: 1393
// Verdict: Accepted
// Submission Date: 2025-11-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int gridSize = 305;
int visiblePoints[gridSize][gridSize];
int highwayCount[gridSize][gridSize];

void initializeTables() {
    for (int i = 1; i < gridSize; i++)
        for (int j = 1; j < gridSize; j++)
            visiblePoints[i][j] = visiblePoints[i - 1][j] + visiblePoints[i][j - 1] - visiblePoints[i - 1][j - 1] + (__gcd(i, j) == 1);
    for (int i = 1; i < gridSize; i++)
        for (int j = 1; j < gridSize; j++)
            highwayCount[i][j] = highwayCount[i - 1][j] + highwayCount[i][j - 1] - highwayCount[i - 1][j - 1] + visiblePoints[i][j] - visiblePoints[i / 2][j / 2];
}

int main() {
    initializeTables();
    int n, m;
    while (cin >> n >> m and (n != 0 or m != 0))
        cout << 2 * highwayCount[n - 1][m - 1] << endl;
    return 0;
}

