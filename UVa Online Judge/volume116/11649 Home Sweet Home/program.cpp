#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int np, nh;
        cin >> np >> nh;
        int a, b, c;
        cin >> a >> b >> c;
        vector<int> ph(np), hh(nh), pr(nh);
        ph[0] = c % 10000 + 1;
        if (np > 1) ph[1] = (a * ph[0] + c) % 10000 + 1;
        for (int i = 2; i < np; i++) ph[i] = (a * ph[i - 1] + b * ph[i - 2] + c) % 10000 + 1;
        int e, f, g, h, ii, j;
        cin >> e >> f >> g >> h >> ii >> j;
        hh[0] = g % 10000 + 1;
        pr[0] = j % 100000 + 1;
        for (int i = 1; i < nh; i++) {
            hh[i] = (e * hh[i - 1] + f * pr[i - 1] + g) % 10000 + 1;
            pr[i] = (h * pr[i - 1] + ii * hh[i - 1] + j) % 100000 + 1;
        }
        vector<pair<int, int>> home(nh);
        for (int i = 0; i < nh; i++) home[i] = {hh[i], pr[i]};
        sort(ph.rbegin(), ph.rend());
        sort(home.rbegin(), home.rend());
        priority_queue<int> pq;
        long long sum = 0;
        int pos = 0, cnt = 0;
        for (auto [height, need] : home) {
            while (pos < np && ph[pos] >= height) pos++;
            pq.push(need);
            sum += need;
            if (sum > pos) {
                sum -= pq.top();
                pq.pop();
            }
        }
        cnt = (int)pq.size();
        cout << "Case " << cs << ": " << cnt << '\n';
    }
    return 0;
}
