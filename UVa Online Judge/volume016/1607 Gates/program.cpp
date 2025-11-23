// Gates
// UVa ID: 1607
// Verdict: Accepted
// Submission Date: 2025-11-22
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010, MAXM = 200010;

int n, m;
int a[MAXM], b[MAXM];
int in[MAXN], out[MAXM];

int run(int k) {
    // 初始化输入：前k个为0，后面为1
    for (int i = 1; i <= k; i++) in[i] = 0;
    for (int i = k + 1; i <= n; i++) in[i] = 1;
    // 计算每个门的输出
    for (int i = 1; i <= m; i++) {
        int A, B;
        // 处理第一个输入
        if (a[i] < 0) A = in[-a[i]];
        else A = out[a[i]];
        // 处理第二个输入  
        if (b[i] < 0) B = in[-b[i]];
        else B = out[b[i]];
        // NAND 运算
        out[i] = !(A & B);
    }
    
    return out[m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int d;
    cin >> d;
    while (d--) {
        cin >> n >> m;
        for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];
        int zero = run(0);  // 全0输入时的输出
        int one = run(n);  // 全1输入时的输出
        if (zero == one) {
            // 所有输入都可以设为常量
            for (int i = 1; i <= n; i++) cout << '0';
            cout << '\n';
            continue;
        }
        // 二分查找分界点
        int l = 1, r = n;
        while (l < r) {
            int t = (l + r) >> 1;
            if (run(t) == one) r = t;
            else l = t + 1;
        }
        // 输出结果
        for (int i = 1; i < r; i++) cout << '0';
        cout << 'x';
        for (int i = r + 1; i <= n; i++) cout << '1';
        cout << '\n';
    }
    return 0;
}
