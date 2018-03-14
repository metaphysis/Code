// The Forrest for the Trees
// UVa ID: 599
// Verdict: Accepted
// Submission Date: 2016-08-12
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 26;

int parent[MAX_N], ranks[MAX_N];

int findSet(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
}

void unionSet(int x, int y)
{
    x = findSet(x);
    y = findSet(y);
    
    if (x == y)
        return;
        
    if (ranks[x] > ranks[y])
        parent[y] = x;
    else
    {
        parent[x] = y;
        if (ranks[x] == ranks[y])
            ranks[y]++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    for (int i = 1; i <= cases; i++)
    {
        memset(ranks, 0, sizeof(ranks));
        memset(parent, -1, sizeof(parent));
        
        while (getline(cin, line), line.length() > 0 && line.front() != '*')
        {
            int start = -1, end = -1;
            for (int j = 0; j < line.length(); j++)
            {
                if (isalpha(line[j]))
                {
                    if (start == -1)
                        start = line[j] - 'A';
                    else
                    {
                        end = line[j] - 'A';
                        break;
                    }
                }
            }
            
            if (parent[start] == -1) parent[start] = start;
            if (parent[end] == -1) parent[end] = end;
            
            unionSet(start, end);
        }
        
        while (getline(cin, line))
        {
            if (line.length() == 0)
                continue;

            for (int j = 0; j < line.length(); j++)
            {
                if (isalpha(line[j]))
                {
                    int vertex = line[j] - 'A';
                    if (parent[vertex] == -1)
                        parent[vertex] = -2;
                }
            }
            
            break;
        }
        
        int trees = 0, acorns = 0;
        for (int j = 0; j < 26; j++)
            if (parent[j] == j)
                trees++;
            else if (parent[j] == -2)
                acorns++;
                
        cout << "There are " << trees << " tree(s) and " << acorns << " acorn(s).\n";
    }
    
	return 0;
}
