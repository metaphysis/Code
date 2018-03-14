// Parity
// UVa ID: 10931
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        bitset<32> bits(n);
        string s = bits.to_string();
        while (s.front() == '0') s.erase(s.begin());
        int parity = 0;
        for (auto d : s)
            if (d == '1')
                parity++;
                
        cout << "The parity of " << s << " is " << parity << " (mod 2).\n";
    }

    return 0;
}
