#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to, minute, time, delay;
    double prob;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        string startName, targetName;
        cin >> startName >> targetName;
        int n;
        cin >> n;
        unordered_map<string, int> id;
        vector<Edge> edges;
        vector<vector<int>> out, rev;
        auto getId = [&](const string &name) {
            if (!id.count(name)) {
                int now = (int)id.size();
                id[name] = now;
                out.push_back({});
                rev.push_back({});
            }
            return id[name];
        };
        int start = getId(startName), target = getId(targetName);
        for (int i = 0; i < n; i++) {
            string fromName, toName;
            int minute, time, percent, delay;
            cin >> fromName >> toName >> minute >> time >> percent >> delay;
            int from = getId(fromName), to = getId(toName);
            int edgeId = (int)edges.size();
            edges.push_back({from, to, minute, time, delay, percent / 100.0});
            out[from].push_back(edgeId);
            rev[to].push_back(edgeId);
        }
        int cityCount = (int)id.size();
        vector<int> rank(cityCount, -1), parent(cityCount, -1);
        queue<int> que;
        rank[target] = 0;
        que.push(target);
        while (!que.empty()) {
            int city = que.front();
            que.pop();
            for (int edgeId : rev[city]) {
                int prev = edges[edgeId].from;
                if (rank[prev] != -1) continue;
                rank[prev] = rank[city] + 1;
                parent[prev] = edgeId;
                que.push(prev);
            }
        }
        if (rank[start] == -1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        int maxRank = *max_element(rank.begin(), rank.end());
        vector<vector<int>> level(maxRank + 1);
        for (int i = 0; i < cityCount; i++)
            if (rank[i] >= 0) level[rank[i]].push_back(i);
        vector<array<double, 60>> value(cityCount), nextValue(cityCount);
        for (int i = 0; i < cityCount; i++)
            for (int j = 0; j < 60; j++) value[i][j] = 1e100;
        for (int j = 0; j < 60; j++) value[target][j] = 0.0;
        for (int curRank = 1; curRank <= maxRank; curRank++) {
            for (int city : level[curRank]) {
                Edge &edge = edges[parent[city]];
                int base = (edge.minute + edge.time) % 60;
                double after = (1.0 - edge.prob) * value[edge.to][base];
                if (edge.prob > 0.0) {
                    double sum = 0.0;
                    for (int k = 1; k <= edge.delay; k++) sum += value[edge.to][(base + k) % 60];
                    after += edge.prob * (sum / edge.delay + (edge.delay + 1) / 2.0);
                }
                for (int phase = 0; phase < 60; phase++) {
                    int wait = (edge.minute - phase + 60) % 60;
                    value[city][phase] = wait + edge.time + after;
                }
            }
        }
        while (true) {
            vector<vector<double>> prefix(cityCount, vector<double>(181, 0.0));
            for (int city = 0; city < cityCount; city++) {
                if (rank[city] == -1) continue;
                for (int i = 0; i < 180; i++) prefix[city][i + 1] = prefix[city][i] + value[city][i % 60];
            }
            double change = 0.0, scale = 1.0;
            for (int city = 0; city < cityCount; city++) {
                if (rank[city] == -1) continue;
                if (city == target) {
                    for (int phase = 0; phase < 60; phase++) nextValue[city][phase] = 0.0;
                    continue;
                }
                for (int phase = 0; phase < 60; phase++) nextValue[city][phase] = 1e100;
                for (int edgeId : out[city]) {
                    Edge &edge = edges[edgeId];
                    if (rank[edge.to] == -1) continue;
                    int base = (edge.minute + edge.time) % 60;
                    double after = (1.0 - edge.prob) * value[edge.to][base];
                    if (edge.prob > 0.0) {
                        double sum = prefix[edge.to][base + edge.delay + 1] - prefix[edge.to][base + 1];
                        after += edge.prob * (sum / edge.delay + (edge.delay + 1) / 2.0);
                    }
                    double cost = edge.time + after;
                    for (int phase = 0; phase < 60; phase++) {
                        int wait = (edge.minute - phase + 60) % 60;
                        nextValue[city][phase] = min(nextValue[city][phase], wait + cost);
                    }
                }
            }
            for (int city = 0; city < cityCount; city++) {
                if (rank[city] == -1) continue;
                for (int phase = 0; phase < 60; phase++) {
                    change = max(change, fabs(nextValue[city][phase] - value[city][phase]));
                    scale = max(scale, fabs(nextValue[city][phase]));
                    value[city][phase] = nextValue[city][phase];
                }
            }
            if (change <= 1e-11 * scale) break;
        }
        double answer = *min_element(value[start].begin(), value[start].end());
        // 输出格式：小数部分后面的尾随零不能输出，否则会 Wrong Answer
        cout << setprecision(10) << answer << '\n';
    }
    return 0;
}
