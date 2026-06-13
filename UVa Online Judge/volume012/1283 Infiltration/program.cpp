// Infiltration
// UVa ID: 1283
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 9530s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, limit;
vector<bitset<75>> cover;
bitset<75> allCovered;
vector<int> ans, cur;

bool dfs(bitset<75> covered, int depth) {
    if (covered == allCovered) {
        ans = cur;
        return true;
    }
    if (depth >= limit) return false;
    
    int u = -1;
    for (int i = 0; i < n; ++i) if (!covered[i]) { u = i; break; }
    if (u == -1) return false;
    
    vector<int> cand;
    for (int i = 0; i < n; ++i) if (cover[i][u]) cand.push_back(i);
    
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
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            cover[i].set(i);
            for (int j = 0; j < n; ++j) if (s[j] == '1') cover[i].set(j);
        }
        allCovered.reset();
        for (int i = 0; i < n; ++i) allCovered.set(i);
        
        for (limit = 1; limit <= n; ++limit) {
            cur.clear();
            if (dfs(bitset<75>(), 0)) break;
        }
        
        cout << "Case " << caseNum << ": " << ans.size();
        for (int x : ans) cout << " " << x;
        cout << "\n";
    }
    return 0;
}
