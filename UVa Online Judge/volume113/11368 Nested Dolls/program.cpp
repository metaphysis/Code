// Nested Dolls
// UVa ID: 11368
// Verdict: Accepted
// Submission Date: 2017-11-05
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct doll
{
    int w, h;
    bool operator<(const doll &d) const
    {
        if (w != d.w) return w > d.w;
        else return h < d.h;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, w, h;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        vector<doll> dolls;
        cin >> n;
        
        for (int i = 1; i <= n; i++)
        {
            cin >> w >> h;
            dolls.push_back(doll{w, h});
        }
        
        sort(dolls.begin(), dolls.end());

        vector<int> heights;
        for (auto d : dolls)
        {
            auto i = upper_bound(heights.begin(), heights.end(), d.h);
            if (i == heights.end())
                heights.push_back(d.h);
            else
                *i = d.h; 
        }

        cout << heights.size() << '\n';
    }
    
    return 0;
}
