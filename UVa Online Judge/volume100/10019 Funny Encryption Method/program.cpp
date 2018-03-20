// Funny Encryption Method
// UVa ID: 10019
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        string n;
        cin >> n;
        int decimal = 0;
        for (auto d : n) decimal = decimal * 10 + d - '0';
        bitset<32> b1(decimal);
        cout << b1.count() << ' ';
        int hexa = 0;
        for (auto d : n) hexa = hexa * 16 + d - '0';
        bitset<32> b2(hexa);
        cout << b2.count() << '\n';
    }

    return 0;
}
