// Laptop
// UVa ID: 1617
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Task {
    int r, d;
    bool operator<(const Task& other) const {
        if (r == other.r) return d < other.d;
        return r < other.r;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<Task> tasks(n);
        for (int i = 0; i < n; i++)
            cin >> tasks[i].r >> tasks[i].d;
        
        sort(tasks.begin(), tasks.end());
        
        int idleCount = 0;
        int currentRight = tasks[0].d;
        
        for (int i = 1; i < n; i++) {
            if (tasks[i].r > currentRight) {
                // 需要开始新的连续段
                idleCount++;
                currentRight = tasks[i].d;
            } else {
                if (tasks[i].d == currentRight) continue;
                else currentRight++;
            }
        }
        
        cout << idleCount << '\n';
    }
    
    return 0;
}
