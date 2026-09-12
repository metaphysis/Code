#include <bits/stdc++.h>
using namespace std;

struct Bowl {
    long double h, r, top;
};
int n;
vector<Bowl> bowls;
vector<vector<long double> > gap;

bool canPut(int a, int b, long double d) {
    if (d >= bowls[a].h) return true;
    long double sa = (bowls[a].top - bowls[a].r) / bowls[a].h, sb = (bowls[b].top - bowls[b].r) / bowls[b].h;
    long double len = min(bowls[b].h, bowls[a].h - d), x1 = d, x2 = d + len;
    long double f1 = bowls[a].r + sa * x1 - bowls[b].r;
    long double f2 = bowls[a].r + sa * x2 - bowls[b].r - sb * len;
    return f1 >= -1e-12L && f2 >= -1e-12L;
}

long double getGap(int a, int b) {
    long double l = 0, r = bowls[a].h;
    for (int k = 0; k < 80; k++) {
        long double mid = (l + r) / 2;
        if (canPut(a, b, mid)) r = mid;
        else l = mid;
    }
    return r;
}

long double getAns() {
    vector<int> p(n);
    long double ans = 1e100L;
    for (int i = 0; i < n; i++) p[i] = i;
    do {
        vector<long double> pos(n, 0);
        for (int k = 1; k < n; k++) {
            pos[k] = 0;
            for (int i = 0; i < k; i++) pos[k] = max(pos[k], pos[i] + gap[p[i]][p[k]]);
        }
        long double cur = 0;
        for (int i = 0; i < n; i++) cur = max(cur, pos[i] + bowls[p[i]].h);
        ans = min(ans, cur);
    } while (next_permutation(p.begin(), p.end()));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        bowls.resize(n);
        for (int i = 0; i < n; i++) cin >> bowls[i].h >> bowls[i].r >> bowls[i].top;
        gap.assign(n, vector<long double>(n, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j) gap[i][j] = getGap(i, j);
        cout << (long long)floor(getAns() + 1e-9L) << '\n';
    }
    return 0;
}
