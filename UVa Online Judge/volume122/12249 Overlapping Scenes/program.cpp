// Overlapping Scenes
// UVa ID: 12249
// Verdict: Accepted
// Submission Date: 2017-11-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void combin(string &a, string &b)
{
    int r = 0;
    for (int i = min(a.length(), b.length()); i >= 1; i--)
        if (a.substr(a.length() - i) == b.substr(0, i))
        {
            r = i;
            break;
        }
    a += b.substr(r);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        vector<string> sence(n);
        for (int i = 0; i < n; i++)
            cin >> sence[i];
            
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        
        int least = 0x3fffffff;
        do
        {
            string a(sence[idx[0]]);
            for (int i = 1; i < idx.size(); i++)
                combin(a, sence[idx[i]]);
            least = min(least, (int)a.length());
        } while (next_permutation(idx.begin(), idx.end()));
        cout << "Case " << c << ": " << least << '\n';
    }
    
    return 0;
}
