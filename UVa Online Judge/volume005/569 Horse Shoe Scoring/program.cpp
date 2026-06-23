// Horse Shoe Scoring
// UVa ID: 569
// Verdict: Accepted
// Submission Date: 2026-05-16
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double R = 10.0;   // 马蹄铁半径

// 计算单次投掷得分
int scoreOneToss(double ax, double ay, double bx, double by) {
    // 坐标变换：将B点平移到A点
    bx -= ax;
    by -= ay;
    // 计算桩心在局部坐标系中的坐标 (px, py)
    double px = -(by * ax - bx * ay) / R;
    double py = -(bx * ax + by * ay) / R;
    // 垂直距离取正值（对称性）
    if (px < 0) px = -px;
    int score = 0;
    // 桩心在半圆开口侧
    if (py >= 0) {
        double d = px * px + py * py;   // 桩心到A距离的平方
        // 套中：距离平方 < (R-1)^2 = 81
        if (d < pow(R - 1, 2)) score += 5;
        // 触碰到：距离平方 < (R+1)^2 = 121
        else if (d < pow(R + 1, 2)) score += 2;
        // 摆荡：检查旋转后能否碰到
        else {
            d = px * px + (py - R) * (py - R);
            if (d <= pow(R * sqrt(2) + 1, 2)) {
                score += 1;
            }
        }
    } else { // 桩心在半圆背侧
        // 检查直径端点是否碰到桩子
        double d = (px - R) * (px - R) + py * py;
        if (d < 1) score += 2;
        // 摆荡
        else {
            d = px * px + (py - R) * (py - R);
            if (d <= pow(R * sqrt(2) + 1, 2)) {
                score += 1;
            }
        }
    }
    return score;
}

int main() {
    double ax, ay, bx, by;
    vector<int> scores;   // 存储每次投掷得分
    // 读取所有投掷
    while (cin >> ax >> ay >> bx >> by) scores.push_back(scoreOneToss(ax, ay, bx, by));
    // 输出表头
    cout << "Turn Score" << endl;
    // 每4次投掷为一个回合
    for (int i = 0; i < (int)scores.size(); i += 4) {
        int turnScore = scores[i] + scores[i + 1] + scores[i + 2] + scores[i + 3];
        // 格式：回合号占4列，得分占6列（自动右对齐）
        printf("%4d%6d\n", i / 4 + 1, turnScore);
    }
    return 0;
}
