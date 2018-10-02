// Free Parentheses
// UVa ID: 1238
// Verdict: Accepted
// Submission Date: 2018-10-02
// UVa Run Time: 0.120s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, number[32], sign[32] = {1}, visited[32][32][6100];
int offset, used[6100];

void dfs(int idx, int open_parentheses, int sum_so_far)
{
    // Check if we have arrived the end of expression or not.
    if (idx == N)
    {
        used[sum_so_far + offset] = 1;
        return;
    }
    // If current state visited, stop and return, it is no need to bactrack.
    if (visited[idx][open_parentheses][sum_so_far + offset]) return;
    // Set current state to visited.
    visited[idx][open_parentheses][sum_so_far + offset] = 1;
    // The idxth number contributes to final expression on current state.
    sum_so_far += number[idx] * sign[idx] * ((open_parentheses % 2 == 1) ? -1 : 1);
    // Add an open parentheses after a subtraction sign.
    if (sign[idx] == -1)
        dfs(idx + 1, open_parentheses + 1, sum_so_far);
    // Add a close parentheses after a number if open parentheses is not zero.
    if (open_parentheses) dfs(idx + 1, open_parentheses - 1, sum_so_far);
    // Do nothing.
    dfs(idx + 1, open_parentheses, sum_so_far);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int si, ni, n;
    char s;
    string line;

    while (getline(cin, line))
    {
        si = 1, ni = 0, offset = 0;

        istringstream iss(line);

        iss >> number[ni];
        offset += number[ni];
        sign[0] = 1;
        ni++;

        while (iss >> s >> n)
        {
            number[ni++] = n;
            offset += n;
            sign[si++] = (s == '-' ? -1 : 1);
        }

        N = ni;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k <= 2 * offset; k++)
                    visited[i][j][k] = 0;
        memset(used, 0, sizeof(used));
        dfs(0, 0, 0);
        cout << count(used, used + 6100, 1) << '\n';
    }

    return 0;
}
