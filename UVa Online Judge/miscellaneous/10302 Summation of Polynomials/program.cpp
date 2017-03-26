// Summation of Polynomials
// UVa ID: 10302
// Verdict: Accepted
// Submission Date: 2017-03-26
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

    long long n, sum;
    while (cin >> n)
    {
        sum = n * (n + 1) / 2;
        sum *= sum;
        cout << sum << '\n';
    }
    
    return 0;
}
