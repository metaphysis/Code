#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<int> isoVal, oneVal, twoVal, bestVal;

void dfs(int u, int parent) {
    int isoSum = 0, baseSum = 0, firstGain = 0, secondGain = 0, leafGain = 0;
    for (int v : graph[u]) {
        if (v == parent) continue;
        dfs(v, u);
        int base = max(bestVal[v], 1 + isoVal[v]), gain = 1 + oneVal[v] - base;
        isoSum += bestVal[v];
        baseSum += base;
        if (gain > firstGain) {
            secondGain = firstGain;
            firstGain = gain;
        } else if (gain > secondGain) secondGain = gain;
        leafGain = max(leafGain, 1 + twoVal[v] - bestVal[v]);
    }
    isoVal[u] = isoSum;
    oneVal[u] = baseSum + firstGain;
    twoVal[u] = baseSum + firstGain + secondGain;
    bestVal[u] = max(twoVal[u], isoSum + leafGain);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNum = 0;
    while (cin >> n && n != 0) {
        unordered_map<string, int> idMap;
        string name;
        for (int i = 0; i < n; i++) {
            cin >> name;
            idMap[name] = i;
        }
        graph.assign(n, vector<int>());
        isoVal.assign(n, 0);
        oneVal.assign(n, 0);
        twoVal.assign(n, 0);
        bestVal.assign(n, -1);
        int e, answer = 0;
        cin >> e;
        for (int i = 0; i < e; i++) {
            string firstName, secondName;
            cin >> firstName >> secondName;
            int u = idMap[firstName], v = idMap[secondName];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            if (bestVal[i] != -1) continue;
            dfs(i, -1);
            answer += bestVal[i];
        }
        cout << "Case " << ++caseNum << ": " << answer << '\n';
    }
    return 0;
}
