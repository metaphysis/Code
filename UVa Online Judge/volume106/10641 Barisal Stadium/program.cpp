// Barisal Stadium
// UVa ID: 10641
// Verdict: Accepted
// Submission Date: 2025-12-21
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f, MAXN = 32, MAXM = 1024;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
    int dot(const Point& b) const { return x * b.x + y * b.y; }
};

int n, m;
Point poly[MAXN], lights[MAXM];
int costs[MAXM];

// 判断灯是否能照亮边ab（从顶点a到b）
bool canCover(int lightIdx, int a, int b) {
    Point edge = poly[b] - poly[a];
    // 外法向量（顺时针旋转90度）
    Point normal(edge.y, -edge.x);
    // 从灯到顶点a的向量
    Point vec = lights[lightIdx] - poly[a];
    // 法向量与光线向量夹角为锐角 => 点积 > 0
    return normal.dot(vec) > 0;
}

struct Interval {
    int l, r, cost;
    bool operator<(const Interval& other) const {
        // 先按起点排序，再按终点排序
        if (l != other.l) return l < other.l;
        return r < other.r;
    }
};

// 直接生成所有可能区间
vector<Interval> getAllIntervals() {
    vector<Interval> intervals;
    for (int i = 0; i < m; i++) {
        // 找到第一个可以覆盖的顶点区间
        int left = -1, right = -1;
        for (int j = 0; j < n; j++) {
            if (canCover(i, j, (j + 1) % n)) {
                left = j;
                right = (j + 1) % n;
                break;
            }
        }
        // 因为是凸多边形，一盏灯不可能覆盖所有边，所以向左侧和右侧扩展时必定不会相遇
        // 向左侧扩展
        while (canCover(i, (left - 1 + n) % n, left)) left = (left - 1 + n) % n;
        // 向右侧扩展
        while (canCover(i, right, (right + 1) % n)) right = (right + 1) % n;
        // 调整覆盖区间
        if (left < right) intervals.push_back({left, right, costs[i]});
        else intervals.push_back({left, right + n, costs[i]});
    }
    // 按照覆盖区间的左端点优先进行排序
    sort(intervals.begin(), intervals.end());
    return intervals;
}

int solve() {
    // 获取所有灯的覆盖区间（已排序）
    vector<Interval> intervals = getAllIntervals();
    // 状态定义：dp[i][j]从顶点i开始覆盖，覆盖到顶点j之间的边的最小费用
    int dp[64][64];
    memset(dp, 0x3f, sizeof dp);
    for (int i = 0; i < n; i++) dp[i][i] = 0;
    for (auto itl : intervals) {
        int last = itl.l;
        for (int i = 0; i <= last; i++) {
            if (dp[i][last] == INF) continue;
            for (int j = itl.l + 1; j <= itl.r; j++)
                dp[i][j] = min(dp[i][j], dp[i][last] + itl.cost);
        }
    }
    // 确定最小费用，注意：覆盖区间长度必须为n
    int answer = INF;
    for (int i = 0; i < n; i++)
        for (int j = i + n; j < 2 * n; j++)
            answer = min(answer, dp[i][j]);
    return answer;
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> poly[i].x >> poly[i].y;
        cin >> m;
        for (int i = 0; i < m; i++) cin >> lights[i].x >> lights[i].y >> costs[i];
        int result = solve();
        if (result == INF) cout << "Impossible.";
        else cout << result;
        cout << '\n';
    }
    return 0;
}
