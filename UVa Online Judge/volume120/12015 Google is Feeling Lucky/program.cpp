// Google is Feeling Lucky
// UVa ID: 12015
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct pv
{
    string url;
    int views;
    
    bool operator<(const pv &v) const
    {
        return views > v.views;
    }
}pages[20];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        for (int i = 0; i < 10; i++)
            cin >> pages[i].url >> pages[i].views;
            
        stable_sort(pages, pages + 10);
        
        cout << "Case #" << c << ":\n";
        cout << pages[0].url << '\n';
        for (int i = 1; i < 10; i++)
            if (pages[i].views == pages[0].views)
                cout << pages[i].url << '\n';
    }

    return 0;
}
