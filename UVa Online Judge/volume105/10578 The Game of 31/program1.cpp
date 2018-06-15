// The Game of 31
// UVa ID: 10578
// Verdict: Accepted
// Submission Date: 2018-06-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int N = 0, P = 1;

int PN[5][5][5][5][5][5], cnt[7];

int dfs(int *cnt, int sum)
{
    int *key = &PN[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][cnt[6]];
    if (~(*key)) return *key;
    for (int i = 1; i <= 6; i++)
    {
        if (cnt[i] == 4 || sum + i > 31) continue;
        cnt[i]++;
        int next = dfs(cnt, sum + i);
        cnt[i]--;
        if (next == N) return *key = P;
    }
    return *key = N;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string s;
    memset(PN, -1, sizeof(PN));
    while (cin >> s)
    {
        cout << s << ' ';
        memset(cnt, 0, sizeof(cnt)); 
        int sum = 0;
        for (auto letter : s) cnt[letter - '0']++, sum += letter - '0';
        int result = dfs(cnt, sum);
        char player1 = (s.length() % 2 ? 'B' : 'A');
        char player2 = (s.length() % 2 ? 'A' : 'B');
        cout << (result == P ? player1 : player2) << '\n';
    }

    return 0;
}
