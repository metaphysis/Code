#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

long long modPow(long long x, long long n) {
    long long ans = 1;
    while (n > 0) {
        if (n & 1) ans = ans * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ans;
}

long long solveRegion(int n, int k, int a, int b, vector<vector<int> > &graph, vector<vector<int> > &reverseGraph, vector<long long> &inv) {
    vector<char> visited(n + 1, 0);
    vector<int> order, stack, nextEdge(n + 1, 0);
    order.reserve(n);
    for (int start = 1; start <= n; start++) {
        if (visited[start]) continue;
        stack.push_back(start);
        visited[start] = 1;
        while (!stack.empty()) {
            int u = stack.back();
            if (nextEdge[u] < (int)graph[u].size()) {
                int v = graph[u][nextEdge[u]++];
                if (!visited[v]) {
                    visited[v] = 1;
                    stack.push_back(v);
                }
            } else {
                order.push_back(u);
                stack.pop_back();
            }
        }
    }
    fill(visited.begin(), visited.end(), 0);
    vector<int> sizes, componentStack;
    for (int i = n - 1; i >= 0; i--) {
        int start = order[i];
        if (visited[start]) continue;
        int size = 0;
        componentStack.push_back(start);
        visited[start] = 1;
        while (!componentStack.empty()) {
            int u = componentStack.back();
            componentStack.pop_back();
            size++;
            for (int v : reverseGraph[u]) {
                if (!visited[v]) {
                    visited[v] = 1;
                    componentStack.push_back(v);
                }
            }
        }
        sizes.push_back(size);
    }
    long long p = (long long)a * modPow(b, mod - 2) % mod;
    long long q = (long long)(b - a) * modPow(b, mod - 2) % mod;
    long long invQ = modPow(q, mod - 2);
    long long answer = 0;
    for (int size : sizes) {
        if (size < k) {
            answer = (answer + size * p) % mod;
            continue;
        }
        long long probability = modPow(q, size);
        long long probabilitySum = 0, truncatedSum = 0;
        for (int i = 0; i < k; i++) {
            probabilitySum = (probabilitySum + probability) % mod;
            truncatedSum = (truncatedSum + (long long)i * probability) % mod;
            if (i + 1 < k) {
                probability = probability * (size - i) % mod;
                probability = probability * inv[i + 1] % mod;
                probability = probability * p % mod;
                probability = probability * invQ % mod;
            }
        }
        long long tail = (1 - probabilitySum + mod) % mod;
        answer = (answer + (long long)size * tail + truncatedSum) % mod;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<long long> inv(2001, 0);
    inv[1] = 1;
    for (int i = 2; i <= 2000; i++) inv[i] = mod - mod / i * inv[mod % i] % mod;
    int testCases;
    cin >> testCases;
    for (int caseId = 1; caseId <= testCases; caseId++) {
        int regionCount, k, a, b;
        cin >> regionCount >> k >> a >> b;
        cout << "Case " << caseId << ":\n";
        for (int regionId = 1; regionId <= regionCount; regionId++) {
            int n, m;
            cin >> n >> m;
            vector<vector<int> > graph(n + 1), reverseGraph(n + 1);
            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                graph[u].push_back(v);
                reverseGraph[v].push_back(u);
            }
            long long answer = solveRegion(n, k, a, b, graph, reverseGraph, inv);
            cout << "Region " << regionId << ": " << answer << '\n';
        }
    }
    return 0;
}
