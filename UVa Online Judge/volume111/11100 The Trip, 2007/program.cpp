// The Trip, 2007
// UVa ID: 11100
// Verdict: Accepted
// Submission Date: 2017-12-03
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, bags[10010], cases = 0;
    
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++) cin >> bags[i];
        sort(bags, bags + n);
        
        vector<vector<int>> pieces;
    
        for (int i = 0; i < n; i++)
        {
            bool putted = false;
            for (int j = 0; j < pieces.size(); j++)
                if (pieces[j].back() < bags[i])
                {
                    pieces[j].push_back(bags[i]);
                    putted = true;
                    break;
                }
            if (!putted) pieces.push_back(vector<int>(1, bags[i]));
        }
        
        if (cases++ > 0) cout << '\n';

        int stacks = pieces.size();
        cout << stacks << '\n';
        for (int i = 0; i < stacks; i++)        
        {
            for (int j = i; j < n; j += stacks)
            {
                if (j > i) cout << ' ';
                cout << bags[j];
            }
            cout << '\n';
        }
    }

    return 0;
}
