#include <bits/stdc++.h>
using namespace std;

const int inf = 1000000000;

struct Road {
    int to, len;
};

vector<vector<Road> > graph;
vector<vector<int> > distCache;
vector<bool> distReady;

void runDijkstra(int source) {
    vector<int> dist(graph.size(), inf);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
    dist[source] = 0;
    que.push({0, source});
    while (!que.empty()) {
        int curDist = que.top().first, cur = que.top().second;
        que.pop();
        if (curDist != dist[cur]) continue;
        for (const Road &road : graph[cur]) {
            int nextDist = curDist + road.len;
            if (nextDist < dist[road.to]) {
                dist[road.to] = nextDist;
                que.push({nextDist, road.to});
            }
        }
    }
    distCache[source] = move(dist);
    distReady[source] = true;
}

void ensureDistance(int source) {
    if (!distReady[source])
        runDijkstra(source);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cityCount;
    cin >> cityCount;
    vector<string> cityNames(cityCount);
    vector<int> population(cityCount);
    map<string, int> cityId;
    for (int i = 0; i < cityCount; i++) {
        cin >> cityNames[i] >> population[i];
        cityId[cityNames[i]] = i;
    }
    graph.assign(cityCount, vector<Road>());
    int roadCount;
    cin >> roadCount;
    for (int i = 0; i < roadCount; i++) {
        string from, to;
        int length, u, v;
        cin >> from >> to >> length;
        u = cityId[from];
        v = cityId[to];
        graph[u].push_back({v, length});
        graph[v].push_back({u, length});
    }
    distCache.assign(cityCount, vector<int>());
    distReady.assign(cityCount, false);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int stock, destCount;
        double rotRate;
        string baseName;
        cin >> stock >> rotRate >> baseName >> destCount;
        vector<int> destinations(destCount);
        for (int i = 0; i < destCount; i++) {
            string name;
            cin >> name;
            destinations[i] = cityId[name];
        }
        sort(destinations.begin(), destinations.end(), [&](int a, int b) {
            return cityNames[a] < cityNames[b];
        });
        int base = cityId[baseName];
        vector<int> nodes(destCount + 1);
        nodes[0] = base;
        for (int i = 0; i < destCount; i++)
            nodes[i + 1] = destinations[i];
        for (int city : nodes)
            ensureDistance(city);
        vector<vector<int> > travelDays(destCount + 1, vector<int>(destCount + 1, inf));
        for (int i = 0; i <= destCount; i++) {
            for (int j = 0; j <= destCount; j++) {
                if (distCache[nodes[i]][nodes[j]] == inf) continue;
                travelDays[i][j] = (distCache[nodes[i]][nodes[j]] + 24) / 25;
            }
        }
        vector<bool> used(destCount, false);
        vector<int> currentOrder, bestOrder;
        double bestProfit = -1.0;
        function<void(int, int, int, double)> dfs = [&](int last, int day, int remaining, double profit) {
            if (currentOrder.size() == destinations.size()) {
                if (profit > bestProfit) {
                    bestProfit = profit;
                    bestOrder = currentOrder;
                }
                return;
            }
            for (int i = 0; i < destCount; i++) {
                if (used[i]) continue;
                int next = i + 1;
                if (travelDays[last][next] == inf) continue;
                int nextDay = day + travelDays[last][next];
                int cityLimit = population[destinations[i]] * 5 / 10000;
                int sellCount = min(remaining, cityLimit);
                double price = 10.0 * pow(rotRate, -nextDay);
                used[i] = true;
                currentOrder.push_back(destinations[i]);
                dfs(next, nextDay + 1, remaining - sellCount, profit + sellCount * price);
                currentOrder.pop_back();
                used[i] = false;
            }
        };
        dfs(0, 0, stock, 0.0);
        for (int i = 0; i < destCount; i++) {
            if (i > 0)
                cout << ' ';
            cout << cityNames[bestOrder[i]];
        }
        cout << " -> " << (long long)ceil(bestProfit) << '\n';
    }
    return 0;
}
