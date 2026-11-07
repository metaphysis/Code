// One Day Tours
// UVa ID: 788
// Verdict: Wrong Answer
// Submission Date: 2026-11-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = (1LL << 60);

struct Road {
    int u;
    int v;
    ll distance;
};

struct State {
    bool valid;
    ll total;
    ll currentDay;
    vector<ll> finishedDays;
    vector<int> order;
    State() : valid(false), total(0), currentDay(0) {}
};

static bool better(const State &a, const State &b) {
    if (!a.valid) return false;
    if (!b.valid) return true;
    if (a.total != b.total) return a.total < b.total;
    if (a.currentDay != b.currentDay) return a.currentDay < b.currentDay;
    for (int i = (int)a.finishedDays.size() - 1; i >= 0; --i)
        if (a.finishedDays[i] != b.finishedDays[i]) return a.finishedDays[i] < b.finishedDays[i];
    return lexicographical_compare(a.order.begin(), a.order.end(), b.order.begin(), b.order.end());
}

static void relax(State &target, const State &candidate) {
    if (better(candidate, target)) target = candidate;
}

static State appendPlace(const State &source, int last, int place, int count, int m, const vector<vector<ll> > &dist) {
    State result = source;
    int from = count % m == 0 ? 0 : last;
    ll step = dist[from][place];
    result.total += step;
    result.currentDay += step;
    result.order.push_back(place);
    if ((count + 1) % m == 0) {
        result.total += dist[place][0];
        result.currentDay += dist[place][0];
        result.finishedDays.push_back(result.currentDay);
        result.currentDay = 0;
    }
    return result;
}

static void solveOriginal(int touristNumber, int n, int m, const vector<Road> &roads) {
    vector<vector<ll> > dist(n + 1, vector<ll>(n + 1, INF));
    for (int i = 0; i <= n; ++i) dist[i][i] = 0;
    for (size_t i = 0; i < roads.size(); ++i) {
        int u = roads[i].u;
        int v = roads[i].v;
        dist[u][v] = min(dist[u][v], roads[i].distance);
        dist[v][u] = min(dist[v][u], roads[i].distance);
    }
    for (int k = 0; k <= n; ++k)
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    int stateCount = 1 << n;
    vector<vector<State> > dp(stateCount, vector<State>(n));
    State initial;
    initial.valid = true;
    for (int i = 0; i < n; ++i) {
        if (dist[0][i + 1] == INF) continue;
        dp[1 << i][i] = appendPlace(initial, 0, i + 1, 0, m, dist);
    }
    for (int mask = 1; mask < stateCount; ++mask) {
        int count = __builtin_popcount((unsigned int)mask);
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i)) || !dp[mask][i].valid) continue;
            for (int j = 0; j < n; ++j) {
                if (mask & (1 << j)) continue;
                int from = count % m == 0 ? 0 : i + 1;
                if (dist[from][j + 1] == INF) continue;
                State candidate = appendPlace(dp[mask][i], i + 1, j + 1, count, m, dist);
                relax(dp[mask | (1 << j)][j], candidate);
            }
        }
    }
    State answer;
    for (int i = 0; i < n; ++i) {
        if (!dp[stateCount - 1][i].valid) continue;
        State candidate = dp[stateCount - 1][i];
        if (n % m != 0) {
            candidate.total += dist[i + 1][0];
            candidate.currentDay += dist[i + 1][0];
            candidate.finishedDays.push_back(candidate.currentDay);
            candidate.currentDay = 0;
        }
        relax(answer, candidate);
    }
    cout << "== Tourist  " << touristNumber << "  --  " << m << " visits a day --\n";
    if (answer.valid) {
        int days = (n + m - 1) / m;
        for (int day = 0; day < days; ++day) {
            cout << " Day  " << day + 1 << ": ";
            int current = 0;
            int begin = day * m;
            int end = min(n, begin + m);
            for (int index = begin; index < end; ++index) {
                int place = answer.order[index];
                cout << "[" << dist[current][place] << "] - " << place << " - ";
                current = place;
            }
            cout << "[" << dist[current][0] << "]\n";
        }
    }
    cout << "===\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<Road> roads;
    int n = 0;
    int touristNumber = 0;
    int u;
    while (cin >> u) {
        if (u < -1) {
            solveOriginal(++touristNumber, n, -u, roads);
            roads.clear();
            n = 0;
        } else {
            int v;
            ll distance;
            if (!(cin >> v >> distance)) return 0;
            roads.push_back(Road{u, v, distance});
            n = max(n, max(u, v));
        }
    }
    return 0;
}
