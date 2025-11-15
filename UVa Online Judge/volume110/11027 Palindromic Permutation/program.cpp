// Palindromic Permutation
// UVa ID: 11027
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 计算阶乘
ll factorial[20];

void init_factorial() {
    factorial[0] = 1;
    for (int i = 1; i <= 15; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
}

// 计算给定字符频率下的排列数
ll count_permutations(const vector<int>& counts) {
    int total = 0;
    for (int c : counts) total += c;
    ll result = factorial[total];
    for (int c : counts) {
        result /= factorial[c];
    }
    return result;
}

// 递归生成左半部分的第 k 个排列
string build_kth(vector<int>& counts, int len, ll k) {
    if (len == 0) return "";

    int total_chars = 0;
    for (int i = 0; i < 26; i++) total_chars += counts[i];

    for (int i = 0; i < 26; i++) {
        if (counts[i] == 0) continue;

        // 尝试将字符 'a' + i 放在当前位置
        counts[i]--;
        ll ways = count_permutations(counts);
        if (k <= ways) {
            return string(1, 'a' + i) + build_kth(counts, len - 1, k);
        } else {
            k -= ways;
            counts[i]++;
        }
    }
    return ""; // 不会执行到这里
}

void solve(int case_num) {
    string s;
    ll n;
    cin >> s >> n;

    // 统计频率
    vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'a']++;
    }

    // 检查能否形成回文
    int odd_count = 0;
    char odd_char = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] % 2 == 1) {
            odd_count++;
            odd_char = 'a' + i;
        }
    }

    int len = s.length();
    if ((len % 2 == 0 && odd_count != 0) || (len % 2 == 1 && odd_count != 1)) {
        cout << "Case " << case_num << ": XXX" << endl;
        return;
    }

    // 构造左半部分的字符计数
    vector<int> half_counts(26, 0);
    for (int i = 0; i < 26; i++) {
        half_counts[i] = freq[i] / 2;
    }

    int half_len = len / 2;

    // 计算左半部分的不同排列数
    ll total_palindromes = count_permutations(half_counts);
    if (n > total_palindromes) {
        cout << "Case " << case_num << ": XXX" << endl;
        return;
    }

    // 生成左半部分的第 n 个排列
    string left_half = build_kth(half_counts, half_len, n);

    // 构造完整回文
    string right_half = left_half;
    reverse(right_half.begin(), right_half.end());

    string palindrome;
    if (len % 2 == 0) {
        palindrome = left_half + right_half;
    } else {
        palindrome = left_half + odd_char + right_half;
    }

    cout << "Case " << case_num << ": " << palindrome << endl;
}

int main() {
    init_factorial();

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        solve(t);
    }
    return 0;
}
