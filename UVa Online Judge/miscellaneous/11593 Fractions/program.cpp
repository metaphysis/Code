// Fractions
// UVa ID: 11593
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

    long long total = 0, up = 1000000000;
    long long originalStart = 10000000, originalEnd = 20000000;
    long long start, end;
    long long times = 1;

    start = originalStart * times, end = originalEnd * times;
    do
    {
        total += (end > up ? up : end) - start + 1;
        times += 1;
        start = originalStart * times, end = originalEnd * times;
    } while (start <= up);

    cout << total << '\n';
    
    return 0;
}
