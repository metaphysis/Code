// Mushroom Misery
// UVa ID: 10613
// Verdict: Accepted
// Submission Date: 2026-04-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 线段结构体：表示某一行(y)上被覆盖的x区间[st, ed)
struct Seg {
    int st, ed, y;
};

// 全局线段数组（使用vector动态扩展）
vector<Seg> segs;

// 比较函数：先按y排序，再按左端点排序
bool cmp(const Seg& a, const Seg& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.st < b.st;
}

// 添加一条线段（如果有效）
inline void addSeg(int st, int ed, int y) {
    if (st < ed) segs.push_back({st, ed, y});
}

// 将圆切割成水平线段
void cutToSegments(double cx, double cy, double r, int sz) {
    int y0 = (int)floor(cy);                     // 圆心所在的行索引
    int yMin = max(0, (int)floor(cy - r));       // 影响的最小行
    int yMax = min(sz, (int)ceil(cy + r));       // 影响的最大行（注意sz是网格边界）

    // 处理圆心下方的行（y < y0）
    for (int y = yMin; y < y0; ++y) {
        double dy = cy - (y + 1);                // 圆心到格子上边界的垂直距离
        double dx = sqrt(r * r - dy * dy);       // 半宽
        int st = max(0, (int)floor(cx - dx));
        int ed = min(sz, (int)ceil(cx + dx));
        addSeg(st, ed, y);
    }

    // 处理圆心所在的行
    int st = max(0, (int)floor(cx - r));
    int ed = min(sz, (int)ceil(cx + r));
    addSeg(st, ed, y0);

    // 处理圆心上方的行（y > y0）
    for (int y = y0 + 1; y < yMax; ++y) {
        double dy = y - cy;                      // 圆心到格子下边界的垂直距离
        double dx = sqrt(r * r - dy * dy);
        int st = max(0, (int)floor(cx - dx));
        int ed = min(sz, (int)ceil(cx + dx));
        addSeg(st, ed, y);
    }
}

int main() {
    int t, sz, n;
    scanf("%d", &t);                             // 测试用例数
    while (t--) {
        segs.clear();                            // 清空全局线段数组
        scanf("%d%d", &sz, &n);                  // 读取网格大小和蘑菇数量

        // 处理每个蘑菇
        for (int i = 0; i < n; ++i) {
            double x, y, r;
            scanf("%lf%lf%lf", &x, &y, &r);
            cutToSegments(x, y, r, sz);
        }

        // 按行排序
        sort(segs.begin(), segs.end(), cmp);

        long long ans = 0;
        // 按行分组，合并区间
        for (size_t i = 0, j = 0; i <= segs.size(); ++i) {
            // 当行号变化或到达末尾时，处理当前组
            if (i == segs.size() || segs[i].y != segs[j].y) {
                int L = segs[j].st, R = segs[j].ed;
                // 合并同一行内的所有区间
                for (size_t k = j + 1; k < i; ++k) {
                    if (segs[k].st <= R) {
                        R = max(R, segs[k].ed);
                    } else {
                        ans += R - L;
                        L = segs[k].st;
                        R = segs[k].ed;
                    }
                }
                ans += R - L;                    // 加上最后一个区间
                j = i;                           // 移动到下一组
            }
        }

        printf("%lld\n", ans);                   // 输出结果
    }
    return 0;
}
