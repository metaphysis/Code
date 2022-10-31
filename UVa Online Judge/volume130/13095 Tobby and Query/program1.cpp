// Tobby and Query
// UVa ID: 13095
// Verdict: Accepted
// Submission Date: 2022-10-30
// UVa Run Time: 0.270s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net


#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

int bit[MAXN], a[MAXN], pos[MAXN], answer[MAXN], n, m;

int query(int x) {
    int sum = 0;
    while (x) {
        sum += bit[x];
        x -= x & -x;
    }
    return sum;
}

void add(int x, int k) {
    while (x <= n) {
        bit[x] += k;
        x += x & -x;
    }
}

struct interval { int l, r, id; } q[MAXN];

bool cmp(const interval & a, const interval & b) { return a.r < b.r; }

int main(int argc, char *argv[]) {
    while (cin >> n) {
        memset(bit, 0, sizeof bit);
        memset(pos, 0, sizeof pos);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> q[i].l >> q[i].r;
            q[i].id = i;
        }
        sort(q, q + m, cmp);
        int r = 0;
        for (int i = 0; i < m; i++) {
            while (r < q[i].r) {
                r++;
                add(r, 1);
                if (pos[a[r]]) add(pos[a[r]], -1);
                pos[a[r]] = r;
            }
            answer[q[i].id] = query(r) - query(q[i].l - 1);
        }
        for (int i = 0; i < m; i++) cout << answer[i] << '\n';
    }
    return 0;
}
