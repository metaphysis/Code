// Bit-wise Sequence
// UVa ID: 10232
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

// 计算组合数 C(n, k)
long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long r = 1;
    if (k > n - k) k = n - k;
    for (int i = 1; i <= k; i++) {
        r = r * (n - i + 1) / i;
    }
    return r;
}

// 在 31 位中，1 的个数 = k，找第 idx 个数（从 0 开始）
int findKth(int k, long long idx) {
    int r = 0;
    int bits = 31;
    for (int pos = 30; pos >= 0; pos--) {
        long long cnt = comb(pos, k);
        if (idx >= cnt) {
            // 在 pos 放 1
            r |= (1 << pos);
            idx -= cnt;
            k--;
            if (k == 0) break;
        }
    }
    return r;
}

int main() {
    long long n;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            continue;
        }
        n--; // 因为我们要从 k=1 组开始找，跳过 0
        for (int k = 1; k <= 31; k++) {
            long long cnt = comb(31, k);
            if (n < cnt) {
                cout << findKth(k, n) << endl;
                break;
            } else {
                n -= cnt;
            }
        }
    }
    return 0;
}
