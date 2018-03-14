// Rock-Paper-Scissors Tournament
// UVa ID: 10903
// Verdict: Accepted
// Submission Date: 2017-12-26
// UVa Run Time: 0.130s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, k, won[110], lost[110];
    int p1, p2;
    string s1, s2;

    while (cin >> n >> k, n > 0)
    {
        memset(won, 0, sizeof(won));
        memset(lost, 0, sizeof(lost));
        
        int t = k * n * (n - 1) / 2;
        for (int i = 1; i <= t; i++)
        {
            cin >> p1 >> s1 >> p2 >> s2;
            if (s1.front() == 'r')
            {
                if (s2.front() == 's') won[p1]++, lost[p2]++;
                else if (s2.front() == 'p') lost[p1]++, won[p2]++; 
            }
            else if (s1.front() == 's')
            {
                if (s2.front() == 'r') won[p2]++, lost[p1]++;
                else if (s2.front() == 'p') won[p1]++, lost[p2]++;
            }
            else if (s1.front() == 'p')
            {
                if (s2.front() == 'r') won[p1]++, lost[p2]++;
                else if (s2.front() == 's') won[p2]++, lost[p1]++;
            }
        }
        
        if (cases++ > 0) cout << '\n';
        
        for (int i = 1; i <= n; i++)
        {
            if (won[i] + lost[i] > 0)
            {
                cout << fixed << setprecision(3) << (double)won[i] / (won[i] + lost[i]) << '\n';
            }
            else
                cout << "-\n";
        }
    }

    return 0;
}
