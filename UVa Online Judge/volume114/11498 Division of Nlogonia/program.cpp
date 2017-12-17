// Division of Nlogonia
// UVa ID: 11498
// Verdict: Accepted
// Submission Date: 2017-12-17
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

    int n, cx, cy, qx, qy;
    
    while (cin >> n, n > 0)
    {
        cin >> cx >> cy;
        for (int i = 1; i <= n; i++)
        {
            cin >> qx >> qy;
            if (qx == cx || qy == cy) cout << "divisa\n";
            else if (qx > cx && qy > cy) cout << "NE\n";
            else if (qx > cx && qy < cy) cout << "SE\n";
            else if (qx < cx && qy > cy) cout << "NO\n";
            else cout << "SO\n";
        }
    }

    return 0;
}
