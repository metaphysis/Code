// Prim, Prim
// UVa ID: 10807
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, MAXE = 10010;

struct edge {
    int from, to, weight, enabled;

    bool operator<(const edge& x) const {
        return weight < x.weight;
    }
};

edge edges[MAXE];
int parent[MAXV], ranks[MAXV], number_of_vertices, number_of_edges;

void make_set()
{
    for (int i = 0; i <= number_of_vertices; i++) parent[i] = i, ranks[i] = 0;
}

int find_set(int x)
{
    return (parent[x] == x ? x : parent[x] = find_set(parent[x]));
}

bool union_set(int x, int y)
{
    x = find_set(x), y = find_set(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

void kruskal()
{
    int A = 0, counterOfA = 0;

    make_set();
    sort(edges, edges + number_of_edges);

    for (int i = 0; i < number_of_edges; i++)
        if (union_set(edges[i].from, edges[i].to)) {
            A += edges[i].weight;
            edges[i].enabled = 0;
            counterOfA++;
        }

    if ((counterOfA + 1) != number_of_vertices) {
        cout << "No way!\n";
        return;
    }
    
    int B, counterOfB = 0;

    make_set();

    for (int i = 0; i < number_of_edges; i++)
        if (edges[i].enabled && union_set(edges[i].from, edges[i].to)) {
            B += edges[i].weight;
            counterOfB++;
        }

    if ((counterOfB + 1) != number_of_vertices) {
        cout << "No way!\n";
        return;
    }

    cout << (A + B) << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int from, to, weight;
    while (cin >> number_of_vertices, number_of_vertices)
    {
        cin >> number_of_edges;
        for (int i = 0; i < number_of_edges; i++)
        {
            cin >> from >> to >> weight;
            edges[i] = (edge){from, to, weight, 1};
        }
        
        kruskal();
    }
    
    return 0;
}
