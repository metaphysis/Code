// Last Blood
// UVa ID: 12667
// Verdict: Accepted
// Submission Date: 2021-12-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, t, m;
    int pid, time, tid;
    int accepted[16][128] = {0};
    int lastBlood[16][2] = {0};
    char problem;
    string verdict;
    cin >> n >> t >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> time >> tid >> problem >> verdict;
        if (verdict == "Yes")
        {
            pid = problem - 'A';
            if (!accepted[pid][tid])
            {
                accepted[pid][tid] = 1;
                lastBlood[pid][0] = tid;
                lastBlood[pid][1] = time;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << (char)('A' + i) << ' ';
        if (lastBlood[i][0])
            cout << lastBlood[i][1] << ' ' << lastBlood[i][0] << '\n';
        else
            cout << "- -\n";
    }
    return 0;
}
