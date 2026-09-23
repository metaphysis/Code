#include <bits/stdc++.h>
using namespace std;

void buildExpr(int progId, const vector<vector<int>>& child, string& expr) {
    if (progId != 0) {
        if (!child[progId].empty()) expr += '(';
        expr += 'P';
        expr += to_string(progId);
    }
    if (!child[progId].empty()) {
        expr += '(';
        for (int i = 0, cnt = child[progId].size(); i < cnt; ++i) {
            if (i > 0) expr += '|';
            buildExpr(child[progId][i], child, expr);
        }
        expr += ')';
    }
    if (progId != 0 && !child[progId].empty()) expr += ')';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, target, caseId = 0;
    const int inf = 1000000000;
    while (cin >> n >> m >> target) {
        if (n == 0 && m == 0 && target == 0) break;
        string init;
        cin >> init;
        vector<int> runTime(n + 1), remain(n + 1), dist(m + 1, inf), source(m + 1);
        vector<vector<int>> useBy(m + 1), output(n + 1), child(n + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        for (int i = 1; i <= n; ++i) {
            int inCnt, outCnt, varId;
            cin >> runTime[i] >> inCnt;
            remain[i] = inCnt;
            for (int j = 0; j < inCnt; ++j) {
                cin >> varId;
                useBy[varId].push_back(i);
            }
            cin >> outCnt;
            output[i].resize(outCnt);
            for (int j = 0; j < outCnt; ++j) cin >> output[i][j];
        }
        for (int i = 1; i <= m; ++i) {
            if (init[i - 1] == '1') {
                dist[i] = 0;
                minHeap.push({0, i});
            }
        }
        while (!minHeap.empty()) {
            pair<int, int> cur = minHeap.top();
            minHeap.pop();
            int curTime = cur.first, varId = cur.second;
            if (curTime != dist[varId]) continue;
            for (int progId : useBy[varId]) {
                --remain[progId];
                if (remain[progId] != 0) continue;
                int endTime = curTime + runTime[progId];
                child[source[varId]].push_back(progId);
                for (int nextVar : output[progId]) {
                    if (endTime < dist[nextVar]) {
                        dist[nextVar] = endTime;
                        source[nextVar] = progId;
                        minHeap.push({endTime, nextVar});
                    }
                }
            }
        }
        cout << "Case " << ++caseId << ": ";
        if (dist[target] == inf) cout << "-1\n\n";
        else {
            string expr;
            expr.reserve(10000);
            buildExpr(0, child, expr);
            cout << dist[target] << ' ' << expr << "\n\n";
        }
    }
    return 0;
}
