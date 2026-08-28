#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCount, colCount, pointCount = 0;
    cin >> rowCount >> colCount;
    vector<int> pointX, pointY;
    int x, y;
    while (cin >> x >> y) {
        if (x < 0 || x >= colCount || y < 0 || y >= rowCount)
            continue;
        pointX.push_back(x);
        pointY.push_back(y);
        pointCount++;
    }
    vector<int> minRadius(pointCount + 1, 0), maxPoint((rowCount - 1) + (colCount - 1) + 2, 0);
    int maxDist = (rowCount - 1) + (colCount - 1);
    for (int centerX = 0; centerX < colCount; centerX++) {
        for (int centerY = 0; centerY < rowCount; centerY++) {
            vector<int> dist(pointCount);
            for (int i = 0; i < pointCount; i++)
                dist[i] = abs(pointX[i] - centerX) + abs(pointY[i] - centerY);
            sort(dist.begin(), dist.end());
            for (int i = 0; i < pointCount; i++) {
                int beginPos = i;
                while (i + 1 < pointCount && dist[beginPos] == dist[i + 1])
                    i++;
                for (int rank = i; rank >= beginPos; rank--)
                    minRadius[rank + 1] = max(minRadius[rank + 1], max(dist[i], 1));
                maxPoint[dist[i]] = max(maxPoint[dist[i]], i + 1);
            }
        }
    }
    for (int i = 1; i <= maxDist + 1; i++)
        maxPoint[i] = max(maxPoint[i], maxPoint[i - 1]);
    cout << "Pmin  Rmin(Pmin)  Pmax(Pmin)\n";
    for (int pMin = 1; pMin <= pointCount; pMin++) {
        if (pMin + 1 <= pointCount && minRadius[pMin] == minRadius[pMin + 1])
            continue;
        cout << setw(4) << pMin << "  " << setw(10) << minRadius[pMin] << "  " << setw(10) << maxPoint[minRadius[pMin]] << '\n';
    }
    return 0;
}
