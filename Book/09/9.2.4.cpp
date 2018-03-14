#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, MAXE = 1000010;

struct edge {
    int from, to, weight, next;
};

edge edges[MAXE];
int first[MAXV];

int main(int argc, char *argv[])
{
    int numberOfVertices, numberOfEdges;
    int u, v, w, idx = 0;
    
    memset(first, -1, sizeof(first));
    
    cin >> numberOfVertices >> numberOfEdges;
    for (int i = 0; i < numberOfEdges; i++)
    {
        cin >> u >> v >> w;
        
        edges[idx] = (edge){u, v, w, first[u]};
        first[u] = idx++;
        
        edges[idx] = (edge){v, u, w, first[v]};
        first[v] = idx++;
    }

    for (int i = 1; i <= numberOfVertices; i++)
        for (int j = first[i]; j != -1; j = edges[j].next)
            cout << edges[j].from << ' ' << edges[j].to << ' ' << edges[j].weight << '\n';

    return 0;
}
