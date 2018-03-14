// Graph Coloring
// UVa ID: 193
// Verdict: Accepted
// Submission Date: 2016-03-16
// UVa Run Time: 0.003s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// The test data on UVa is so weak that backtracking can be accepted.

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> edges;
vector<bool> black;
vector<int> answer;
int maximum, n;

void backtrack(int node)
{
    if (node == n + 1)
    {
        int total = 0;
        for (int i = 1; i <= n; i++)
            if (black[i])
                total++;
                
        if (total > maximum)
        {
            maximum = total;
            answer.clear();
            for (int i = 1; i <= n; i++)
                if (black[i])
                    answer.push_back(i);
        }
        
        return;
    }
    
    bool blacked = false;
    for (int i = 0; i < edges[node].size(); i++)
        if (black[edges[node][i]])
        {
            blacked = true;
            break;
        }

    if (blacked == false)
    {
    
        black[node] = true;
        backtrack(node + 1);
        black[node] = false;
    }
    
    backtrack(node + 1);
}

void findMaximum()
{
    maximum = 0;
    black.resize(n + 1);
    fill(black.begin(), black.end(), false);
    
    backtrack(1);

    cout << maximum << "\n";
    for (int i = 0; i < answer.size(); i++)
        cout << (i > 0 ? " " : "" ) << answer[i];
    cout << "\n";
}

int main(int argc, char *argv[])
{
    int m, k, start, end;

    cin >> m;
    while (m--)
    {
        cin >> n >> k;

        edges.clear();
        edges.resize(n + 1);

        for (int i = 1; i <= k; i++)
        {
            cin >> start >> end;
            edges[start].push_back(end);
            edges[end].push_back(start);
        }

        findMaximum();
    }

    return 0;
}
