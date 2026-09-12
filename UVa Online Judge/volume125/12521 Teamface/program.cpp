#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, tc = 0;
    while (cin >> t >> n, t || n) {
        int m = n / t;
        vector<string> name(t);
        vector<int> cap(t);
        for (int i = 0; i < t; ++i)
            cin >> name[i] >> cap[i];
        vector<vector<unsigned char>> adj(n + 1, vector<unsigned char>(n + 1));
        vector<vector<int>> fr(n + 1);
        vector<int> sz(n + 1);
        for (int i = 0; i < n; ++i) {
            int x, s, f;
            cin >> x >> s >> f;
            sz[x] = s;
            while (f--) {
                int y;
                cin >> y;
                if (!adj[x][y]) {
                    adj[x][y] = adj[y][x] = 1;
                    fr[x].push_back(y);
                    fr[y].push_back(x);
                }
            }
        }
        cout << "Case " << ++tc << ":\n";
        vector<int> mark(n + 1), cnt(n + 1);
        int tag = 0;
        for (int i = 0; i < t; ++i) {
            ++tag;
            vector<int> cand, team;
            cand.push_back(cap[i]);
            for (int x : fr[cap[i]])
                cand.push_back(x);
            for (int x : cand)
                mark[x] = tag;
            for (int x : cand) {
                cnt[x] = 0;
                for (int y : fr[x])
                    if (mark[y] == tag) ++cnt[x];
            }
            for (int x : cand)
                if (cnt[x] >= m - 1) team.push_back(x);
            vector<int> num(51);
            for (int x : team)
                ++num[sz[x]];
            cout << name[i] << '\n';
            for (int s = 1; s <= 50; ++s)
                if (num[s]) cout << s << ' ' << num[s] << '\n';
        }
    }
    return 0;
}
