// Containers
// UVa ID: 1062
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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    int cases = 0;

    while (cin >> line, line != "end")
    {
        vector<string> stacks;
        string empty;
        
        for (int i = 0; i < line.length(); i++)
        {
            bool placed = false;
            for (int j = 0; j < stacks.size(); j++)
            {
                if (line[i] <= stacks[j].back())
                {
                    stacks[j].push_back(line[i]);
                    placed = true;
                    break;
                }
            }
            
            if (!placed)
            {
                stacks.push_back(empty);
                stacks.back().push_back(line[i]);
            }
        }

        cout << "Case " << ++cases << ": " << stacks.size() << '\n';
    }
    
    return 0;
}
