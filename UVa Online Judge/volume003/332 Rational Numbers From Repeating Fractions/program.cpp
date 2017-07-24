// Rational Numbers From Repeating Fractions
// UVa ID: 332
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.040s
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
    string fraction;
    
    while (cin >> j, j >= 0)
    {
        cin >> fraction;
        
        long long int numerator, denominator;
        
        fraction = fraction.substr(2);
        if (j == 0)
        {
            numerator = stoll(fraction);
            denominator = pow(10, fraction.length());
        }
        else
        {
            int k = fraction.length() - j;
            string preRepeated = fraction.substr(0, k);
            if (preRepeated.length() == 0) preRepeated = "0";
            
            numerator = stoll(fraction) - stoll(preRepeated);
            denominator = pow(10, k + j) - pow(10, k);
        }
        
        long long int a = numerator, b = denominator, c;
        while (b != 0) c = a % b, a = b, b = c;

        cout << "Case " << ++cases << ": " << numerator / a << "/" << denominator / a << '\n';
    }
    
	return 0;
}
