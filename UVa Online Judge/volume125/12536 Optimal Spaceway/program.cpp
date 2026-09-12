#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

long double calcCost(long double sumWeight, long double sumX, long double sumY, long double sumXX, long double sumYY, long double sumXY) {
    long double meanX = sumX / sumWeight, meanY = sumY / sumWeight;
    long double varX = sumXX / sumWeight - meanX * meanX;
    long double varY = sumYY / sumWeight - meanY * meanY;
    long double covXY = sumXY / sumWeight - meanX * meanY;
    long double diff = varX - varY, cost = (varX + varY - sqrtl(diff * diff + 4.0L * covXY * covXY)) / 2.0L;
    if (cost < 0) cost = 0;
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, caseId = 0;
    while (cin >> n >> q) {
        if (n == 0 && q == 0) break;
        vector<Point> cities(n);
        long double sumWeight = n, sumX = 0, sumY = 0, sumXX = 0, sumYY = 0, sumXY = 0;
        for (int i = 0; i < n; i++) {
            long double x, y;
            cin >> x >> y;
            cities[i] = {x, y};
            sumX += x;
            sumY += y;
            sumXX += x * x;
            sumYY += y * y;
            sumXY += x * y;
        }
        cout << "Case " << ++caseId << ":\n";
        cout << fixed << setprecision(5) << calcCost(sumWeight, sumX, sumY, sumXX, sumYY, sumXY) << '\n';
        for (int i = 1; i <= q; i++) {
            int s, m;
            cin >> s >> m;
            long double extra = m - 1.0L;
            long double queryWeight = sumWeight + extra;
            long double queryX = sumX + extra * cities[s].x;
            long double queryY = sumY + extra * cities[s].y;
            long double queryXX = sumXX + extra * cities[s].x * cities[s].x;
            long double queryYY = sumYY + extra * cities[s].y * cities[s].y;
            long double queryXY = sumXY + extra * cities[s].x * cities[s].y;
            cout << i << ": " << calcCost(queryWeight, queryX, queryY, queryXX, queryYY, queryXY) << '\n';
        }
    }
    return 0;
}
