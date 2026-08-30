#include <bits/stdc++.h>
using namespace std;

int nodeCount, edgeCount;
vector<vector<int> > graph;
vector<vector<bool> > reachable;
vector<int> matchRight;
vector<bool> visited;

bool findMatch(int node) {
    for (int nextNode = 0; nextNode < nodeCount; nextNode++) {
        if (!reachable[node][nextNode] || visited[nextNode])
            continue;
        visited[nextNode] = true;
        if (matchRight[nextNode] == -1 || findMatch(matchRight[nextNode])) {
            matchRight[nextNode] = node;
            return true;
        }
    }
    return false;
}

int solve() {
    int matchCount = 0;
    for (int midNode = 0; midNode < nodeCount; midNode++)
        for (int fromNode = 0; fromNode < nodeCount; fromNode++)
            if (reachable[fromNode][midNode])
                for (int toNode = 0; toNode < nodeCount; toNode++)
                    reachable[fromNode][toNode] = reachable[fromNode][toNode] || reachable[midNode][toNode];
    matchRight.assign(nodeCount, -1);
    visited.assign(nodeCount, false);
    for (int node = 0; node < nodeCount; node++) {
        fill(visited.begin(), visited.end(), false);
        if (findMatch(node))
            matchCount++;
    }
    return nodeCount - matchCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> nodeCount >> edgeCount) {
        reachable.assign(nodeCount, vector<bool>(nodeCount, false));
        int fromNode, toNode;
        for (int edgeIndex = 0; edgeIndex < edgeCount; edgeIndex++) {
            cin >> fromNode >> toNode;
            reachable[fromNode][toNode] = true;
        }
        cout << solve() << '\n';
    }
    return 0;
}
