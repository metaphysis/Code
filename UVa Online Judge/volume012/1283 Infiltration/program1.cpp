// Infiltration
// UVa ID: 1283
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 0.660s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

int n, limit;
vector<bitset<75>> cover;
vector<vector<int>> inNeighbors;  // 预处理入邻点
bitset<75> allCovered;
vector<int> ans, cur;

int heuristic(bitset<75>& covered) {
    int remain = n - covered.count();
    if (remain == 0) return 0;
    int maxCover = 1;
    for (int i = 0; i < n; ++i) {
        int cnt = (cover[i] & ~covered).count();
        if (cnt > maxCover) maxCover = cnt;
    }
    return (remain + maxCover - 1) / maxCover;
}

bool dfs(bitset<75> covered, int depth) {
    if (covered == allCovered) {
        ans = cur;
        return true;
    }
    if (depth >= limit) return false;
    if (depth + heuristic(covered) > limit) return false;
    
    // 找最难覆盖的点（候选点最少）
    int u = -1, minCand = n + 1;
    for (int i = 0; i < n; ++i) if (!covered[i]) {
        int cnt = 0;
        for (int v : inNeighbors[i]) if (!covered[v]) ++cnt;
        if (cnt < minCand) minCand = cnt, u = i;
    }
    if (u == -1) return false;
    
    // 候选点按覆盖能力降序
    vector<int> cand = inNeighbors[u];
    sort(cand.begin(), cand.end(), [&](int a, int b) {
        return (cover[a] & ~covered).count() > (cover[b] & ~covered).count();
    });
    
    for (int v : cand) {
        cur.push_back(v + 1);
        if (dfs(covered | cover[v], depth + 1)) return true;
        cur.pop_back();
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNum = 0;
    while (cin >> n) {
        ++caseNum;
        cover.assign(n, bitset<75>());
        inNeighbors.assign(n, vector<int>());
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            cover[i].set(i);
            inNeighbors[i].push_back(i);
            for (int j = 0; j < n; ++j) if (s[j] == '1') {
                cover[i].set(j);
                inNeighbors[j].push_back(i);
            }
        }
        allCovered.reset();
        for (int i = 0; i < n; ++i) allCovered.set(i);
        
        // 贪心上界
        bitset<75> greedyCovered;
        int upper = 0;
        while (greedyCovered != allCovered) {
            int best = -1, bestCnt = -1;
            for (int i = 0; i < n; ++i) if (!greedyCovered[i]) {
                int cnt = (cover[i] & ~greedyCovered).count();
                if (cnt > bestCnt) bestCnt = cnt, best = i;
            }
            if (best == -1) break;
            ++upper;
            greedyCovered |= cover[best];
        }
        
        for (limit = 1; limit <= upper; ++limit) {
            cur.clear();
            if (dfs(bitset<75>(), 0)) break;
        }
        
        cout << "Case " << caseNum << ": " << ans.size();
        for (int x : ans) cout << " " << x;
        cout << "\n";
    }
    return 0;
}
