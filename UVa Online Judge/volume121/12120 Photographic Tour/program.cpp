// Photographic Tour
// UVa ID: 12120
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.030s

#include <bits/stdc++.h>
using namespace std;

struct Road {
    int to;
    int cost;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e;
    int caseNumber = 1;

    while (cin >> n >> e) {
        if (n == 0 && e == 0)
            break;

        vector<vector<Road>> graph(n);

        for (int i = 0; i < e; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            graph[x].push_back({y, z});
            graph[y].push_back({x, z});
        }

        int ticketCount;
        cin >> ticketCount;

        vector<int> tickets(ticketCount);
        for (int i = 0; i < ticketCount; ++i)
            cin >> tickets[i];

        vector<vector<bool>> forward(ticketCount + 1, vector<bool>(n, false));
        vector<vector<bool>> backward(ticketCount + 1, vector<bool>(n, false));

        // 正向计算使用前若干张车票后可以到达的地点
        forward[0][0] = true;

        for (int i = 0; i < ticketCount; ++i)
            for (int from = 0; from < n; ++from) {
                if (!forward[i][from])
                    continue;

                for (const Road &road : graph[from])
                    if (road.cost == tickets[i])
                        forward[i + 1][road.to] = true;
            }

        // 反向计算从某个地点出发能否完成剩余行程
        backward[ticketCount][n - 1] = true;

        for (int i = ticketCount - 1; i >= 0; --i)
            for (int from = 0; from < n; ++from)
                for (const Road &road : graph[from])
                    if (road.cost == tickets[i] && backward[i + 1][road.to])
                        backward[i][from] = true;

        int answer = 0;

        // 判断每个地点是否可能出现在某条合法路线中
        for (int place = 0; place < n; ++place) {
            bool possible = false;

            for (int i = 0; i <= ticketCount; ++i)
                if (forward[i][place] && backward[i][place]) {
                    possible = true;
                    break;
                }

            if (possible)
                ++answer;
        }

        cout << "Tour " << caseNumber++ << ": " << answer << '\n';
    }

    return 0;
}
