// Water Tanks
// UVa ID: 1066
// Verdict: Wrong Answer
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163211486

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, cases = 1;
    const double f = 0.097;
    while (cin >> n, n) {
        // H[i]表示第i个罐子的高度，V[i]表示第i个罐子到第n个罐子的高度之和
        vector<double> H(n + 1), V(n + 2, 0.0);
        for (int i = 1; i <= n; i++) cin >> H[i];
        for (int i = n; i >= 1; i--) V[i] = H[i] + V[i + 1];
        vector<double> p(n);
        for (int i = 1; i < n; i++) cin >> p[i];
        // 第一个罐子的水面高度最终都会达到最大高度H[1]，可以确定第一根管子所在位置的压力
        double C = 1.0 + f * (H[1] - p[1]);
        // answer表示在达到平衡时所有罐子水面高度之和
        double answer = H[1];
        // 通过模拟确定各个罐子的水面高度
        // pa是第i个管子右侧被水面没过之前的空气压力
        double pa = 1.0;
        // pp是第i个管子在达到稳定平衡后的压力
        double pp = C;
        for (int i = 2; i <= n; i++) {
            // 最后一个罐子右侧没有管子，因此与其他罐子的处理不同
            if (i == n) {
                // 初始水面高度为p[i - 1]，空气压力为pa，达到平衡时左侧管子处的压力为pp
                // 令罐子中水面最终高度为x，达到平衡时罐子中空气的压强为p1，体积为v1，则有
                // pa * (V[i] - p[i - 1]) = p1 * v1
                // v1 = V[i] - x
                // p1 + f * (x - p[i - 1]) = pp
                // 整理可得
                // pa * (V[i] - p[i - 1]) / (V[i] - x) + f * (x - p[i - 1]) = pp
                // 整理可得
                // f * x^2 - (f * V[i] + f * p[i - 1] + pp) * x + (f * p[i - 1] + pp) * V[i] - pa * (V[i] - p[i - 1]) = 0
                // 利用一元二次方程的求根公式
                // a = f，b = -(f * V[i] + f * p[i - 1] + pp)，c = (f * p[i - 1] + pp) * V[i] - pa * (V[i] - p[i - 1])
                double a = f, b = -(f * V[i] + f * p[i - 1] + pp), c = (f * p[i - 1] + pp) * V[i] - pa * (V[i] - p[i - 1]);
                double x = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;
                answer += x;
                continue;
            }
            // 以两个罐子的情况进行说明：
            // 水在第一个罐子的高度达到p[1]后，会通过管子流到第二个罐子中，在水面到达第一个管子的高度前，
            // 罐子2以及罐子2右侧的罐子中的空气压力均为1个大气压，当罐子2的水平达到第一个管子的高度时，
            // 水面没过第一个管子，罐子2以及之后的罐子中的空气开始一起被压缩，我们需要判断，水面是否可以
            // 达到第二根管子的高度
            // 计算水面刚好达到当前罐子右侧管子高度时的压力，检查是否存在矛盾
            double p1 = pa, v1 = V[i] - p[i - 1], v2 = V[i] - p[i];
            // 根据波义尔定律计算压强
            double p2 = p1 * v1 / v2;
            // 检查压强是否会超过罐子左侧管子的压力，如果超过，则当前罐子的水面不会达到右侧管子的高度
            // 那么水最终不会进入右侧的罐子，计算当前罐子的水面最终高度，停止模拟
            if (p2 + f * (p[i] - p[i - 1]) >= pp) {
                // 重新确定水面的高度x，满足以下约束
                // p1 * v1 = p2 * v2
                // v2 = V[i] - x
                // p2 + f * (x - p[i - 1]) = pp
                // 即
                // p1 * v1 / (V[i] - x) + f * (x - p[i - 1]) = pp
                // 整理可得
                // f * x^2 - (f * V[i] + f * p[i - 1] + pp) * x + (f * p[i - 1] + pp) * V[i] - p1 * v1 = 0
                // 利用一元二次方程的求根公式
                // a = f，b = -(f * V[i] + f * p[i - 1] + pp)，c = (f * p[i - 1] + pp) * V[i] - p1 * v1
                double a = f, b = -(f * V[i] + f * p[i - 1] + pp), c = (f * p[i - 1] + pp) * V[i] - p1 * v1;
                double x = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;
                answer += x;
                break;
            }
            // 如果压力小于或者等于罐子左侧管子的压力，那么水可以通过右侧的管子进入右侧罐子
            // 继续压缩空气，此时有一个临界点，即右侧罐子的水面也达到管子的水平，如果继续，
            // 则左侧罐子里的空气和右侧罐子里的空气将被水面隔断，分开继续压缩，我们需要
            // 计算是否能够达到这个临界点，如果不能达到这个临界点，那么左侧罐子的水平与
            // 右侧管子平齐，右侧罐子的水面低于其左侧管子的水平，需要确定右侧罐子水面的
            // 实际高度
            v2 = V[i] - 2 * p[i];
            p2 = p1 * v1 / v2;
            if (p2 + f * (p[i] - p[i - 1]) >= pp) {
                // 确定第i+1个罐子中水面的高度x，满足以下约束
                // p1 * v1 = p2 * v2;
                // v2 = V[i] - p[i] - x
                // p2 + f * (p[i] - p[i - 1]) = pp
                // 即
                // p1 * v1 / (V[i] - p[i] - x) + f * (p[i] - p[i - 1]) = pp
                // 整理可得
                // x = V[i] - p[i] - p1 * v1 / (pp - f * (p[i] - p[i - 1]))
                double x = V[i] - p[i] - p1 * v1 / (pp - f * (p[i] - p[i - 1]));
                answer += p[i]  + x;
                break;
            }
            // 水面高度能够超过右侧管子的高度，此时左侧罐子上方的空气和右侧罐子的空气分隔，
            // 各自被独立压缩，先计算左侧罐子中最终的水面高度
            // 在两部分空气被分隔之前，空气的压力为临界点时空气的压力p2，体积为H[i] - p[i]
            double p3 = p2, v3 = H[i] - p[i];
            // 令水面高度为x，满足以下约束：
            // p4 * v4 = p3 * v3
            // v4 = H[i] - x
            // p4 + f * (x - p[i - 1]) = pp
            // 即
            // p3 * v3 / (H[i] - x) + f * (x - p[i - 1]) = pp
            // 整理可得：
            // f * x^2 - (f * H[i] + f * p[i - 1] + pp) * x + (f * p[i - 1] + pp) * H[i] - p3 * v3 = 0
            // 利用一元二次方程的求根公式
            // a = f，b = -(f * H[i] + f * p[i - 1] + pp)，c = (f * p[i - 1] + pp) * H[i] - p3 * v3
            double a = f, b = -(f * H[i] + f * p[i - 1] + pp), c = (f * p[i - 1] + pp) * H[i] - p3 * v3;
            double x = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;
            answer += x;
            // 求得高度后，更新右侧管子在被水面淹没之前空气的压力以及达到平衡后管子处的压力
            pa = p2;
            pp = (p3 * v3) / (H[i] - x) + f * (x - p[i]);
        }
        cout << "Case " << cases++ << ": " << fixed << setprecision(3) << answer << "\n\n";
    }
    return 0;
}
