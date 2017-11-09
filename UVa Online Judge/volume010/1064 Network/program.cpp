// Network
// UVa ID: 1064
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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int n, m;
    int number, starting, ending;
    
    while (cin >> n >> m, n > 0)
    {
        int buffer = 0, most = 0;
        vector<int> length(n + 1, 0);
        vector<int> waiting(n + 1, 1);
        vector<set<int>> buffered(n + 1, set<int>());
        vector<map<int, int>> packets(n + 1, map<int, int>());
        
        for (int i = 1; i <= n; i++)
            cin >> length[i];

        for (int i = 1; i <= m; i++)
        {
            cin >> number >> starting >> ending;
 
            if (waiting[number] == starting)
            {
                waiting[number] = ending + 1;
                int w = waiting[number];

                while (buffered[number].find(w) != buffered[number].end())
                {
                    buffer -= packets[number][w] - w + 1;
                    buffered[number].erase(w);
                    waiting[number] = packets[number][w] + 1;
                    packets[number].erase(w);
                }
            }
            else
            {
                buffer += ending - starting + 1;
                most = max(most, buffer);
                buffered[number].insert(starting);
                packets[number][starting] = ending;
            }
        }
        
        cout << "Case " << ++cases << ": " << most << "\n\n";
    }
    
    return 0;
}
