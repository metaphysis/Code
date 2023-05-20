// Back to Edit Distance
// UVa ID: 12747
// Verdict: Accepted
// Submission Date: 2023-05-20
// UVa Run Time: 0.120s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> order, events;

int lis() {
    vector<int> M; M.push_back(events.front());
    for (auto it = events.begin() + 1; it != events.end(); it++)
        if (*it > M.back()) M.push_back(*it);
        else {
            auto location = upper_bound(M.begin(), M.end(), *it);
            *location = *it;
        }
    return M.size();
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, index;
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        cin >> n;
        order.resize(n);
        events.resize(n);
        for (int i = 1; i <= n; i++) {
            cin >> index;
            order[index - 1] = i;
        }
        for (int i = 1; i <= n; i++) {
            cin >> index;
            events[i - 1] = order[index - 1];
        }
        cout << 2 * (n - lis()) << '\n';
    }
    return 0;
}
