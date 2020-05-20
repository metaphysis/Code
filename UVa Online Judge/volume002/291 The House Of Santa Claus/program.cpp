// The House Of Santa Claus
// UVa ID: 291
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> edges(6);
int drawed[6][6] = { 0 };
vector < int > path;

void dfs(int index, int visited)
{
    if (visited == 8)
    {
        path.push_back(index);
        for (int i = 0; i < path.size(); i++)
            cout << path[i];
        cout << endl;
        path.erase(path.end() - 1);
        return;
    }
    
    for (int i = 0; i < edges[index].size(); i++)
    {
        if (drawed[index][edges[index][i]] == 0 &&
            drawed[edges[index][i]][index] == 0)
        {
            drawed[index][edges[index][i]] = 1;
            drawed[edges[index][i]][index] = 1;
            
            path.push_back(index);
            dfs(edges[index][i], visited + 1);
            path.erase(path.end() - 1);
            
            drawed[index][edges[index][i]] = 0;
            drawed[edges[index][i]][index] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    edges[1].push_back(2);
    edges[1].push_back(3);
    edges[1].push_back(5);
    
    edges[2].push_back(1);
    edges[2].push_back(3);
    edges[2].push_back(5);

    edges[3].push_back(1);
    edges[3].push_back(2);
    edges[3].push_back(4);
    edges[3].push_back(5);

    edges[4].push_back(3);
    edges[4].push_back(5);
    
    edges[5].push_back(1);
    edges[5].push_back(2);
    edges[5].push_back(3);
    edges[5].push_back(4);
    
    dfs(1, 0);
     
	return 0;
}
