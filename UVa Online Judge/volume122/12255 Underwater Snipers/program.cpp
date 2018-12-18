// Underwater Snipers
// UVa ID: 12255
// Verdict: Accepted
// Submission Date: 2018-12-18
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    long long x, y;
    point (long long x = 0, long long y = 0): x(x), y(y) {}
    bool operator<(const point &p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
} guards[10010];

int T;
long long k, N, S, D;

bool satisfy(long long m)
{
    long long H = guards[0].y - k + m;
    if (H > D) return false;
    int s = 1;
    long long X = guards[0].x + (long long)sqrt(D * D - H * H), w, h;
    for (int i = 0; i < N; i++)
    {
        w = guards[i].x - X, h = guards[i].y - k + m;
        if (w * w + h * h <= D * D) continue;
        if (h > D)
        {
            s = S + 1;
            break;
        }
        X = guards[i].x + (long long)sqrt(D * D - h * h);
        s++;
        if (s > S) break;
    }
    return s <= S;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> k >> N >> S >> D;
        for (int i = 0; i < N; i++) cin >> guards[i].x >> guards[i].y;
        sort(guards, guards + N);
        long long low = 1LL, high = 10000000000LL, m, M;
        if (!satisfy(low))
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        while (low <= high)
        {
            m = (low + high) / 2;
            if (satisfy(m)) M = m, low = m + 1;
            else high = m - 1;
        }
        cout << M << '\n';
    }

    return 0;
}
