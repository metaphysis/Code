#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    unsigned long long weight;
};

void addBasis(unsigned long long value, unsigned long long basis[]) {
    for (int i = 60; i >= 0; --i) {
        if (((value >> i) & 1ULL) == 0) continue;
        if (basis[i] == 0) {
            basis[i] = value;
            return;
        }
        value ^= basis[i];
    }
}

unsigned long long getMaxXor(unsigned long long basis[]) {
    unsigned long long result = 0;
    for (int i = 60; i >= 0; --i)
        if ((result ^ basis[i]) > result) result ^= basis[i];
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        int n, m;
        cin >> n >> m;
        vector<vector<Edge>> graph(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            unsigned long long w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        vector<int> visited(n + 1, 0), stack;
        vector<unsigned long long> distance(n + 1, 0);
        unsigned long long basis[61] = {};
        visited[1] = 1;
        stack.push_back(1);
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (const Edge &edge : graph[u]) {
                int v = edge.to;
                if (!visited[v]) {
                    visited[v] = 1;
                    distance[v] = distance[u] ^ edge.weight;
                    stack.push_back(v);
                } else {
                    unsigned long long cycleValue = distance[u] ^ distance[v] ^ edge.weight;
                    addBasis(cycleValue, basis);
                }
            }
        }
        cout << "Case #" << caseId << ": " << getMaxXor(basis) << '\n';
    }
    return 0;
}
