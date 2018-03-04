// Farey Sequences
// UVa ID: 10408
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.100s
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

struct fraction
{
    int a, b;
    fraction (int a = 0, int b = 0): a(a), b(b) {}
    bool operator<(const fraction &f) const
    {
        return a * f.b < b * f.a;
    }
    bool operator==(const fraction &f) const
    {
        return a * f.b == b * f.a;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, k;
    vector<fraction> fs;
    for (int i = 1; i <= 1000; i++)
        for (int j = 1; j < 1000; j++)
        {
            int g = __gcd(i, j);
            fs.push_back(fraction(j / g, i / g));
        }
    sort(fs.begin(), fs.end());
    fs.erase(unique(fs.begin(), fs.end()), fs.end());
        
    while (cin >> n >> k)
    {
        for (int i = 0; i < fs.size(); i++)
        {
            if (fs[i].b <= n) k--;
            if (k == 0)
            {
                cout << fs[i].a << '/' << fs[i].b << '\n';
                break;
            }
        }
    }

    return 0;
}
