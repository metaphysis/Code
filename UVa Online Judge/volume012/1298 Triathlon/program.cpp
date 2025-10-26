// Triathlon
// UVa ID: 1298
// Verdict: Accepted
// Submission Date: 2025-10-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;
const double SCALE = 100000.0;  // 数值放大系数，提高计算稳定性

// 二维点/向量
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;

// 有向直线
struct Line {
    Point p;      // 直线上一点
    Vector v;     // 方向向量
    double angle; // 极角
    Line() {}
    Line(Point p, Vector v) : p(p), v(v) { angle = atan2(v.y, v.x); }
    bool operator<(const Line& l) const { return angle < l.angle; }
};

// 浮点数比较
int cmp(double x) { if (fabs(x) < EPS) return 0; return x > 0 ? 1 : -1; }

// 向量运算
Vector operator+(Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator-(Vector a, Vector b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator*(Vector a, double k) { return Vector(a.x * k, a.y * k); }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

// 判断点p是否在直线L左侧
bool onLeft(Point p, Line L) { return cross(L.v, p - L.p) > 0; }

// 求两直线交点
Point getIntersection(Line a, Line b) {
    Vector u = a.p - b.p;
    double t = cross(b.v, u) / cross(a.v, b.v);
    return a.p + a.v * t;
}

// 将直线方程 Ax+By+C=0 转换为 Line 结构
Line toLine(double A, double B, double C) {
    if (fabs(A) < fabs(B)) return Line(Point(0, -C/B), Vector(B, -A));
    else return Line(Point(-C/A, 0), Vector(B, -A));
}

// 半平面交主算法
bool halfplaneIntersect(vector<Line> lines) {
    int n = lines.size();
    if (n == 0) return false;
    sort(lines.begin(), lines.end());
    vector<Line> q(n + 1);    // 双端队列
    vector<Point> inter(n + 1); // 交点数组
    int head = 0, tail = 0;
    q[tail] = lines[0];
    for (int i = 1; i < n; i++) {
        // 删除队尾无效直线
        while (head < tail && !onLeft(inter[tail - 1], lines[i])) tail--;
        // 删除队首无效直线
        while (head < tail && !onLeft(inter[head], lines[i])) head++;
        q[++tail] = lines[i];
        // 处理平行直线，保留更优者
        if (cmp(lines[i].angle - q[tail - 1].angle) == 0) {
            if (onLeft(lines[i].p, q[tail - 1])) q[--tail] = lines[i];
            else tail--;
        }
        // 计算新交点
        if (head < tail) inter[tail - 1] = getIntersection(q[tail - 1], q[tail]);
    }
    // 最后检查队列首尾
    while (head < tail && !onLeft(inter[tail - 1], q[head])) tail--;
    while (head < tail && !onLeft(inter[head], q[tail])) head++;
    return tail - head > 1;  // 交区域是否非空
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        vector<vector<double>> athletes(n, vector<double>(3));
        for (int i = 0; i < n; i++) cin >> athletes[i][0] >> athletes[i][1] >> athletes[i][2];
        for (int i = 0; i < n; i++) {
            bool canWin = true;
            vector<Line> lines;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                // 淘汰条件：当前选手在所有项目上都不优于对手
                if (athletes[i][0] <= athletes[j][0] && athletes[i][1] <= athletes[j][1] && athletes[i][2] <= athletes[j][2]) {
                    canWin = false;
                    break;
                }
                // 跳过条件：当前选手在所有项目上都优于对手
                if (athletes[i][0] >= athletes[j][0] && athletes[i][1] >= athletes[j][1] && athletes[i][2] >= athletes[j][2]) {
                    continue;
                }
                // 构造不等式：Ti < Tj 对应的半平面
                double A = SCALE / athletes[j][0] - SCALE / athletes[j][2] - SCALE / athletes[i][0] + SCALE / athletes[i][2];
                double B = SCALE / athletes[j][1] - SCALE / athletes[j][2] - SCALE / athletes[i][1] + SCALE / athletes[i][2];
                double C = SCALE / athletes[j][2] - SCALE / athletes[i][2];
                lines.push_back(toLine(A, B, C));
            }
            if (!canWin) { cout << "No\n"; continue; }
            // 添加边界约束：X>0, Y>0, X+Y<1
            lines.push_back(Line(Point(0, 0), Vector(1, 0)));   // X >= 0
            lines.push_back(Line(Point(0, 0), Vector(0, -1)));  // Y >= 0
            lines.push_back(toLine(-1, -1, 1));                 // X + Y <= 1
            cout << (halfplaneIntersect(lines) ? "Yes\n" : "No\n");
        }
    }
    return 0;
}
