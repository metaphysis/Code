// The Largest Circle
// UVa ID: 12779
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

// 欧几里得算法求最大公约数，支持非负整数
long long gcd(long long a, long long b) {
    while (b) { long long t = a % b; a = b; b = t; }
    return a;
}

int main() {
    int x1, y1, x2, y2, x3, y3, x4, y4;
    while (scanf("%d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4) == 8) {
        if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 && x3 == 0 && y3 == 0 && x4 == 0 && y4 == 0) break;
        long long ux = (long long)x2 - x1, uy = (long long)y2 - y1;
        long long vx = (long long)x4 - x1, vy = (long long)y4 - y1;
        long long cross = ux * vy - uy * vx;
        if (cross < 0) cross = -cross;          // 平行四边形面积
        long long areaSq = cross * cross;       // 面积平方
        long long len1Sq = ux * ux + uy * uy;   // 第一条边平方
        long long len2Sq = vx * vx + vy * vy;   // 第二条边平方
        // 两组高的平方分别为 areaSq/len1Sq 和 areaSq/len2Sq，取较小者即分母较大者
        long long denom = max(len1Sq, len2Sq);
        long long num = areaSq;                 // 此时 min_h_sq = num / denom
        long long a = num, b = 4 * denom;       // 面积系数为 num / (4*denom)
        if (a == 0) b = 1;                      // 分子为0时，分母化为1
        else {
            long long g = gcd(a, b);
            a /= g;
            b /= g;
        }
        printf("(%lld/%lld)*pi\n", a, b);
    }
    return 0;
}
