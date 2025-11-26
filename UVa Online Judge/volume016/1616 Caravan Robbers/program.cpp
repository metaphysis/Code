// Caravan Robbers
// UVa ID: 1616
// Verdict: Wrong Answer
// Submission Date: 2025-11-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct Interval {
    int a, b;
    bool operator<(const Interval& other) const { return a < other.a; }
};

Interval intervals[MAXN];
int n;

bool check(long long p, long long q) {
    long long last = intervals[0].a * q;  // 统一乘以q来避免分数
    for (int i = 0; i < n; i++) {
        long long currentStart = intervals[i].a * q;
        long long currentEnd = intervals[i].b * q;
        long long start = max(last, currentStart);
        long long end = start + p;
        if (end > currentEnd) return false;
        last = end;
    }
    return true;
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) 
            scanf("%d%d", &intervals[i].a, &intervals[i].b);
        sort(intervals, intervals + n);
        // 收集所有可能的连续重叠区间段的区间数作为候选分母
        vector<int> candidates;
        int i = 0;
        while (i < n) {
            int j = i;
            long long minEnd = intervals[i].b;
            while (j < n && intervals[j].a < minEnd) {
                minEnd = min(minEnd, (long long)intervals[j].b);
                j++;
            }
            candidates.push_back(j - i);
            i = j;
        }
        // 去重并排序
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
        // 二分搜索分子
        long long left = 0, right = 1000000;
        long long bestP = 0, bestQ = 1;
        while (left <= right) {
            long long mid = (left + right) / 2;
            bool found = false;
            // 只检查候选分母
            for (int q : candidates) {
                if (check(mid, q)) {
                    found = true;
                    if (mid * bestQ > bestP * q) {
                        bestP = mid;
                        bestQ = q;
                    }
                }
            }
            if (found) left = mid + 1;
            else right = mid - 1;
        }
        long long g = __gcd(bestP, bestQ);
        bestP /= g;
        bestQ /= g;
        printf("%lld/%lld\n", bestP, bestQ);
    }
    return 0;
}
