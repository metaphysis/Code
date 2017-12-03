// Watering Grass
// UVa ID: 10382
// Verdict: Accepted
// Submission Date: 2017-12-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct sprinkler
{
    double sl, sr;
    
    bool operator<(const sprinkler &s) const
    {
        if (sl != s.sl) return sl < s.sl;
        return sr < s.sr;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    double l, w, sl, sr;
    
    while (cin >> n >> l >> w)
    {
        cases++;

        vector<sprinkler> sprinklers;
        
        for (int i = 0; i < n; i++)
        {
            cin >> sl >> sr;
            sprinklers.push_back(sprinkler{sl, sr});
        }
        sort(sprinklers.begin(), sprinklers.end());
        
        double rightmost = 0;
        vector<sprinkler> cycles;
        
        for (int i = 0; i < n; i++)
        {
            sprinkler s = sprinklers[i];

            if (s.sr * 2 < w) continue;

            double sright = s.sl + sqrt(s.sr * s.sr - w * w / 4);
            double sleft = s.sl - sqrt(s.sr * s.sr - w * w / 4);

            if (cycles.empty())
            {
                if (sleft <= 0)
                {
                    cycles.push_back(s);
                    rightmost = sright;
                }
            }
            else
            {
                if (sright <= rightmost || sleft > rightmost) continue;
                bool poped = false;
                while (cycles.size() >= 2)
                {
                    sprinkler p = cycles[cycles.size() - 2];
                    double pright = p.sl + sqrt(p.sr * p.sr - w * w / 4);
                    if (sleft <= pright)
                    {
                        poped = true;
                        cycles.pop_back();
                    }
                    else break;
                }
                if (cycles.size() == 1 && sleft <= 0)
                {
                    poped = true;
                    cycles.pop_back();
                }
                if (rightmost < l || poped) cycles.push_back(s);
                rightmost = min(l, sright);
            }
        }
        
        if (rightmost < l) cout << "-1\n";
        else cout << cycles.size() << '\n';
    }

    return 0;
}
