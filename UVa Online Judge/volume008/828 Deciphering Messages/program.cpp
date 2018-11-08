// Deciphering Messages
// UVa ID: 828
// Verdict: Accepted
// Submission Date: 2018-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string key, msg;
int flag, N, keyLength, isKeyLetter[26];
char plaintext[102400];

void dfs(int u, int m, int n)
{
    if (flag || u > msg.length()) return;
    if (u == msg.length())
    {
        for (int i = 0; i < n; i++) cout << plaintext[i];
        cout << '\n';
        flag = 1;
        return;
    }
    
    if (msg[u] == ' ')
    {
        plaintext[n] = ' ';
        dfs(u + 1, m, n + 1);
    }
    else
    {
        if (u + 2 < msg.length() && msg[u + 1] != ' ' && msg[u + 2] != ' ')
        {
            int x = (msg[u + 1] - 'A' - N + 26) % 26;
            if (isKeyLetter[x] && msg[u] == key[m] && msg[u + 2] == key[(m + 1) % key.length()])
            {
                plaintext[n] = 'A' + x;
                dfs(u + 3, (m + 1) % key.length(), n + 1);
            }
        }

        int y = (msg[u] - 'A' - N + 26) % 26;
        if (!isKeyLetter[y])
        {
            plaintext[n] = 'A' + y;
            dfs(u + 1, m, n + 1);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, M;
    cin >> cases;
    for (int cs = 0; cs < cases; cs++)
    {
        if (cs) cout << '\n';
        cin >> key >> N >> M;
        memset(isKeyLetter, 0, sizeof(isKeyLetter));
        for (auto letter : key) isKeyLetter[letter - 'A'] = 1;
        cin.ignore(256, '\n');
        for (int i = 1; i <= M; i++)
        {
            getline(cin, msg);
            flag = 0;
            dfs(0, 0, 0);
            if (!flag) cout << "error in encryption\n";
        }
    }

    return 0;
}
