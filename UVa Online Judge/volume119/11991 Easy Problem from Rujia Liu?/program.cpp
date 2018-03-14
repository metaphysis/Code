// Easy Problem from Rujia Liu?
// UVa ID: 11991
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m;
    while (cin >> n >> m)
    {
        map<int, vector<int>> occurrence;
        
        int x;
        for (int i = 0; i < n; i++)
        {
            cin >> x;
            occurrence[x].push_back(i + 1);
        }
        
        int k, v;
        for (int i = 0; i < m; i++)
        {
            cin >> k >> v;
            map<int, vector<int>>::iterator it = occurrence.find(v);
            if (it != occurrence.end() && k <= (*it).second.size())
                cout << (*it).second[k - 1] << '\n';
            else
                cout << "0\n";
        }
    }

    return 0;
}
