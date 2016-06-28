// Rational Numbers From Repeating Fractions
// UVa IDs: 332
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

long long int getGcd(long long int a, long long int b)
{
    if (a == 0) return b;
    if (a < b) return getGcd(b, a);
    if (a > 0) return getGcd(a % b, b);
}

int main(int argc, char *argv[])
{
    int j, cases = 0;
    string fractions;
    
    while (cin >> j, j > 0)
    {
        cin >> fractions;
        
        fractions = fractions.substr(2);
        int k = fractions.length() - j;
        string repeating = fractions.substr(fractions.length() - j);
        while (fractions.length() <= 20)
            fractions += repeating;
        
        string first = fractions.substr(0, k + j);
        string second = fractions.substr(0, k);
        if (second.length() == 0) second = "0";
        
        long long int numerator = stoll(first) - stoll(second);
        long long int denominator = pow(10, k + j) - pow(10, k);
        long long int gcd = getGcd(numerator, denominator);

        cout << "Case " << ++cases << ": " << numerator / gcd << "/" << denominator / gcd << endl;
    }
    
	return 0;
}
