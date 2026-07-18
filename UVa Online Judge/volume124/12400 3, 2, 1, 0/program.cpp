// 3, 2, 1, 0
// UVa ID: 12400
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 简易大整数，小端存储（低位在 vector 开头），支持判断奇偶、右移一位、乘以5、加上另一个数乘以小整数
struct BigInt {
    vector<unsigned int> a; // 每个元素32位

    BigInt(unsigned int x = 0) {
        if (x == 0) a.push_back(0);
        else while (x) { a.push_back(x & 0xffffffffu); x >>= 32; }
    }

    bool isOdd() const { return a[0] & 1u; }

    // 右移一位（除以2）
    void shiftRightOne() {
        unsigned int carry = 0;
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            unsigned long long val = ((unsigned long long)carry << 32) | a[i];
            a[i] = (unsigned int)(val >> 1);
            carry = (unsigned int)(val & 1ull);
        }
        if (a.size() > 1 && a.back() == 0) a.pop_back();
    }

    // 乘以5
    void multiply5() {
        unsigned long long carry = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            unsigned long long tmp = (unsigned long long)a[i] * 5 + carry;
            a[i] = (unsigned int)(tmp & 0xffffffffull);
            carry = tmp >> 32;
        }
        while (carry) {
            a.push_back((unsigned int)(carry & 0xffffffffull));
            carry >>= 32;
        }
    }

    // 当前数 += b * d （d 为 2 或 3）
    void addMul(const BigInt& b, unsigned int d) {
        unsigned long long carry = 0;
        size_t n = b.a.size();
        if (a.size() < n) a.resize(n, 0);
        for (size_t i = 0; i < n; ++i) {
            unsigned long long tmp = (unsigned long long)b.a[i] * d + carry + a[i];
            a[i] = (unsigned int)(tmp & 0xffffffffull);
            carry = tmp >> 32;
        }
        size_t i = n;
        while (carry) {
            if (i < a.size()) {
                unsigned long long tmp = (unsigned long long)a[i] + carry;
                a[i] = (unsigned int)(tmp & 0xffffffffull);
                carry = tmp >> 32;
                ++i;
            } else {
                a.push_back((unsigned int)(carry & 0xffffffffull));
                carry >>= 32;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, K;
    while (cin >> N >> M >> K) {
        // K=0 时无意义，按不可能处理
        if (K == 0) {
            cout << "Impossible.\n";
            continue;
        }
        vector<int> digit(K);          // digit[i] 表示第 i 位（权重 10^i）
        digit[0] = 2;                  // 最低位固定为 2
        BigInt q(1);                   // q_1 = 1
        BigInt pow5(5);                // 5^1
        for (int i = 1; i < K; ++i) {
            int d = q.isOdd() ? 3 : 2; // 决定当前位数字
            digit[i] = d;
            // 计算分子 = q + d * 5^i，然后右移一位得到新的 q
            q.addMul(pow5, (unsigned int)d);
            q.shiftRightOne();
            pow5.multiply5();          // 准备下一轮的 5^(i+1)
        }
        // 统计 2 和 3 的个数
        int cnt2 = 0, cnt3 = 0;
        for (int i = 0; i < K; ++i) {
            if (digit[i] == 2) ++cnt2;
            else ++cnt3;
        }
        if (cnt2 <= M && cnt3 <= N) {
            string ans;
            ans.reserve(K);
            for (int i = K - 1; i >= 0; --i) ans.push_back(char('0' + digit[i]));
            cout << ans << '\n';
        } else cout << "Impossible.\n";
    }
    return 0;
}
