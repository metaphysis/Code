// Breaking Board
// UVa ID: 12705
// Verdict: Accepted
// Submission Date: 2022-10-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T; cin >> T;
    cin.ignore(256, '\n');
    vector<int> grid;
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 6; j++)
            grid.push_back(i + j);
    sort(grid.begin(), grid.end());

    string line;
    while (T--)
    {
        getline(cin, line);
        map<char, int> t;
        for (auto c : line)
            if (c != ' ')
                t[c]++;
        vector<int> ch;
        for (auto p : t) ch.push_back(p.second);
        sort(ch.begin(), ch.end(), greater<int>());
        int cost = 0;
        for (int i = 0; i < ch.size(); i++)
            cost += ch[i] * grid[i];
        cout << cost << '\n';
    }
    
    return 0;
}
