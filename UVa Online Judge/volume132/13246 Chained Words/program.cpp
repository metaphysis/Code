#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id;
};

bool isConnected(const vector<vector<Edge>> &adj, const vector<int> &inDeg, const vector<int> &outDeg) {
    vector<vector<int>> graph(26);
    vector<int> visited(26, 0), stackNode;
    int start = -1;
    for (int i = 0; i < 26; ++i) {
        if (inDeg[i] + outDeg[i] > 0) {
            start = i;
            break;
        }
    }
    for (int i = 0; i < 26; ++i)
        for (const Edge &edge : adj[i]) {
            graph[i].push_back(edge.to);
            graph[edge.to].push_back(i);
        }
    stackNode.push_back(start);
    visited[start] = 1;
    while (!stackNode.empty()) {
        int node = stackNode.back();
        stackNode.pop_back();
        for (int next : graph[node])
            if (!visited[next]) {
                visited[next] = 1;
                stackNode.push_back(next);
            }
    }
    for (int i = 0; i < 26; ++i)
        if (inDeg[i] + outDeg[i] > 0 && !visited[i])
            return false;
    return true;
}

void solveCase() {
    int wordCount;
    cin >> wordCount;
    vector<string> words(wordCount);
    vector<vector<Edge>> adj(26);
    vector<int> inDeg(26, 0), outDeg(26, 0);
    for (int i = 0; i < wordCount; ++i) {
        cin >> words[i];
        int from = words[i].front() - 'a', to = words[i].back() - 'a';
        adj[from].push_back({to, i});
        ++outDeg[from];
        ++inDeg[to];
    }
    for (int i = 0; i < 26; ++i)
        sort(adj[i].begin(), adj[i].end(), [&words](const Edge &left, const Edge &right) {
            if (words[left.id] != words[right.id])
                return words[left.id] < words[right.id];
            return left.id < right.id;
        });
    for (int i = 0; i < 26; ++i)
        if (inDeg[i] != outDeg[i]) {
            cout << "No way\n";
            return;
        }
    if (!isConnected(adj, inDeg, outDeg)) {
        cout << "No way\n";
        return;
    }
    int firstId = 0;
    for (int i = 1; i < wordCount; ++i)
        if (words[i] < words[firstId])
            firstId = i;
    int firstFrom = words[firstId].front() - 'a', firstTo = words[firstId].back() - 'a';
    vector<int> used(wordCount, 0), position(26, 0), stackNode, stackEdge, postOrder, answer;
    used[firstId] = 1;
    stackNode.push_back(firstTo);
    while (!stackNode.empty()) {
        int node = stackNode.back();
        while (position[node] < (int)adj[node].size() && used[adj[node][position[node]].id])
            ++position[node];
        if (position[node] < (int)adj[node].size()) {
            Edge edge = adj[node][position[node]++];
            used[edge.id] = 1;
            stackNode.push_back(edge.to);
            stackEdge.push_back(edge.id);
        } else {
            stackNode.pop_back();
            if (!stackEdge.empty()) {
                postOrder.push_back(stackEdge.back());
                stackEdge.pop_back();
            }
        }
    }
    if ((int)postOrder.size() != wordCount - 1) {
        cout << "No way\n";
        return;
    }
    answer.push_back(firstId);
    for (auto it = postOrder.rbegin(); it != postOrder.rend(); ++it)
        answer.push_back(*it);
    for (int i = 0; i < wordCount; ++i) {
        if (i > 0)
            cout << ' ';
        cout << words[answer[i]];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--)
        solveCase();
    return 0;
}
