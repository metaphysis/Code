// Don Giovanni's Last Dinner
// UVa ID: 10962
// Verdict: Accepted
// Submission Date: 2026-01-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 分数结构体
struct Fraction {
    long long n, d;  // 分子，分母
    Fraction() : n(0), d(1) {}
    Fraction(long long n, long long d = 1) : n(n), d(d) { simplify(); }
    // 简化分数（约分）
    void simplify() {
        if (d < 0) n = -n, d = -d;
        long long g = __gcd(abs(n), d);
        if (g) n /= g, d /= g;
    }
    // 分数加法
    Fraction operator+(const Fraction& other) const {
        return Fraction(n * other.d + other.n * d, d * other.d);
    }
    // 比较运算符
    bool operator<(const Fraction& other) const { return n * other.d < other.n * d; }
    bool operator<=(const Fraction& other) const { return n * other.d <= other.n * d; }
    bool operator==(const Fraction& other) const { return n * other.d == other.n * d; }
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int R, r, N, C;
        cin >> R >> r >> N >> C;
        Fraction donTime(0, 1);
        vector<pair<Fraction, int>> events;
        // 读取每盘菜的信息，计算 Don Giovanni 吃完每盘菜的时间
        for (int i = 0; i < N; i++) {
            int s, g;
            cin >> s >> g;
            donTime = donTime + Fraction(g, R);
            events.push_back({donTime, s - g});
        }
        // 模拟 Leporello 的进食过程，合并连续进食区间
        vector<pair<Fraction, Fraction>> intervals;
        for (auto& evt : events) {
            // 计算开始吃这盘菜的时间
            Fraction startTime = intervals.empty() ? evt.first : intervals.back().second;
            if (startTime < evt.first) startTime = evt.first;
            // 计算吃完这盘菜的时间
            Fraction endTime = startTime + Fraction(evt.second, r);
            // 判断是否需要合并区间
            if (intervals.empty() || intervals.back().second < startTime)
                intervals.push_back({startTime, endTime});
            else
                intervals.back().second = endTime;
        }
        // 处理每个召唤
        for (int i = 0; i < C; i++) {
            int t;
            cin >> t;
            Fraction callTime(t, 1);
            bool full = false;
            // 检查召唤时间是否在任意一个进食区间内
            for (auto& seg : intervals)
                if (seg.first <= callTime && callTime <= seg.second) {
                    full = true;
                    break;
                }
            cout << (full ? "full" : "clear") << '\n';
        }
        // 测试用例之间输出空行
        if (T) cout << '\n';
    }
    return 0;
}
