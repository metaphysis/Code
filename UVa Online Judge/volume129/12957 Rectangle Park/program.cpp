// Rectangle Park
// UVa ID: 12957
// Verdict: Accepted
// Submission Date: 2026-06-02
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

bool cmpX(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) 
            cin >> pts[i].x >> pts[i].y;
        
        sort(pts.begin(), pts.end(), cmpX);
        
        long long ans = 0;
        const int INF = 1e9 + 5;
        
        for (int i = 0; i < N; ++i) {
            int maxVal = INF;   // 记录已扫描的、y > y_i 的点中，最小的 y 值
            int minVal = -INF;  // 记录已扫描的、y < y_i 的点中，最大的 y 值
            
            for (int j = i + 1; j < N; ++j) {
                int yI = pts[i].y, yJ = pts[j].y;
                
                if (yI != yJ) {
                    // 判断矩形内部是否无点：yJ 在 (yI, yJ) 区间内没有其他点
                    if ((yJ > yI && yJ < maxVal) || (yJ < yI && yJ > minVal))
                        ++ans;
                }
                
                // 用当前点更新极值
                if (yJ > yI) maxVal = min(maxVal, yJ);
                else if (yJ < yI) minVal = max(minVal, yJ);
                // yJ == yI 时不更新
            }
        }
        
        cout << ans << '\n';
    }
    return 0;
}
