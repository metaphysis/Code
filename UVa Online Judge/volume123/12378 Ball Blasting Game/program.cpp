// Ball Blasting Game
// UVa ID: 12378
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算单个测试用例的最大爆炸次数
int maxExplosions(const string& str) {
    // 压缩连续同色块，只保留颜色序列
    string s;
    for (char c : str)
        if (s.empty() || s.back() != c)
            s.push_back(c);
    int n = s.size();
    if (n == 0) return 0; // 防御性
    // Manacher 算法计算以每个位置为中心的奇数长度回文半径
    vector<int> d1(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; ++i) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k])
            ++k;
        d1[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    // 最大半径即为最大爆炸次数
    return *max_element(d1.begin(), d1.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        string str;
        cin >> str;
        cout << maxExplosions(str) << '\n';
    }
    return 0;
}
