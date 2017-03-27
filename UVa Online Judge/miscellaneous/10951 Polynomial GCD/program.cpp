// Polynomial GCD
// UVa ID: 10951
// Verdict: Accepted
// Submission Date: 2017-03-27
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

int n;

bool bigger(vector<int> &a, vector<int> &b)
{
    if (a.size() != b.size()) return a.size() > b.size();
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return a[i] > b[i];
    return false;
}

int findInverse(int a, int b)
{
    for (int i = 1; i < n; i++)
        if ((b * i) % n == a)
            return i;
}

vector<int> mod(vector<int> a, vector<int> b)
{
    int c = findInverse(a[0], b[0]);
    for (int i = 0; i < b.size(); i++)
    {
        a[i] -= b[i] * c;
        a[i] %= n;
        a[i] = (a[i] + n) % n;
        
    }
    while (a.size() > 0 && a.front() == 0) a.erase(a.begin());
    return a;
}

vector<int> gcd1(vector<int> a, vector<int> b)
{
    if (!bigger(a, b)) a.swap(b);
    if (b.size() == 0) return a;
    else return gcd1(b, mod(a, b));
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int d, coefficient, cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ':';
        
        vector<int> poly1;
        cin >> d;
        for (int i = 0; i <= d; i++)
        {
            cin >> coefficient;
            poly1.push_back(coefficient);
        }
        
        vector<int> poly2;
        cin >> d;
        for (int i = 0; i <= d; i++)
        {
            cin >> coefficient;
            poly2.push_back(coefficient);
        }
        
        vector<int> gcd = gcd1(poly1, poly2);

        int c = findInverse(1, gcd[0]);
        
        cout << ' ' << (gcd.size() - 1);
        for (int i = 0; i < gcd.size(); i++)
            cout << ' ' << (gcd[i] * c) % n;
        cout << '\n';
    }

    return 0;
}
