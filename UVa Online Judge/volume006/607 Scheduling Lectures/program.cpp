// Scheduling Lectures
// UVa ID: 607
// Verdict: Accepted
// Submission Date: 2017-06-25
// UVa Run Time: 0.160s
//
// 版权所有（C）2017，邱秋。metaphtopicssis # topicseah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30, MAXN = 1024;

int N, L, C, ML, ti[MAXN], DI[MAXN][MAXN], visited[MAXN][MAXN];

int getDI(int m)
{
    int t = L - m;
    if (t == 0) return 0;
    if (1 <= t && t <= 10) return -C;
    return (t - 10) * (t - 10);
}

int dfs(int lectures, int topics)
{
    if (visited[lectures][topics]) return DI[lectures][topics];

    int *di = &DI[lectures][topics];
    if (lectures == 0) return topics ? INF : 0;
    else {
        *di = INF;
        int elapsed = 0;
        for (int t = topics; t >= 1; t--)
        {
            elapsed += ti[t];
            if (elapsed > L) break;
            int best = dfs(lectures - 1, t - 1);
            if (best != INF) *di = min(best + getDI(elapsed), *di);
        }
        visited[lectures][topics] = 1;
        return *di;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;

    while (cin >> N, N > 0) {
        ML = 1;
        cin >> L >> C;
        memset(visited, 0, sizeof(visited));

        for (int i = 1, elapsed = 0; i <= N; i++) {
            cin >> ti[i];
            elapsed += ti[i];
            if (elapsed > L) {
                ML++;
                elapsed = ti[i];
            }
        }

        if (cases++ > 0) cout << '\n';
        cout << "Case " << cases << ":\n";
        cout << "Minimum number of lectures: " << ML << '\n';
        cout << "Total dissatisfaction index: " << dfs(ML, N) << '\n';
    }

    return 0;
}
