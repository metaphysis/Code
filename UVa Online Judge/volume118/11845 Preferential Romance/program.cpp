#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to;
};

int getId(const string& name, unordered_map<string, int>& idMap, int& count) {
    if (!idMap.count(name)) idMap[name] = count++;
    return idMap[name];
}

void parseLine(string line, unordered_map<string, int>& idMap, int& count, vector<Edge>& edges) {
    string formatted, token, last;
    for (char ch : line) {
        if (ch == ',' || ch == ';') {
            formatted += ' ';
            formatted += ch;
            formatted += ' ';
        } else formatted += ch;
    }
    stringstream input(formatted);
    while (input >> token) {
        if (token == "," || token == ";") last.clear();
        else {
            int current = getId(token, idMap, count);
            if (!last.empty()) edges.push_back({getId(last, idMap, count), current});
            last = token;
        }
    }
}

bool isAcyclic(int vertexCount, const vector<Edge>& edges, int skip) {
    vector<int> indegree(vertexCount, 0), nextVertex(vertexCount);
    vector<vector<int>> graph(vertexCount);
    for (int i = 0; i < (int)edges.size(); i++) {
        if (i == skip) continue;
        graph[edges[i].from].push_back(edges[i].to);
        indegree[edges[i].to]++;
    }
    queue<int> ready;
    for (int i = 0; i < vertexCount; i++)
        if (indegree[i] == 0) ready.push(i);
    int visited = 0;
    while (!ready.empty()) {
        int current = ready.front();
        ready.pop();
        visited++;
        for (int next : graph[current])
            if (--indegree[next] == 0) ready.push(next);
    }
    return visited == vertexCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string nameA, nameB, lineA, lineB;
    while (cin >> nameA >> nameB) {
        getline(cin, lineA);
        if (nameA == "*" && nameB == "*") break;
        getline(cin, lineA);
        getline(cin, lineB);
        unordered_map<string, int> idMap;
        vector<Edge> edges;
        int vertexCount = 0;
        parseLine(lineA, idMap, vertexCount, edges);
        parseLine(lineB, idMap, vertexCount, edges);
        if (isAcyclic(vertexCount, edges, -1)) {
            cout << "F\n";
            continue;
        }
        bool passable = false;
        for (int i = 0; i < (int)edges.size(); i++)
            if (isAcyclic(vertexCount, edges, i)) {
                passable = true;
                break;
            }
        cout << (passable ? "P\n" : "N\n");
    }
    return 0;
}
