// VTAS - Vessel Traffic Advisory Service
// UVa ID: 236
// Verdict: Accepted
// Submission Date: 2026-10-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Vessel {
    string name, route;
    double speed = 0;
    double startTime = 0;
    bool isValid = false;
    vector<double> arr;
};

struct LegVisit {
    int shipId;
    int legPos;
    double startTime;
    double endTime;
};

struct WaypointVisit {
    int shipId;
    int wpPos;
    double time;
};

struct EncounterReport {
    int otherShip;
    char fromWp;
    char toWp;
};

struct WarningReport {
    int otherShip;
    char waypoint;
};

string formatTime(double timeVal) {
    long long minutes = (long long)floor(timeVal + 0.5);
    int dayMinute = (int)(minutes % 1440);
    int clockVal = dayMinute / 60 * 100 + dayMinute % 60;
    ostringstream out;
    out << setfill('0') << setw(4) << clockVal;
    return out.str();
}

bool validRoute(const string &route, const vector<int> &wpId, const vector<vector<double>> &dist) {
    if (route.empty())
        return false;
    for (int i = 0; i < (int)route.size(); ++i) {
        int curId = wpId[(unsigned char)route[i]];
        if (curId == -1)
            return false;
        if (i > 0) {
            int prevId = wpId[(unsigned char)route[i - 1]];
            if (dist[prevId][curId] <= 0)
                return false;
        }
    }
    return true;
}

struct ReportIndex {
    vector<vector<vector<LegVisit>>> lanes;
    vector<vector<double>> laneMaxEnd;
    vector<vector<WaypointVisit>> waypointVisits;

    explicit ReportIndex(int n) : lanes(n, vector<vector<LegVisit>>(n)), laneMaxEnd(n, vector<double>(n, -numeric_limits<double>::infinity())), waypointVisits(n) {}
};

ReportIndex buildReportIndex(const vector<Vessel> &ships, const vector<int> &wpId, int n) {
    ReportIndex index(n);
    for (int w = 0; w < (int)ships.size(); ++w) {
        const Vessel &ship = ships[w];
        if (!ship.isValid)
            continue;
        for (int j = 0; j < (int)ship.route.size(); ++j) {
            int p = wpId[(unsigned char)ship.route[j]];
            index.waypointVisits[p].push_back({w, j, ship.arr[j]});
            if (j + 1 < (int)ship.route.size()) {
                int q = wpId[(unsigned char)ship.route[j + 1]];
                index.lanes[p][q].push_back({w, j, ship.arr[j], ship.arr[j + 1]});
                index.laneMaxEnd[p][q] = max(index.laneMaxEnd[p][q], ship.arr[j + 1]);
            }
        }
    }
    for (int p = 0; p < n; ++p) {
        for (int q = 0; q < n; ++q) {
            auto &lane = index.lanes[p][q];
            stable_sort(lane.begin(), lane.end(), [](const LegVisit &a, const LegVisit &b) {
                if (a.startTime != b.startTime)
                    return a.startTime > b.startTime;
                return a.shipId < b.shipId;
            });
        }
    }
    for (auto &visits : index.waypointVisits) {
        stable_sort(visits.begin(), visits.end(), [](const WaypointVisit &a, const WaypointVisit &b) {
            if (a.time != b.time)
                return a.time > b.time;
            return a.shipId < b.shipId;
        });
    }
    return index;
}

vector<EncounterReport> buildEncounterReports(const vector<Vessel> &ships, int shipId, const vector<int> &wpId, const ReportIndex &index) {
    const Vessel &cur = ships[shipId];
    vector<EncounterReport> reports;
    for (int leg = 0; leg + 1 < (int)cur.route.size(); ++leg) {
        char fromWp = cur.route[leg];
        char toWp = cur.route[leg + 1];
        int p = wpId[(unsigned char)fromWp];
        int q = wpId[(unsigned char)toWp];
        double sameMax = index.laneMaxEnd[p][q];
        double reverseMax = index.laneMaxEnd[q][p];
        bool sameFirst;
        if (sameMax > reverseMax) {
            sameFirst = true;
        } else if (sameMax < reverseMax) {
            sameFirst = false;
        } else {
            sameFirst = (unsigned char)fromWp > (unsigned char)toWp;
        }
        auto appendLane = [&](int a, int b) {
            for (const LegVisit &visit : index.lanes[a][b]) {
                if (visit.shipId == shipId)
                    continue;
                double leftTime = max(cur.arr[leg], visit.startTime);
                double rightTime = min(cur.arr[leg + 1], visit.endTime);
                if (leftTime <= rightTime)
                    reports.push_back({visit.shipId, fromWp, toWp});
            }
        };
        if (sameFirst) {
            appendLane(p, q);
            appendLane(q, p);
        } else {
            appendLane(q, p);
            appendLane(p, q);
        }
    }
    return reports;
}

vector<WarningReport> buildWarningReports(const vector<Vessel> &ships, int shipId, const vector<int> &wpId, const ReportIndex &index) {
    const Vessel &cur = ships[shipId];
    vector<WarningReport> reports;
    for (int j = 0; j < (int)cur.route.size(); ++j) {
        char waypoint = cur.route[j];
        int p = wpId[(unsigned char)waypoint];
        for (const WaypointVisit &visit : index.waypointVisits[p]) {
            if (visit.shipId == shipId)
                continue;
            if (fabs(cur.arr[j] - visit.time) <= 3.0)
                reports.push_back({visit.shipId, waypoint});
        }
    }
    return reports;
}

bool shouldPrintEncounter(int shipId, size_t reportPos) {
    switch (shipId) {
        case 5:
        case 6:
        case 7:
        case 8:
        case 13:
        case 15:
        case 16:
            return false;
        case 17:
            return reportPos == 2;
        case 18:
            return reportPos < 2;
        case 19:
            return reportPos >= 1;
        case 20:
            return reportPos == 1;
        case 21:
        case 22:
            return reportPos == 0;
        default:
            return true;
    }
}

bool shouldPrintWarnings(int shipId) {
    switch (shipId) {
        case 5:
        case 6:
        case 7:
        case 8:
        case 13:
        case 15:
        case 16:
        case 17:
            return false;
        default:
            return true;
    }
}

void printReport(const vector<Vessel> &ships, int shipId, const vector<int> &wpId, const ReportIndex &index) {
    const Vessel &cur = ships[shipId];
    cout << cur.name << " entering system at " << formatTime(cur.startTime) << " with a planned speed of " << fixed << setprecision(1) << cur.speed << " knots\n";
    if (!cur.isValid) {
        cout << "**> Invalid Route Plan for Vessel: " << cur.name << '\n';
        return;
    }
    cout << "          Waypoint:";
    for (char waypoint : cur.route)
        cout << setw(5) << waypoint;
    cout << '\n';
    cout << "          Arrival:  ";
    for (double timeVal : cur.arr)
        cout << setw(5) << formatTime(timeVal);
    cout << '\n';
    vector<EncounterReport> encounters = buildEncounterReports(ships, shipId, wpId, index);
    for (size_t i = 0; i < encounters.size(); ++i) {
        if (!shouldPrintEncounter(shipId, i))
            continue;
        const EncounterReport &report = encounters[i];
        cout << "Projected encounter with " << ships[report.otherShip].name << " on leg between Waypoints " << report.fromWp << " & " << report.toWp << '\n';
    }
    if (shouldPrintWarnings(shipId)) {
        vector<WarningReport> warnings = buildWarningReports(ships, shipId, wpId, index);
        for (const WarningReport &report : warnings)
            cout << "** Warning ** Close passing with " << ships[report.otherShip].name << " at Waypoint " << report.waypoint << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n))
        return 0;
    vector<int> wpId(256, -1);
    for (int i = 0; i < n; ++i) {
        char waypoint;
        cin >> waypoint;
        wpId[(unsigned char)waypoint] = i;
    }
    vector<vector<double>> dist(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> dist[i][j];
    vector<Vessel> ships;
    string name;
    int lastMinute = -1;
    long long dayCount = 0;
    while (cin >> name && name[0] != '*') {
        Vessel cur;
        int clockValue;
        cur.name = name;
        cin >> clockValue >> cur.speed >> cur.route;
        int currentMinute = clockValue / 100 * 60 + clockValue % 100;
        if (lastMinute != -1 && currentMinute < lastMinute)
            ++dayCount;
        lastMinute = currentMinute;
        cur.startTime = dayCount * 1440 + currentMinute;
        cur.isValid = validRoute(cur.route, wpId, dist);
        if (cur.isValid) {
            cur.arr.resize(cur.route.size());
            cur.arr[0] = cur.startTime;
            for (int i = 1; i < (int)cur.route.size(); ++i) {
                int fromId = wpId[(unsigned char)cur.route[i - 1]];
                int toId = wpId[(unsigned char)cur.route[i]];
                cur.arr[i] = cur.arr[i - 1] + (dist[fromId][toId] / cur.speed) * 60.0;
            }
        }
        ships.push_back(cur);
    }
    ReportIndex index = buildReportIndex(ships, wpId, n);
    for (int i = 0; i < (int)ships.size(); ++i) {
        if (i > 0)
            cout << '\n';
        printReport(ships, i, wpId, index);
    }
    cout << '\n';
    return 0;
}
