// Schedule of Taiwan Baseball League
// UVa ID: 678
// Verdict: Accepted
// Submission Date: 2026-07-02
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct DayInfo {
    vector<pair<int,int>> taipei;
    vector<pair<int,int>> kaohsiung;
};

// 生成两个大小相等的集合之间的 m 天完美匹配（循环平移）
vector<vector<pair<int,int>>> generateCrossMatches(const vector<int>& X, const vector<int>& Y) {
    int m = (int)X.size();
    vector<vector<pair<int,int>>> res(m);
    for (int d = 0; d < m; ++d) {
        for (int i = 0; i < m; ++i)
            res[d].push_back({X[i], Y[(i + d) % m]});
    }
    return res;
}

// 递归生成大小为 s（2 的幂）的队伍集合的单循环赛程（只生成配对，不分配场地）
vector<vector<pair<int,int>>> generateRoundRobin(const vector<int>& teams) {
    int s = (int)teams.size();
    vector<vector<pair<int,int>>> days;
    if (s == 2) {
        days.push_back({{teams[0], teams[1]}});
        return days;
    }
    int m = s / 2;
    vector<int> left(teams.begin(), teams.begin() + m);
    vector<int> right(teams.begin() + m, teams.end());
    vector<vector<pair<int,int>>> leftDays = generateRoundRobin(left);
    vector<vector<pair<int,int>>> rightDays = generateRoundRobin(right);
    // 内部阶段：左右两组内部比赛并行进行，共 m-1 天
    for (int i = 0; i < m - 1; ++i) {
        vector<pair<int,int>> cur;
        cur.insert(cur.end(), leftDays[i].begin(), leftDays[i].end());
        cur.insert(cur.end(), rightDays[i].begin(), rightDays[i].end());
        days.push_back(cur);
    }
    // 跨组阶段：生成两组之间的比赛，共 m 天
    vector<vector<pair<int,int>>> cross = generateCrossMatches(left, right);
    for (int i = 0; i < m; ++i) {
        vector<pair<int,int>> cur;
        cur.insert(cur.end(), cross[i].begin(), cross[i].end());
        days.push_back(cur);
    }
    return days;
}

int main() {
    int K;
    cin >> K;
    vector<int> Ns(K);
    for (int i = 0; i < K; ++i) cin >> Ns[i];
    for (int idx = 0; idx < K; ++idx) {
        if (idx) cout << '\n';          // 用例间空行
        int N = Ns[idx];
        int m = N / 4;                  // N 为 2 的幂且 >= 4
        // 构造四组队伍编号（内部使用 0-based）
        vector<int> A1(m), A2(m), B1(m), B2(m);
        for (int i = 0; i < m; ++i) A1[i] = i;
        for (int i = 0; i < m; ++i) A2[i] = m + i;
        for (int i = 0; i < m; ++i) B1[i] = 2 * m + i;
        for (int i = 0; i < m; ++i) B2[i] = 3 * m + i;
        vector<int> A(2 * m), B(2 * m);
        iota(A.begin(), A.end(), 0);
        iota(B.begin(), B.end(), 2 * m);
        // 内部赛程
        vector<vector<pair<int,int>>> innerA = generateRoundRobin(A); // 2m-1 天
        vector<vector<pair<int,int>>> innerB = generateRoundRobin(B);
        // 跨组匹配
        vector<vector<pair<int,int>>> matchA1B1 = generateCrossMatches(A1, B1);
        vector<vector<pair<int,int>>> matchA2B2 = generateCrossMatches(A2, B2);
        vector<vector<pair<int,int>>> matchA1B2 = generateCrossMatches(A1, B2);
        vector<vector<pair<int,int>>> matchA2B1 = generateCrossMatches(A2, B1);
        int totalDays = N - 1;
        vector<DayInfo> schedule(totalDays);
        // 内部阶段
        for (int d = 0; d < 2 * m - 1; ++d) {
            schedule[d].taipei = innerA[d];
            schedule[d].kaohsiung = innerB[d];
        }
        // 跨组阶段1（前 m 天）
        for (int d = 0; d < m; ++d) {
            int day = (2 * m - 1) + d;
            schedule[day].taipei = matchA1B1[d];
            schedule[day].kaohsiung = matchA2B2[d];
        }
        // 跨组阶段2（后 m 天）
        for (int d = 0; d < m; ++d) {
            int day = (2 * m - 1) + m + d;
            schedule[day].taipei = matchA1B2[d];
            schedule[day].kaohsiung = matchA2B1[d];
        }
        // 计算每天每支球队所在城市（0:台北, 1:高雄）
        vector<vector<int>> cityPerDay(totalDays, vector<int>(N, -1));
        for (int d = 0; d < totalDays; ++d) {
            for (auto& p : schedule[d].taipei) {
                cityPerDay[d][p.first] = 0;
                cityPerDay[d][p.second] = 0;
            }
            for (auto& p : schedule[d].kaohsiung) {
                cityPerDay[d][p.first] = 1;
                cityPerDay[d][p.second] = 1;
            }
        }
        int totalTravels = 0;
        // 输出每一天
        for (int d = 0; d < totalDays; ++d) {
            cout << "Day " << d + 1 << ":\n";
            cout << "  Taipei:";
            for (size_t i = 0; i < schedule[d].taipei.size(); ++i)
                cout << " (" << schedule[d].taipei[i].first + 1 << "-" << schedule[d].taipei[i].second + 1 << ")";
            cout << ".\n";
            cout << "  Kaohsiung:";
            for (size_t i = 0; i < schedule[d].kaohsiung.size(); ++i)
                cout << " (" << schedule[d].kaohsiung[i].first + 1 << "-" << schedule[d].kaohsiung[i].second + 1 << ")";
            cout << ".\n";
            // 输出从当前天到下一日的旅行信息（最后一天无后续）
            if (d < totalDays - 1) {
                vector<int> travelers;
                for (int i = 0; i < N; ++i) {
                    if (cityPerDay[d][i] != cityPerDay[d + 1][i]) {
                        travelers.push_back(i);
                        ++totalTravels;
                    }
                }
                if (travelers.empty()) {
                    cout << "  No teams travelling between day " << d + 1 << " and day " << d + 2 << "." << endl;
                } else {
                    cout << "  Teams travelling between day " << d + 1 << " and day " << d + 2 << ": ";
                    for (size_t i = 0; i < travelers.size(); ++i) {
                        if (i > 0) cout << ",";
                        cout << travelers[i] + 1;
                    }
                    cout << "." << endl;
                }
            }
        }
        cout << "Total number of travels: " << totalTravels << endl;
    }
    return 0;
}
