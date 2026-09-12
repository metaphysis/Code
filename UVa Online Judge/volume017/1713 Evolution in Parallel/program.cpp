#include <bits/stdc++.h>
using namespace std;

vector<string> seqs;

bool isSub(int a, int b) {
    if (a == -1) return true;
    int i = 0, j = 0, n = seqs[a].size(), m = seqs[b].size();
    while (i < n && j < m) {
        if (seqs[a][i] == seqs[b][j]) i++;
        j++;
    }
    return i == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        string now;
        cin >> now;
        seqs.assign(n, "");
        for (int i = 0; i < n; i++) cin >> seqs[i];
        bool ok = true;
        for (int i = 0; i < n; i++) {
            int p = 0, q = 0;
            while (p < (int)seqs[i].size() && q < (int)now.size()) {
                if (seqs[i][p] == now[q]) p++;
                q++;
            }
            if (p != (int)seqs[i].size()) ok = false;
        }
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [](int a, int b) {
            return seqs[a].size() < seqs[b].size();
        });
        vector<vector<int>> grp;
        for (int l = 0; l < n;) {
            int r = l;
            while (r < n && seqs[ord[r]].size() == seqs[ord[l]].size()) r++;
            if (r - l > 2) ok = false;
            vector<int> cur;
            for (int i = l; i < r; i++) cur.push_back(ord[i]);
            grp.push_back(cur);
            l = r;
        }
        vector<vector<char>> can(n, vector<char>(n + 1));
        int g = grp.size();
        for (int i = 0; i < g && ok; i++) {
            if (grp[i].size() == 1) {
                int x = grp[i][0];
                if (i == 0) can[x][n] = 1;
                else if (grp[i - 1].size() == 1) {
                    int p = grp[i - 1][0];
                    bool a = isSub(p, x);
                    for (int j = 0; j <= n; j++) {
                        if (!can[p][j]) continue;
                        if (a) can[x][j] = 1;
                        if (isSub(j == n ? -1 : j, x)) can[x][p] = 1;
                    }
                } else {
                    int a = grp[i - 1][0], b = grp[i - 1][1];
                    if (isSub(a, x)) can[x][b] = 1;
                    if (isSub(b, x)) can[x][a] = 1;
                }
                bool any = false;
                for (int j = 0; j <= n; j++) any = any || can[x][j];
                if (!any) ok = false;
            } else {
                int x = grp[i][0], y = grp[i][1];
                bool any = false;
                if (i == 0) any = true;
                else if (grp[i - 1].size() == 1) {
                    int p = grp[i - 1][0];
                    for (int j = 0; j <= n && !any; j++) {
                        if (!can[p][j]) continue;
                        int q = j == n ? -1 : j;
                        if (isSub(p, x) && isSub(q, y)) any = true;
                        if (isSub(p, y) && isSub(q, x)) any = true;
                    }
                } else {
                    int a = grp[i - 1][0], b = grp[i - 1][1];
                    if (isSub(a, x) && isSub(b, y)) any = true;
                    if (isSub(a, y) && isSub(b, x)) any = true;
                }
                if (!any) ok = false;
            }
        }
        if (!ok) {
            cout << "impossible\n";
            continue;
        }
        vector<int> bel(n);
        int flip = 0, other = -1;
        if (grp.back().size() == 1) {
            int x = grp.back()[0];
            for (int j = 0; j <= n; j++) {
                if (can[x][j]) {
                    other = j == n ? -1 : j;
                    break;
                }
            }
        }
        for (int i = g - 1; i >= 0; i--) {
            if (grp[i].size() == 1) {
                int x = grp[i][0];
                bel[x] = flip;
                if (i == 0) continue;
                if (grp[i - 1].size() == 1) {
                    int p = grp[i - 1][0];
                    if (other != p && can[p][other == -1 ? n : other] && isSub(p, x)) continue;
                    if (other == p) {
                        int pre = -1;
                        if (can[p][p == -1 ? n : p] && isSub(p, x)) pre = p;
                        for (int j = 0; j <= n && pre == -1; j++) {
                            int q = j == n ? -1 : j;
                            if (can[p][j] && isSub(q, x)) pre = q;
                        }
                        other = pre;
                        flip ^= 1;
                    }
                } else {
                    int a = grp[i - 1][0], b = grp[i - 1][1];
                    if (other == a) flip ^= 1;
                    other = -1;
                }
            } else {
                int x = grp[i][0], y = grp[i][1];
                bel[x] = flip;
                bel[y] = flip ^ 1;
                if (i == 0) continue;
                if (grp[i - 1].size() == 1) {
                    int p = grp[i - 1][0], pre = -1;
                    for (int j = 0; j <= n; j++) {
                        int q = j == n ? -1 : j;
                        if (can[p][j] && isSub(p, x) && isSub(q, y)) {
                            pre = q;
                            break;
                        }
                    }
                    if (pre == -1) {
                        for (int j = 0; j <= n; j++) {
                            int q = j == n ? -1 : j;
                            if (can[p][j] && isSub(p, y) && isSub(q, x)) {
                                pre = q;
                                break;
                            }
                        }
                        flip ^= 1;
                    }
                    other = pre;
                } else {
                    int a = grp[i - 1][0], b = grp[i - 1][1];
                    if (isSub(a, y) && isSub(b, x)) flip ^= 1;
                    other = -1;
                }
            }
        }
        vector<int> path[2];
        for (int i = 0; i < n; i++) path[bel[i]].push_back(i);
        sort(path[0].begin(), path[0].end(), [](int a, int b) {
            return seqs[a].size() < seqs[b].size();
        });
        sort(path[1].begin(), path[1].end(), [](int a, int b) {
            return seqs[a].size() < seqs[b].size();
        });
        cout << path[0].size() << ' ' << path[1].size() << '\n';
        for (int x : path[0]) cout << seqs[x] << '\n';
        for (int x : path[1]) cout << seqs[x] << '\n';
    }
    return 0;
}
