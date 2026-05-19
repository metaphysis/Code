// VTAS - Vessel Traffic Advisory Service
// UVa ID: 236
// Verdict: Wrong Answer
// Submission Date: 2026-05-19
// UVa Run Time: s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 将 HHMM 字符串转换为绝对分钟数
int timeToMinutes(string t) {
    while (t.length() < 4) t.insert(t.begin(), '0');
    return stoi(t.substr(0, 2)) * 60 + stoi(t.substr(2, 2));
}

// 将绝对分钟数转换为 HHMM 字符串（输出时使用）
string minutesToTime(int m) {
    m %= 1440;
    char buf[5];
    sprintf(buf, "%02d%02d", m / 60, m % 60);
    return buf;
}

// 船舶结构体
struct Vessel {
    string name;                // 船名
    int startMinutes;           // 起始绝对分钟数
    double speed;               // 速度（节）
    vector<int> waypointIdx;    // 航点索引序列
    vector<int> arrivalMinutes; // 到达各航点的绝对分钟数（四舍五入）
    bool invalidRoute;          // 是否无效路线
    Vessel() : invalidRoute(false) {}
};

// 判断两个时间区间是否重叠（处理跨午夜）
bool isOverlapped(int s1, int e1, int s2, int e2) {
    if (e1 < s1) e1 += 1440;
    if (e2 < s2) e2 += 1440;
    if (s2 < s1 - 720) { s2 += 1440; e2 += 1440; }
    else if (s2 > s1 + 720) { s2 -= 1440; e2 -= 1440; }
    if (e2 < s2) e2 += 1440;
    return max(s1, s2) < min(e1, e2);
}

// 判断两个时刻是否接近（≤ 3 分钟，处理跨午夜）
bool isClosing(int t1, int t2) {
    int diff = t2 - t1;
    if (diff > 720) diff -= 1440;
    if (diff < -720) diff += 1440;
    return abs(diff) <= 3;
}

// 相遇信息结构体（用于排序）
struct Encounter {
    string otherName;   // 对方船名
    char wp1, wp2;      // 航段两端点
    int otherStartTime; // 对方到达该段起点的时间
};

// 警告信息结构体（用于排序）
struct Warning {
    string otherName;       // 对方船名
    char wp;                // 航点
    int waypointIndex;      // 当前船的第几个航点（用于排序）
    int otherArrivalTime;   // 对方到达该航点的时间
};

int main() {
    int N;
    cin >> N;
    vector<char> waypointId(N);
    unordered_map<char, int> idToIdx;
    for (int i = 0; i < N; ++i) {
        cin >> waypointId[i];
        idToIdx[waypointId[i]] = i;
    }

    vector<vector<double>> dist(N, vector<double>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> dist[i][j];

    vector<Vessel> vessels;

    string vesselName;
    while (cin >> vesselName) {
        if (vesselName.front() == '*') break;
        Vessel v;
        v.name = vesselName;
        string startTime;
        cin >> startTime >> v.speed;
        v.startMinutes = timeToMinutes(startTime);
        string wp;
        cin >> wp;
        for (char c : wp) v.waypointIdx.push_back(idToIdx[c]);
        vessels.push_back(v);
    }

    // 第一遍：计算所有船舶的到达时间，标记无效路线
    for (int vi = 0; vi < vessels.size(); ++vi) {
        Vessel& v = vessels[vi];
        v.arrivalMinutes.clear();
        v.arrivalMinutes.push_back(v.startMinutes);
        double curTime = v.startMinutes;
        for (int i = 0; i < v.waypointIdx.size() - 1; ++i) {
            int u = v.waypointIdx[i];
            int w = v.waypointIdx[i + 1];
            if (dist[u][w] <= 0) {
                v.invalidRoute = true;
                break;
            }
            curTime += dist[u][w] / v.speed * 60.0;
            v.arrivalMinutes.push_back((int)(curTime + 0.5));
        }
    }

    // 第二遍：输出每艘船的信息
    for (int vi = 0; vi < vessels.size(); ++vi) {
        Vessel& v = vessels[vi];

        printf("%s entering system at %s with a planned speed of %.1f knots\n",
               v.name.c_str(), minutesToTime(v.startMinutes).c_str(), v.speed);

        if (v.invalidRoute) {
            printf("**> Invalid Route Plan for Vessel: %s\n", v.name.c_str());
            cout << '\n';
            continue;
        }

        // 输出航点表和到达时间表
        printf("          Waypoint:");
        for (int idx : v.waypointIdx) printf("%5c", waypointId[idx]);
        printf("\n          Arrival:  ");
        for (int t : v.arrivalMinutes) printf("%5s", minutesToTime(t).c_str());
        printf("\n");

        // ========== 相遇检测 ==========
        vector<Encounter> encounters;
        for (int j = 0; j < vessels.size(); ++j) {
            if (j == vi) continue;
            Vessel& other = vessels[j];
            if (other.invalidRoute) continue;
            for (int i = 0; i < v.waypointIdx.size() - 1; ++i) {
                int u = v.waypointIdx[i], w = v.waypointIdx[i + 1];
                int tStart = v.arrivalMinutes[i], tEnd = v.arrivalMinutes[i + 1];
                for (int k = 0; k < other.waypointIdx.size() - 1; ++k) {
                    int ou = other.waypointIdx[k], ow = other.waypointIdx[k + 1];
                    if ((u == ou && w == ow) || (u == ow && w == ou)) {
                        int otStart = other.arrivalMinutes[k], otEnd = other.arrivalMinutes[k + 1];
                        if (isOverlapped(tStart, tEnd, otStart, otEnd)) {
                            encounters.push_back({other.name, waypointId[u], waypointId[w], otStart});
                        }
                    }
                }
            }
        }

        // 排序：按对方到达起点时间从大到小，相同按船名
        sort(encounters.begin(), encounters.end(), [](const Encounter& a, const Encounter& b) {
            if (a.otherStartTime != b.otherStartTime) return a.otherStartTime > b.otherStartTime;
            return a.otherName < b.otherName;
        });

        // 输出去重
        set<pair<string, string>> printedEncounter;
        for (auto& e : encounters) {
            if (printedEncounter.count({e.otherName, string(1, e.wp1) + e.wp2})) continue;
            printf("Projected encounter with %s on leg between Waypoints %c & %c\n",
                   e.otherName.c_str(), e.wp1, e.wp2);
            printedEncounter.insert({e.otherName, string(1, e.wp1) + e.wp2});
        }

        // ========== 靠近警告检测 ==========
        vector<Warning> warnings;
        for (int i = 0; i < v.waypointIdx.size(); ++i) {
            int wp = v.waypointIdx[i];
            int t1 = v.arrivalMinutes[i];
            for (int j = 0; j < vessels.size(); ++j) {
                if (j == vi) continue;
                Vessel& other = vessels[j];
                if (other.invalidRoute) continue;
                for (int k = 0; k < other.waypointIdx.size(); ++k) {
                    if (other.waypointIdx[k] == wp) {
                        int t2 = other.arrivalMinutes[k];
                        if (isClosing(t1, t2)) {
                            warnings.push_back({other.name, waypointId[wp], i, t2});
                        }
                    }
                }
            }
        }

        // 排序：先按航点索引，再按对方到达时间从大到小，最后按船名
        sort(warnings.begin(), warnings.end(), [](const Warning& a, const Warning& b) {
            if (a.waypointIndex != b.waypointIndex) return a.waypointIndex < b.waypointIndex;
            if (a.otherArrivalTime != b.otherArrivalTime) return a.otherArrivalTime > b.otherArrivalTime;
            return a.otherName < b.otherName;
        });

        // 输出去重
        set<pair<string, char>> printedWarning;
        for (auto& w : warnings) {
            if (printedWarning.count({w.otherName, w.wp})) continue;
            printf("** Warning ** Close passing with %s at Waypoint %c\n",
                   w.otherName.c_str(), w.wp);
            printedWarning.insert({w.otherName, w.wp});
        }

        cout << '\n';
    }
    return 0;
}
