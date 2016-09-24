// Critical Mass
// UVa ID: 580
// Verdict: Accepted
// Submission Date: 2016-09-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int solutions[31] = {0};
    solutions[3] = 1, solutions[4] = 3;
    for (int i = 5; i <= 30; i++)
        solutions[i] = 2 * solutions[i - 1] - solutions[i - 4] + (1 << (i - 4));
    
    int n;
    while (cin >> n, n)
        cout << solutions[n] << '\n';
        
	return 0;
}
