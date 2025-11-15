// Oh Your Royal Greediness
// UVa ID: 11776
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int N;
    int caseNum = 1;
    while (cin >> N && N != -1) {
        vector<pair<int, int>> events; // (time, type) type: +1 start, -1 end
        for (int i = 0; i < N; i++) {
            int S, E;
            cin >> S >> E;
            events.push_back({S, 1});
            events.push_back({E, -1});
        }
        // 排序规则：时间升序，时间相同则开始事件在前
        sort(events.begin(), events.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second; // +1 在前，-1 在后
        });
        int count = 0;
        int max_count = 0;
        for (auto& e : events) {
            count += e.second;
            if (count > max_count) max_count = count;
        }
        cout << "Case " << caseNum << ": " << max_count << endl;
        caseNum++;
    }
    return 0;
}
