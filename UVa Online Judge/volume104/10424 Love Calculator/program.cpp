// Love Calculator
// UVa ID: 10424
// Verdict: Accepted
// Submission Date: 2017-12-26
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

int add(int n)
{
    while (n >= 10)
    {
        int t = 0;
        while (n > 0)
        {
            t += n % 10;
            n /= 10;
        }
        n = t;
    }
    return n;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string name1, name2;
    
    while (getline(cin, name1))
    {
        getline(cin, name2);

        int n1 = 0;
        for (int i = 0; i < name1.length(); i++)
        {
            if (isalpha(name1[i]))
            {
                n1 += tolower(name1[i]) - 'a' + 1;
            }
        }
        
        int n2 = 0;
        for (int i = 0; i < name2.length(); i++)
        {
            if (isalpha(name2[i]))
            {
                n2 += tolower(name2[i]) - 'a' + 1;
            }
        }
        
        n1 = add(n1), n2 = add(n2);

        if (n1 > n2) swap(n1, n2);
        
        cout << fixed << setprecision(2) << ((double)n1 / n2 * 100.0) << " %\n";
    }

    return 0;
}
