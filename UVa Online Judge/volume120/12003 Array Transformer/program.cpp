// Array Transformer
// UVa ID: 12003
// Verdict: Accepted
// Submission Date: 2020-04-29
// UVa Run Time: 0.990s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300010, MAXM = 1010;

int n, m, u, s, link[MAXN], A[MAXN], B[MAXN];
int head[MAXM], tail[MAXM];

void build()
{
    s = sqrt(n);
    int block = n / s;
    if (block * s < n) block++;
    for (int i = 1; i <= block; i++) head[i] = (i - 1) * s + 1, tail[i] = i * s;
    tail[block] = n;
    for (int i = 1; i <= block; i++) {
        for (int j = head[i]; j <= tail[i]; j++) link[j] = i;
        sort(A + head[i], A + tail[i] + 1);
    }
}

int query(int L, int R, int v)
{
    int k = 0;
    for (int i = L; i <= min(R, tail[link[L]]); i++) k += (B[i] < v);
    for (int i = link[L] + 1; i < link[R]; i++)
        k += lower_bound(A + head[i], A + tail[i] + 1, v) - A - head[i];
    if (link[L] != link[R])
        for (int i = head[link[R]]; i <= R; i++) k += (B[i] < v);
    return k;
}

void update(int L, int R, int p, int k)
{
    int belong = link[p];
    int pp = lower_bound(A + head[belong], A + tail[belong] + 1, B[p]) - A;
    B[p] = (long long)(u) * k / (R - L + 1);
    while (pp > head[belong] && B[p] < A[pp - 1]) { swap(A[pp - 1], A[pp]); pp--; }
    while (pp < tail[belong] && B[p] > A[pp + 1]) { swap(A[pp + 1], A[pp]); pp++; }
    A[pp] = B[p];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> n >> m >> u;
    for (int i = 1; i <= n; i++) {
        cin >> A[i]; B[i] = A[i];
    }
    build();
    for (int i = 1, L, R, v, p; i <= m; i++) {
        cin >> L >> R >> v >> p;
        update(L, R, p, query(L, R, v));
    }
    for (int i = 1; i <= n; i++) cout << B[i] << '\n';

    return 0;
}
