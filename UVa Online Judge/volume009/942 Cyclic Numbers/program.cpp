// Cyclic Numbers
// UVa ID: 942
// Verdict: Accepted
// Submission Date: 2017-03-16
// UVa Run Time: 0.020s
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, n, m;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        cout << (n / m) << '.';
        n %= m;
        
        if (n == 0)
        {
            cout << "0\n";
            continue;
        }
        
        unordered_map<int, int> appeared;
        vector<int> quotient;

        while (n > 0)
        {
            if (appeared.find(n) != appeared.end()) break;
            appeared[n] = quotient.size();
            n *= 10;
            quotient.push_back(n / m);
            n %= m;
        }
        
        int loop = 0;
        if (n > 0)
        {
            loop = appeared[n];
            for (int i = 0; i < loop; i++) cout << quotient[i];
            cout << '(';
        }
        
        for (int i = loop; i < quotient.size(); i++) cout << quotient[i];
            
        if (n > 0) cout << ')';
        cout << '\n';
    }
    
    return 0;
}
