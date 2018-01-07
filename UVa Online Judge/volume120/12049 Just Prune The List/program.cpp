// Just Prune The List
// UVa ID: 12049
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.190s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m, element;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        multiset<int> existed;
        for (int i = 0; i < n; i++)
        {
            cin >> element;
            existed.insert(element);
        }
        
        int cnt = 0;
        for (int j = 0; j < m; j++)
        {
            cin >> element;
            multiset<int>::iterator it = existed.find(element);
            if (it != existed.end()) existed.erase(it);
            else cnt++;
        }
        cnt += existed.size();
        cout << cnt << '\n';
    }
    
    return 0;
}
