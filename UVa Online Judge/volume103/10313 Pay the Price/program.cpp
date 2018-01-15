// Pay the Price
// UVa ID: 10313
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
    long long ways[320] = {0};

    for (int i = 1; i <= 300; i++) coins[i] = i;
    
    ways[0] = 1;
    for (int i = 1; i <= 300; i++)
        for (int j = coins[i]; j <= 300; j++)
                ways[j] += ways[j - coins[i]];
        
    for (int i = 1; i <= 300; i++)
        cout << ways[i] << '\n';

    return 0;
}
