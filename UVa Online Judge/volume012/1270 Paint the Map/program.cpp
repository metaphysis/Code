// Paint the Map
// UVa ID: 1270
// Verdict: Accepted
// Submission Date: 2026-10-16
// UVa Run Time: 0.500s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int getCountryId(const string &name, unordered_map<string, int> &idMap, vector<string> &names, vector<vector<int>> &graph) {
    auto it = idMap.find(name);
    if (it != idMap.end()) return it->second;
    int id = names.size();
    idMap[name] = id;
    names.push_back(name);
    graph.push_back(vector<int>());
    return id;
}

int chooseVertex(const vector<vector<int>> &graph, const vector<int> &colors) {
    int n = graph.size(), bestVertex = -1, bestSat = -1, bestDegree = -1;
    for (int i = 0; i < n; i++) {
        if (colors[i] != -1) continue;
        bool used[5] = {};
        for (int next : graph[i]) if (colors[next] != -1) used[colors[next]] = true;
        int sat = 0, degree = graph[i].size();
        for (int color = 0; color < 5; color++) if (used[color]) sat++;
        if (sat > bestSat || (sat == bestSat && degree > bestDegree)) {
            bestVertex = i;
            bestSat = sat;
            bestDegree = degree;
        }
    }
    return bestVertex;
}

bool dfsColoring(const vector<vector<int>> &graph, vector<int> &colors, int coloredCount, int usedCount) {
    int n = graph.size();
    if (coloredCount == n) return true;
    int vertex = chooseVertex(graph, colors);
    bool forbidden[5] = {};
    for (int next : graph[vertex]) if (colors[next] != -1) forbidden[colors[next]] = true;
    int limit = min(5, usedCount + 1);
    for (int color = 0; color < limit; color++) {
        if (forbidden[color]) continue;
        colors[vertex] = color;
        if (dfsColoring(graph, colors, coloredCount + 1, max(usedCount, color + 1))) return true;
        colors[vertex] = -1;
    }
    return false;
}

void solveMap(const vector<string> &lines, int mapCount) {
    unordered_map<string, int> idMap;
    vector<string> names;
    vector<vector<int>> graph;
    vector<pair<int, int>> edges;
    for (const string &line : lines) {
        string country, neighbor;
        stringstream ss(line);
        if (!(ss >> country)) continue;
        int u = getCountryId(country, idMap, names, graph);
        while (ss >> neighbor) {
            int v = getCountryId(neighbor, idMap, names, graph);
            if (u != v) edges.emplace_back(min(u, v), max(u, v));
        }
    }
    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());
    for (const auto &edge : edges) {
        int u = edge.first, v = edge.second;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> colors(names.size(), -1);
    cout << "Map #" << mapCount << '\n';
    if (dfsColoring(graph, colors, 0, 0)) {
        vector<int> order(names.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return names[a] < names[b];
        });
        const vector<string> colorNames = {"Blue", "Green", "Pink", "Red", "Yellow"};
        for (int index : order) cout << names[index] << ' ' << colorNames[colors[index]] << '\n';
    } else {
        cout << "Impossible\n";
    }
    // 如果按照题目描述的要求，在每组测试数据的输出之后输出一个空行会导致在线测试特判器工作不正常，从而无法通过
    // 为了通过测试，不能输出空行，这是在线特殊评判程序对输出格式的要求与题目描述不一致所致。
    //cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int mapCount = 0;
    string line, first;
    vector<string> lines;
    while (getline(cin, line)) {
        stringstream ss(line);
        if (!(ss >> first)) continue;
        if (first == "END") break;
        if (first == "#") {
            if (!lines.empty()) solveMap(lines, ++mapCount);
            lines.clear();
        } else {
            lines.push_back(line);
        }
    }
    if (!lines.empty()) solveMap(lines, ++mapCount);
    return 0;
}
