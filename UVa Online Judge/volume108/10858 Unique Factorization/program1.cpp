// Unique factorsization
// UVa ID: 10858
// Verdict: Accepted
// Submission Date: 2018-01-14
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

int cnt;
vector<int> factors, result[12048];
int divisors[1024];

void dfs(int n, int depth, int idx)
{
    if (n == 1)
    {
        for (int i = 0; i < depth; i++)
            result[cnt].push_back(divisors[i]);
        cnt++;
    }
    else
    {
        for (int i = idx; i < factors.size(); i++)
        {
            if ((n / factors[i] >= factors[i] || n == factors[i]) && n % factors[i] == 0)
            {
                divisors[depth] = factors[i];
                dfs(n / factors[i], depth + 1, i);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        int maxF = (int)sqrt(n);
        
        factors.clear();
        for (int i = 2; i <= maxF; i++)
            if (n % i == 0)
            {
                factors.push_back(i);
                if (i * i != n) factors.push_back(n / i);
            }
        sort(factors.begin(), factors.end());

        cnt = 0;
        if (factors.size()) dfs(n, 0, 0);

        cout << cnt << '\n';
        for (int i = 0; i < cnt; i++)
        {
            auto it = result[i].begin();
            cout << *it;
            for (it++; it != result[i].end(); it++) cout << ' ' << *it;
            cout << '\n';
            result[i].clear();
        }
    }

    return 0;
}
