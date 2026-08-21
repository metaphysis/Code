#include <bits/stdc++.h>
using namespace std;

class Matcher {
private:
    vector<vector<int>> graph;
    vector<int> pairU, pairV, dist;

    bool bfs() {
        queue<int> que;
        for (int u = 0; u < (int)graph.size(); u++)
            if (pairU[u] == -1) {
                dist[u] = 0;
                que.push(u);
            } else {
                dist[u] = -1;
            }
        bool found = false;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v : graph[u]) {
                int w = pairV[v];
                if (w == -1) {
                    found = true;
                } else if (dist[w] == -1) {
                    dist[w] = dist[u] + 1;
                    que.push(w);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : graph[u]) {
            int w = pairV[v];
            if (w == -1 || (dist[w] == dist[u] + 1 && dfs(w))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

public:
    Matcher(vector<vector<int>> newGraph) {
        graph = newGraph;
        pairU.assign(graph.size(), -1);
        pairV.assign(0, -1);
        for (const vector<int>& edges : graph)
            for (int v : edges)
                pairV.resize(max((int)pairV.size(), v + 1), -1);
        dist.resize(graph.size());
    }

    int matchMax() {
        int result = 0;
        while (bfs())
            for (int u = 0; u < (int)graph.size(); u++)
                if (pairU[u] == -1 && dfs(u))
                    result++;
        return result;
    }
};

bool isH(const vector<string>& mp, int r, int c, const string& word) {
    for (int k = 0; k < (int)word.size(); k++)
        if (mp[r][c + k] != word[k]) return false;
    return true;
}

bool isV(const vector<string>& mp, int r, int c, const string& word) {
    for (int k = 0; k < (int)word.size(); k++)
        if (mp[r + k][c] != word[k]) return false;
    return true;
}

int solve(const vector<string>& mp) {
    const string hWord = "GARBANCILLOS", vWord = "ASTRAGALUS";
    int rowCnt = mp.size(), colCnt = mp[0].size();
    vector<vector<vector<int>>> hAt(rowCnt, vector<vector<int>>(colCnt));
    vector<vector<vector<int>>> vAt(rowCnt, vector<vector<int>>(colCnt));
    int hCnt = 0, vCnt = 0;
    for (int r = 0; r < rowCnt; r++)
        for (int c = 0; c + (int)hWord.size() <= colCnt; c++)
            if (isH(mp, r, c, hWord)) {
                for (int k = 0; k < (int)hWord.size(); k++)
                    hAt[r][c + k].push_back(hCnt);
                hCnt++;
            }
    for (int r = 0; r + (int)vWord.size() <= rowCnt; r++)
        for (int c = 0; c < colCnt; c++)
            if (isV(mp, r, c, vWord)) {
                for (int k = 0; k < (int)vWord.size(); k++)
                    vAt[r + k][c].push_back(vCnt);
                vCnt++;
            }
    vector<vector<int>> graph(hCnt);
    for (int r = 0; r < rowCnt; r++)
        for (int c = 0; c < colCnt; c++) {
            for (int h : hAt[r][c])
                for (int v : vAt[r][c])
                    graph[h].push_back(v);
        }
    Matcher matcher(graph);
    return matcher.matchMax();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    while (testCnt--) {
        int rowCnt, colCnt;
        cin >> rowCnt >> colCnt;
        vector<string> mp(rowCnt);
        for (string& row : mp) cin >> row;
        cout << solve(mp) << '\n';
    }
    return 0;
}
