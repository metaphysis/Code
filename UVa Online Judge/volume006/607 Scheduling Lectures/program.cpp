// Scheduling Lectures
// UVa ID: 607
// Verdict: Accepted
// Submission Date: 2017-06-25
// UVa Run Time: 0.260s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30, MAXN = 1024;

int N, L, C, T, topics[MAXN], DI[MAXN][MAXN], visited[MAXN][MAXN];
int cases = 0;

int cost(int m)
{
    int r = L - m;
    if (r == 0) return 0;
    if (1 <= r && r <= 10) return -C;
    return (r - 10) * (r - 10);
}

int dp(int x, int y)
{
    if (visited[x][y]) return DI[x][y];

    int *di = &DI[x][y];
    if (x == 0) return y ? INF : 0;
    else
    {
        *di = INF;
        int m = 0;
        for (int i = y; i >= 1; i--)
        {
            m += topics[i];
            if (m > L) break;
            int best = dp(x - 1, i - 1);
            if (best != INF) *di = min(best + cost(m), *di);
        }
        visited[x][y] = 1;
        return *di;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N, N > 0)
    {
        cin >> L >> C;
        
        memset(visited, 0, sizeof(visited));

        int minutes = 0;
        T = 1;

        for (int i = 1; i <= N; i++)
        {
            cin >> topics[i];
            
            minutes += topics[i];
            if (minutes > L)
            {
                T++;
                minutes = topics[i];
            }
        }

        if (cases++ > 0) cout << '\n';
        cout << "Case " << cases << ":\n";
        cout << "Minimum number of lectures: " << T << '\n';
        cout << "Total dissatisfaction index: " << dp(T, N) << '\n';
    }
    
    return 0;
}
