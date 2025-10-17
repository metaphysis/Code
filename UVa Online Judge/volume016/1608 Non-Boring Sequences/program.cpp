// Non-Boring Sequences
// UVa ID: 1608
// Verdict: Accepted
// Submission Date: 2025-10-13
// UVa Run Time: 0.120s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> a, pre, nxt;

bool check(int l, int r) {
    if (l >= r) return true;
    for (int i = l, j = r; i <= j; i++, j--) {
        if (pre[i] < l && nxt[i] > r) return check(l, i - 1) && check(i + 1, r);
        if (pre[j] < l && nxt[j] > r) return check(l, j - 1) && check(j + 1, r);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T, n;
    cin >> T;
    while (T-- && cin >> n) {
        a.resize(n); pre.resize(n); nxt.resize(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        unordered_map<int, int> pos;
        for (int i = 0; i < n; i++) {
            pre[i] = pos.count(a[i]) ? pos[a[i]] : -1;
            pos[a[i]] = i;
        }
        pos.clear();
        for (int i = n - 1; i >= 0; i--) {
            nxt[i] = pos.count(a[i]) ? pos[a[i]] : n;
            pos[a[i]] = i;
        }
        
        cout << (check(0, n - 1) ? "non-boring" : "boring") << '\n';
    }
    
    return 0;
}
