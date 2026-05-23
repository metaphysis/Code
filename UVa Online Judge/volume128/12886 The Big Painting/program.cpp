// The Big Painting
// UVa ID: 12886
// Verdict: Accepted
// Submission Date: 2026-05-23
// UVa Run Time: 0.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

const ULL BASE1 = 911382323;   // 行哈希基数
const ULL BASE2 = 972663749;   // 列哈希基数

int hp, wp, hm, wm;
vector<string> pattern, text;

void solve() {
    // 读入原画
    pattern.resize(hp);
    for (int i = 0; i < hp; ++i) cin >> pattern[i];
    // 读入巨作
    text.resize(hm);
    for (int i = 0; i < hm; ++i) cin >> text[i];

    // 预计算幂
    vector<ULL> pow1(max(wm, wp) + 1), pow2(max(hm, hp) + 1);
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= max(wm, wp); ++i) pow1[i] = pow1[i - 1] * BASE1;
    for (int i = 1; i <= max(hm, hp); ++i) pow2[i] = pow2[i - 1] * BASE2;

    // 计算模式矩阵的哈希值
    ULL patternHash = 0;
    for (int i = 0; i < hp; ++i) {
        ULL rowHash = 0;
        for (int j = 0; j < wp; ++j) {
            ULL val = (pattern[i][j] == 'x') ? 1 : 0;
            rowHash = rowHash * BASE1 + val;
        }
        patternHash = patternHash * BASE2 + rowHash;
    }

    // 计算文本矩阵每行的前缀哈希
    vector<vector<ULL>> rowHash(hm + 1, vector<ULL>(wm + 1, 0));
    for (int i = 1; i <= hm; ++i)
        for (int j = 1; j <= wm; ++j) {
            ULL val = (text[i - 1][j - 1] == 'x') ? 1 : 0;
            rowHash[i][j] = rowHash[i][j - 1] * BASE1 + val;
        }

    // 计算文本矩阵的二维哈希
    vector<vector<ULL>> hash2D(hm + 1, vector<ULL>(wm + 1, 0));
    for (int i = 1; i <= hm; ++i)
        for (int j = 1; j <= wm; ++j)
            hash2D[i][j] = hash2D[i - 1][j] * BASE2 + rowHash[i][j];

    // 枚举所有可能的左上角位置
    int ans = 0;
    for (int i = hp; i <= hm; ++i)
        for (int j = wp; j <= wm; ++j) {
            int r1 = i - hp + 1, c1 = j - wp + 1;
            ULL subHash = hash2D[i][j]
                        - hash2D[r1 - 1][j] * pow2[hp]
                        - hash2D[i][c1 - 1] * pow1[wp]
                        + hash2D[r1 - 1][c1 - 1] * pow1[wp] * pow2[hp];
            if (subHash == patternHash) ++ans;
        }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> hp >> wp >> hm >> wm) solve();
    return 0;
}
