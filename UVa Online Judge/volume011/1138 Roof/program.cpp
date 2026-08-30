#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int x1, y1, x2, y2;
};

struct Event {
    int x, id;
    bool isStart;
};

struct EventCmp {
    bool operator()(const Event &a, const Event &b) const {
        if (a.x != b.x)
            return a.x < b.x;
        return a.isStart > b.isStart;
    }
};

__int128 getNumerator(const Segment &s, long long x2) {
    return (__int128)s.y1 * (2LL * s.x2 - x2) + (__int128)s.y2 * (x2 - 2LL * s.x1);
}

__int128 getDenominator(const Segment &s) {
    return 2LL * (s.x2 - s.x1);
}

int compareHeight(const Segment &a, const Segment &b, long long x2) {
    __int128 leftValue = getNumerator(a, x2) * getDenominator(b);
    __int128 rightValue = getNumerator(b, x2) * getDenominator(a);
    if (leftValue < rightValue)
        return -1;
    if (leftValue > rightValue)
        return 1;
    return 0;
}

bool isLowerLeft(const Segment &s) {
    return s.y1 < s.y2;
}

int getLowerX(const Segment &s) {
    return isLowerLeft(s) ? s.x1 : s.x2;
}

int getLowerY(const Segment &s) {
    return isLowerLeft(s) ? s.y1 : s.y2;
}

int findTarget(int id, int x, const vector<Segment> &segments, const vector<int> &active) {
    const Segment &source = segments[id];
    int lowerY = getLowerY(source), target = -1;
    for (int otherId : active) {
        if (otherId == id)
            continue;
        const Segment &other = segments[otherId];
        if (compareHeight(other, source, 2LL * x) > 0)
            continue;
        if (target == -1 || compareHeight(other, segments[target], 2LL * x) > 0)
            target = otherId;
    }
    return target;
}

void solveCase() {
    int n;
    cin >> n;
    vector<Segment> segments(n);
    vector<Event> events;
    events.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> segments[i].x1 >> segments[i].y1 >> segments[i].x2 >> segments[i].y2;
        events.push_back({segments[i].x1, i, true});
        events.push_back({segments[i].x2, i, false});
    }
    sort(events.begin(), events.end(), EventCmp());
    vector<long long> direct(n, 0), total(n, 0);
    vector<int> target(n, -1), active;
    int pos = 0;
    while (pos < (int)events.size()) {
        int currentX = events[pos].x, endPos = pos;
        while (endPos < (int)events.size() && events[endPos].x == currentX)
            endPos++;
        for (int i = pos; i < endPos; i++)
            if (events[i].isStart)
                active.push_back(events[i].id);
        for (int i = pos; i < endPos; i++) {
            int id = events[i].id;
            if (getLowerX(segments[id]) == currentX)
                target[id] = findTarget(id, currentX, segments, active);
        }
        for (int i = pos; i < endPos; i++) {
            if (!events[i].isStart) {
                int id = events[i].id;
                for (int j = 0; j < (int)active.size(); j++) {
                    if (active[j] == id) {
                        active.erase(active.begin() + j);
                        break;
                    }
                }
            }
        }
        if (endPos < (int)events.size()) {
            int nextX = events[endPos].x;
            if (nextX > currentX && !active.empty()) {
                long long middleX2 = (long long)currentX + nextX;
                int highest = active[0];
                for (int id : active)
                    if (compareHeight(segments[id], segments[highest], middleX2) > 0)
                        highest = id;
                direct[highest] += nextX - currentX;
            }
        }
        pos = endPos;
    }
    vector<int> inDegree(n, 0);
    for (int i = 0; i < n; i++) {
        total[i] = direct[i];
        if (target[i] != -1)
            inDegree[target[i]]++;
    }
    queue<int> que;
    for (int i = 0; i < n; i++)
        if (inDegree[i] == 0)
            que.push(i);
    while (!que.empty()) {
        int current = que.front();
        que.pop();
        if (target[current] == -1)
            continue;
        int next = target[current];
        total[next] += total[current];
        inDegree[next]--;
        if (inDegree[next] == 0)
            que.push(next);
    }
    for (int i = 0; i < n; i++)
        cout << total[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseIndex = 0; caseIndex < testCount; caseIndex++) {
        if (caseIndex > 0)
            cout << '\n';
        solveCase();
    }
    return 0;
}
