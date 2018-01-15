// Pay the Price
// UVa ID: 10313
// Verdict: Accepted
// Submission Date: 2018-01-16
// UVa Run Time: 0.060s
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

    int coins[320];
    for (int i = 1; i <= 300; i++) coins[i] = i;

    long long ways1[320] = {0};   
    ways1[0] = 1;
    for (int i = 1; i <= 300; i++)
        for (int j = coins[i]; j <= 300; j++)
                ways1[j] += ways1[j - coins[i]];

    long long ways2[320][1010] = {0};
    ways2[0][0] = 1;
    for (int i = 1; i <= 300; i++)
        for (int j = coins[i]; j <= 300; j++)
            for (int k = 1; k <= 1000; k++)
                ways2[j][k] += ways2[j - coins[i]][k - 1];
            
    int N, L1, L2;
    string line;

    while (getline(cin, line))
    {
        istringstream iss(line);
        
        int cnt = 1;
        iss >> N;
        if (iss >> L1) cnt++;
        if (iss >> L2) cnt++;
        if (cnt == 1) cout << ways1[N] << '\n';
        else
        {
            if (cnt == 2) L2 = L1, L1 = 0;
            long long total = 0;
            for (int i = L1; i <= L2; i++) total += ways2[N][i];
            cout << total << '\n';
        }
    }

    return 0;
}
