// Flea circus
// UVa ID: 10938
// Verdict: Accepted
// Submission Date: 2017-02-26
// UVa Run Time: 0.110s
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 5010, MAXE = 10010;

struct edge
{
    int id, u, v, next;
};

edge input[MAXE], query[MAXE];
int idx, first_input[MAXV], first_query[MAXV];
int number_of_vertices, number_of_queries;
int parent[MAXV], ranks[MAXV], ancestor[MAXV], visited[MAXV];
int father[MAXV], colored[MAXV], answer[MAXV];

void make_set()
{
    for (int i = 0; i < number_of_vertices; i++) parent[i] = i, ranks[i] = 0;
}

// 带路径压缩的查找，使用递归实现。
int find_set(int x)
{
    return (x == parent[x] ? x : parent[x] = find_set(parent[x]));
}

//  集合的按秩合并。
bool union_set(int x, int y)
{
    x = find_set(x), y = find_set(y);
    if (x != y)
    {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else
        {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

void lca(int u)
{
    ancestor[find_set(u)] = u;
    visited[u] = 1;

    for (int i = first_input[u]; i != -1; i = input[i].next)
        if (!visited[input[i].v])
        {
            father[input[i].v] = u;

            lca(input[i].v);
            union_set(u, input[i].v);
            ancestor[find_set(u)] = u;
        }

    colored[u] = 1;

    for (int i = first_query[u]; i != -1; i = query[i].next)
        if (colored[query[i].v])
            answer[query[i].id] = ancestor[find_set(query[i].v)];
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int u, v;
    while (cin >> number_of_vertices, number_of_vertices)
    {
        idx = 0;
        memset(first_input, -1, sizeof(int) * number_of_vertices);

        for (int i = 0; i < number_of_vertices - 1; i++)
        {
            cin >> u >> v;
            u--, v--;

            input[idx] = (edge){idx, u, v, first_input[u]};
            first_input[u] = idx++;

            input[idx] = (edge){idx, v, u, first_input[v]};
            first_input[v] = idx++;
        }

        idx = 0;
        memset(first_query, -1, sizeof(int) * number_of_vertices);

        cin >> number_of_queries;
        for (int i = 0; i < number_of_queries; i++)
        {
            cin >> u >> v;
            u--, v--;

            query[idx] = (edge){i, u, v, first_query[u]};
            first_query[u] = idx++;
            
            query[idx] = (edge){i, v, u, first_query[v]};
            first_query[v] = idx++;
        }

        memset(visited, 0, sizeof(int) * number_of_vertices);
        memset(colored, 0, sizeof(int) * number_of_vertices);
        memset(father, -1, sizeof(int) * number_of_vertices);
        make_set();
        
        lca(0);
        
        for (int i = 0; i < number_of_queries; i++)
        {
            int aa = answer[i], uu = query[2 * i].u, vv = query[2 * i].v;
            vector<int> sequence;
            while (uu != aa)
            {
                sequence.push_back(uu);
                uu = father[uu];
            }
            sequence.push_back(aa);
            
            int position = 0;
            while (vv != aa)
            {
                sequence.insert(sequence.end() - position, vv);
                vv = father[vv];
                position++;
            }
            
            int middle = sequence.size() / 2;
            if (sequence.size() % 2 == 1)
            {
                cout << "The fleas meet at " << (sequence[middle] + 1) << ".\n";
            }
            else
            {
                int left = sequence[middle - 1], right = sequence[middle];
                if (left > right) swap(left, right);
                cout << "The fleas jump forever between ";
                cout << (left + 1) << " and " << (right + 1) << ".\n";
            }
        }
    }

    return 0;
}
