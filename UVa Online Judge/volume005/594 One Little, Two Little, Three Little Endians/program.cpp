// One Little, Two Little, Three Little Endians
// UVa ID: 594
// Verdict: Accepted
// Submission Date: 2016-08-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        cout << n << " converts to ";
        
        bitset<32> little(n);
        string binary = little.to_string();

        string next;
        next += binary.substr(24, 8) + binary.substr(16, 8) + binary.substr(8, 8) + binary.substr(0, 8);
        
        if (next.front() == '0')
        {
            bitset<32> big(next);
            cout << big.to_ulong() << '\n';
        }
        else
        {
            next.front() = '0';
            bitset<32> big(next);
            cout << (int)(-pow(2, 31) + big.to_ulong()) << '\n';
        }
    }
    
	return 0;
}
