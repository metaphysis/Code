// DRM
// UVa ID: 11336
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

// 读取地图，返回 (id, 地点集合, 街道集合)
tuple<string, unordered_set<string>, set<pair<string, string>>> readMap() {
    string id;
    cin >> id;
    unordered_set<string> places;
    set<pair<string, string>> streets;
    string a, b;
    while (cin >> a) {
        if (a == "*") {
            cin >> b; // 第二个 *
            cin >> b; // 第三个 *
            break;
        }
        cin >> b;
        places.insert(a);
        places.insert(b);
        if (a > b) swap(a, b);
        streets.insert({a, b});
    }
    return {id, places, streets};
}

int main() {
    while (true) {
        auto [id1, oldPlaces, oldStreets] = readMap();
        if (id1 == "END") break;
        auto [id2, newPlaces, newStreets] = readMap();
        
        // 条件1：新地点必须包含所有旧地点
        bool ok = true;
        for (const string& p : oldPlaces) 
            if (newPlaces.find(p) == newPlaces.end()) { ok = false; break; }
        
        if (!ok) {
            cout << "NO: " << id2 << " is not a more detailed version of " << id1 << "\n";
            continue;
        }
        
        // 构建新地图的邻接表
        unordered_map<string, vector<string>> newAdj;
        for (auto& e : newStreets) {
            newAdj[e.first].push_back(e.second);
            newAdj[e.second].push_back(e.first);
        }
        
        // 条件2：检查旧地图的每条街道
        for (auto& e : oldStreets) {
            string u = e.first, v = e.second;
            // BFS 从 u 到 v，只允许经过新地点（但 u 和 v 本身允许是旧地点）
            unordered_set<string> visited;
            queue<string> q;
            q.push(u);
            visited.insert(u);
            bool reachable = false;
            while (!q.empty()) {
                string cur = q.front(); q.pop();
                if (cur == v) { reachable = true; break; }
                for (string nxt : newAdj[cur]) {
                    if (visited.count(nxt)) continue;
                    // 中间节点必须是新地点（不在 oldPlaces 中），或者就是终点 v
                    if (nxt != v && oldPlaces.count(nxt)) continue;
                    visited.insert(nxt);
                    q.push(nxt);
                }
            }
            if (!reachable) { ok = false; break; }
        }
        
        if (ok) cout << "YES: " << id2 << " is a more detailed version of " << id1 << "\n";
        else cout << "NO: " << id2 << " is not a more detailed version of " << id1 << "\n";
    }
    return 0;
}
