// Friendship Networks
// UVa ID: 12786
// Verdict: Accepted
// Submission Date: 2023-04-28
// UVa Run Time: 0.270s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    vector<int> ds;
    while (cin >> n) {
        ds.clear();
        for (int i = 0, d; i < n; i++) {
            cin >> d;
            ds.push_back(d);
        }
        sort(ds.begin(), ds.end(), greater<int>());
        int flag = 1;
        while (true) {
            int u = ds.front();
            ds[0] = 0;
            for (int i = 1, j = 0; i < ds.size() && j < u; i++, j++)
                if (!ds[i]) { flag = 0; break; }
                else ds[i]--;
            if (!flag) break;
            sort(ds.begin(), ds.end(), greater<int>());
            if (ds.front() == 0 && ds.back() == 0) break;
        }
        cout << flag << '\n';
    }
    return 0;
}
