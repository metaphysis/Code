// Polly the Polynomial
// UVa ID: 498
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.070s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    istringstream iss;
    
    vector<long long> coefficients;
    
    string line;
    while (getline(cin, line))
    {
        iss.clear();
        iss.str(line);
        
        coefficients.clear();
        long long number;
        while (iss >> number)
            coefficients.push_back(number);
            
        getline(cin, line);
        iss.clear();
        iss.str(line);
        
        bool first = true;
        while (iss >> number)
        {
            long long sum = 0, base = 1;
            for (int i = coefficients.size() - 1; i >= 0; i--)
            {
                sum += base * coefficients[i];
                base *= number;
            }
            if (first) first = false;
            else cout << ' ';
            cout << sum;
        }
        cout << '\n';
    }
    
	return 0;
}
