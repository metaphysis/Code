// Detection of Extraterrestrial
// UVa ID: 12012
// Verdict: Accepted
// Submission Date: 2025-12-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int base = 131;
const int MAXN = 1005;

ull power[MAXN], h[MAXN];
int answer[MAXN];
string s;
int n;

inline ull getHash(int l, int r) {
    return h[r] - h[l - 1] * power[r - l + 1];
}

int main() {
    power[0] = 1;
    for (int i = 1; i < MAXN; i++) power[i] = power[i - 1] * base;

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; caseNo++) {
        cin >> s;
        n = s.length();
        s = ' ' + s; // 转为 1-indexed

        // 计算前缀哈希
        for (int i = 1; i <= n; i++) h[i] = h[i - 1] * base + s[i];

        // 初始化答案数组
        fill(answer, answer + n + 1, 0);

        // 枚举块长度
        for (int length = 1; length <= n; length++) {
            // 对于每个起点，计算连续相同块的个数
            for (int i = 1; i + length - 1 <= n; i++) {
                int cnt = 1;
                ull curHash = getHash(i, i + length - 1);
                int j = i + length;
                while (j + length - 1 <= n && getHash(j, j + length - 1) == curHash) {
                    cnt++;
                    j += length;
                }
                // 对于每个块数 X，更新最大长度
                for (int k = 1; k <= cnt; k++) answer[k] = max(answer[k], k * length);
            }
        }

        // 输出结果
        cout << "Case #" << caseNo << ':';
        for (int i = 1; i <= n; i++) cout << ' ' << answer[i];
        cout << '\n';
    }
    return 0;
}
