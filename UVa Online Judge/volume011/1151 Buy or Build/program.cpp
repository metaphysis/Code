// Buy or Build
// UVa ID: 1151
// Verdict: Accepted
// Submission Date: 2017-01-12
// UVa Run Time: 0.160s
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

const int MAXV = 1010, MAX_DIST = 1000000000, MAX_SUBNET = 10;

struct point
{
    int x, y;
};

int cases = 0;
int number_of_cities, number_of_subnet, cities_in_subnet, min_cost_of_total;
int subnet[MAX_SUBNET][MAXV], cost_of_setup[MAXV][MAXV], dist_of_subnet[MAX_SUBNET][MAX_SUBNET];
int dist_to_tree[MAXV], intree[MAXV];
point cities[MAXV];

int prim()
{
    int min_weight_sum = 0;

    // update the distance between tree and vertex which is out-of-tree.
    for (int i = 0; i < number_of_cities; i++)
    {
        dist_to_tree[i] = MAX_DIST;
        if (intree[i]) dist_to_tree[i] = 0;
        else
        {
            for (int j = 0; j < number_of_cities; j++)
                if (intree[j] && dist_to_tree[i] > cost_of_setup[i][j])
                    dist_to_tree[i] = cost_of_setup[i][j];
        }
    }

    // find a vertex which is out-of-tree.
    int u = 0;
    for (int i = 0; i < number_of_cities; i++)
        if (intree[i])
        {
            u = i;
            break;
        }

    // if no vertex out of tree, set the first vertex out of tree.
    intree[u] = 0, dist_to_tree[u] = 0;
    while (!intree[u])
    {
        intree[u] = 1;
        min_weight_sum += dist_to_tree[u];
        
        for (int i = 0; i < number_of_cities; i++)
            if (!intree[i] && dist_to_tree[i] > cost_of_setup[u][i])
                dist_to_tree[i] = cost_of_setup[u][i];

        int min_dist = MAX_DIST;
        for (int i = 0; i < number_of_cities; i++)
            if (!intree[i] && min_dist > dist_to_tree[i])
            {
                min_dist = dist_to_tree[i];
                u = i;
            }
    }

    return min_weight_sum;
}

void get_cost_of_all(int flag[], int idx)
{
    int current_cost = 0;
    
    memset(intree, 0, sizeof(intree));

    vector<int> selected;
    for (int i = 0; i < idx; i++)
    {
        current_cost += subnet[flag[i]][0];
        for (int j = 1; j <= number_of_cities && subnet[flag[i]][j]; j++)
            intree[subnet[flag[i]][j] - 1] = 1;
        selected.push_back(flag[i]);
    }
    
    current_cost += prim();
    
    int min_cost_of_subnet = MAX_DIST;
    do
    {
        int cost_of_subnet = 0;
        for (int i = 0; i < idx - 1; i++)
            cost_of_subnet += dist_of_subnet[selected[i]][selected[i + 1]];
        min_cost_of_subnet = min(min_cost_of_subnet, cost_of_subnet);
    } while (next_permutation(selected.begin(), selected.end()));

    current_cost += min_cost_of_subnet;

    min_cost_of_total = min(min_cost_of_total, current_cost);
}

void generate(int flag[], int idx, int last)
{
    if (idx < last)
    {
        if (idx == 0)
        {
            for (int i = 0; i < number_of_subnet; i++)
            {
                flag[idx] = i;
                generate(flag, idx + 1, last);
            }
        }
        else
        {
            for (int i = flag[idx - 1] + 1; i < number_of_subnet; i++)
            {
                flag[idx] = i;
                generate(flag, idx + 1, last);
            }
        }
    }
    else
        get_cost_of_all(flag, idx);
}

void enumerating_subset()
{
    for (int i = 1; i <= number_of_subnet; i++)
    {
        int *flag = new int[number_of_subnet];
        generate(flag, 0, i);
        delete [] flag;
    }
}

int get_cost_of_setup(int i, int j)
{
    int x_diff = cities[i].x - cities[j].x, y_diff = cities[i].y - cities[j].y;
    return x_diff * x_diff + y_diff * y_diff;
}

int get_dist_of_subnet(int i, int j)
{
    int min_dist = MAX_DIST;
    
    for (int ii = 1; subnet[i][ii]; ii++)
        for (int jj = 1; subnet[j][jj]; jj++)
            min_dist = min(min_dist, cost_of_setup[subnet[i][ii] - 1][subnet[j][jj] - 1]);
            
    return min_dist;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        cin >> number_of_cities >> number_of_subnet;

        for (int i = 0; i < number_of_subnet; i++)
        {
            cin >> cities_in_subnet >> subnet[i][0];
            for (int j = 1; j <= cities_in_subnet; j++)
                cin >> subnet[i][j];

            subnet[i][cities_in_subnet + 1] = 0;
        }

        for (int i = 0; i < number_of_cities; i++)
            cin >> cities[i].x >> cities[i].y;

        for (int i = 0; i < number_of_cities; i++)
            for (int j = i; j < number_of_cities; j++)
                cost_of_setup[i][j] = cost_of_setup[j][i] = get_cost_of_setup(i, j);

        for (int i = 0; i < number_of_subnet; i++)
            for (int j = i + 1; j < number_of_subnet; j++)
                dist_of_subnet[i][j] = dist_of_subnet[j][i] = get_dist_of_subnet(i, j);

        // no sub network selected.
        memset(intree, 0, sizeof(intree));
        min_cost_of_total = prim();

        // some sub network selected.
        enumerating_subset();
        
        cout << min_cost_of_total << '\n';
    }

    return 0;
}
