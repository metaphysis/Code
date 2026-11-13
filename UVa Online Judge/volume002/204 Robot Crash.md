[UVa 204 Robot Crash](https://blog.csdn.net/metaphysis/article/details/152732870)

## 题目理解

本题要求判断两个机器人是否会在水平条带区域内发生碰撞。两个机器人从条带两端同时发射，在遇到墙壁时会按照反射定律反弹。我们需要找到它们是否会在同一位置、同一时间（时间差不超过 $0.5$ 秒）相遇。

## 关键点分析

1. **坐标系与运动范围**：条带高度为 $10$ 单位（$0 ≤ y ≤ 10$），机器人从左右两端发射
2. **角度限制**：
   - 左枪角度：$-85°$ 到 $85°$（相对于正x轴逆时针）
   - 右枪角度：$95°$ 到 $180°$ 或 $-95°$ 到 $-180°$
3. **碰撞条件**：在同一位置且时间差不超过 $0.5$ 秒
4. **墙壁反射**：入射角等于反射角，速度大小不变

## 解题思路

### 核心算法

1. **坐标变换与镜像处理**：
   - 将右枪机器人的运动镜像到左枪坐标系中考虑
   - 通过交换坐标和速度方向来统一处理

2. **路径构建**：
   - 根据初始位置、速度和运动时间构建机器人的运动轨迹
   - 考虑墙壁反射，将轨迹分段处理

3. **碰撞检测**：
   - 计算两机器人可能相遇的时间窗口
   - 检查在这段时间内它们的轨迹段是否有交点
   - 考虑时间差不超过 $0.5$ 秒的限制

4. **边界处理**：
   - 使用镜像法处理y坐标超出 $[0,10]$ 范围的情况
   - 确保轨迹计算在有效范围内

## 算法复杂度

- 时间复杂度：$O(k)$，其中k是轨迹段的数量
- 空间复杂度：$O(k)$，用于存储轨迹段

## 参考代码

```cpp
// Robot Crash
// UVa ID: 204
// Verdict: Accepted
// Submission Date: 2025-10-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);                    // 圆周率
const double DEG_TO_RAD = PI / 180.0;            // 角度转弧度系数
const double EPS = 1e-7;                         // 浮点数比较精度
const int LENGTH = (1 << 20);                    // 输入缓冲区大小

// 快速读取下一个字符
inline int nextChar() {
    static char buffer[LENGTH], *p = buffer, *end = buffer;
    if (p == end) {
        if ((end = buffer + fread(buffer, 1, LENGTH, stdin)) == buffer) return EOF;
        p = buffer;
    }
    return *p++;
}

// 快速读取双精度浮点数
inline double readDouble() {
    int ch, sign = 1;
    double value = 0, decimal = 0, div = 1;
    while (isspace(ch = nextChar()));
    if (ch == '-') {
        sign = -1;
        ch = nextChar();
    } else if (ch == '+') {
        ch = nextChar();
    }
    while (isdigit(ch)) {
        value = value * 10 + (ch - '0');
        ch = nextChar();
    }
    if (ch == '.') {
        ch = nextChar();
        while (isdigit(ch)) {
            decimal = decimal * 10 + (ch - '0');
            div *= 10;
            ch = nextChar();
        }
    }
    return sign * (value + decimal / div);
}

// 浮点数相等比较
inline bool eq(double a, double b) { return fabs(a - b) < EPS; }
// 浮点数小于等于比较
inline bool le(double a, double b) { return a < b + EPS; }
// 浮点数大于等于比较
inline bool ge(double a, double b) { return a + EPS > b; }

// 点结构体
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    // 点比较：先按x坐标，再按y坐标
    bool operator<(const Point& p) const {
        return eq(x, p.x) ? (y < p.y) : (x < p.x);
    }
};

// 向量结构体
struct Vector {
    double x, y;
    Vector(double x = 0, double y = 0) : x(x), y(y) {}
};

// 线段结构体
struct Segment {
    Point start, end;
    Segment() : start(Point(0,0)), end(Point(0,0)) {}
    Segment(Point s, Point e) : start(s), end(e) {}
};

// 直线结构体：ax + by + c = 0
struct Line {
    double a, b, c;
    Line(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {}
    // 通过两点构造直线
    Line(Point p1, Point p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = -a * p1.x - b * p1.y;
    }
    // 判断点是否在直线上
    bool contains(Point p) const {
        return eq(a * p.x + b * p.y + c, 0);
    }
};

// 检查两个区间是否重叠
inline bool intervalsOverlap(double a1, double a2, double b1, double b2) {
    if (a1 > a2) swap(a1, a2);
    if (b1 > b2) swap(b1, b2);
    return le(max(a1, b1), min(a2, b2));
}

// 判断两线段是否相交，如果相交则返回交点
bool segmentsIntersect(const Segment& s1, const Segment& s2, Segment* result) {
    // 检查包围盒是否重叠
    if (!intervalsOverlap(s1.start.x, s1.end.x, s2.start.x, s2.end.x) ||
        !intervalsOverlap(s1.start.y, s1.end.y, s2.start.y, s2.end.y)) {
        return false;
    }
    
    Line line1(s1.start, s1.end);
    Line line2(s2.start, s2.end);
    double det = line1.a * line2.b - line2.a * line1.b;
    
    // 处理平行或共线情况
    if (eq(det, 0)) {
        if (!line1.contains(s2.start) || !line2.contains(s1.start)) return false;
        Point p1 = s1.start, p2 = s1.end;
        Point q1 = s2.start, q2 = s2.end;
        if (p2 < p1) swap(p1, p2);
        if (q2 < q1) swap(q1, q2);
        result->start = max(p1, q1);
        result->end = min(p2, q2);
        return true;
    }
    
    // 计算交点坐标
    double x = (line2.c * line1.b - line1.c * line2.b) / det;
    double y = (line2.a * line1.c - line1.a * line2.c) / det;
    result->start = Point(x, y);
    result->end = Point(x, y);
    
    // 检查交点是否在线段范围内
    return le(min(s1.start.x, s1.end.x), x) && le(x, max(s1.start.x, s1.end.x)) &&
           le(min(s1.start.y, s1.end.y), y) && le(y, max(s1.start.y, s1.end.y)) &&
           le(min(s2.start.x, s2.end.x), x) && le(x, max(s2.start.x, s2.end.x)) &&
           le(min(s2.start.y, s2.end.y), y) && le(y, max(s2.start.y, s2.end.y));
}

// 调整点坐标到边界范围内，并相应调整速度向量
void adjustToBounds(Point& p, Vector& v) {
    if (p.y > 10) {
        double cycles = floor(p.y * 0.05 + EPS);
        p.y -= cycles * 20;
        if (p.y > 10) {
            p.y = 20 - p.y;
            v.y = -v.y;
        }
    } else if (p.y < 0) {
        double cycles = floor(-p.y * 0.05 + EPS);
        p.y += cycles * 20;
        if (p.y < -10) {
            p.y += 20;
        } else {
            p.y = -p.y;
            v.y = -v.y;
        }
    }
}

// 构建机器人在给定时间范围内的运动路径（考虑墙壁反射）
vector<Segment> buildPath(Point pos, Vector vel, double startTime, double endTime) {
    vector<Segment> path;
    // 调整起始位置
    pos.x += vel.x * startTime;
    pos.y += vel.y * startTime;
    adjustToBounds(pos, vel);
    
    double time = startTime;
    while (true) {
        double nextTime = endTime;
        // 计算下一次碰到墙壁的时间
        if (!eq(vel.y, 0)) {
            if (vel.y > 0) {
                nextTime = time + (10 - pos.y) / vel.y;
            } else {
                nextTime = time - pos.y / vel.y;
            }
            if (nextTime > endTime) nextTime = endTime;
        }
        
        // 计算下一位置
        Point nextPos(pos.x + vel.x * (nextTime - time), pos.y + vel.y * (nextTime - time));
        path.push_back(Segment(pos, nextPos));
        
        // 更新位置和时间
        pos = nextPos;
        time = nextTime;
        vel.y = -vel.y;  // 碰到墙壁，y方向速度反向
        
        if (ge(time, endTime)) break;
    }
    return path;
}

// 检查特定情况下的碰撞
bool checkCollisionCase(const Point& p1, const Vector& v1, const Point& p2,
                       const Vector& v2, bool flipped, double* bestTime, Point* collisionPoint) {
    double dist = p2.x - p1.x;
    if (eq(dist, 0)) {
        // 特殊情况：初始x坐标相同
        if (eq(p2.y, p1.y) && !flipped) {
            *bestTime = 0;
            *collisionPoint = p1;
            return true;
        }
        return false;
    }
    if (dist < 0) return false;
    
    // 计算相遇时间
    double meetTime = dist / (v1.x - v2.x);
    double rightMaxTime = meetTime + v1.x / (v1.x - v2.x) * 0.5;
    if (rightMaxTime > *bestTime) {
        rightMaxTime = *bestTime;
        if (!ge(rightMaxTime, meetTime)) return false;
    }
    
    double leftMinTime = max(0.0, meetTime + v2.x / (v1.x - v2.x) * 0.5);
    
    // 构建两机器人的运动路径
    vector<Segment> rightPath = buildPath(p2, v2, meetTime, rightMaxTime);
    vector<Segment> leftPath = buildPath(p1, v1, leftMinTime, meetTime);
    reverse(leftPath.begin(), leftPath.end());
    
    Segment intersection(Point(0,0), Point(0,0));
    bool found = false;
    
    // 检查路径段是否有交点
    for (const auto& seg2 : rightPath) {
        for (const auto& seg1 : leftPath) {
            if (segmentsIntersect(seg1, seg2, &intersection)) {
                found = true;
                break;
            }
        }
        if (found) break;
    }
    
    if (!found) return false;
    
    // 计算碰撞时间和位置
    double collisionTime = (intersection.end.x - p2.x) / v2.x;
    double x = flipped ? (p1.x + p2.x - intersection.end.x) : intersection.end.x;
    
    // 更新最佳碰撞点
    if (eq(*bestTime, collisionTime)) {
        if (x < collisionPoint->x) {
            collisionPoint->x = x;
            collisionPoint->y = intersection.end.y;
        }
    } else {
        *bestTime = collisionTime;
        collisionPoint->x = x;
        collisionPoint->y = intersection.end.y;
    }
    return true;
}

// 主碰撞检测函数
bool checkCollision(Point p1, Vector v1, Point p2, Vector v2, Point* result) {
    double bestTime = numeric_limits<double>::max();
    bool found = checkCollisionCase(p1, v1, p2, v2, false, &bestTime, result);
    
    // 交换位置和速度，检查镜像情况
    swap(p1.y, p2.y); swap(v1, v2);
    v1.x = -v1.x; v2.x = -v2.x;
    found |= checkCollisionCase(p1, v1, p2, v2, true, &bestTime, result);
    
    return found;
}

int main(int argc, char* argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int caseNum = 0;
    Point robot1, robot2, collisionPoint;
    double angle1, angle2, speed1, speed2;
    
    // 读取输入直到文件结束
    while (true) {
        robot1.x = readDouble(); robot1.y = readDouble();
        angle1 = readDouble(); speed1 = readDouble();
        robot2.x = readDouble(); robot2.y = readDouble();
        angle2 = readDouble(); speed2 = readDouble();
        
        // 检查结束条件
        if (robot1.x == 0 && robot1.y == 0 && angle1 == 0 && speed1 == 0 &&
            robot2.x == 0 && robot2.y == 0 && angle2 == 0 && speed2 == 0) break;
        
        // 角度转弧度
        angle1 *= DEG_TO_RAD;
        angle2 *= DEG_TO_RAD;
        
        // 计算速度向量
        Vector vel1(speed1 * cos(angle1), speed1 * sin(angle1));
        Vector vel2(speed2 * cos(angle2), speed2 * sin(angle2));
        
        // 检查碰撞并输出结果
        if (checkCollision(robot1, vel1, robot2, vel2, &collisionPoint)) {
            printf("Robot Problem #%d: Robots collide at (%.2lf,%.2lf)\n\n",
                   ++caseNum, collisionPoint.x + EPS, collisionPoint.y + EPS);
        } else {
            printf("Robot Problem #%d: Robots do not collide.\n\n", ++caseNum);
        }
    }
    return 0;
}
```

## 代码要点说明

1. **快速输入**：使用自定义的`readDouble()`函数提高输入效率
2. **精度处理**：使用EPS处理浮点数比较，避免精度误差
3. **路径构建**：`buildPath()`函数考虑墙壁反射，将连续运动分解为多个线段
4. **碰撞检测**：通过检查轨迹段相交来判断碰撞，考虑时间窗口限制
5. **镜像处理**：交换坐标和速度方向来处理对称情况

这个解法通过几何计算和路径分析，高效地解决了机器人碰撞检测问题。
