#include <bits/stdc++.h>
using namespace std;

class Solver {
    int n;
    vector<vector<int>> graph;
    vector<int> dfn, low, stk, compId, compSize;
    vector<bool> inStack;
    int timer = 0;
    int compCount = 0;
    void tarjan(int u) {
        dfn[u] = low[u] = ++timer;
        stk.push_back(u);
        inStack[u] = true;
        for (int v : graph[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) low[u] = min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u]) {
            int size = 0;
            while (true) {
                int v = stk.back();
                stk.pop_back();
                inStack[v] = false;
                compId[v] = compCount;
                ++size;
                if (v == u) break;
            }
            compSize.push_back(size);
            ++compCount;
        }
    }
public:
    int solve(int pageCount, int linkCount) {
        n = pageCount;
        graph.assign(n, {});
        for (int i = 0; i < linkCount; ++i) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
        }
        dfn.assign(n, 0);
        low.assign(n, 0);
        compId.assign(n, -1);
        inStack.assign(n, false);
        stk.clear();
        compSize.clear();
        timer = 0;
        compCount = 0;
        for (int i = 0; i < n; ++i) {
            if (!dfn[i]) tarjan(i);
        }
        vector<bool> hasSelfLoop(compCount, false);
        for (int u = 0; u < n; ++u) {
            for (int v : graph[u]) {
                if (u == v) hasSelfLoop[compId[u]] = true;
            }
        }
        int badMask = 0;
        for (int c = 0; c < compCount; ++c) {
            bool good = (compSize[c] > 1) || hasSelfLoop[c];
            if (!good) badMask |= 1 << c;
        }
        if (badMask == 0) return 0;
        vector<int> inMask(compCount, 0), outMask(compCount, 0);
        for (int u = 0; u < n; ++u) {
            for (int v : graph[u]) {
                int cu = compId[u], cv = compId[v];
                if (cu == cv) continue;
                outMask[cu] |= 1 << cv;
                inMask[cv] |= 1 << cu;
            }
        }
        int answer = compCount;
        int allMask = (1 << compCount) - 1;
        for (int mask = 0; mask <= allMask; ++mask) {
            if ((mask & badMask) != badMask) continue;
            int sourceCount = 0, sinkCount = 0;
            for (int c = 0; c < compCount; ++c) {
                if (!(mask & (1 << c))) continue;
                if ((inMask[c] & mask) == 0) ++sourceCount;
                if ((outMask[c] & mask) == 0) ++sinkCount;
            }
            answer = min(answer, max(sourceCount, sinkCount));
        }
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int pageCount, linkCount;
        cin >> pageCount >> linkCount;
        Solver solver;
        cout << solver.solve(pageCount, linkCount) << '\n';
    }
    return 0;
}
