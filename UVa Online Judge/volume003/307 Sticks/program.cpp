// Sticks
// UVa ID: 307
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, totalLength, minLength, maxDepth;
vector<int> sticks;
vector<bool> visited;

bool backtrack(int depth, int current, int length)
{
    // how to pruning?
    if (depth == maxDepth) return true;
    
    for (int i = 1; i <= n; i++)
        if (visited[i] == false)
        {
            if (current + sticks[i] > length)
                continue;
                
            if (current + sticks[i] <= length)
            {
                visited[i] = true;
                if (backtrack(depth + 1, (current + sticks[i]) % length, length)) return true;
                visited[i] = false;
            }
        }
        
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    while (cin >> n, n)
    {
        totalLength = 0;
        minLength = 0;
        sticks.resize(n + 1);
        visited.resize(n + 1);
        
        for (int i = 1; i <= n; i++)
        {
            cin >> sticks[i];
            totalLength += sticks[i];
            minLength = max(minLength, sticks[i]);
        }

        sort(sticks.begin(), sticks.end(), greater<int>());

        for (int length = minLength; length <= totalLength; length++)
        {
            if (totalLength % length != 0)
                continue;
            
            maxDepth = sticks.size() - 1;
            fill(visited.begin(), visited.end(), false);
            for (int i = 1; i <= n; i++)
                if (sticks[i] == length)
                {
                    visited[i] = true;
                    maxDepth--;
                }
                    
            if (backtrack(0, 0, length))
            {
                cout << length << endl;
                break;
            }
        }
    }
    
	return 0;
}
