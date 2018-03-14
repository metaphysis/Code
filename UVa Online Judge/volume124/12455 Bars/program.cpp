// Bars
// UVa ID: 12455
// Verdict: Accepted
// Submission Date: 2017-11-11
// UVa Run Time: 0.050s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, length[24], n, p, t;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> p;
        
        t = 0;
        for (int i = 0; i < p; i++)
        {
            cin >> length[i];
            t += length[i];
        }
            
        vector<int> all;
        all.push_back(0);
        for (int i = 0; i < p; i++)
        {
            int current = all.size();
            for (int j = 0; j < current; j++)
                all.push_back(all[j] + length[i]);
        }

        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());
        
        if (binary_search(all.begin(), all.end(), n)) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}
