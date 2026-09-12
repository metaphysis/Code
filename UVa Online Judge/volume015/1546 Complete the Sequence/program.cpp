#include <bits/stdc++.h>
using namespace std;

int solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int s, c;
        cin >> s >> c;
        vector<long long> cur(s), last(s);
        int i, j;
        for (i = 0; i < s; i++)
            cin >> cur[i];
        for (i = 0; i < s; i++) {
            last[i] = cur.back();
            if (i + 1 == s)
                break;
            vector<long long> next;
            for (j = 0; j + 1 < (int)cur.size(); j++)
                next.push_back(cur[j + 1] - cur[j]);
            cur = next;
        }
        for (i = 0; i < c; i++) {
            if (s > 1) {
                for (j = s - 2; j >= 0; j--)
                    last[j] += last[j + 1];
            }
            if (i > 0)
                cout << ' ';
            cout << last[0];
        }
        cout << '\n';
    }
    return 0;
}

int main() {
    return solve();
}
