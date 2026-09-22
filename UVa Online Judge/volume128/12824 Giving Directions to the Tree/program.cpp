#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id;
    char type;
};

struct Solution {
    int cnt;
    vector<pair<int, char>> path;
};

int nodeCount, edgeCount, limitLen;
vector<vector<Edge>> treeGraph;
vector<vector<vector<Solution>>> dp;
vector<int> fixedInLen, fixedOutLen, fixedBestLen;

bool betterSolution(const Solution &a, const Solution &b) {
    if (a.cnt != b.cnt)
        return a.cnt > b.cnt;
    return a.path < b.path;
}

Solution mergeSolution(const Solution &a, const Solution &b, int edgeId, char edgeType) {
    Solution result;
    result.cnt = a.cnt + b.cnt + (edgeId == 0 ? 0 : 1);
    result.path.reserve(a.path.size() + b.path.size() + (edgeId == 0 ? 0 : 1));
    vector<pair<int, char>> extra;
    if (edgeId != 0)
        extra.push_back(make_pair(edgeId, edgeType));
    int i = 0, j = 0, k = 0;
    while (i < (int)a.path.size() || j < (int)b.path.size() || k < (int)extra.size()) {
        pair<int, char> current;
        bool hasA = i < (int)a.path.size();
        bool hasB = j < (int)b.path.size();
        bool hasC = k < (int)extra.size();
        if (hasA)
            current = a.path[i];
        else if (hasB)
            current = b.path[j];
        else
            current = extra[k];
        if (hasB && b.path[j] < current)
            current = b.path[j];
        if (hasC && extra[k] < current)
            current = extra[k];
        result.path.push_back(current);
        if (hasA && a.path[i] == current)
            ++i;
        if (hasB && b.path[j] == current)
            ++j;
        if (hasC && extra[k] == current)
            ++k;
    }
    return result;
}

void updateSolution(Solution &target, const Solution &candidate) {
    if (betterSolution(candidate, target))
        target = candidate;
}

void initSolutions(vector<vector<Solution>> &solutions) {
    for (int i = 0; i < (int)solutions.size(); ++i)
        for (int j = 0; j < (int)solutions[i].size(); ++j)
            solutions[i][j].cnt = -1;
}

void getFixedInfo(int u) {
    fixedInLen[u] = 0;
    fixedOutLen[u] = 0;
    fixedBestLen[u] = 0;
    for (const Edge &edge : treeGraph[u]) {
        int v = edge.to;
        getFixedInfo(v);
        fixedBestLen[u] = max(fixedBestLen[u], fixedBestLen[v]);
        if (edge.type == 'd')
            fixedOutLen[u] = max(fixedOutLen[u], fixedOutLen[v] + 1);
        else if (edge.type == 'u')
            fixedInLen[u] = max(fixedInLen[u], fixedInLen[v] + 1);
    }
    fixedBestLen[u] = max(fixedBestLen[u], fixedInLen[u] + fixedOutLen[u]);
}

void solveDp(int u) {
    dp[u].assign(limitLen + 1, vector<Solution>(limitLen + 1));
    for (int i = 0; i <= limitLen; ++i)
        for (int j = 0; j <= limitLen; ++j)
            dp[u][i][j].cnt = -1;
    dp[u][0][0].cnt = 0;
    for (const Edge &edge : treeGraph[u]) {
        int v = edge.to;
        solveDp(v);
        vector<vector<Solution>> bestD(limitLen + 1, vector<Solution>(limitLen + 1));
        vector<vector<Solution>> bestU(limitLen + 1, vector<Solution>(limitLen + 1));
        initSolutions(bestD);
        initSolutions(bestU);
        Solution bestFree;
        bestFree.cnt = -1;
        for (int childIn = 0; childIn <= limitLen; ++childIn) {
            for (int childOut = 0; childOut <= limitLen - childIn; ++childOut) {
                if (dp[v][childIn][childOut].cnt == -1)
                    continue;
                updateSolution(bestD[childOut][childIn], dp[v][childIn][childOut]);
                updateSolution(bestU[childIn][childOut], dp[v][childIn][childOut]);
                updateSolution(bestFree, dp[v][childIn][childOut]);
            }
        }
        for (int childOut = 0; childOut <= limitLen; ++childOut)
            for (int childIn = 1; childIn <= limitLen; ++childIn)
                updateSolution(bestD[childOut][childIn], bestD[childOut][childIn - 1]);
        for (int childIn = 0; childIn <= limitLen; ++childIn)
            for (int childOut = 1; childOut <= limitLen; ++childOut)
                updateSolution(bestU[childIn][childOut], bestU[childIn][childOut - 1]);
        vector<vector<Solution>> nextDp(limitLen + 1, vector<Solution>(limitLen + 1));
        initSolutions(nextDp);
        for (int inLen = 0; inLen <= limitLen; ++inLen) {
            for (int outLen = 0; outLen <= limitLen - inLen; ++outLen) {
                if (dp[u][inLen][outLen].cnt == -1)
                    continue;
                const Solution &current = dp[u][inLen][outLen];
                if (edge.type == 0) {
                    Solution candidate = mergeSolution(current, bestFree, 0, 0);
                    updateSolution(nextDp[inLen][outLen], candidate);
                }
                if (edge.type == 0 || edge.type == 'd') {
                    for (int childOut = 0; childOut < limitLen; ++childOut) {
                        int newOut = max(outLen, childOut + 1);
                        if (inLen + newOut > limitLen)
                            continue;
                        if (bestD[childOut][limitLen].cnt == -1)
                            continue;
                        Solution candidate = mergeSolution(current, bestD[childOut][limitLen], edge.id, 'd');
                        updateSolution(nextDp[inLen][newOut], candidate);
                    }
                }
                if (edge.type == 0 || edge.type == 'u') {
                    for (int childIn = 0; childIn < limitLen; ++childIn) {
                        int newIn = max(inLen, childIn + 1);
                        if (newIn + outLen > limitLen)
                            continue;
                        if (bestU[childIn][limitLen].cnt == -1)
                            continue;
                        Solution candidate = mergeSolution(current, bestU[childIn][limitLen], edge.id, 'u');
                        updateSolution(nextDp[newIn][outLen], candidate);
                    }
                }
            }
        }
        dp[u].swap(nextDp);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 1;
    while (true) {
        vector<tuple<int, int, char>> inputEdges;
        vector<int> describedNodes;
        int u;
        if (!(cin >> u))
            break;
        if (u == 0)
            continue;
        while (u != 0) {
            describedNodes.push_back(u);
            string token;
            while (cin >> token) {
                if (token == "0")
                    break;
                int v = 0, pos = 0;
                while (pos < (int)token.size() && isdigit(token[pos])) {
                    v = v * 10 + token[pos] - '0';
                    ++pos;
                }
                char type = 0;
                if (pos < (int)token.size())
                    type = token[pos];
                inputEdges.push_back(make_tuple(u, v, type));
            }
            cin >> u;
        }
        nodeCount = 1;
        for (const auto &item : inputEdges) {
            nodeCount = max(nodeCount, get<0>(item));
            nodeCount = max(nodeCount, get<1>(item));
        }
        for (int x : describedNodes)
            nodeCount = max(nodeCount, x);
        treeGraph.assign(nodeCount + 1, vector<Edge>());
        edgeCount = 0;
        for (const auto &item : inputEdges) {
            int from = get<0>(item);
            int to = get<1>(item);
            char type = get<2>(item);
            int id = 0;
            if (type == 0)
                id = ++edgeCount;
            treeGraph[from].push_back({to, id, type});
        }
        fixedInLen.assign(nodeCount + 1, 0);
        fixedOutLen.assign(nodeCount + 1, 0);
        fixedBestLen.assign(nodeCount + 1, 0);
        getFixedInfo(1);
        limitLen = fixedBestLen[1];
        dp.assign(nodeCount + 1, vector<vector<Solution>>());
        solveDp(1);
        Solution answer;
        answer.cnt = -1;
        for (int inLen = 0; inLen <= limitLen; ++inLen)
            for (int outLen = 0; outLen <= limitLen - inLen; ++outLen)
                updateSolution(answer, dp[1][inLen][outLen]);
        cout << "Case " << caseNumber++ << ": " << answer.cnt;
        for (const auto &item : answer.path)
            cout << " (" << item.first << "," << item.second << ")";
        cout << '\n';
    }
    return 0;
}
