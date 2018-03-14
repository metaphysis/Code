// Gas Stations
// UVa ID: 12321
// Verdict: Accepted
// Submission Date: 2017-12-03
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct station
{
    int sl, sr;
    
    bool operator<(const station &s) const
    {
        if (sl != s.sl) return sl < s.sl;
        return sr < s.sr;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, l, g, sl, sr;
    
    while (cin >> l >> g, l > 0)
    {
        cases++;

        vector<station> stations;
        
        for (int i = 0; i < g; i++)
        {
            cin >> sl >> sr;
            stations.push_back(station{sl, sr});
        }
        sort(stations.begin(), stations.end());
        
        int rightmost = 0;
        vector<station> needed;
        
        for (int i = 0; i < g; i++)
        {
            station s = stations[i];

            int sright = s.sl + s.sr, sleft = s.sl - s.sr;

            if (needed.empty())
            {
                if (sleft <= 0)
                {
                    needed.push_back(s);
                    rightmost = sright;
                }
            }
            else
            {
                if (sright <= rightmost || sleft > rightmost) continue;
                bool poped = false;
                while (needed.size() >= 2)
                {
                    station p = needed[needed.size() - 2];
                    int pright = p.sl + p.sr;
                    if (sleft <= pright)
                    {
                        poped = true;
                        needed.pop_back();
                    }
                    else break;
                }
                if (needed.size() == 1 && sleft <= 0)
                {
                    poped = true;
                    needed.pop_back();
                }
                if (rightmost < l || poped) needed.push_back(s);
                rightmost = min(l, sright);
            }
        }
        
        if (rightmost < l) cout << "-1\n";
        else cout << (g - needed.size()) << '\n';
    }

    return 0;
}
