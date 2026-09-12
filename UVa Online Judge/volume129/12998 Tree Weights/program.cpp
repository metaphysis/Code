#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;

class Fenwick {
private:
    int n;
    vector<long long> tree;
public:
    Fenwick(int size) : n(size), tree(size + 1, 0) {}
    void add(int pos, long long value) {
        value %= mod;
        if (value < 0) value += mod;
        for (int i = pos; i <= n; i += i & -i) {
            tree[i] += value;
            if (tree[i] >= mod) tree[i] -= mod;
        }
    }
    long long prefixSum(int pos) const {
        long long result = 0;
        for (int i = pos; i > 0; i -= i & -i) {
            result += tree[i];
            if (result >= mod) result -= mod;
        }
        return result;
    }
    long long rangeSum(int left, int right) const {
        long long result = prefixSum(right) - prefixSum(left - 1);
        if (result < 0) result += mod;
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    for (int caseId = 1; caseId <= testCases; ++caseId) {
        int n;
        cin >> n;
        vector<vector<int>> graph(n + 1);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<int> parent(n + 1, 0), depth(n + 1, 0), tin(n + 1, 0), tout(n + 1, 0), childCount(n + 1, 0);
        vector<pair<int, int>> dfsStack;
        dfsStack.push_back({1, 0});
        int timer = 0;
        while (!dfsStack.empty()) {
            int u = dfsStack.back().first;
            int &edgeIndex = dfsStack.back().second;
            if (edgeIndex == 0) tin[u] = ++timer;
            if (edgeIndex < static_cast<int>(graph[u].size())) {
                int v = graph[u][edgeIndex++];
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                ++childCount[u];
                dfsStack.push_back({v, 0});
            } else {
                tout[u] = timer;
                dfsStack.pop_back();
            }
        }
        vector<bool> isLeaf(n + 1, false);
        for (int u = 1; u <= n; ++u) isLeaf[u] = childCount[u] == 0;
        vector<long long> power2(n + 1, 1), inversePower2(n + 1, 1);
        long long inverseTwo = (mod + 1) / 2;
        for (int i = 1; i <= n; ++i) {
            power2[i] = power2[i - 1] * 2 % mod;
            inversePower2[i] = inversePower2[i - 1] * inverseTwo % mod;
        }
        Fenwick bit(n);
        int operations;
        cin >> operations;
        cout << "Case " << caseId << ":\n";
        while (operations--) {
            int type, u;
            cin >> type >> u;
            if (type == 1) {
                long long total = bit.rangeSum(tin[u], tout[u]);
                long long answer;
                if (isLeaf[u]) answer = total * inversePower2[depth[u]] % mod;
                else answer = total * inversePower2[depth[u] + 1] % mod;
                cout << answer << '\n';
            } else {
                long long x;
                cin >> x;
                x %= mod;
                if (x < 0) x += mod;
                bit.add(tin[u], x * power2[depth[u]] % mod);
            }
        }
    }
    return 0;
}
