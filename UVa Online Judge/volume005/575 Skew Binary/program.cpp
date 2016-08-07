// Skew Binary
// UVa ID: 575
// Verdict: Accepted
// Submission Date: 2016-08-07
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

    string line;
    while (getline(cin, line), line != "0")
    {
        long long number = 0, exponent = 2;

        for (int i = line.length() - 1; i >= 0; i--)
        {
            number += (line[i] - '0') * (exponent - 1);
            exponent *= 2;
        }

        cout << number << '\n';
    }
    
	return 0;
}
