// Sharing Chocolate
// UVa ID: 1099
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int cases = 0;
    int n, x, y, parts[20];
    
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": ";

        cin >> x >> y;
        for (int i = 0; i < n; i++)
            cin >> parts[i];

        sort(parts, parts + n, greater<int>());
        
        vector<pair<int, int>> remain;
        remain.push_back(make_pair(x, y));
        int pieces = 0;
        
        while (true)
        {
            
        }
        
        cout << (pieces == n && remain.size() == 0 ? "Yes\n" : "No\n");
    }
    
    return 0;
}
