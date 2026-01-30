// Brownie Points II
// UVa ID: 10869
// Verdict: Accepted
// Submission Date: 2026-01-20
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, sameX, sameY, stan, minStanX; // sameX: 同一x坐标点数, sameY: 同一y坐标点数, stan: 斯坦得分, minStanX: 该x坐标上斯坦得分的最小值
};

int main() {
    int n;
    while (scanf("%d", &n) && n) {
        vector<Point> p(n);
        vector<int> ys(n);
        
        // 读取输入
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &p[i].x, &p[i].y);
            ys[i] = p[i].y;
        }
        
        // 离散化y坐标
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        int m = ys.size();
        auto yid = [&](int y) { return lower_bound(ys.begin(), ys.end(), y) - ys.begin(); };
        
        // 计算sameX: 同一x坐标的点数
        sort(p.begin(), p.end(), [](const Point& a, const Point& b) { 
            return a.x < b.x || (a.x == b.x && a.y < b.y); 
        });
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && p[j].x == p[i].x) ++j;
            int cnt = j - i;
            for (int k = i; k < j; ++k) p[k].sameX = cnt;
            i = j;
        }
        
        // 计算sameY: 同一y坐标的点数
        sort(p.begin(), p.end(), [](const Point& a, const Point& b) { 
            return a.y < b.y || (a.y == b.y && a.x < b.x); 
        });
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && p[j].y == p[i].y) ++j;
            int cnt = j - i;
            for (int k = i; k < j; ++k) p[k].sameY = cnt;
            i = j;
        }
        
        // 树状数组操作
        vector<int> bit(m + 2, 0);
        auto add = [&](int idx, int v) { 
            for (++idx; idx <= m; idx += idx & -idx) bit[idx] += v; 
        };
        auto sum = [&](int idx) { 
            int s = 0; 
            for (++idx; idx > 0; idx -= idx & -idx) s += bit[idx]; 
            return s; 
        };
        auto query = [&](int l, int r) { 
            return l > r ? 0 : sum(r) - sum(l - 1); 
        };
        
        // 第一次扫描: 计算右侧且y>当前y的点数（右上象限）
        sort(p.begin(), p.end(), [](const Point& a, const Point& b) { 
            return a.x < b.x || (a.x == b.x && a.y > b.y); 
        });
        // 初始所有点都在右侧
        for (auto& pt : p) add(yid(pt.y), 1);
        for (auto& pt : p) {
            int idx = yid(pt.y);
            add(idx, -1); // 将当前点从右侧移除
            pt.stan = query(idx + 1, m - 1); // 右侧且y>当前y的点数
        }
        
        // 第二次扫描: 计算左侧且y<当前y的点数（左下象限）
        sort(p.begin(), p.end(), [](const Point& a, const Point& b) { 
            return a.x > b.x || (a.x == b.x && a.y < b.y); 
        });
        fill(bit.begin(), bit.end(), 0);
        // 初始所有点都在左侧
        for (auto& pt : p) add(yid(pt.y), 1);
        for (auto& pt : p) {
            int idx = yid(pt.y);
            add(idx, -1); // 将当前点从左侧移除
            pt.stan += query(0, idx - 1); // 左侧且y<当前y的点数
        }
        
        // 计算每个x坐标上斯坦得分的最小值
        sort(p.begin(), p.end(), [](const Point& a, const Point& b) { 
            return a.x < b.x || (a.x == b.x && a.y < b.y); 
        });
        for (int i = 0; i < n; ) {
            int j = i, mn = INT_MAX;
            while (j < n && p[j].x == p[i].x) {
                mn = min(mn, p[j].stan);
                ++j;
            }
            for (int k = i; k < j; ++k) p[k].minStanX = mn;
            i = j;
        }
        
        // 找出斯坦的最大保证得分
        int maxStan = 0;
        for (auto& pt : p) {
            if (pt.stan == pt.minStanX) {
                maxStan = max(maxStan, pt.stan);
            }
        }
        
        // 收集奥利可能得分
        set<int> ollie;
        for (auto& pt : p) {
            if (pt.stan == pt.minStanX && pt.stan == maxStan) {
                // ollie = n - stan - sameX - sameY + 1
                ollie.insert(n - pt.stan - pt.sameX - pt.sameY + 1);
            }
        }
        
        // 输出结果
        printf("Stan: %d; Ollie:", maxStan);
        for (int s : ollie) printf(" %d", s);
        printf(";\n");
    }
    return 0;
}
