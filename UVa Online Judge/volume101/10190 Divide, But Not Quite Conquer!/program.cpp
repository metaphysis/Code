// Divide, But Not Quite Conquer!
// UVa ID: 10190
// Verdict: Accepted
// Submission Date: 2018-03-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

    int n, m;
    while (cin >> n >> m)
    {
        if (n <= 1 || m <= 1)
        {
            cout << "Boring!\n";
            continue;
        }

        bool divided = true;
        vector<int> r;
        r.push_back(n);
        while (n > 1)
        {
            if (n % m != 0)
            {
                divided = false;
                break;
            }
            r.push_back(n / m);
            n /= m;
        }
        if (!divided) cout << "Boring!\n";
        else
        {
            for (int i = 0; i < r.size(); i++)
            {
                if (i) cout << ' ';
                cout << r[i];
            }
            cout << '\n';
        }
    }

    return 0;
}
