// Waking up Brain
// UVa ID: 10507
// Verdict: Accepted
// Submission Date: 2018-01-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, M;
    while (cin >> N)
    {
        cin >> M;
    
        int wakeup[26] = {0}, appeared[26] = {0}, connected[26][26] = {0};
        char area;

        for (int i = 0; i < 3; i++)
        {
            cin >> area;
            wakeup[area - 'A'] = 1;
            appeared[area - 'A'] = 1;
        }
        
        char area1, area2;
        for (int i = 1; i <= M; i++)
        {
            cin >> area1 >> area2;
            connected[area1 - 'A'][area2 - 'A'] = connected[area2 - 'A'][area1 - 'A'] = 1;
            appeared[area1 - 'A'] = appeared[area2 - 'A'] = 1;
        }

        int actived = 3, years = 0;
        while (true)
        {
            vector<int> pending;
            for (int i = 0; i < 26; i++)
                if (appeared[i] && wakeup[i] == 0)
                {
                    int linked = 0;
                    for (int j = 0; j < 26; j++)
                        if (appeared[j] && wakeup[j] && connected[i][j])
                            linked++;
                    if (linked >= 3)
                    {
                        pending.push_back(i);
                    }
                }
            if (pending.size() == 0) break;
            for (auto p : pending) { wakeup[p] = 1; actived++; }
            years++;
        }
        
        if (actived == N) cout << "WAKE UP IN, " << years << ", YEARS\n";
        else cout << "THIS BRAIN NEVER WAKES UP\n";
    }

    return 0;
}
