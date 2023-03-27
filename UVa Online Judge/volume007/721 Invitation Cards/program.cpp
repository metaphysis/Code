// Invitation Cards
// UVa ID: 721
// Verdict: Accepted
// Submission Date: 2023-03-27
// UVa Run Time: 0.310s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010, INF = 0x3f3f3f3f;

struct edge {
    int v, w, nxt;
} g1[MAXN], g2[MAXN];

struct block {
    int u, d;
    bool operator<(const block &b) const { return d > b.d; }
};

int head1[MAXN], head2[MAXN], d1[MAXN], d2[MAXN], cnt1, cnt2;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases, P, Q;
    cin >> cases;
    while (cases--) {
        cin >> P >> Q;
        cnt1 = cnt2 = 0;
        for (int i = 1; i <= P; i++) head1[i] = head2[i] = -1;
        for (int i = 0, u, v, w; i < Q; i++) {
            cin >> u >> v >> w;
            g1[cnt1] = edge{v, w, head1[u]};
            head1[u] = cnt1++;
            g2[cnt2] = edge{u, w, head2[v]};
            head2[v] = cnt2++;
        }
        for (int i = 1; i <= P; i++) d1[i] = INF;
        d1[1] = 0;
        priority_queue<block> q;
        q.push(block{1, d1[1]});
        while (!q.empty()) {
            block b1 = q.top(); q.pop();
            if (d1[b1.u] < b1.d) continue;
            for (int i = head1[b1.u]; ~i; i = g1[i].nxt)
                if (d1[g1[i].v] > d1[b1.u] + g1[i].w) {
                    d1[g1[i].v] = d1[b1.u] + g1[i].w;
                    q.push(block{g1[i].v, d1[g1[i].v]});
                }
        }
        for (int i = 1; i <= P; i++) d2[i] = INF;
        d2[1] = 0;
        q.push(block{1, d2[1]});
        while (!q.empty()) {
            block b2 = q.top(); q.pop();
            if (d2[b2.u] < b2.d) continue;
            for (int i = head2[b2.u]; ~i; i = g2[i].nxt)
                if (d2[g2[i].v] > d2[b2.u] + g2[i].w) {
                    d2[g2[i].v] = d2[b2.u] + g2[i].w;
                    q.push(block{g2[i].v, d2[g2[i].v]});
                }
        }
        long long sum = 0;
        for (int i = 1; i <= P; i++) sum += d1[i] + d2[i];
        cout << sum << '\n';
    }
    return 0;
}
