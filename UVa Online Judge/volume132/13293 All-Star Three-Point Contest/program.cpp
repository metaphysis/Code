// All-Star Three-Point Contest
// UVa ID: 13293
// Verdict: Accepted
// Submission Date: 2019-01-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct player
{
    string name, realName;
    int scores;
    bool operator<(const player &p) const
    {
        if (scores != p.scores) return scores > p.scores;
        return realName < p.realName;
    }
} players[110];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int P, cases = 0;
    string line;
    while (cin >> P)
    {
        cin.ignore(256, '\n');
        for (int i = 0; i < P; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            string block[6];
            for (int j = 0; j < 6; j++)
                getline(iss, block[j], ';');
            players[i].name = block[0];
            transform(block[0].begin(), block[0].end(), block[0].begin(), ::toupper);
            players[i].realName = block[0];
            players[i].scores = 0;
            for (int j = 1; j <= 5; j++)
            {
                iss.clear();
                iss.str(block[j]);
                for (int k = 1, s; k <= 5; k++)
                {
                    iss >> s;
                    players[i].scores += s;
                    if (k == 5) players[i].scores += s;
                }
            }
        }
        sort(players, players + P);
        cout << "Case " << ++cases << ":\n";
        for (int i = 0; i < P; i++)
            cout << players[i].name << ' ' << players[i].scores << '\n';
    }

    return 0;
}
