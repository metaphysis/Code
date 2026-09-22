#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id;
    char type;
};

struct Solution {
    int cnt = -1;
    vector<pair<int, char>> path;
};

using Matrix = vector<vector<Solution>>;

int n, m, limitLen;
vector<vector<Edge>> graph;
vector<Matrix> dp;
vector<int> fixedIn, fixedOut, fixedBest;

bool better(const Solution &a, const Solution &b) {
    if (a.cnt != b.cnt) return a.cnt > b.cnt;
    return a.path < b.path;
}

void update(Solution &a, const Solution &b) { if (better(b, a)) a = b; }

Matrix makeMatrix() { return Matrix(limitLen + 1, vector<Solution>(limitLen + 1)); }

Solution mergeSolution(const Solution &a, const Solution &b, int id = 0, char type = 0) {
    Solution result;
    result.cnt = a.cnt + b.cnt + (id != 0);
    result.path = a.path;
    result.path.insert(result.path.end(), b.path.begin(), b.path.end());
    if (id != 0) result.path.push_back({id, type});
    sort(result.path.begin(), result.path.end());
    return result;
}

void getFixedInfo(int u) {
    for (const Edge &e : graph[u]) {
        getFixedInfo(e.to);
        fixedBest[u] = max(fixedBest[u], fixedBest[e.to]);
        if (e.type == 'd') fixedOut[u] = max(fixedOut[u], fixedOut[e.to] + 1);
        else if (e.type == 'u') fixedIn[u] = max(fixedIn[u], fixedIn[e.to] + 1);
    }
    fixedBest[u] = max(fixedBest[u], fixedIn[u] + fixedOut[u]);
}

void solve(int u) {
    dp[u] = makeMatrix();
    dp[u][0][0].cnt = 0;
    for (const Edge &e : graph[u]) {
        int v = e.to;
        solve(v);
        Matrix bestD = makeMatrix();
        Matrix bestU = makeMatrix();
        Solution bestFree;
        for (int in = 0; in <= limitLen; ++in) {
            for (int out = 0; out + in <= limitLen; ++out) {
                if (dp[v][in][out].cnt == -1) continue;
                update(bestD[out][in], dp[v][in][out]);
                update(bestU[in][out], dp[v][in][out]);
                update(bestFree, dp[v][in][out]);
            }
        }
        for (int out = 0; out <= limitLen; ++out)
            for (int in = 1; in <= limitLen; ++in)
                update(bestD[out][in], bestD[out][in - 1]);
        for (int in = 0; in <= limitLen; ++in)
            for (int out = 1; out <= limitLen; ++out)
                update(bestU[in][out], bestU[in][out - 1]);
        Matrix next = makeMatrix();
        for (int in = 0; in <= limitLen; ++in) {
            for (int out = 0; in + out <= limitLen; ++out) {
                if (dp[u][in][out].cnt == -1) continue;
                const Solution &current = dp[u][in][out];
                if (e.type == 0) update(next[in][out], mergeSolution(current, bestFree));
                if (e.type == 0 || e.type == 'd') {
                    for (int childOut = 0; childOut < limitLen; ++childOut) {
                        int newOut = max(out, childOut + 1);
                        if (in + newOut > limitLen) continue;
                        if (bestD[childOut][limitLen].cnt == -1) continue;
                        update(next[in][newOut], mergeSolution(current, bestD[childOut][limitLen], e.id, 'd'));
                    }
                }
                if (e.type == 0 || e.type == 'u') {
                    for (int childIn = 0; childIn < limitLen; ++childIn) {
                        int newIn = max(in, childIn + 1);
                        if (newIn + out > limitLen) continue;
                        if (bestU[childIn][limitLen].cnt == -1) continue;
                        update(next[newIn][out], mergeSolution(current, bestU[childIn][limitLen], e.id, 'u'));
                    }
                }
            }
        }
        dp[u].swap(next);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 1;
    int root;
    while (cin >> root) {
        if (root == 0) continue;
        vector<tuple<int, int, char>> edges;
        n = 1;
        while (root != 0) {
            n = max(n, root);
            string token;
            while (cin >> token && token != "0") {
                int v = 0, pos = 0;
                while (pos < (int)token.size() && isdigit(token[pos])) {
                    v = v * 10 + token[pos] - '0';
                    ++pos;
                }
                char type = pos < (int)token.size() ? token[pos] : 0;
                edges.push_back({root, v, type});
                n = max(n, v);
            }
            cin >> root;
        }
        graph.assign(n + 1, {});
        m = 0;
        for (const auto &[u, v, type] : edges) {
            int id = type == 0 ? ++m : 0;
            graph[u].push_back({v, id, type});
        }
        fixedIn.assign(n + 1, 0);
        fixedOut.assign(n + 1, 0);
        fixedBest.assign(n + 1, 0);
        getFixedInfo(1);
        limitLen = fixedBest[1];
        dp.assign(n + 1, {});
        solve(1);
        Solution answer;
        for (int in = 0; in <= limitLen; ++in)
            for (int out = 0; in + out <= limitLen; ++out)
                update(answer, dp[1][in][out]);
        cout << "Case " << caseNumber++ << ": " << answer.cnt;
        for (const auto &[id, type] : answer.path) cout << " (" << id << "," << type << ")";
        cout << '\n';
    }
    return 0;
}
