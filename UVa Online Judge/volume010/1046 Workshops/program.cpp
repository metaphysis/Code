// Workshops
// UVa ID: 1046
// Verdict: Accepted
// Submission Date: 2026-02-27
// UVa Run Time: 1.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Workshop {
    int participants;
    int duration;
};

struct Room {
    int seats;
    int availableTime;
};

bool canAssign(const Workshop &w, const Room &r) {
    return r.seats >= w.participants && r.availableTime >= w.duration;
}

bool dfs(int u, const vector<vector<int>> &adj, vector<int> &matchR, vector<bool> &seen) {
    for (int v : adj[u]) {
        if (!seen[v]) {
            seen[v] = true;
            if (matchR[v] == -1 || dfs(matchR[v], adj, matchR, seen)) {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int trial = 0, w, r;
    while (cin >> w, w) {
        trial++;
        
        vector<Workshop> workshops(w);
        for (int i = 0; i < w; i++)
            cin >> workshops[i].participants >> workshops[i].duration;
        
        cin >> r;
        vector<Room> rooms(r);
        for (int i = 0; i < r; i++) {
            int seats, hh, mm;
            char colon;
            cin >> seats >> hh >> colon >> mm;
            rooms[i].seats = seats;
            rooms[i].availableTime = (hh - 14) * 60 + mm;
        }
        
        // 构建邻接表
        vector<vector<int>> adj(w);
        for (int i = 0; i < w; i++)
            for (int j = 0; j < r; j++)
                if (canAssign(workshops[i], rooms[j]))
                    adj[i].push_back(j);
        
        // 按人数降序排序工作坊
        vector<int> order(w);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return workshops[a].participants > workshops[b].participants;
        });
        
        // 匈牙利算法求最大匹配
        vector<int> matchR(r, -1);
        int matched = 0;
        for (int u : order) {
            vector<bool> seen(r, false);
            if (dfs(u, adj, matchR, seen))
                matched++;
        }
        
        // 统计帐篷人数
        int tentWorkshops = w - matched;
        int tentParticipants = 0;
        vector<bool> used(w, false);
        for (int j = 0; j < r; j++)
            if (matchR[j] != -1)
                used[matchR[j]] = true;
        for (int i = 0; i < w; i++)
            if (!used[i])
                tentParticipants += workshops[i].participants;
        
        cout << "Trial " << trial << ": " << tentWorkshops << " " << tentParticipants << "\n\n";
    }
    return 0;
}

