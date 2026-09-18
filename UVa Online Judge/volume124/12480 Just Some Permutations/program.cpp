#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> answers[20];
vector<int> graph[20], path;
bool visited[20];
int n;

void dfs(int current) {
    visited[current] = true;
    path.push_back(current);
    for (int next : graph[current])
        if (!visited[next]) dfs(next);
}

void addAnswer() {
    path.clear();
    int start = -1;
    for (int value = 1; value <= n; value++) {
        if (graph[value].size() == 1) {
            start = value;
            break;
        }
    }
    if (start == -1) return;
    memset(visited, false, sizeof(visited));
    dfs(start);
    if (static_cast<int>(path.size()) != n) return;
    answers[n].push_back(path);
    reverse(path.begin(), path.end());
    answers[n].push_back(path);
}

void enumerateGraphs(int diff) {
    if (diff == 0) {
        addAnswer();
        return;
    }
    for (int left = 1; left + diff <= n; left++) {
        int right = left + diff;
        if (graph[left].size() >= 2 || graph[right].size() >= 2) continue;
        graph[left].push_back(right);
        graph[right].push_back(left);
        enumerateGraphs(diff - 1);
        graph[left].pop_back();
        graph[right].pop_back();
    }
}

void initialize() {
    for (n = 2; n < 20; n++) {
        for (int value = 1; value <= n; value++) graph[value].clear();
        enumerateGraphs(n - 1);
        sort(answers[n].begin(), answers[n].end());
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initialize();
    int testCount;
    cin >> testCount;
    for (int caseNumber = 1; caseNumber <= testCount; caseNumber++) {
        int size, rank;
        cin >> size >> rank;
        cout << "Case " << caseNumber << ":";
        if (rank > static_cast<int>(answers[size].size())) {
            cout << " -1\n";
        } else {
            for (int value : answers[size][rank - 1]) cout << " " << value;
            cout << '\n';
        }
    }
    return 0;
}
