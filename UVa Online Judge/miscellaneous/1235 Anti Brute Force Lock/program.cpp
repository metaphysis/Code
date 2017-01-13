// Anti Brute Force Lock
// UVa ID: 1235
// Verdict: Accepted
// Submission Date: 2017-01-12
// UVa Run Time: 0.030s
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

const int MAX_DIST = 1000000, MAXV = 510;

int edges[MAXV][MAXV], n, dist_to_tree[MAXV], intree[MAXV];
string password[MAXV];

int prim(int u)
{
    int min_weight_sum = 0;

    for (int i = 0; i <= n; i++)
    {
        intree[i] = 0; dist_to_tree[i] = MAX_DIST;
    }

    dist_to_tree[u] = 0;
    while (!intree[u])
    {
        intree[u] = 1;

        min_weight_sum += dist_to_tree[u];

        for (int v = 1; v <= n; v++)
        {
            if (!intree[v] && dist_to_tree[v] > edges[u][v])
                dist_to_tree[v] = edges[u][v];
        }

        int min_dist_to_tree = MAX_DIST;
        for (int v = 1; v <= n; v++)
        {
            if (!intree[v] && min_dist_to_tree > dist_to_tree[v])
            {
                min_dist_to_tree = dist_to_tree[v];
                u = v;
            }
        }
    }

    return min_weight_sum;
}

int get_rolls(int i, int j)
{
    int rolls = 0;
    for (int k = 0; k < 4; k++)
    {
        int a = password[i][k] - '0', b = password[j][k] - '0';
        if (a < b) swap(a, b);
        rolls += min(a - b, 10 + b - a);
    }
    return rolls;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        password[0] = "0000";
        for (int i = 1; i <= n; i++)
            cin >> password[i];
            
        for (int i = 0; i <= n; i++)
            for (int j = i; j <= n; j++)
                edges[i][j] = edges[j][i] = get_rolls(i, j);
                
        int min_rolls = prim(1);
        int start_rolls = MAX_DIST;
        for (int i = 1; i <= n; i++)
            start_rolls = min(start_rolls, edges[0][i]);
        min_rolls += start_rolls;

        cout << min_rolls << '\n';
    }

    return 0;
}
