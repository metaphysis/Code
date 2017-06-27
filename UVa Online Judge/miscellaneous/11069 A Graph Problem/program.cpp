// A Graph Problem
// UVa ID: 11069
// Verdict: Accepted
// Submission Date: 2017-06-27
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

    long long f[80] = {0};

    f[1] = f[2] = 1;
	for (int i = 3; i <= 80; i++)
		f[i] = f[i - 2] + f[i - 3];

	int n;
	while (cin >> n) cout << (f[n] + f[n - 1]) << '\n';

    return 0;
}
