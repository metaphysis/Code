// Gangs
// UVa ID: 11290
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<unsigned __int128> catalan;      // catalan[n] = C_n

// 生成第 k 个长度为 2n 的合法路径（k 从 1 开始）
string generateRun(int n, unsigned __int128 k) {
    if (n == 0) return "";
    // 原始路径组：E + X + S，X 为长度为 2(n-1) 的路径
    if (k <= catalan[n - 1])
        return "E" + generateRun(n - 1, k) + "S";
    k -= catalan[n - 1];
    // 非原始路径组，按第一次返回位置 i 从大到小
    for (int i = n - 1; i >= 1; --i) {
        unsigned __int128 cntX = catalan[i - 1];
        unsigned __int128 cntY = catalan[n - i];
        unsigned __int128 groupSize = cntX * cntY;
        if (k <= groupSize) {
            // 组内先按 X 的顺序，再按 Y 的顺序
            unsigned __int128 idxY = (k - 1) % cntY + 1;
            unsigned __int128 idxX = (k - 1) / cntY + 1;
            string X = generateRun(i - 1, idxX);
            string Y = generateRun(n - i, idxY);
            return "E" + X + "S" + Y;
        }
        k -= groupSize;
    }
    return "";   // 不会执行到
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<int, unsigned long long>> queries;
    int N;
    unsigned long long M;
    int maxN = 0;
    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;
        queries.push_back({N, M});
        maxN = max(maxN, N);
    }
    int maxn = maxN - 1;
    catalan.assign(maxn + 1, 0);
    catalan[0] = 1;
    // 递推计算卡特兰数：C_i = C_{i-1} * (4i-2) / (i+1)
    for (int i = 1; i <= maxn; ++i) catalan[i] = catalan[i - 1] * (4 * i - 2) / (i + 1);
    for (auto &q : queries) {
        int n = q.first - 1;
        unsigned __int128 k = (unsigned __int128)q.second;
        if (k > catalan[n]) cout << "ERROR\n";
        else cout << generateRun(n, k) << '\n';
    }
    return 0;
}
