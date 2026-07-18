// Jacquard Circuits
// UVa ID: 1059
// Verdict: Accepted
// Submission Date: 2026-07-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long gcdll(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) { long long t = a % b; a = b; b = t; }
    return a;
}

void printInt128(__int128 v) {
    if (v == 0) { cout << 0; return; }
    if (v < 0) { cout << '-'; v = -v; }
    string s;
    while (v > 0) { s.push_back('0' + v % 10); v /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNo = 0;
    int N, M;
    while (cin >> N >> M && (N || M)) {
        ++caseNo;
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;
        // 删除共线中间点
        while (true) {
            bool removed = false;
            int n = (int)pts.size();
            for (int i = 0; i < n; ++i) {
                int prev = (i - 1 + n) % n;
                int next = (i + 1) % n;
                long long cross = (pts[i].x - pts[prev].x) * (pts[next].y - pts[i].y)
                                - (pts[i].y - pts[prev].y) * (pts[next].x - pts[i].x);
                if (cross == 0) {
                    pts.erase(pts.begin() + i);
                    removed = true;
                    break;
                }
            }
            if (!removed) break;
        }
        int n = (int)pts.size();
        long long g = 0;
        long long SA = 0;
        long long B = 0;
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            long long dx = pts[j].x - pts[i].x;
            long long dy = pts[j].y - pts[i].y;
            g = gcdll(g, dx);
            g = gcdll(g, dy);
            SA += pts[i].x * pts[j].y - pts[i].y * pts[j].x;
            B += gcdll(dx, dy);
        }
        if (SA < 0) SA = -SA;
        long long a = SA / (g * g);
        long long b = B / g;
        long long sumK = (long long)M * (M + 1) / 2;
        long long sumK2 = (long long)M * (M + 1) * (2LL * M + 1) / 6;
        __int128 numerator = (__int128)a * sumK2 - (__int128)b * sumK + (__int128)2 * M;
        __int128 ans = numerator / 2;
        cout << "Case " << caseNo << ": ";
        printInt128(ans);
        cout << '\n';
    }
    return 0;
}
