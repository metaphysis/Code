// Marks Distribution
// UVa ID: 10910
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

    int ways[71][71];
    int N, T, P;
    
    while (cin >> N >> T >> P)
    {
        memset(ways, 0, sizeof(ways));
        
        ways[0][0] = 1;
        for (int i = 1; i <= N; i++)
            for (int j = P; j <= T; j++)
                for (int k = T; k >= P; k--)
                    ways[j][k] += ways[j][k - j];
    }
    return 0;
}
