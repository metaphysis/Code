#include <bits/stdc++.h>

using namespace std;

int N, V;
int volume[128], price[128];
int dp1[128][1024], dp2[1024], flag[128];

int dfs(int n, int v)
{
    if (~dp1[n][v]) return dp1[n][v];
    if (n == N) return 0;
    int r1 = dfs(n + 1, v);
    int r2 = 0;
    if (v + volume[n] <= V) r2 = dfs(n + 1, v + volume[n]) + price[n];
    flag[n] = r1 < r2;
    return dp1[n][v] = max(r1, r2);
}

int main(int argc, char *argv[])
{
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> V;
        for (int i = 0; i < N; i++) cin >> volume[i] >> price[i];

        memset(dp1, -1, sizeof(dp1));
        memset(flag, 0, sizeof(flag));
        cout << dfs(0, 0) << ' ';

        memset(dp2, 0, sizeof(dp2));
        for (int n = 0; n < N; n++)
            for (int v = V; v >= volume[n]; v--)
                dp2[v] = max(dp2[v], dp2[v - volume[n]] + price[n]);
        cout << dp2[V] << '\n';
    }
    return 0;
}
