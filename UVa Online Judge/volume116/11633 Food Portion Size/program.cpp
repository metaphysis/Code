// Food Portion Size
// UVa ID: 11633
// Verdict: Accepted
// Submission Date: 2026-01-09
// UVa Run Time: 0.870s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Fraction {
    long long num, den; // 分子、分母
    Fraction(long long n = 0, long long d = 1) {
        long long g = __gcd(n, d);
        num = n / g;
        den = d / g;
        if (den < 0) num = -num, den = -den; // 保证分母为正
    }
    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }
};

int main() {
    int n;
    while (cin >> n, n) {
        int a, b;
        cin >> a >> b;
        vector<int> food(n);
        for (int i = 0; i < n; ++i) cin >> food[i];

        // 存储所有可能的分量值 S 的候选
        set<Fraction> candidates;

        // 对于每个学生，将其食量 y_i 的 1/1、1/2、1/3 作为 S 的可能取值
        for (int yi : food) {
            candidates.insert(Fraction(yi, 1));
            candidates.insert(Fraction(yi, 2));
            candidates.insert(Fraction(yi, 3));
        }

        // 对于每两个学生的食量，计算它们和的一半（即可能的最优 S 在中间的情况）
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                candidates.insert(Fraction(food[i] + food[j], 2));

        Fraction bestCost(LLONG_MAX, 1); // 初始化最优成本为无穷大
        Fraction bestS(0, 1);

        // 遍历所有候选 S
        for (const Fraction& S : candidates) {
            if (S.num <= 0) continue; // S 必须为正
            long long totalWaste = 0;
            long long totalTrips = 0;
            bool valid = true;

            for (int yi : food) {
                // 计算该学生需要的份数（向上取整）
                long long portions = (yi * S.den + S.num - 1) / S.num;
                if (portions > 3) { valid = false; break; } // 超过 3 次，不满足约束
                long long totalFood = portions * S.num;
                long long waste = totalFood - yi * S.den; // 浪费的食物（乘以分母后的整数）
                totalWaste += waste;
                totalTrips += portions;
            }

            if (!valid) continue; // 该 S 不满足约束，跳过

            // 计算总成本：a * waste + b * trips
            Fraction cost(a * totalWaste + b * totalTrips * S.den, S.den);
            if (cost < bestCost) {
                bestCost = cost;
                bestS = S;
            }
        }

        // 输出最优成本
        if (bestCost.den == 1) cout << bestCost.num << "\n";
        else cout << bestCost.num << " / " << bestCost.den << "\n";
    }
    return 0;
}
