#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, MAXB = 10010;

int n, m, s, a[MAXN], link[MAXN];
vector<int> block[MAXB];

int query(int L) {
    int i = 1;
    while (i <= s && L > (int)block[i].size()) L -= block[i++].size();
    return block[i][L - 1];
}

void rebuild() {
    vector<int> tmp;
    for (int i = 1; i <= s; i++) {
        tmp.insert(tmp.end(), block[i].begin(), block[i].end());
        block[i].clear();
    }
    s = sqrt(m) + 1;
    for (int i = 1; i <= m; i++) block[(i - 1) / s + 1].push_back(tmp[i - 1]);
}

void update(int L, int x) {
    int i = 1;
    while (i <= s && L > (int)block[i].size()) L -= block[i++].size();
    block[i].insert(block[i].begin() + L - 1, x);
    if ((int)block[i].size() > 10 * s) rebuild();
}

int main(int argc, char *argv[]) {
    cin >> n;
    s = sqrt(n) + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        link[i] = (i - 1) / s + 1;
        block[link[i]].push_back(a[i]);
    }
    m = n;
    int c, L, R, x;
    for (int i = 0; i < n; i++) {
        cin >> c >> L >> R >> x;
        if (c == 0) { update(L, R); m++; }
        else cout << query(R) << '\n';
    }
    return 0;
}
