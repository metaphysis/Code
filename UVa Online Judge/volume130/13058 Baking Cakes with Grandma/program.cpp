#include <bits/stdc++.h>
using namespace std;

bool hasPoly(const vector<long long> &pos, const unordered_set<long long> &st, long long total, int m) {
    long long step = total / m, cur;
    for (int i = 0; i < (int)pos.size(); i++) {
        cur = pos[i];
        bool ok = true;
        for (int j = 1; j < m; j++) {
            cur += step;
            if (!st.count(cur)) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, ans;
    long long total;
    while (cin >> n) {
        vector<long long> arc(n), pos(n);
        total = 0;
        for (int i = 0; i < n; i++) {
            cin >> arc[i];
            total += arc[i];
        }
        pos[0] = 0;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + arc[i - 1];
        unordered_set<long long> st;
        for (int i = 0; i < n; i++) st.insert(pos[i]);
        vector<int> divs;
        for (long long i = 1; i * i <= total; i++) {
            if (total % i == 0) {
                if (i >= 3 && i <= n) divs.push_back((int)i);
                if (total / i != i && total / i >= 3 && total / i <= n) divs.push_back((int)(total / i));
            }
        }
        sort(divs.begin(), divs.end(), greater<int>());
        ans = -1;
        for (int i = 0; i < (int)divs.size(); i++) {
            if (hasPoly(pos, st, total, divs[i])) {
                ans = divs[i];
                break;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
