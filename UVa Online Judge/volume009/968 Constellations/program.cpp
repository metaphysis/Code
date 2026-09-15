#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
    vector<int> parent, rankValue;

    int addNode() {
        int id = parent.size();
        parent.push_back(id);
        rankValue.push_back(0);
        return id;
    }

    int findRoot(int node) {
        if (parent[node] != node) parent[node] = findRoot(parent[node]);
        return parent[node];
    }

    bool unite(int first, int second) {
        int rootFirst = findRoot(first), rootSecond = findRoot(second);
        if (rootFirst == rootSecond) return false;
        if (rankValue[rootFirst] < rankValue[rootSecond]) swap(rootFirst, rootSecond);
        parent[rootSecond] = rootFirst;
        if (rankValue[rootFirst] == rankValue[rootSecond]) rankValue[rootFirst]++;
        return true;
    }
};

int getNode(int x, int y, map<pair<int, int>, int> &nodeMap, DisjointSet &disjointSet, int &constellationCount) {
    pair<int, int> point = make_pair(x, y);
    map<pair<int, int>, int>::iterator iterator = nodeMap.find(point);
    if (iterator != nodeMap.end()) return iterator->second;
    int node = disjointSet.addNode();
    nodeMap[point] = node;
    constellationCount++;
    return node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        map<pair<int, int>, int> nodeMap;
        DisjointSet disjointSet;
        int constellationCount = 0;
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int firstNode = getNode(x1, y1, nodeMap, disjointSet, constellationCount);
            int secondNode = getNode(x2, y2, nodeMap, disjointSet, constellationCount);
            if (disjointSet.unite(firstNode, secondNode)) constellationCount--;
        }
        cout << constellationCount << '\n';
    }
    return 0;
}
