// Integer Inquiry
// UVa ID: 424
// Verdict: Accepted
// Submission Date: 2016-07-13
// UVa Run Time: 0.000s
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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line, result = string(110, 0);
    while (getline(cin, line), line != "0")
    {
        int digit = 0, carry = 0;
        int j =  result.length() - 1;
        for (int i = line.length() - 1; i >= 0; i--, j--)
        {
            digit = line[i] - '0' + result[j] + carry;
            result[j] = digit % 10;
            carry = digit / 10;
        }

        while (j >= 0)
        {
            digit = result[j] + carry;
            result[j] = digit % 10;
            carry = digit / 10;
            j--;
        }
    }
    
    for (int i = 0; i < result.length(); i++)
    {
        if (result[i] == 0) continue;
        for (int j = i; j < result.length(); j++)
            cout << (char)(result[j] + '0');
        break;
    }
    cout << endl;
    
	return 0;
}
