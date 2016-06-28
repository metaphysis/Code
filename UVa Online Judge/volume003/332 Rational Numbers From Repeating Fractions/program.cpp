// Rational Numbers From Repeating Fractions
// UVa IDs: 332
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.120s
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
    int j, cases = 0;
    string fractions;
    
    while (cin >> j, j >= 0)
    {
        cin >> fractions;
        
        long long int numerator, denominator;
        if (j == 0)
        {
            fractions = fractions.substr(2);
            numerator = stoll(fractions);
            denominator = pow(10, fractions.length());
        }
        else
        {
            fractions = fractions.substr(2);
            int k = fractions.length() - j;
            string repeating = fractions.substr(fractions.length() - j);
            while (fractions.length() <= 30)
                fractions += repeating;
            
            string first = fractions.substr(0, k + j);
            string second = fractions.substr(0, k);
            if (second.length() == 0) second = "0";
            
            numerator = stoll(first) - stoll(second);
            denominator = pow(10, k + j) - pow(10, k);
        }
        
        long long int a = numerator, b = denominator, c;
        while (b != 0)
            c = a % b, a = b, b = c;

        cout << "Case " << ++cases << ": " << numerator / a << "/" << denominator / a << endl;
    }
    
	return 0;
}
