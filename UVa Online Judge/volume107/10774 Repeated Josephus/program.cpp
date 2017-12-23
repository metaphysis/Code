// Repeated Josephus
// UVa ID: 10774
// Verdict: Accepted
// Submission Date: 2017-12-23
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int survivor[30010] = {0};
    
    int last = 0;
    for (int i = 2; i <= 30010; i++)
    {
        survivor[i - 1] = last + 1;
        last = (last + 2) % i;
    }
    
    int n, cases = 0;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;

        int cycle = 0;
        while (survivor[n] != n)
        {
            cycle++;
            n = survivor[n];
        }
        cout << "Case " << c << ": " << cycle << ' ' << n << '\n';
    }

    return 0;
}
