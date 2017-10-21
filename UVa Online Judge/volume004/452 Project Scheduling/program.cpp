// Project Scheduling
// UVa ID: 452
// Verdict: Accepted
// Submission Date: 
// UVa Run Time: 0.110s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
    
    getline(cin, line);
    int cases = stoi(line);
    
    getline(cin, line);
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        
        int edges[30][30] = {}, days_needed[30] = {}, elapsed[30] = {}, indegree[30] = {}, visited[30] = {};
        
        while (getline(cin, line), line.length() > 0)
        {
            char letter;
            int days;
            string pretask;
            
            istringstream iss(line);
            iss >> letter >> days >> pretask;
            
            visited[letter - 'A'] = 1;
            elapsed[letter - 'A'] = days;
            days_needed[letter - 'A'] = days;
            
            for (int j = 0; j < pretask.length(); j++)
                edges[pretask[j] - 'A'][letter - 'A'] = 1;
            indegree[letter - 'A'] += pretask.length();
        }
        
        // topological sorting
        int unvisited[30];
        memcpy(unvisited, visited, sizeof(visited));
        
        while (true)
        {
            int indexer = -1;
            for (int j = 0; j < 26; j++)
                if (unvisited[j] && indegree[j] == 0)
                {
                    indexer = j;
                    break;
                }
            if (indexer == -1) break;
                
            unvisited[indexer] = 0;
            for (int j = 0; j < 26; j++)
                if (edges[indexer][j])
                {
                    elapsed[j] = max(elapsed[j], elapsed[indexer] + days_needed[j]);
                    indegree[j]--;
                }
        }
        
        int max_days = 0;
        for (int i = 0; i < 26; i++)
            if (visited[i])
                max_days = max(max_days, elapsed[i]);
        
        cout << max_days << '\n';
    }
    
	return 0;
}
