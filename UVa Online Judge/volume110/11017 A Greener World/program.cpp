// A Greener World
// UVa ID: 11017
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 1.600s
// https://blog.csdn.net/metaphysis/article/details/163173942

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int d, theta, N;
    while (cin >> d >> theta >> N) {
        if (d == 0 && theta == 0 && N == 0) break;
        vector<pair<int,int>> pts(N);
        for (int i = 0; i < N; ++i)
            cin >> pts[i].first >> pts[i].second;
        // ---- 计算面积 ----
        long long crossSum = 0;
        for (int i = 0; i < N; ++i) {
            int j = (i + 1) % N;
            crossSum += 1LL * pts[i].first * pts[j].second
                      - 1LL * pts[j].first * pts[i].second;
        }
        if (crossSum < 0) crossSum = -crossSum;
        long double pi = acosl(-1.0L);
        long double thetaRad = theta * pi / 180.0L;
        long double sinTheta = sinl(thetaRad);
        long double area = (long double)crossSum * d * d * sinTheta / 2.0L;
        long long areaRounded = (long long)(area + 0.5L);
        // ---- 计算新树数量 ----
        int yMin = pts[0].second, yMax = pts[0].second;
        for (auto &p : pts) {
            if (p.second < yMin) yMin = p.second;
            if (p.second > yMax) yMax = p.second;
        }
        long long YStart = 2LL * yMin - 1;
        long long YEnd   = 2LL * yMax + 1;
        if (YStart % 2 == 0) ++YStart;
        if (YEnd   % 2 == 0) --YEnd;
        long long newTrees = 0;
        vector<long double> xs;
        xs.reserve(N);
        for (long long Y = YStart; Y <= YEnd; Y += 2) {
            xs.clear();
            for (int i = 0; i < N; ++i) {
                int j = (i + 1) % N;
                long long x1 = pts[i].first,  y1 = pts[i].second;
                long long x2 = pts[j].first,  y2 = pts[j].second;
                if (y1 == y2) continue;
                long long y1_2 = 2 * y1, y2_2 = 2 * y2;
                if ((Y > y1_2 && Y < y2_2) || (Y > y2_2 && Y < y1_2)) {
                    long double X = (long double)(2 * x1)
                                  + ((long double)(Y - 2 * y1) * (x2 - x1))
                                  / (long double)(y2 - y1);
                    xs.push_back(X);
                }
            }
            sort(xs.begin(), xs.end());
            for (size_t k = 0; k + 1 < xs.size(); k += 2) {
                long double L = xs[k], R = xs[k + 1];
                if (L >= R) continue;
                long long A = (long long)floorl(L) + 1;   // > L 的最小整数
                long long B = (long long)ceill(R) - 1;    // < R 的最大整数
                if (A > B) continue;
                if (A % 2 == 0) ++A;   // 调整为奇数
                if (B % 2 == 0) --B;
                if (A > B) continue;
                newTrees += (B - A) / 2 + 1;
            }
        }
        cout << newTrees << " " << areaRounded << "\n";
    }
    return 0;
}
