// Help Dexter
// UVa ID: 12406
// Verdict: Accepted
// Submission Date: 2017-11-11
// UVa Run Time: 0.020s
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

struct number
{
    long long value, length;
    
    bool operator<(const number &n) const
    {
        if (length != n.length) return length < n.length;
        return value < n.value;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<number> all;
    
    all.push_back(number{1, 1});
    all.push_back(number{2, 1});
    
    int low = 0;
    for (int i = 1; i <= 16; i++)
    {
        int up = all.size();
        for (int j = low; j < up; j++)
        {
            all.push_back(number{all[j].value * 10 + 1, all[j].length + 1});
            all.push_back(number{all[j].value * 10 + 2, all[j].length + 1});
        }
        low = up;
    }
    
    sort(all.begin(), all.end());
    
    vector<number> valid[20];
    for (int i = 0; i < all.size(); i++)
    {
        if (all[i].value & 1) continue;
        valid[all[i].length].push_back(all[i]);
    }

    int cases;
    long long p, q, least, most;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";
        
        cin >> p >> q;
        
        q = (1 << q);
        least = most = 0;
 
        for (int i = 0; i < valid[p].size(); i++)
        {
            if (valid[p][i].length != p) continue;
            if (valid[p][i].value % q == 0)
            {
                if (!least)
                    least = valid[p][i].value;
                else
                    most = valid[p][i].value;
            }
        }
        
        if (!least) cout << "impossible\n";
        else
        {
            cout << least;
            if (most) cout << ' ' << most;
            cout << '\n';
        }
    }
    
    return 0;
}
