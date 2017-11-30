// Number Sequence
// UVa ID: 10706
// Verdict: Accepted
// Submission Date: 2017-11-30
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

    long long indices[32000] = {0}, T = (1LL << 31) - 1;
    int digit[150000], A = 0, C = 0;
    
    for (int i = 1; ; i++)
    {
        int L = 0;
        for (int j = 1; i >= j; j *= 10) L++;
        int N = i;
        for (int j = L - 1; j >= 0; j--) digit[C + j] = N % 10, N /= 10;
        C += L;
        indices[i] += indices[i - 1] + C;
        if (indices[i] > T) { A = i + 1; break; }
    }
    
    int cases, Q;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> Q;
        int k = lower_bound(indices, indices + A, Q) - indices;
        if (indices[k] == Q) cout << (k % 10) << '\n';
        else cout << digit[Q - indices[k - 1] - 1] << '\n';
    }

    return 0;
}
