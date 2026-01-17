// Megamind
// UVa ID: 13276
// Verdict: Accepted
// Submission Date: 2026-01-13
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseNum = 1; caseNum <= t; ++caseNum) {
        long long e, p, k, r;
        cin >> e >> p >> k >> r;
        // 情况1：一枪解决
        if (p >= e) {
            cout << "Case " << caseNum << ": 1\n";
            continue;
        }
        // 情况2：第一个弹匣内解决
        if (k * p >= e) {
            long long shots = (e + p - 1) / p;
            cout << "Case " << caseNum << ": " << shots << "\n";
            continue;
        }
        // 情况3：每个完整周期净伤害非正 且 第一个弹匣打不完
        if (k * p - r <= 0) {
            cout << "Case " << caseNum << ": -1\n";
            continue;
        }
        // 一般情况
        long long net = k * p - r;
        // 第一个弹匣后剩余能量
        long long rem = e - k * p;
        // 需要完整周期数（从第一个弹匣后开始算）
        long long cycles = (rem + net - 1) / net;
        // 计算总射击次数
        long long shots = k; // 第一个弹匣
        if (cycles > 0) {
            // 前 cycles-1 个完整周期
            shots += (cycles - 1) * k;
            // 最后一个周期前的剩余能量
            long long beforeLast = e - k * p - (cycles - 1) * net;
            // 换弹回复
            beforeLast += r;
            // 最后一个周期需要的射击次数
            shots += (beforeLast + p - 1) / p;
        }
        cout << "Case " << caseNum << ": " << shots << '\n';
    }
    return 0;
}
