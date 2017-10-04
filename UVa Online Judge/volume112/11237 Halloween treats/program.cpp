// Halloween treats
// UVa ID: 11237
// Verdict: Accepted
// Submission Date: 2016-08-02
// UVa Run Time: 0.100s
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

int indexer[100010];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int c, n;
    while (cin >> c >> n, c && n) {
        memset(indexer, -1, sizeof(indexer));
        indexer[0] = 0;
        int treats, solved = 0, remainder = 0;

        for (int i = 1; i <= n; i++) {
            cin >> treats;
            if (solved) continue;

            remainder = (remainder + treats) % c;
            if (indexer[remainder] >= 0) {
                int start = indexer[remainder] + 1;
                cout << start;
                for (int j = start + 1; j <= i; j++) cout << ' ' << j;
                cout << '\n';
                solved = true;
            }
            else indexer[remainder] = i;
        }
    }

	return 0;
}
