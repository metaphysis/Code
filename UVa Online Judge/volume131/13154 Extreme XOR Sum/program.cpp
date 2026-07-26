// Extreme XOR Sum
// UVa ID: 13154
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.210s
// https://blog.csdn.net/metaphysis/article/details/163173249

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int nSize;
        cin >> nSize;
        vector<int> arr(nSize);
        for (int i = 0; i < nSize; ++i) cin >> arr[i];

        // 前缀异或，用于快速求连续区间异或
        vector<int> prefixXor(nSize + 1, 0);
        for (int i = 0; i < nSize; ++i) prefixXor[i + 1] = prefixXor[i] ^ arr[i];

        int q;
        cin >> q;
        cout << "Case " << caseNo << ":\n";

        while (q--) {
            int b, e;
            cin >> b >> e;
            int len = e - b + 1;

            // 长度为1时直接输出
            if (len == 1) {
                cout << arr[b] << "\n";
                continue;
            }

            // 若长度为2的幂，则所有元素的系数均为1，答案为区间异或
            if ((len & (len - 1)) == 0) {
                cout << (prefixXor[e + 1] ^ prefixXor[b]) << "\n";
                continue;
            }

            // 一般情况：枚举 n = len-1 的所有二进制子集 k
            int nVal = len - 1;
            int ans = 0;
            int k = nVal;
            while (true) {
                ans ^= arr[b + k];
                if (k == 0) break;
                k = (k - 1) & nVal;   // 枚举下一个子集
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
