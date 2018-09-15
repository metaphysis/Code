// Fast Food
// UVa ID: 662
// Verdict: Accepted
// Submission Date: 2018-09-15
// UVa Run Time: 0.040s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct state
{
    int sum, pre_depot;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int N, K, dist[210], interval[210][210], tds[210][210];
    state dp[210][210];

    while (cin >> N >> K)
    {
        if (N == 0) break;

        for (int i = 1; i <= N; i++)
        {
            cin >> dist[i];
            if (i > 1) dist[i] -= dist[1];
        }
        dist[1] = 0;

        for (int i = 1; i <= N; i++)
            for (int j = i; j <= N; j++)
                interval[i][j] = interval[j][i] = abs(dist[i] - dist[j]);

        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
            {
                tds[i][j] = 0;
                for (int k = min(i, j); k <= max(i, j); k++)
                    tds[i][j] += interval[k][i];
            }

        memset(dp, 0x3f, sizeof(dp));
        for (int i = 1; i <= N; i++)
        {
            dp[1][i].sum = tds[i][1] + tds[i][N];
            dp[1][i].pre_depot = i;
        }
        for (int i = 1; i < K; i++)
            for (int j = 1; j <= N; j++)
            {
                if (dp[i][j].sum == INF) continue;
                for (int k = j + 1; k <= N; k++)
                {
                    int new_sum = dp[i][j].sum - tds[j][N];
                    for (int l = j + 1; l < k; l++)
                        new_sum += min(interval[l][j], interval[l][k]);
                    new_sum += tds[k][N];
                    if (new_sum < dp[i + 1][k].sum)
                    {
                        dp[i + 1][k].sum = new_sum;
                        dp[i + 1][k].pre_depot = j;
                    }
                }
            }

        cout << "Chain " << ++cases << '\n';
        int minimal_sum = INF, last_depot = -1;
        for (int i = 1; i <= N; i++)
            if (minimal_sum > dp[K][i].sum)
            {
                minimal_sum = dp[K][i].sum;
                last_depot = i;
            }
        vector<int> all_depot;
        int idx = K;
        while (idx)
        {
            all_depot.push_back(last_depot);
            last_depot = dp[idx--][last_depot].pre_depot;
        }

        reverse(all_depot.begin(), all_depot.end());
        vector<int> served[all_depot.size()];
        int start, end, pre_depot, next_depot, pre_i, next_i;
        for (int i = 0; i < all_depot.size(); i++)
        {
            if (i == 0) start = 1;
            else start = all_depot[i];

            if (i == all_depot.size() - 1) end = N;
            else end = all_depot[i + 1];

            pre_depot = all_depot[i];
            if (i == all_depot.size() - 1) next_depot = all_depot[i];
            else next_depot = all_depot[i + 1];

            pre_i = i;
            if (i == all_depot.size() - 1) next_i = i;
            else next_i = i + 1;
            for (int j = start; j <= end; j++)
            {
                if (interval[j][pre_depot] < interval[j][next_depot]) served[pre_i].push_back(j);
                else served[next_i].push_back(j);
            }
        }

        for (int i = 0; i < all_depot.size(); i++)
        {
            cout << "Depot " << (i + 1);
            cout << " at restaurant " << all_depot[i];
            cout << " serves ";
            if (served[i].front() == served[i].back())
            {
                cout << "restaurant ";
                cout << served[i].front();
            }
            else
            {
                cout << "restaurants ";
                cout << served[i].front() << " to " << served[i].back();
            }
            cout << '\n';
        }
        cout << "Total distance sum = " << minimal_sum << '\n';
        cout << '\n';
    }

    return 0;
}
