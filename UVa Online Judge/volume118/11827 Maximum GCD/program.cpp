// Maximum GCD
// UVa ID: 11827
// Verdict: Accepted
// Submission Date: 2017-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, n;
    cin >> cases;
    
    cin.ignore(1024, '\n');
    
    for (int c = 1; c <= cases; c++)
    {
        vector<int> number;
        
        string line;
        getline(cin, line);
        
        istringstream iss(line);
        while (iss >> n) number.push_back(n);
        
        int maxGcd = 1;
        for (int i = 0; i < number.size(); i++)
            for (int j = i + 1; j < number.size(); j++)
                maxGcd = max(maxGcd, gcd(number[i], number[j]));
                
        cout << maxGcd << '\n';
    }
    
    return 0;
}
