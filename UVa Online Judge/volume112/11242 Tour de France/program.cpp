// Tour de France
// UVa ID: 11242
// Verdict: Accepted
// Submission Date: 2017-11-07
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

struct ratio
{
    int n, m;

    bool operator<(ratio &f) const
    {
        return n * f.m < m * f.n;
    }
    
    bool operator==(ratio &f) const
    {
        return n * f.m == m * f.n;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int fs, rs, ft[10], rt[10];

    while (cin >> fs, fs > 0)
    {
        cin >> rs;
        
        for (int i = 0; i < fs; i++)
            cin >> ft[i];
        for (int i = 0; i < rs; i++)
            cin >> rt[i];
            
        vector<ratio> ratios;
        for (int i = 0; i < rs; i++)
            for (int j = 0; j < fs; j++)
                ratios.push_back(ratio{rt[i], ft[j]});
                
        sort(ratios.begin(), ratios.end());
        ratios.erase(unique(ratios.begin(), ratios.end()), ratios.end());
        
        if (ratios.size() == 1)
        {
            cout << "1.00\n";
            continue;
        }
        
        double spread = 0.0;
        for (int i = 0; i <= ratios.size() - 2; i++)
        {
            ratio f1 = ratios[i];
            ratio f2 = ratios[i + 1];

            double next = (double)(f2.n * f1.m) / (double)(f2.m * f1.n);
            if (next > spread + 1e-7) spread = next;
        }
        
        cout << fixed << setprecision(2) << (spread + 1e-7) << '\n';
    }
    
    return 0;
}
