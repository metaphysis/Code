// Station Balance
// UVa ID: 410
// Verdict: Accepted
// Submission Date: 2016-07-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// http://www.algorithmist.com/index.php/UVa_410

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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int chambers, specimens, mass, cases = 0;
    
    while (cin >> chambers >> specimens)
    {
        int total_masses = 0;
        vector<int> masses;
        for (int i = 1; i <= specimens; i++)
        {
            cin >> mass;
            masses.push_back(mass);
            total_masses += mass;
        }
        
        while (masses.size() < 2 * chambers)
            masses.push_back(0);
            
        sort(masses.begin(), masses.end());
        
        int average_masses = 0;
        cout << "Set #" << ++cases << '\n';
        for (int i = 0; i < chambers; i++)
        {
            cout << ' ' << i << ':';
            int a = masses[i], b = masses[2 * chambers - 1 - i];
            if (a > 0 || b > 0)
            {
                if (a > 0) cout << ' ' << a;
                if (b > 0) cout << ' ' << b;
            }
            cout << '\n';
            average_masses += fabs((a + b) * chambers - total_masses);
        }
        cout << "IMBALANCE = ";
        cout << fixed << setprecision(5) << (double)average_masses / (double)chambers;
        cout << "\n\n";
    }
    
	return 0;
}
