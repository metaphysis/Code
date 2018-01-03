// All Integer Average
// UVa ID: 12060
// Verdict: Accepted
// Submission Date: 2018-01-04
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

int gcd(int a, int b)
{
    if (a < b) swap(a, b);
    return b ? gcd(b, a % b) : a;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, k, cases = 0;
    while (cin >> n, n > 0)
    {
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> k;
            sum += k;
        }
        
        cout << "Case " << ++cases << ":\n";
        if (sum == 0)
        {
            cout << "0\n";
            continue;
        }
        
        if (abs(sum) % n == 0)
        {
            if (sum < 0) cout << "- ";
            cout << abs(sum) / n << '\n';
            continue;
        }

        int a = abs(sum) / n, b = abs(sum) % n;
        int g = gcd(b, n); b /= g, n /= g;
        string aa = to_string(a), bb = to_string(b), nn = to_string(n);
        
        int leftPadding = 0;
        if (sum < 0) leftPadding = 2;
        if (a > 0) leftPadding += aa.length();

        for (int i = 0; i < (leftPadding + nn.length() - bb.length()); i++) cout << ' ';
        cout << bb << '\n';

        if (sum < 0) cout << "- ";
        if (a) cout << aa;
        for (int i = 0; i < nn.length(); i++) cout << '-';
        cout << '\n';
        
        for (int i = 0; i < leftPadding; i++) cout << ' ';
        cout << nn << '\n';
    }

    return 0;
}
