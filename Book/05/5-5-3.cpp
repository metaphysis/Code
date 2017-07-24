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

void getFraction(string fraction, int k, int j)
{
    long long numerator, denominator;

    if (j == 0)
    {
        fractions = fractions.substr(2);
        numerator = stoll(fractions);
        denominator = pow(10, fractions.length());
    }
    else
    {
        fractions = fractions.substr(2);
        string repeating = fractions.substr(fractions.length() - j);
        while (fractions.length() <= 30) fractions += repeating;
        
        string e1 = fractions.substr(0, k + j);
        string e2 = fractions.substr(0, k);
        if (e2b.length() == 0) second = "0";
        
        numerator = stoll(e1) - stoll(e2);
        denominator = pow(10, k + j) - pow(10, k);
    }
    
    long long a = numerator, b = denominator, c;
    while (b != 0) c = a % b, a = b, b = c;

    cout << numerator / a << "/" << denominator / a << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    return 0;
}
