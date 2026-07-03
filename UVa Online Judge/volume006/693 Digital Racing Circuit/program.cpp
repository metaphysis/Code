// Digital Racing Circuit
// UVa ID: 693
// Verdict: Accepted
// Submission Date: 2026-07-03
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x_, double y_) : x(x_), y(y_) {}
};

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

bool onSegment(const Point &p, const Point &a, const Point &b) {
    if (fabs(cross({a.x - p.x, a.y - p.y}, {b.x - p.x, b.y - p.y})) > EPS) return false;
    return p.x >= min(a.x, b.x) - EPS && p.x <= max(a.x, b.x) + EPS &&
           p.y >= min(a.y, b.y) - EPS && p.y <= max(a.y, b.y) + EPS;
}

// 判断线段 AB 与 CD 是否相交，若相交则返回 AB 上的参数 t (0<=t<=1)
bool lineIntersect(const Point &A, const Point &B, const Point &C, const Point &D, double &t) {
    Point AB = {B.x - A.x, B.y - A.y};
    Point CD = {D.x - C.x, D.y - C.y};
    Point AC = {C.x - A.x, C.y - A.y};
    double denom = cross(AB, CD);
    if (fabs(denom) < EPS) {
        // 平行或共线
        if (fabs(cross(AB, AC)) < EPS) {
            // 共线，投影到 AB 方向
            double len2 = dot(AB, AB);
            if (len2 < EPS) return false;
            double tC = dot(AC, AB) / len2;
            Point AD = {D.x - A.x, D.y - A.y};
            double tD = dot(AD, AB) / len2;
            double low = max(0.0, min(tC, tD));
            double high = min(1.0, max(tC, tD));
            if (low <= high + EPS) {
                t = low;
                return true;
            }
            return false;
        }
        return false;
    }
    double tNum = cross(AC, CD);
    double uNum = cross(AC, AB);
    t = tNum / denom;
    double u = uNum / denom;
    if (t >= -EPS && t <= 1 + EPS && u >= -EPS && u <= 1 + EPS) {
        t = max(0.0, min(1.0, t));
        return true;
    }
    return false;
}

// 计算线段 P0->P1 与水平终点线（y=goalY, x∈[goalX1,goalX2]）的首次交点参数 t (0<t<=1)
bool getGoalIntersection(const Point &P0, const Point &P1, double goalY, double goalX1, double goalX2, double &t) {
    if (fabs(P0.y - goalY) < EPS && fabs(P1.y - goalY) < EPS) {
        // 水平共线
        double dx = P1.x - P0.x;
        if (fabs(dx) < EPS) return false; // 无移动
        double t1 = (goalX1 - P0.x) / dx;
        double t2 = (goalX2 - P0.x) / dx;
        double low = max(0.0, min(t1, t2));
        double high = min(1.0, max(t1, t2));
        if (low <= high + EPS) {
            if (low > EPS) { t = low; return true; }
            return false; // t=0 不视为离开后的到达
        }
        return false;
    }
    double dy = P1.y - P0.y;
    if (fabs(dy) < EPS) return false;
    double tc = (goalY - P0.y) / dy;
    if (tc > EPS && tc <= 1.0 + EPS) {
        double x = P0.x + tc * (P1.x - P0.x);
        if (x >= goalX1 - EPS && x <= goalX2 + EPS) {
            t = max(0.0, min(1.0, tc));
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int numCourses;
    cin >> numCourses;
    for (int courseIdx = 0; courseIdx < numCourses; ++courseIdx) {
        // 读取内墙
        vector<Point> inner, outer;
        int x, y;
        while (cin >> x) {
            if (x == 99999) break;
            cin >> y;
            inner.push_back(Point((double)x, (double)y));
        }
        // 读取外墙
        while (cin >> x) {
            if (x == 99999) break;
            cin >> y;
            outer.push_back(Point((double)x, (double)y));
        }
        // 构建墙线段（内墙+外墙，均闭合）
        vector<pair<Point, Point>> wallSegs;
        auto addWall = [&](const vector<Point> &w) {
            int n = (int)w.size();
            for (int i = 0; i < n; ++i) {
                int j = (i + 1) % n;
                wallSegs.push_back({w[i], w[j]});
            }
        };
        addWall(inner);
        addWall(outer);
        // 终点线信息
        Point pi = inner[0], po = outer[0];
        double goalY = pi.y;
        double goalX1 = min(pi.x, po.x);
        double goalX2 = max(pi.x, po.x);
        Point ref = inner[0]; // 用于计算环绕数的参考点
        // 处理驾驶记录
        bool firstRecord = true;
        while (true) {
            int sx;
            if (!(cin >> sx)) break;
            if (sx == 99999) break; // 空记录
            int sy;
            double lapTime;
            cin >> sy >> lapTime;
            // 读取加速度列表
            vector<pair<int, int>> accel;
            while (cin >> x) {
                if (x == 99999) break;
                cin >> y;
                accel.push_back({x, y});
            }
            bool ok = true;
            // 1. 检查起点是否在起点线上
            if (!(sy == goalY && sx >= goalX1 - EPS && sx <= goalX2 + EPS)) ok = false;
            // 2. 检查起点是否在墙线段上
            if (ok) {
                Point sp((double)sx, (double)sy);
                for (auto &seg : wallSegs) {
                    if (onSegment(sp, seg.first, seg.second)) {
                        ok = false;
                        break;
                    }
                }
            }
            // 3. 检查加速度分量
            if (ok) {
                for (auto &a : accel) {
                    if (a.first < -1 || a.first > 1 || a.second < -1 || a.second > 1) {
                        ok = false;
                        break;
                    }
                }
            }
            // 4. 模拟
            if (ok) {
                Point pos((double)sx, (double)sy);
                Point vel(0.0, 0.0);
                double totalAngle = 0.0;
                bool reached = false;
                int L = (int)accel.size();
                int i;
                for (i = 0; i < L; ++i) {
                    // 更新速度
                    vel.x += accel[i].first;
                    vel.y += accel[i].second;
                    Point P1 = {pos.x + vel.x, pos.y + vel.y};
                    // 计算与终点线的交点参数
                    double tArrive = -1.0;
                    bool hasArrive = getGoalIntersection(pos, P1, goalY, goalX1, goalX2, tArrive);
                    double tCheck = hasArrive ? tArrive : 1.0;
                    // 碰撞检测（只检测到 tCheck 为止）
                    bool crashed = false;
                    for (auto &seg : wallSegs) {
                        double t;
                        if (lineIntersect(pos, P1, seg.first, seg.second, t)) {
                            if (t <= tCheck + EPS) {
                                crashed = true;
                                break;
                            }
                        }
                    }
                    if (crashed) { ok = false; break; }
                    // 累加相对于参考点的角度变化（轨迹段）
                    Point PEnd = {pos.x + vel.x * tCheck, pos.y + vel.y * tCheck};
                    double th0 = atan2(pos.y - ref.y, pos.x - ref.x);
                    double th1 = atan2(PEnd.y - ref.y, PEnd.x - ref.x);
                    double dth = th1 - th0;
                    while (dth > PI) dth -= 2 * PI;
                    while (dth < -PI) dth += 2 * PI;
                    totalAngle += dth;
                    if (hasArrive) {
                        // 到达终点
                        double actualTime = i + tArrive;
                        // 加速度数量必须正好用完
                        if (L != i + 1) ok = false;
                        // 时间误差
                        if (ok && fabs(actualTime - lapTime) > 0.01 + 1e-9) ok = false;
                        // 环绕数检查（顺时针为 -2π）
                        if (ok) {
                            if (fabs(totalAngle + 2 * PI) < 1e-5) {
                                // 顺时针，OK
                            } else if (fabs(totalAngle - 2 * PI) < 1e-5) {
                                ok = false; // 逆时针
                            } else {
                                ok = false;
                            }
                        }
                        reached = true;
                        break;
                    }
                    // 未到达，更新位置
                    pos = P1;
                }
                if (!reached) ok = false;
            }
            cout << (ok ? "OK" : "NG") << "\n";
        }
        if (courseIdx != numCourses - 1) cout << "\n";
    }
    return 0;
}
