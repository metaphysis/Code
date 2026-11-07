// One Day Tours
// UVa ID: 788
// Verdict: Wrong Answer
// Submission Date: 2026-11-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long weight;
};

struct Road {
    int from;
    int to;
    long long weight;
};

struct State {
    bool valid;
    long long totalDistance;
    long long currentDayDistance;
    vector<long long> finishedDayDistances;
    vector<long long> visitDistances;
    vector<int> visitOrder;
    State() : valid(false), totalDistance(0), currentDayDistance(0) {}
};

struct QueueNode {
    long long distance;
    int vertex;
    int version;
};

struct QueueCompare {
    bool operator()(const QueueNode &a, const QueueNode &b) const {
        return a.distance > b.distance;
    }
};

struct Tourist {
    int n;
    int visitsPerDay;
    vector<vector<Edge> > graph;
};

static bool betterState(const State &a, const State &b) {
    if (!b.valid) return a.valid;
    if (!a.valid) return false;
    if (a.totalDistance != b.totalDistance) return a.totalDistance < b.totalDistance;
    if (a.currentDayDistance != b.currentDayDistance) return a.currentDayDistance < b.currentDayDistance;
    int as = (int)a.finishedDayDistances.size();
    int bs = (int)b.finishedDayDistances.size();
    int common = min(as, bs);
    for (int i = 1; i <= common; ++i) {
        long long ad = a.finishedDayDistances[as - i];
        long long bd = b.finishedDayDistances[bs - i];
        if (ad != bd) return ad < bd;
    }
    if (as != bs) return as < bs;
    return lexicographical_compare(a.visitOrder.begin(), a.visitOrder.end(), b.visitOrder.begin(), b.visitOrder.end());
}

static State moveState(const State &source, long long distance) {
    State result = source;
    result.totalDistance += distance;
    result.currentDayDistance += distance;
    return result;
}

static void relaxState(State &target, const State &candidate) {
    if (betterState(candidate, target)) target = candidate;
}

static vector<State> shortestPaths(const Tourist &tourist, int mask, const vector<State> &sources) {
    int n = tourist.n;
    vector<State> distance(n + 1);
    vector<int> version(n + 1, 0);
    priority_queue<QueueNode, vector<QueueNode>, QueueCompare> queue;
    for (int vertex = 0; vertex <= n; ++vertex) {
        if (!sources[vertex].valid) continue;
        if (betterState(sources[vertex], distance[vertex])) {
            distance[vertex] = sources[vertex];
            ++version[vertex];
            queue.push(QueueNode{distance[vertex].totalDistance, vertex, version[vertex]});
        }
    }
    while (!queue.empty()) {
        QueueNode current = queue.top();
        queue.pop();
        if (current.version != version[current.vertex]) continue;
        int u = current.vertex;
        for (size_t i = 0; i < tourist.graph[u].size(); ++i) {
            int v = tourist.graph[u][i].to;
            if (v != 0 && (mask & (1 << (v - 1))) == 0) continue;
            State candidate = moveState(distance[u], tourist.graph[u][i].weight);
            if (betterState(candidate, distance[v])) {
                distance[v] = candidate;
                ++version[v];
                queue.push(QueueNode{distance[v].totalDistance, v, version[v]});
            }
        }
    }
    return distance;
}

static void printAnswer(int touristNumber, const Tourist &tourist, const State &answer) {
    cout << "== Tourist " << touristNumber << " -- " << tourist.visitsPerDay << " visits a day --\n";
    int dayCount = (int)answer.finishedDayDistances.size();
    int visitIndex = 0;
    for (int day = 0; day < dayCount; ++day) {
        long long previousDistance = 0;
        int placesToday = min(tourist.visitsPerDay, tourist.n - visitIndex);
        cout << "Day " << day + 1 << ": ";
        for (int j = 0; j < placesToday; ++j) {
            long long reachedDistance = answer.visitDistances[visitIndex];
            if (j > 0) cout << " - ";
            cout << "[" << reachedDistance - previousDistance << "] - " << answer.visitOrder[visitIndex];
            previousDistance = reachedDistance;
            ++visitIndex;
        }
        cout << " - [" << answer.finishedDayDistances[day] - previousDistance << "]\n";
    }
    cout << "===\n";
}

static State solveTourist(const Tourist &tourist) {
    int n = tourist.n;
    int stateCount = 1 << n;
    vector<vector<State> > seeds(stateCount, vector<State>(n + 1));
    seeds[0][0].valid = true;
    State answer;
    for (int mask = 0; mask < stateCount; ++mask) {
        int visitedCount = __builtin_popcount((unsigned)mask);
        vector<State> best = shortestPaths(tourist, mask, seeds[mask]);
        bool mustReturn = visitedCount > 0 && (visitedCount == n || visitedCount % tourist.visitsPerDay == 0);
        if (mustReturn) {
            if (!best[0].valid) continue;
            State returned = best[0];
            returned.finishedDayDistances.push_back(returned.currentDayDistance);
            returned.currentDayDistance = 0;
            if (visitedCount == n) {
                relaxState(answer, returned);
                continue;
            }
            vector<State> hotelSource(n + 1);
            hotelSource[0] = returned;
            best = shortestPaths(tourist, mask, hotelSource);
        }
        for (int u = 0; u <= n; ++u) {
            if (!best[u].valid) continue;
            for (size_t i = 0; i < tourist.graph[u].size(); ++i) {
                int v = tourist.graph[u][i].to;
                if (v == 0 || (mask & (1 << (v - 1))) != 0) continue;
                int nextMask = mask | (1 << (v - 1));
                State candidate = moveState(best[u], tourist.graph[u][i].weight);
                candidate.visitOrder.push_back(v);
                candidate.visitDistances.push_back(candidate.currentDayDistance);
                relaxState(seeds[nextMask][v], candidate);
            }
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int touristNumber = 0;
    while (true) {
        vector<Road> roads;
        int firstValue;
        int visitsPerDay = 0;
        int n = 0;
        bool hasTourist = false;
        while (cin >> firstValue) {
            if (firstValue < -1) {
                visitsPerDay = -firstValue;
                hasTourist = true;
                break;
            }
            int secondValue;
            long long distance;
            if (!(cin >> secondValue >> distance)) return 0;
            roads.push_back(Road{firstValue, secondValue, distance});
            n = max(n, max(firstValue, secondValue));
        }
        if (!hasTourist) break;
        Tourist tourist;
        tourist.n = n;
        tourist.visitsPerDay = visitsPerDay;
        tourist.graph.assign(n + 1, vector<Edge>());
        for (size_t i = 0; i < roads.size(); ++i) {
            int u = roads[i].from;
            int v = roads[i].to;
            long long w = roads[i].weight;
            tourist.graph[u].push_back(Edge{v, w});
            tourist.graph[v].push_back(Edge{u, w});
        }
        State answer = solveTourist(tourist);
        ++touristNumber;
        printAnswer(touristNumber, tourist, answer);
    }
    return 0;
}
