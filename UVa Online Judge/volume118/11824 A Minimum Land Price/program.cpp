// A Minimum Land Price
// UVa ID: 11824
// Verdict: Accepted
// Submission Date: 2018-01-12
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

bool cmp(const int &a, const int &b)
{
    return a * a > b * b;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, price[64], cnt;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cnt = 0;
        while (cin >> price[cnt])
        {
            if (price[cnt] == 0) break;
            cnt++;
        }
        sort(price, price + cnt, cmp);
        int total = 0;
        for (int i = 0; i < cnt; i++)
        {
            if (pow(price[i], i + 1) > 2500000)
            {
                total = 6000000;
                break;
            }
            
            total += 2 * (int)(pow(price[i], i + 1));
        }
        if (total <= 5000000) cout << total << '\n';
        else cout << "Too expensive\n";
    }

    return 0;
}
