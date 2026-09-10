#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
    vector<int> father, rankValue;
    DisjointSet(int n) {
        father.resize(n);
        rankValue.assign(n, 0);
        iota(father.begin(), father.end(), 0);
    }
    int find(int x) {
        if (father[x] == x) return x;
        return father[x] = find(father[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rankValue[x] < rankValue[y]) swap(x, y);
        father[y] = x;
        if (rankValue[x] == rankValue[y]) rankValue[x]++;
    }
};

int categoryCount, attractionCount, timerValue;
vector<vector<pair<int, int>>> graphData;
vector<int> firstCategory, secondCategory, degreeValue, dfn, low;
vector<bool> isBridge;

void tarjan(int u, int parentEdge) {
    dfn[u] = low[u] = ++timerValue;
    for (const auto &item : graphData[u]) {
        int v = item.first, edgeId = item.second;
        if (edgeId == parentEdge) continue;
        if (!dfn[v]) {
            tarjan(v, edgeId);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) isBridge[edgeId] = true;
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

bool isConnected() {
    int root = -1;
    for (int i = 0; i < categoryCount; i++)
        if (degreeValue[i] > 0) {
            root = i;
            break;
        }
    if (root == -1) return false;
    DisjointSet disjointSet(categoryCount);
    for (int i = 0; i < attractionCount; i++)
        disjointSet.unite(firstCategory[i], secondCategory[i]);
    int rootFather = disjointSet.find(root);
    for (int i = 0; i < categoryCount; i++)
        if (degreeValue[i] > 0 && disjointSet.find(i) != rootFather) return false;
    return true;
}

int solve() {
    if (!isConnected()) return -1;
    dfn.assign(categoryCount, 0);
    low.assign(categoryCount, 0);
    isBridge.assign(attractionCount, false);
    timerValue = 0;
    for (int i = 0; i < categoryCount; i++)
        if (degreeValue[i] > 0 && !dfn[i]) tarjan(i, -1);
    vector<int> oddCategories;
    for (int i = 0; i < categoryCount; i++)
        if (degreeValue[i] % 2 == 1) oddCategories.push_back(i);
    if (oddCategories.size() != 0 && oddCategories.size() != 2) return -1;
    if (oddCategories.empty()) return 0;
    for (int i = 0; i < attractionCount; i++) {
        int u = firstCategory[i], v = secondCategory[i];
        bool touchesOdd = (degreeValue[u] % 2 == 1) || (degreeValue[v] % 2 == 1);
        bool hasLeafEndpoint = degreeValue[u] == 1 || degreeValue[v] == 1;
        if (touchesOdd && (!isBridge[i] || hasLeafEndpoint)) return i;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> attractionCount >> categoryCount) {
        graphData.assign(categoryCount, vector<pair<int, int>>());
        firstCategory.assign(attractionCount, -1);
        secondCategory.assign(attractionCount, -1);
        degreeValue.assign(categoryCount, 0);
        for (int category = 0; category < categoryCount; category++) {
            int count;
            cin >> count;
            for (int j = 0; j < count; j++) {
                int attraction;
                cin >> attraction;
                if (firstCategory[attraction] == -1) firstCategory[attraction] = category;
                else secondCategory[attraction] = category;
            }
        }
        for (int i = 0; i < attractionCount; i++) {
            if (secondCategory[i] == -1) secondCategory[i] = firstCategory[i];
            int u = firstCategory[i], v = secondCategory[i];
            if (u == v) {
                degreeValue[u] += 2;
                graphData[u].push_back({v, i});
            } else {
                degreeValue[u]++;
                degreeValue[v]++;
                graphData[u].push_back({v, i});
                graphData[v].push_back({u, i});
            }
        }
        cout << solve() << '\n';
    }
    return 0;
}
