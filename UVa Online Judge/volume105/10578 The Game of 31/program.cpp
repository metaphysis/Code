// The Game of 31
// UVa ID: 10578
// Verdict: Accepted
// Submission Date: 2018-06-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int A = 0, B = 1, A_WIN = 0, A_LOSE = 1, B_WIN = 2, B_LOSE = 3;

int cache[5][5][5][5][5][5], cnt[7];

int dfs(int *cnt, int sum, int player)
{
    int *key = &cache[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][cnt[6]];
    if (~(*key))
    {
        if (player == A) return *key ? A_WIN : A_LOSE;
        if (player == B) return *key ? B_WIN : B_LOSE;
    }

    for (int i = 1; i <= 6; i++)
    {
        if (cnt[i] == 4) continue;
        if (sum + i > 31) continue;
        cnt[i]++;
        int result = dfs(cnt, sum + i, !player);
        cnt[i]--;
        if (player == A && result == B_LOSE) { *key = 1; return A_WIN; }
        if (player == B && result == A_LOSE) { *key = 1; return B_WIN; }
    }

    *key = 0;
    return player == A ? A_LOSE : B_LOSE;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string s;

    memset(cache, -1, sizeof(cache));

    while (cin >> s)
    {
        cout << s << ' ';
        
        memset(cnt, 0, sizeof(cnt));
        
        int sum = 0;
        for (auto letter : s)
            cnt[letter - '0']++, sum += letter - '0';
        int result = dfs(cnt, sum, s.length() % 2);
        if (result == A_WIN || result == B_LOSE) cout << "A\n";
        else cout << "B\n";
    }

    return 0;
}
