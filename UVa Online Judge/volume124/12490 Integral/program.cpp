// Integral
// UVa ID: 12490
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Interval {
    int l, r;
    int fl, fr;
    int k;          // 内部未知点个数
    int dir;        // 1递增，-1递减，0相等
    ll minSum, maxSum;
};

// 向下取整除法，b > 0
ll floorDiv(ll a, ll b) {
    if (a >= 0) return a / b;
    return (a - b + 1) / b;
}

// 向上取整除法，b > 0
ll ceilDiv(ll a, ll b) {
    return -floorDiv(-a, b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    ll Y;
    while (cin >> N >> M >> Y) {
        vector<pair<int, ll>> pts;
        pts.reserve(M);
        for (int i = 0; i < M; ++i) {
            int x;
            ll f;
            cin >> x >> f;
            pts.emplace_back(x, f);
        }
        sort(pts.begin(), pts.end());
        ll f0 = pts.front().second;
        ll fN = pts.back().second;
        // 奇偶性检查
        if ((2LL * Y - f0 - fN) % 2 != 0) {
            cout << "N\n";
            continue;
        }
        ll sumKnownInternal = 0;
        for (auto &p : pts) {
            if (p.first != 0 && p.first != N)
                sumKnownInternal += p.second;
        }
        ll T = (2LL * Y - f0 - fN) / 2;          // 所有内部点总和
        ll target = T - sumKnownInternal;        // 未知点总和
        vector<Interval> intervals;
        ll totalMin = 0, totalMax = 0;
        bool ok = true;
        for (size_t i = 0; i + 1 < pts.size(); ++i) {
            int L = pts[i].first, R = pts[i + 1].first;
            ll FL = pts[i].second, FR = pts[i + 1].second;
            int k = R - L - 1;
            if (k <= 0) continue;
            Interval in;
            in.l = L; in.r = R;
            in.fl = FL; in.fr = FR;
            in.k = k;
            ll low = min(FL, FR), high = max(FL, FR);
            in.minSum = 1LL * k * low;
            in.maxSum = 1LL * k * high;
            totalMin += in.minSum;
            totalMax += in.maxSum;
            if (FL < FR) in.dir = 1;
            else if (FL > FR) in.dir = -1;
            else in.dir = 0;

            intervals.push_back(in);
        }
        if (target < totalMin || target > totalMax) {
            cout << "N\n";
            continue;
        }
        int K = (int)intervals.size();
        vector<ll> suffixMin(K + 1, 0), suffixMax(K + 1, 0);
        for (int i = K - 1; i >= 0; --i) {
            suffixMin[i] = intervals[i].minSum + suffixMin[i + 1];
            suffixMax[i] = intervals[i].maxSum + suffixMax[i + 1];
        }
        vector<ll> ans;
        ans.reserve(N - 1 - (M - 2));  // 未知点数
        ll sumAssigned = 0;             // 已处理完的所有区间总和
        for (int idx = 0; idx < K; ++idx) {
            Interval &in = intervals[idx];
            ll curSum = 0;              // 当前区间已分配前缀和
            ll prev = in.fl;            // 前一个值，初始为左边界
            // 处理相等情况
            if (in.dir == 0) {
                ll v = in.fl;
                for (int p = 0; p < in.k; ++p) {
                    ans.push_back(v);
                    curSum += v;
                }
                sumAssigned += curSum;
                continue;
            }
            ll afterMin = (idx + 1 < K ? suffixMin[idx + 1] : 0);
            ll afterMax = (idx + 1 < K ? suffixMax[idx + 1] : 0);
            for (int pos = 1; pos <= in.k; ++pos) {
                int rem = in.k - pos;   // 当前点之后的点数
                ll remainTotal = target - sumAssigned - curSum; // 从当前点开始到末尾的总和
                ll lower, upper;
                if (in.dir == 1) { // 递增
                    // v >= prev, v <= in.fr
                    // 最小总和条件: (rem+1)*v + afterMin <= remainTotal  => v <= floor((remainTotal-afterMin)/(rem+1))
                    // 最大总和条件: v + rem*in.fr + afterMax >= remainTotal => v >= remainTotal - afterMax - rem*in.fr
                    ll lower1 = remainTotal - afterMax - 1LL * rem * in.fr;
                    ll upper1 = floorDiv(remainTotal - afterMin, rem + 1);
                    lower = max(prev, lower1);
                    upper = min((ll)in.fr, upper1);
                } else { // 递减
                    // v <= prev, v >= in.fr
                    // 最小总和: v + rem*in.fr + afterMin <= remainTotal => v <= remainTotal - rem*in.fr - afterMin
                    // 最大总和: (rem+1)*v + afterMax >= remainTotal => v >= ceil((remainTotal-afterMax)/(rem+1))
                    ll lower1 = ceilDiv(remainTotal - afterMax, rem + 1);
                    ll upper1 = remainTotal - 1LL * rem * in.fr - afterMin;
                    lower = max((ll)in.fr, lower1);
                    upper = min(prev, upper1);
                }
                // 理论上一定存在，但保险
                if (lower > upper) { ok = false; break; }
                ll v = lower;
                ans.push_back(v);
                curSum += v;
                prev = v;
            }
            if (!ok) break;
            sumAssigned += curSum;
        }
        if (!ok || (ll)ans.size() != (N - 1 - (M - 2))) {
            cout << "N\n";
            continue;
        }
        cout << "S";
        for (size_t i = 0; i < ans.size(); ++i) {
            cout << ' ' << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
