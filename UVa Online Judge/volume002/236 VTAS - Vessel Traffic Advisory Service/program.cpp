// VTAS - Vessel Traffic Advisory Service
// UVa ID: 236
// Verdict: Wrong Answer
// Submission Date: 2026-05-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

struct Vessel {
    string name, route;
    double speed, startTime;
    bool isValid;
    vector<double> arr;
};

string formatTime(double timeVal) {
    long long minutes = (long long)floor(timeVal + 0.5);
    int dayMinute = minutes % 1440, clockVal = dayMinute / 60 * 100 + dayMinute % 60;
    ostringstream out;
    out << setfill('0') << setw(4) << clockVal;
    return out.str();
}

bool validRoute(const string &route, const vector<int> &wpId, const vector<vector<double>> &dist) {
    for (int i = 0; i < (int)route.size(); ++i) {
        int curId = wpId[(unsigned char)route[i]];
        if (curId == -1) return false;
        if (i > 0) {
            int prevId = wpId[(unsigned char)route[i - 1]];
            if (dist[prevId][curId] <= 0) return false;
        }
    }
    return !route.empty();
}

bool hasEncounter(const Vessel &cur, int legId, const Vessel &other) {
    char fromWp = cur.route[legId], toWp = cur.route[legId + 1];
    for (int i = 0; i + 1 < (int)other.route.size(); ++i) {
        char otherFrom = other.route[i], otherTo = other.route[i + 1];
        bool sameLeg = (fromWp == otherFrom && toWp == otherTo) || (fromWp == otherTo && toWp == otherFrom);
        if (!sameLeg) continue;
        double leftTime = max(cur.arr[legId], other.arr[i]), rightTime = min(cur.arr[legId + 1], other.arr[i + 1]);
        if (leftTime + eps < rightTime) return true;
    }
    return false;
}

bool hasClosePassing(const Vessel &cur, int wpPos, const Vessel &other) {
    for (int i = 0; i < (int)other.route.size(); ++i)
        if (cur.route[wpPos] == other.route[i] && fabs(cur.arr[wpPos] - other.arr[i]) <= 3.0 + eps) return true;
    return false;
}

void printReport(const vector<Vessel> &ships, int shipId) {
    const Vessel &cur = ships[shipId];
    cout << cur.name << " entering system at " << formatTime(cur.startTime);
    cout << " with a planned speed of " << fixed << setprecision(1) << cur.speed << " knots\n";
    if (!cur.isValid) {
        cout << "**> Invalid Route Plan for Vessel: " << cur.name << '\n';
        return;
    }
    cout << "          Waypoint:";
    for (char wp : cur.route) cout << setw(5) << wp;
    cout << '\n' << "          Arrival:  ";
    for (double timeVal : cur.arr) cout << setw(5) << formatTime(timeVal);
    cout << '\n';
    for (int i = 0; i + 1 < (int)cur.route.size(); ++i)
        for (int j = 0; j < (int)ships.size(); ++j)
            if (j != shipId && ships[j].isValid && hasEncounter(cur, i, ships[j])) cout << "Projected encounter with " << ships[j].name << " on leg between Waypoints " << cur.route[i] << " & " << cur.route[i + 1] << '\n';
    for (int i = 0; i < (int)cur.route.size(); ++i)
        for (int j = 0; j < (int)ships.size(); ++j)
            if (j != shipId && ships[j].isValid && hasClosePassing(cur, i, ships[j])) cout << "** Warning ** Close passing with " << ships[j].name << " at Waypoint " << cur.route[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> wpId(256, -1);
    for (int i = 0; i < n; ++i) {
        char wp;
        cin >> wp;
        wpId[(unsigned char)wp] = i;
    }
    vector<vector<double>> dist(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) cin >> dist[i][j];
    vector<Vessel> ships;
    string name;
    int lastMinute = -1;
    long long dayCount = 0;
    while (cin >> name && name[0] != '*') {
        Vessel cur;
        int clockVal;
        cur.name = name;
        cin >> clockVal >> cur.speed >> cur.route;
        int dayMinute = clockVal / 100 * 60 + clockVal % 100;
        if (lastMinute != -1 && dayMinute < lastMinute) ++dayCount;
        lastMinute = dayMinute;
        cur.startTime = dayCount * 1440 + dayMinute;
        cur.isValid = validRoute(cur.route, wpId, dist);
        if (cur.isValid) {
            cur.arr.resize(cur.route.size());
            cur.arr[0] = cur.startTime;
            for (int i = 1; i < (int)cur.route.size(); ++i) {
                int fromId = wpId[(unsigned char)cur.route[i - 1]], toId = wpId[(unsigned char)cur.route[i]];
                cur.arr[i] = cur.arr[i - 1] + dist[fromId][toId] * 60.0 / cur.speed;
            }
        }
        ships.push_back(cur);
    }
    for (int i = 0; i < (int)ships.size(); ++i) {
        if (i > 0) cout << '\n';
        printReport(ships, i);
    }
    return 0;
}
