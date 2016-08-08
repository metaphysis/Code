// Multiplying by Rotation
// UVa ID: 550
// Verdict: Accepted
// Submission Date: 2016-08-08
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

    int base, first_factor, second_factor;
    while (cin >> base >> first_factor >> second_factor)
    {
        int n = 1, x, exponent = base;

        while (true)
        {
            int r = first_factor * (exponent - 1) % (second_factor * base - 1);
            if (r == 0)
                break;
            exponent = (exponent * base) % (second_factor * base - 1);
            n++;
        }
        
        cout << n << endl;
    }
    
	return 0;
}
