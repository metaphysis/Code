// Re-connecting Computer Sites
// UVa ID: 908
// Verdict: Accepted
// Submission Date: 2017-01-11
// UVa Run Time: 0.000s
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
#include <vector>

using namespace std;

struct edge
{
    int from, to, weight;
    
    bool operator<(const edge& x) const {
        return weight < x.weight;
    }
};

vector<edge> edges;
vector<int> parent, ranks;

void make_set()
{
    parent.resize(edges.size()); ranks.resize(edges.size());
    for (int i = 0; i < edges.size(); i++) {
        parent[i] = i; ranks[i] = 0;
    }
}

int find_set(int x)
{
    return (parent[x] == x ? x : parent[x] = find_set(parent[x]));
}

void union_set(int x, int y)
{
    x = find_set(x), y = find_set(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
    }
}

long long kruskal()
{
    long long min_weight_sum = 0;
    
    make_set();
    sort(edges.begin(), edges.end());
    
    for (int i = 0; i < edges.size(); i++) {
        int x = find_set(edges[i].from), y = find_set(edges[i].to);
        if (x != y) {
            union_set(x, y);
            min_weight_sum += edges[i].weight;
        }
    }
    
    return min_weight_sum;
}

int N, K, M;
 
int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int from, to, cost, cases = 0;
    while (cin >> N)
    {
        if (cases++ > 0) cout << '\n';

        long long original_cost = 0;
        for (int i = 2; i <= N; i++)
        {
            cin >> from >> to >> cost;
            original_cost += cost;
        }
        cout << original_cost << '\n';
        
        edges.clear();

        cin >> K;
        for (int i = 1; i <= K; i++)
        {
            cin >> from >> to >> cost;
            edges.push_back((edge){from - 1, to - 1, cost});
        }
        
        cin >> M;
        for (int i = 1; i <= M; i++)
        {
            cin >> from >> to >> cost;
            edges.push_back((edge){from - 1, to - 1, cost});
        }
        
        cout << kruskal() << '\n';
    }
 
    return 0;   
}
