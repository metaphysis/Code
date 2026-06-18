// Ruler
// UVa ID: 1377
// Verdict: Accepted
// Submission Date: 2026-06-18
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, caseNo;
vector<int> tar;          // 目标长度（去重）
int id[1000001];          // 长度 -> 位索引（0~49），-1表示不存在
int bestM, bestL;
vector<int> bestScales;

// 计算当前刻度集合能覆盖的目标掩码
int getMask(const vector<int>& s) {
    int mask = 0;
    for (int i = 0; i < (int)s.size(); ++i)
        for (int j = i + 1; j < (int)s.size(); ++j) {
            int d = abs(s[i] - s[j]);
            if (d < 1000001 && id[d] != -1) mask |= (1 << id[d]);
        }
    return mask;
}

void dfs(vector<int>& s, int mask, int L) {
    int m = s.size();
    if (m >= bestM) return;
    if (mask == (1 << n) - 1) { bestM = m; bestL = L; bestScales = s; return; }
    if (m == 7) return;

    // 生成候选刻度
    vector<int> cand;
    for (int d : tar)
        for (int x : s) {
            if (x + d > 0 && x + d < L) cand.push_back(x + d);
            if (x - d > 0 && x - d < L) cand.push_back(x - d);
        }
    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());

    for (int x : cand) {
        if (find(s.begin(), s.end(), x) != s.end()) continue;
        // 计算新增覆盖
        int add = 0;
        for (int y : s) {
            int d = abs(x - y);
            if (d < 1000001 && id[d] != -1 && !(mask & (1 << id[d])))
                add |= (1 << id[d]);
        }
        if (!add) continue;
        s.push_back(x);
        dfs(s, mask | add, L);
        s.pop_back();
    }
}

void solve() {
    sort(tar.begin(), tar.end());
    tar.erase(unique(tar.begin(), tar.end()), tar.end());
    n = tar.size();
    memset(id, -1, sizeof(id));
    for (int i = 0; i < n; ++i) id[tar[i]] = i;

    bestM = 8; bestL = INT_MAX; bestScales.clear();

    for (int L : tar) {
        vector<int> s = {0, L};
        int mask = 0;
        if (id[L] != -1) mask = 1 << id[L];
        dfs(s, mask, L);
        if (bestM == 2) break;
    }

    printf("Case %d:\n%d\n", caseNo, bestM);
    sort(bestScales.begin(), bestScales.end());
    for (int i = 0; i < bestM; ++i) printf("%d%c", bestScales[i], i + 1 == bestM ? '\n' : ' ');
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        tar.resize(n);
        for (int i = 0; i < n; ++i) scanf("%d", &tar[i]);
        ++caseNo;
        solve();
    }
    return 0;
}
