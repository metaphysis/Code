// Chess Queen
// UVa ID: 11538
// Verdict: Accepted
// Submission Date: 2017-04-12
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
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long ways[1000010] = {0};
    
    for (long long i = 1; i <= 1000000; i++)
        ways[i] = ways[i - 1] + i * (i - 1);
        
    long long M, N;
    while (cin >> M >> N, M > 0)
    {
        if (M < N) swap(M, N);
        long long r = M * N * (M + N - 2);
        r += 2 * (M - N + 1) * N * (N - 1);
        r += 4 * ways[N - 1];
        cout << r << '\n';
    }
    
    return 0;
}
