// The Windows Property
// UVa ID: 261
// Verdict: Accepted
// Submission Date: 2016-05-26
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    vector < set<string> > pattern(1100);
    
    string line;
    while (getline(cin, line))
    {
        for (int i = 0; i < pattern.size(); i++)
            pattern[i].clear();
        
        bool good = true;
        int position = -1;
        for (int i = 0; i < line.length(); i++)
        {
            for (int k = 1; k <= (i + 1); k++)
            {
                string p = line.substr(i - k + 1, k);
                pattern[k].insert(p);
                if (pattern[k].size() > (k + 1))
                {
                    good = false;
                    position = i + 1;
                    goto out;
                }
            }
        }

    out:        
        if (good)
            cout << "YES" << endl;
        else
            cout << "NO:" << position << endl;
    }
    
	return 0;
}
