#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int from, to;
    long long start, cost;
};

struct Visit {
    int hill;
    long long time;
};

struct Ant {
    long long period;
    vector<Segment> segments;
    vector<Visit> visits;
};

long long getGcd(long long x, long long y) {
    while (y != 0) {
        long long temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

long long getPositiveMod(long long x, long long mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

Ant buildAnt(const vector<int> &points, const map<pair<int, int>, long long> &roads) {
    Ant ant;
    ant.period = 0;
    int pointCount = points.size();
    for (int i = 0; i < pointCount; i++) {
        ant.visits.push_back({points[i], ant.period});
        int from = points[i], to = points[(i + 1) % pointCount];
        int left = min(from, to), right = max(from, to);
        long long cost = roads.at({left, right});
        ant.segments.push_back({from, to, ant.period, cost});
        ant.period += cost;
    }
    return ant;
}

bool canMeetAtHills(const Ant &first, const Ant &second) {
    long long gcdPeriod = getGcd(first.period, second.period);
    for (const Visit &firstVisit : first.visits)
        for (const Visit &secondVisit : second.visits)
            if (firstVisit.hill == secondVisit.hill && getPositiveMod(firstVisit.time - secondVisit.time, gcdPeriod) == 0)
                return true;
    return false;
}

bool canMeetOnRoads(const Ant &first, const Ant &second) {
    long long gcdPeriod = getGcd(first.period, second.period);
    for (const Segment &firstSegment : first.segments) {
        for (const Segment &secondSegment : second.segments) {
            bool sameRoad = (firstSegment.from == secondSegment.from && firstSegment.to == secondSegment.to) || (firstSegment.from == secondSegment.to && firstSegment.to == secondSegment.from);
            if (!sameRoad)
                continue;
            long long difference = firstSegment.start - secondSegment.start;
            long long remainder = getPositiveMod(difference, gcdPeriod);
            bool sameDirection = firstSegment.from == secondSegment.from && firstSegment.to == secondSegment.to;
            if (sameDirection && remainder == 0)
                return true;
            if (!sameDirection) {
                long long distance = min(remainder, gcdPeriod - remainder);
                if (distance <= firstSegment.cost)
                    return true;
            }
        }
    }
    return false;
}

bool canMeet(const Ant &first, const Ant &second) {
    return canMeetAtHills(first, second) || canMeetOnRoads(first, second);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, testCase = 1;
    while (cin >> n >> m >> a) {
        if (n == 0 && m == 0 && a == 0)
            break;
        map<pair<int, int>, long long> roads;
        for (int i = 0; i < m; i++) {
            int x, y;
            long long t;
            cin >> x >> y >> t;
            roads[{min(x, y), max(x, y)}] = t;
        }
        vector<Ant> ants;
        for (int i = 0; i < a; i++) {
            vector<int> points;
            int hill;
            while (cin >> hill && hill != 0)
                points.push_back(hill);
            ants.push_back(buildAnt(points, roads));
        }
        vector<vector<int>> graph(a);
        for (int i = 0; i < a; i++) {
            for (int j = i + 1; j < a; j++) {
                if (canMeet(ants[i], ants[j])) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
        vector<bool> visited(a, false);
        queue<int> que;
        if (a > 0) {
            visited[0] = true;
            que.push(0);
        }
        while (!que.empty()) {
            int current = que.front();
            que.pop();
            for (int next : graph[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    que.push(next);
                }
            }
        }
        bool success = true;
        for (bool state : visited)
            if (!state)
                success = false;
        cout << "Revolution #" << testCase << '\n';
        if (success)
            cout << "Revolution can start.\n\n";
        else
            cout << "Revolution fails.\n\n";
        testCase++;
    }
    return 0;
}
