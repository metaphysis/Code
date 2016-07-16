// Extraploation Using a Difference Table
// UVa ID: 326
// Verdict: Accepted
// Submission Date: 2016-06-28
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
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n, n)
    {
        vector<long long int> number;
        for (int i = 1; i <= n; i++)
        {
            int value;
            cin >> value;
            number.push_back(value);
        }
        
        for (int i = n - 1; i >= 1; i--)
            for (int j = 0; j <= i - 1; j++)
                number[j] = number[j + 1] - number[j];
        
        int k;
        cin >> k;
        for (int i = 1; i <= k; i++)
            for (int j = 1; j <= n - 1; j++)
                number[j] += number[j - 1];
        
        cout << "Term " << (n + k) << " of the sequence is " << number.back() << endl;
    }
    
	return 0;
}
