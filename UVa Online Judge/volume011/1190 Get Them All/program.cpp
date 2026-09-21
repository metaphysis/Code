#include <bits/stdc++.h>
using namespace std;

struct Event {
    long long time, depart;
    int pos, seat, load, id;
};

struct EventCmp {
    bool operator()(const Event &a, const Event &b) const {
        if (a.time != b.time)
            return a.time > b.time;
        if (a.pos != b.pos)
            return a.pos > b.pos;
        if (a.depart != b.depart)
            return a.depart > b.depart;
        return a.id > b.id;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string name;
    while (cin >> name && name != "TheEnd") {
        int n;
        long long s, t;
        cin >> n >> s >> t;
        vector<vector<long long>> dis(n, vector<long long>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j)
                    continue;
                cin >> dis[i][j];
            }
        }
        vector<long long> wait(n, 0);
        long long total = 0;
        for (int i = 1; i < n; ++i) {
            cin >> wait[i];
            total += wait[i];
        }
        long long limit;
        cin >> limit;
        cout << name << '\n';
        if (total == 0) {
            cout << "0 seconds needed\n";
            continue;
        }
        priority_queue<Event, vector<Event>, EventCmp> eventQue;
        vector<int> lastNext(n, -1);
        set<long long> requestTime;
        int vehicleId = 1;
        int reached = 0;
        long long finishTime = -1;
        int firstSeat = static_cast<int>(max(s, 3LL));
        eventQue.push({0, 0, 0, firstSeat, 0, vehicleId});
        while (!eventQue.empty()) {
            Event current = eventQue.top();
            eventQue.pop();
            if (current.time > limit)
                break;
            if (current.pos == 0) {
                reached += current.load;
                current.load = 0;
            } else {
                long long take = min(static_cast<long long>(current.seat - current.load), wait[current.pos]);
                wait[current.pos] -= take;
                current.load += static_cast<int>(take);
                if (wait[current.pos] > 0 && requestTime.insert(current.time).second) {
                    ++vehicleId;
                    long long depart = current.time + 2;
                    int seat = static_cast<int>(max(s - (vehicleId - 1) * t, 3LL));
                    eventQue.push({depart, depart, 0, seat, 0, vehicleId});
                }
            }
            if (reached == total) {
                finishTime = current.time;
                break;
            }
            int nextPos;
            if (current.load == current.seat) {
                nextPos = 0;
            } else if (lastNext[current.pos] == -1) {
                nextPos = (current.pos + 1) % n;
            } else {
                int k0 = lastNext[current.pos];
                nextPos = (k0 + 1) % n;
                if (nextPos == current.pos)
                    nextPos = (k0 + 2) % n;
            }
            lastNext[current.pos] = nextPos;
            eventQue.push({current.time + dis[current.pos][nextPos], current.depart, nextPos, current.seat, current.load, current.id});
        }
        if (finishTime != -1)
            cout << finishTime << " seconds needed\n";
        else
            cout << reached << " contestants reached\n";
    }
    return 0;
}
