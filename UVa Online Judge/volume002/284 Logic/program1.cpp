// Logic
// UVa ID: 284
// Verdict: Accepted
// Submission Date: 2019-04-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

vector<int> edges[MAXV];
int visited[MAXV];
int input[MAXV], idxOfInput, output[MAXV], idxOfOutput;
int value[MAXV];
char operation[MAXV];

void dfs(int u)
{
    visited[u] = 1;
    int r = 1;
    if (operation[u] == '|') r = 0;
    for (auto v : edges[u])
    {
        if (!visited[v])
            dfs(v);
        if (operation[u] == '!') r = !value[v];
        else if (operation[u] == '|') r |= value[v];
        else r &= value[v];
    }
    value[u] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, block;

    getline(cin, line);
    int cases = stoi(line);

    for (int cs = 1; cs <= cases; cs++)
    {
        for (int i = 0; i < MAXV; i++) edges[i].clear();
        idxOfInput = idxOfOutput = 0;
        while (getline(cin, line), line.front() != 'e')
        {
            istringstream iss(line);
            iss >> block;
            int v = (block[0] - '0') * 10 + (block[1] - '0');
            operation[v] = block[2];
            if (operation[v] == 'i') input[idxOfInput++] = v;
            if (operation[v] == 'o') output[idxOfOutput++] = v;
            while (iss >> block)
            {
                if (block == "..") break;
                int u = (block[0] - '0') * 10 + (block[1] - '0');
                edges[u].push_back(v);
            }
        }

        getline(cin, line);
        int sets = stoi(line);
        
        for (int s = 0; s < sets; s++)
        {
            getline(cin, line);

            memset(visited, 0, sizeof(visited));
            for (int j = 0; j < idxOfInput; j++)
            {
                value[input[j]] = line[j] - '0';
                visited[input[j]] = 1;
            }

            for (int j = 0; j < MAXV; j++)
                if (!visited[j])
                    dfs(j);
            
            for (int j = 0; j < idxOfOutput; j++)
                cout << value[output[j]];
            cout << '\n';
        }
        cout << '\n';
    }
    
    return 0;
}
