#include <bits/stdc++.h>
using namespace std;

bool buildTree(const vector<int> &seq, vector<vector<int>> &graph) {
    int vertexCount = seq.size() + 2;
    vector<int> degree(vertexCount, 1);
    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int value : seq) {
        if (value < 0 || value >= vertexCount) return false;
        degree[value]++;
    }
    for (int i = 0; i < vertexCount; i++)
        if (degree[i] == 1) leaves.push(i);
    for (int value : seq) {
        if (leaves.empty()) return false;
        int leaf = leaves.top();
        leaves.pop();
        graph[leaf].push_back(value);
        graph[value].push_back(leaf);
        degree[leaf]--;
        degree[value]--;
        if (degree[value] == 1) leaves.push(value);
    }
    if (leaves.size() != 2) return false;
    int first = leaves.top();
    leaves.pop();
    int second = leaves.top();
    graph[first].push_back(second);
    graph[second].push_back(first);
    for (vector<int> &adjacency : graph)
        sort(adjacency.begin(), adjacency.end());
    return true;
}

void printTree(const vector<vector<int>> &graph) {
    cout << graph.size() << '\n';
    for (const vector<int> &adjacency : graph) {
        for (int i = 0; i < (int)adjacency.size(); i++) {
            if (i > 0) cout << ' ';
            cout << adjacency[i];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    bool firstCase = true;
    while (getline(cin, line)) {
        stringstream input(line);
        vector<int> seq;
        int value;
        while (input >> value) seq.push_back(value);
        if (seq.empty()) continue;
        if (!firstCase) cout << "*\n";
        firstCase = false;
        vector<vector<int>> graph(seq.size() + 2);
        if (buildTree(seq, graph))
            printTree(graph);
        else
            cout << "impossible\n";
    }
    return 0;
}
