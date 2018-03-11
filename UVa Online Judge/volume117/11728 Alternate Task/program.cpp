// Alternate Task
// UVa ID: 11728
// Verdict: Accepted
// Submission Date: 2018-03-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

    int S[1001] = {0};
    for (int i = 1; i <= 1000; i++)
    {
        int sum = 0;
        for (int j = 1; j <= i; j++)
            if (i % j == 0)
                sum += j;
        if (sum <= 1000) S[sum] = i;
    }
    
    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": ";
        if (S[n]) cout << S[n] << '\n';
        else cout << "-1\n";
    }

    return 0;
}
