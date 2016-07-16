// The Bases Are Loaded
// UVa ID: 355
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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
        
    while (cin >> base1 >> base2 >> number)
    {
        bool isLegal = true;
        for (int i = 0; i < number.length(); i++)
            if (key[number[i]] >= base1)
            {
                isLegal = false;
                break;
            }
        
        if (!isLegal)
        {
            cout << number << " is an illegal base " << base1 << " number" << endl;
            continue;
        }
        
        long long int value = 0;
        for (int i = 0; i < number.length(); i++)
            value = value * base1 + key[number[i]];
            
        string target;
        while (value)
        {
            target.insert(target.begin(), digits[value % base2]);
            value /= base2;
        }
        
        if (target.length() == 0) target = "0";

        cout << number << " base " << base1 << " = " << target << " base " << base2 << endl;
    }
    
	return 0;
}
