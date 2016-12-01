// S-Trees
// UVa ID: 712
// Verdict: Accepted
// Submission Date: 2016-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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

int n, m, cases = 0, level[10], base;
string variable, terminal, vva;

char travel(int i, int depth)
{
    if (depth == n) return terminal[i - base];
    if (vva[level[depth]] == '0')
        return travel(2 * i + 1, depth + 1);
    else
        return travel(2 * i + 2, depth + 1);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    while (cin >> n, n > 0)
    {
        cout << "S-Tree #" << ++cases << ":\n";
        
        base = pow(2, n) - 1;

        for (int i = 0; i < n; i++)
        {
            cin >> variable;
            level[i] = variable.back() - '0' - 1;
        }

        cin >> terminal >> m;

        for (int i = 1; i <= m; i++)
        {
            cin >> vva;
            cout << travel(0, 0);
        }
        
        cout << "\n\n";
    }
    
	return 0;
}
