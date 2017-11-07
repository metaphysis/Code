// Antiarithmetic?
// UVa ID: 10730
// Verdict: 
// Submission Date: 
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

struct element {
    int idx, number;
    
    bool operator<(const element &e) const
    {
        if (number != e.number) return number < e.number;
        return idx < e.idx;
    }
    
} elements[10010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    char colon;

    while (cin >> n, n > 0)
    {
        cin >> colon;
        
        for (int i = 0; i < n; i++)
        {
            elements[i].idx = i;
            cin >> elements[i].number;
        }
        
        sort(elements, elements + n);
        n = unique(elements, elements + n) - elements;
    }
    
    return 0;
}
