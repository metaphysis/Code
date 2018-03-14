// Basically Speaking
// UVa ID: 389
// Verdict: Accepted
// Submission Date: 2016-06-27
// UVa Run Time: 0.270s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string number;
    int base1, base2;
    string digits = "0123456789ABCDEF";
    map<char, int> key;
    
    for (int i = 0; i < digits.length(); i++)
        key.insert(make_pair(digits[i], i));
        
    while (cin >> number >> base1 >> base2)
    {
        int value = 0;
        for (int i = 0; i < number.length(); i++)
            value = value * base1 + key[number[i]];
            
        string target;
        while (value)
        {
            target.insert(target.begin(), digits[value % base2]);
            value /= base2;
        }
        
        if (target.length() == 0) target = "0";
        if (target.length() > 7) target = "ERROR";
        
        cout << setw(7) << right << target << endl;
    }
    
	return 0;
}
