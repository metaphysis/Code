// Lock Manager
// UVa ID: 10145
// Verdict: Accepted
// Submission Date: 2022-01-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int cs = 0; cs < T; cs++)
    {
        if (cs) cout << '\n';
        char mode;
        int trid, item;
        map<int, set<int>> shared;
        map<int, int> exclusive;
        set<int> blocked;
        while (cin >> mode)
        {
            if (mode == '#') break;
            cin >> trid >> item;
            if (blocked.count(trid)) cout << "IGNORED\n";
            else
            {
                if (mode == 'X')
                {
                    if (exclusive[item] && exclusive[item] != trid)
                    {
                        cout << "DENIED\n";
                        blocked.insert(trid);
                        continue;
                    }
                    if (shared[item].size() > 1)
                    {
                        cout << "DENIED\n";
                        blocked.insert(trid);
                        continue;
                    }
                    if (shared[item].size() == 1 && *shared[item].begin() != trid)
                    {
                        cout << "DENIED\n";
                        blocked.insert(trid);
                        continue;
                    }
                    cout << "GRANTED\n";
                    exclusive[item] = trid;
                }
                if (mode == 'S')
                {
                    if (exclusive[item] && exclusive[item] != trid)
                    {
                        cout << "DENIED\n";
                        blocked.insert(trid);
                        continue;
                    }
                    cout << "GRANTED\n";
                    shared[item].insert(trid);
                }
            }
        }
        
    }
    return 0;
}
