// Square Pegs And Round Holes
// UVa IDs: 356
// Verdict: Accepted
// Submission Date: 2016-06-28
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n)
    {
        if (cases++) cout << endl;

        cout << "In the case n = " << n << ", " << (2 * n - 1) * 4;
        cout << " cells contain segments of the circle." << endl;

        int contained = 0;
        for (int i = 1; i <= n - 1; i++)
            for (int j = 1; j <= n - 1; j++)
                if (4 * (i * i + j * j) <= (2 * n - 1) * (2 * n - 1))
                    contained++;

        cout << "There are " << contained * 4 << " cells completely contained in the circle." << endl;
    }

	return 0;
}
