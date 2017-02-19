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
        int stacks = 0, containers = line.length();
        
        while (line.length() > 0)
        {
            vector<char> last(line.length());
            vector<int> lis(line.length(), 1);
            vector<vector<int>> sequences(line.length());
            
            for (int i = 0; i < line.length(); i++)
            {
                last[i] = line[i];
                sequences[i].push_back(i);
            }

            for (int i = 1; i < line.length(); i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (last[j] >= line[i] && (lis[j] + 1) > lis[i])
                    {
                        lis[i] = lis[j] + 1;
                        sequences[i].assign(sequences[j].begin(), sequences[j].end());
                        sequences[i].push_back(i);
                    }
                }
            }
            
            stacks++;
            
            int maxLength = 1, maxSequences = 0;
            for (int i = 1; i < line.length(); i++)
            {
                if (lis[i] > maxLength)
                {
                    maxLength = lis[i];
                    maxSequences = i;
                }
            }
            
            //cout << "maxLength = " << maxLength << '\n';
            
            for (int i = sequences[maxSequences].size() - 1; i >= 0; i--)
                line.erase(line.begin() + sequences[maxSequences][i]);
        }
        
        cout << "Case " << ++cases << ": " << stacks << '\n';
    }
    
    return 0;
}
