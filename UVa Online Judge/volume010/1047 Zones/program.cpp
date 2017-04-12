// Zones
// UVa ID: 1047
// Verdict: Accepted
// Submission Date: 2017-04-12
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct data
{
    int sets, bit, customers;
};

data towers[30];
int planned, built, areas;
int used[20], recommended, maxCustomers = 0;

void dfs(int start, int depth, int bit)
{
    if (depth >= built)
    {
        int customers = 0;
        int all = planned + areas;

        for (int i = 0; i < planned; i++)
            if (used[i])
                customers += towers[i].customers;
                
        // inclusion-exclusion principle
        for (int i = planned; i < all; i++)
        {
            int a = bit, b = towers[i].bit, ones = 0;
            while (a && b)
            {
                if ((a & b) & 1) ones++;
                a >>= 1, b >>= 1;
            }

            if (ones >= 2) customers -= towers[i].customers * (ones - 1);
        }
        
        if (customers > maxCustomers)
        {
            maxCustomers = customers;
            recommended = bit;
        }
        return;
    }

    for (int i = start; i < planned; i++)
        if (!used[i])
        {
            used[i] = 1;
            dfs(i + 1, depth + 1, bit | (1 << i));
            used[i] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;

    while (cin >> planned >> built, planned > 0)
    {
        cout << "Case Number  " << ++cases << '\n';

        maxCustomers = 0;
        memset(towers, 0, sizeof(towers));
        memset(used, 0, sizeof(used));

        for (int i = 0; i < planned; i++)
        {
            towers[i].sets = 1, towers[i].bit = 1 << i;
            cin >> towers[i].customers;
        }

        cin >> areas;
        for (int i = 0; i < areas; i++)
        {
            int idx, bit = 0;

            cin >> towers[i + planned].sets;

            for (int j = 0; j < towers[i + planned].sets; j++)
            {
                cin >> idx;
                bit |= (1 << (idx - 1));
            }

            towers[i + planned].bit = bit;
            cin >> towers[i + planned].customers;
        }

        dfs(0, 0, 0);

        cout << "Number of Customers: " << maxCustomers << '\n';
        cout << "Locations recommended:";
        for (int i = 0; i < planned; i++)
            if (recommended & (1 << i))
                cout << ' ' << (i + 1);
        cout << "\n\n";
    }

    return 0;
}
