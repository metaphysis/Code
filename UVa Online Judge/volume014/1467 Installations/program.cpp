// Installations
// UVa ID: 1467
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Job {
    int s, d;
};

int n, p;
vector<Job> jobs;

bool cmpByDeadline(const Job& a, const Job& b) {
    return a.d < b.d;
}

int handle(int x) {
    int time = 0, first = 0, second = 0;
    for (int i = 0; i <= p; ++i) {
        if (i == x) continue;
        time += jobs[i].s;
        int penalty = max(0, time - jobs[i].d);
        if (penalty >= second) {
            second = penalty;
            if (second > first) swap(first, second);
        }
    }
    time += jobs[x].s;
    int penalty = max(0, time - jobs[x].d);
    if (penalty >= second) {
        second = penalty;
        if (second > first) swap(first, second);
    }
    return first + second;
}

int solve() {
    sort(jobs.begin(), jobs.end(), cmpByDeadline);
    
    int time = 0, first = 0, second = 0;
    for (int i = 0; i < n; ++i) {
        time += jobs[i].s;
        int penalty = max(0, time - jobs[i].d);
        if (penalty >= second) {
            second = penalty;
            p = i;  // 关键：每次都更新 p 为当前位置
        }
        if (second > first) swap(first, second);
    }
    
    int ans = first + second;
    for (int i = 0; i < p; ++i) 
        ans = min(ans, handle(i));
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        jobs.resize(n);
        for (int i = 0; i < n; ++i) 
            cin >> jobs[i].s >> jobs[i].d;
        cout << solve() << '\n';
    }
    return 0;
}
