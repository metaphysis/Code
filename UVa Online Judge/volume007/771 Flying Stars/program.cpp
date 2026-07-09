// Flying Stars
// UVa ID: 771
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 解析 "hh:mm" 为分钟数
int parseTime(const string& s) {
    int h = stoi(s.substr(0, 2));
    int m = stoi(s.substr(3, 2));
    return h * 60 + m;
}

// 解析时区 "+hh:mm" 或 "-hh:mm" 为分钟偏移
int parseTimezone(const string& s) {
    int sign = (s[0] == '+') ? 1 : -1;
    int h = stoi(s.substr(1, 2));
    int m = stoi(s.substr(4, 2));
    return sign * (h * 60 + m);
}

// 将分钟数格式化为 "hh:mm"（0~1439）
string formatTime(int t) {
    t %= 1440;
    if (t < 0) t += 1440;
    char buf[6];
    sprintf(buf, "%02d:%02d", t / 60, t % 60);
    return string(buf);
}

// 将总分钟数格式化为 "d:hh:mm"
string formatDuration(int total) {
    int days = total / 1440;
    int rem = total % 1440;
    char buf[20];
    sprintf(buf, "%d:%02d:%02d", days, rem / 60, rem % 60);
    return string(buf);
}

struct Flight {
    string id;
    string dest;
    int dep;   // 本地起飞时间，分钟 (0~1439)
    int dur;   // 飞行时长，分钟
};

struct Airport {
    string id;
    int offset;    // 时区偏移，分钟
    int boarding;  // 登机/转机耗时，分钟
    vector<Flight> flights;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string srcId, dstId, startStr;
    bool firstCase = true;
    while (cin >> srcId >> dstId >> startStr) {
        if (!firstCase) cout << '\n';
        firstCase = false;
        int N;
        cin >> N;
        unordered_map<string, int> idx;
        vector<Airport> airports(N);
        for (int i = 0; i < N; ++i) {
            string id, tz, boardStr;
            int M;
            cin >> id >> tz >> boardStr >> M;
            idx[id] = i;
            airports[i].id = id;
            airports[i].offset = parseTimezone(tz);
            airports[i].boarding = parseTime(boardStr);
            airports[i].flights.resize(M);
            for (int j = 0; j < M; ++j) {
                string fid, dest, depStr, durStr;
                cin >> fid >> dest >> depStr >> durStr;
                airports[i].flights[j].id = fid;
                airports[i].flights[j].dest = dest;
                airports[i].flights[j].dep = parseTime(depStr);
                airports[i].flights[j].dur = parseTime(durStr);
            }
        }
        int src = idx[srcId];
        int dst = idx[dstId];
        int startLocal = parseTime(startStr);
        int offsetSrc = airports[src].offset;
        const int INF = 1e9;
        vector<int> dist(N, INF);
        vector<int> prevNode(N, -1);
        vector<string> prevFlight(N, "");
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[src] = 0;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [curDist, u] = pq.top();
            pq.pop();
            if (curDist != dist[u]) continue;
            if (u == dst) break;
            int ready = curDist + airports[u].boarding; // 可登机绝对时间
            // 计算 ready 时刻该机场的本地时间
            int localReady = (startLocal + ready + (airports[u].offset - offsetSrc)) % 1440;
            if (localReady < 0) localReady += 1440;
            for (const Flight& f : airports[u].flights) {
                int wait = (f.dep - localReady) % 1440;
                if (wait < 0) wait += 1440;
                int depAbs = ready + wait;
                int arrAbs = depAbs + f.dur;
                int v = idx[f.dest];
                if (arrAbs < dist[v]) {
                    dist[v] = arrAbs;
                    prevNode[v] = u;
                    prevFlight[v] = f.id;
                    pq.push({arrAbs, v});
                }
            }
        }
        // 输出总旅行时间
        cout << formatDuration(dist[dst]) << '\n';
        // 输出到达目的地当地时间
        int arrivalLocal = (startLocal + dist[dst] + (airports[dst].offset - offsetSrc)) % 1440;
        if (arrivalLocal < 0) arrivalLocal += 1440;
        cout << formatTime(arrivalLocal) << '\n';
        // 回溯路径
        vector<string> route;
        int cur = dst;
        while (cur != src) {
            route.push_back(prevFlight[cur]);
            cur = prevNode[cur];
        }
        reverse(route.begin(), route.end());
        for (const string& fid : route) cout << fid << '\n';
    }
    return 0;
}
