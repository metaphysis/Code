// Timetable
// UVa ID: 1725
// Verdict: Accepted
// Submission Date: 2026-10-07
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Train {
    int depart;
    int arrive;
    int from;
    int to;
};

int parseTime(const string &timeText) {
    return (timeText[0] - '0') * 600 + (timeText[1] - '0') * 60 + (timeText[3] - '0') * 10 + (timeText[4] - '0');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        int city, count, index, minute;
        vector<Train> trains;
        vector<vector<int>> departList(1440), arriveList(1440);
        for (city = 1; city <= n; city++) {
            cin >> count;
            for (int i = 0; i < count; i++) {
                string departText, arriveText;
                int depart, arrive, to;
                cin >> departText >> arriveText >> to;
                depart = parseTime(departText);
                arrive = parseTime(arriveText);
                index = trains.size();
                trains.push_back({depart, arrive, city, to});
                departList[depart].push_back(index);
                arriveList[arrive].push_back(index);
            }
        }
        vector<int> bestDepart(n + 1, -1), rideDepart(trains.size(), -1);
        vector<pair<int, int>> answer;
        int lastDepart = -1;
        for (minute = 0; minute < 1440; minute++) {
            for (int trainIndex : arriveList[minute]) {
                Train &train = trains[trainIndex];
                if (rideDepart[trainIndex] >= 0 && bestDepart[train.to] < rideDepart[trainIndex])
                    bestDepart[train.to] = rideDepart[trainIndex];
            }
            if (bestDepart[n] > lastDepart) {
                answer.push_back({bestDepart[n], minute});
                lastDepart = bestDepart[n];
            }
            for (int trainIndex : departList[minute]) {
                Train &train = trains[trainIndex];
                if (train.from == 1)
                    rideDepart[trainIndex] = minute;
                else if (bestDepart[train.from] >= 0)
                    rideDepart[trainIndex] = bestDepart[train.from];
            }
        }
        cout << answer.size() << '\n';
        for (pair<int, int> connection : answer) {
            int departHour, departMinute, arriveHour, arriveMinute;
            departHour = connection.first / 60;
            departMinute = connection.first % 60;
            arriveHour = connection.second / 60;
            arriveMinute = connection.second % 60;
            cout << setfill('0') << setw(2) << departHour << ':';
            cout << setfill('0') << setw(2) << departMinute << ' ';
            cout << setfill('0') << setw(2) << arriveHour << ':';
            cout << setfill('0') << setw(2) << arriveMinute << '\n';
        }
    }
    return 0;
}
