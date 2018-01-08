// Forests
// UVa ID: 10227
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        int P, T;
        multiset<int> op[110];
        cin >> P >> T;
        
        int people, tree;
        string line;
        while (getline(cin, line), line.length() > 0)
        {
            istringstream iss(line);
            iss >> people >> tree;
            op[people].insert(tree);
        }
        
        int diff = 0;
        for (int i = 1; i <= P; i++)
            for (int j = i + 1; j <= P; j++)
            {
                vector<int> r(100, 0);
                set_difference(op[i].begin(), op[i].end(), op[j].begin(), op[j].end(), r.begin());
                if (r.front() > 0) diff++;
            }
        if (c > 1) cout << '\n';
        cout << diff << '\n';
    }

    return 0;
}
