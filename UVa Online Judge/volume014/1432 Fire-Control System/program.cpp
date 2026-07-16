// Fire-Control System
// UVa ID: 1432
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.200s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
struct Point {
    double ang;
    int d2;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    int caseNo = 0;
    while (cin >> N >> K) {
        if (N == 0 && K == 0) break;
        ++caseNo;
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            double a = atan2(y, x);
            if (a < 0) a += 2 * PI;
            pts[i].ang = a;
            pts[i].d2 = x * x + y * y;
        }
        if (K == 0) {
            cout << "Case #" << caseNo << ": ";
            cout << fixed << setprecision(2) << 0.00 << "\n";
            continue;
        }
        vector<int> idxAng(N);
        iota(idxAng.begin(), idxAng.end(), 0);
        sort(idxAng.begin(), idxAng.end(), [&](int a, int b) {
            return pts[a].ang < pts[b].ang;
        });
        vector<int> idxDist(N);
        iota(idxDist.begin(), idxDist.end(), 0);
        sort(idxDist.begin(), idxDist.end(), [&](int a, int b) {
            return pts[a].d2 < pts[b].d2;
        });
        double ans = 1e100;
        for (int i = 0; i < N; ++i) {
            int rIdx = idxDist[i];
            int R2 = pts[rIdx].d2;
            if (i > 0 && pts[idxDist[i - 1]].d2 == R2) continue;
            vector<double> angs;
            angs.reserve(N);
            for (int j = 0; j < N; ++j) {
                int pIdx = idxAng[j];
                if (pts[pIdx].d2 <= R2)
                    angs.push_back(pts[pIdx].ang);
            }
            int M = (int)angs.size();
            if (M < K) continue;
            vector<double> ext(2 * M);
            for (int j = 0; j < M; ++j) {
                ext[j] = angs[j];
                ext[j + M] = angs[j] + 2 * PI;
            }
            int left = 0, right = 0, cnt = 0;
            while (right < 2 * M) {
                while (right < 2 * M && cnt < K) {
                    ++cnt;
                    ++right;
                }
                if (cnt < K) break;
                while (cnt >= K) {
                    double width = ext[right - 1] - ext[left];
                    double area = (width / 2.0) * R2;
                    if (area < ans) ans = area;
                    --cnt;
                    ++left;
                }
            }
        }
        cout << "Case #" << caseNo << ": ";
        cout << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
