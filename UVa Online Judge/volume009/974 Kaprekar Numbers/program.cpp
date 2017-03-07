// Kaprekar Numbers
// UVa ID: 974
// Verdict: Accepted
// Submission Date: 2017-03-07
// UVa Run Time: s
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

    int kaprekar[10000], counter = 0;
    
    for (int i = 2; i <= 40000; i++)
    {
        int j = i * i, k = 10;
        while (j > k)
        {
            int quotient = j / k, remainder = j % k;
            if (quotient > 0 && remainder > 0 && (i == (quotient + remainder)))
            {
                kaprekar[counter++] = i;
                //cout << i << '\n';
                break;
            }
            
            k *= 10;
        }
    }
    
    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        int INF, SUP;
        cin >> INF >> SUP;
        
        cout << "case #" << c << '\n';
        
        int printed = 0;
        for (int i = 0; i < counter; i++)
            if (kaprekar[i] >= INF && kaprekar[i] <= SUP)
            {
                cout << kaprekar[i] << '\n';
                printed++;
            }
            
        if (printed == 0) cout << "no kaprekar numbers\n";
    }
    
    return 0;
}
