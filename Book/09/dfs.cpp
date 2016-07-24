#include <iostream>

using namespace std;

vector<vector<int>> edges;
vector<int> parent, color, time_of_discover, time_of_finish;

void dfs(int current)
{
    discovered[current] = true;
    for (int i = 0; i < edges[current].size(); i++)
        if (discovered[edges[current][i]] == false)
        {
            parent[edges[current][i]] = current;
            dfs(edges[current][i]);
        }
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    cin.ignore();
    
    edges.clear();
    edges.resize(n + 1);
    
    for (int i = 1; i <= n; i++)
    {
        string line;
        getline(cin, line);
        istringstream iss(line);
        int m;
        while (iss >> m)
        {
            edges[i].push_back(m);
            edges[m].push_back(i);
        }
    }

    parent.resize(edges.size());
    discovered.resize(edges.size());

    fill(parent.begin(), parent.end(), -1);
    fill(discovered.begin(), discovered.end(), false);
        
    dfs(1);
    
    for (int i = 1; i < parent.size(); i++)
        cout << parent[i] << " ";
    cout << endl;
    
    return 0;
}
