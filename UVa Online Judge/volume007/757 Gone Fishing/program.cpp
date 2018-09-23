// Gone Fishing
// UVa ID: 757
// Verdict: Accepted
// Submission Date: 2018-09-23
// UVa Run Time: 0.190s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, h, fi[32], di[32], ti[32];
int cache[32][1024], used[32][1024];

int dfs(int idx, int minutes)
{
    if (idx == n || minutes >= h) return 0;
    if (~cache[idx][minutes]) return cache[idx][minutes];

    int fishes = 0, most = 0, next = fi[idx], temp;

    // No Stop, continue to next lake.
    temp = dfs(idx + 1, minutes + ti[idx] * 5);
    if (temp >= most)
    {
        most = temp;
        used[idx][minutes] = 0;
    }
    
    // Stay and fishing.
    for (int m = minutes + 5; m <= h; m += 5)
    {
        fishes += next;
        temp = fishes + dfs(idx + 1, m + ti[idx] * 5);
        if (temp >= most)
        {
            most = temp;
            used[idx][minutes] = m - minutes;
        }
        // Use first then subtract.
        if (next <= di[idx]) next = 0;
        else next -= di[idx];
    }

    return cache[idx][minutes] = most;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    
    while (cin >> n, n > 0)
    {
        cin >> h;

        h *= 60;
        for (int i = 0; i < n; i++)
            cin >> fi[i];
        for (int i = 0; i < n; i++)
            cin >> di[i];
        for (int i = 0; i < n - 1; i++)
            cin >> ti[i];

        memset(cache, -1, sizeof(cache));
        memset(used, 0, sizeof(used));
        dfs(0, 0);

        if (cases++ > 0) cout << '\n';
        for (int i = 0, m = 0; i < n; i++)
        {
            if (i) cout << ", ";
            if (m <= h)
            {
                cout << used[i][m];
                m += used[i][m] + ti[i] * 5;
            }
            else
                cout << '0';
        }
        cout << '\n';
        cout << "Number of fish expected: " << cache[0][0] << '\n';
        
    }

    return 0;
}
