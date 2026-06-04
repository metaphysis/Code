// Kool Konstructions
// UVa ID: 12769
// Verdict: Accepted
// Submission Date: 2026-06-04
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100002;

int bit[MAX_N]; // 树状数组

// 单点加
void add(int idx, int val) {
    while (idx < MAX_N) {
        bit[idx] += val;
        idx += idx & -idx;
    }
}

// 前缀和
int sum(int idx) {
    int res = 0;
    while (idx > 0) {
        res += bit[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    while (cin >> T && T != 0) {
        memset(bit, 0, sizeof(bit)); // 每个测试用例重置树状数组
        
        while (T--) {
            char op;
            cin >> op;
            
            if (op == 'B') {
                int a, b, y;
                cin >> a >> b >> y;
                add(a, y);
                add(b + 1, -y);
            } else { // op == 'Q'
                int a;
                cin >> a;
                cout << sum(a) << '\n';
            }
        }
    }
    
    return 0;
}
