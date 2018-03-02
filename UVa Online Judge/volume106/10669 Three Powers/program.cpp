// Three Powers
// UVa ID: 10669
// Verdict: Accepted
// Submission Date: 2018-03-03
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

string multiply(string s)
{
    string r;
    int carry = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        carry += (s[i] - '0') * 3;
        r.insert(r.begin(), (carry % 10) + '0');
        carry /= 10;
    }
    if (carry) r.insert(r.begin(), carry + '0');
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string element[64] = {"1"};
    for (int i = 1; i < 64; i++)
        element[i] = multiply(element[i - 1]);

    unsigned long long n;
    while (cin >> n, n > 0)
    {
        bitset<64> nn(n - 1);
        string bits = nn.to_string();
        vector<string> subs;
        for (int i = bits.length() - 1, j = 0; i >= 0; i--, j++)
            if (bits[i] == '1')
                subs.push_back(element[j]);
        cout << "{ ";
        for (int i = 0; i < subs.size(); i++)
        {
            if (i) cout << ' ';
            cout << subs[i];
            if (i < subs.size() - 1) cout << ',';
        }
        cout << " }\n";
    }
    
    return 0;
}
