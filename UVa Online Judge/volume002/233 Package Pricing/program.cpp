// Package Pricing
// UVa ID: 233
// Verdict: Accepted
// Submission Date: 2016-06-21
// UVa Run Time: 0.460s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct package
{
    int catalogue;
    double price;
    int supply[4];
};

struct choice
{
    double price;
    int index, parent;
};

int n;
vector < package > packages;
int base[4];
double minPrice;
map < int, int > counter;
choice memo[1048576];

int getIndex(int count[])
{
    int index = 0;
    for (int j = 0; j < 4; j++)
        index += count[j] * base[j];
    return index;
}

void dp(package need)
{
    base[0] = (need.supply[1] + 1) * (need.supply[2] + 1) * (need.supply[3] + 1);
    base[1] = (need.supply[2] + 1) * (need.supply[3] + 1);
    base[2] = need.supply[3] + 1;
    base[3] = 1;

    int current[4], next[4], maxState = getIndex(need.supply);

    for (int i = 0; i <= maxState; i++)
        memo[i] = (choice){1E20, -1, -1};

    memo[0] = (choice){0, -1, -1};
    for (int state = 0; state <= maxState; state++)
    {
        int s = state;
        for (int i = 0; i < 4; i++)
            current[i] = s / base[i], s %= base[i];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 4; j++)
                next[j] = min(current[j] + packages[i].supply[j], need.supply[j]);

            int index = getIndex(next);

            if (memo[index].price > memo[state].price + packages[i].price)
                memo[index] = (choice){memo[state].price + packages[i].price, i, state};
        }
    }

    counter.clear();
    for (int state = maxState; state > 0; state = memo[state].parent)
        counter[packages[memo[state].index].catalogue]++;
    minPrice = memo[maxState].price;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string line;

    while (getline(cin, line))
    {
        packages.clear();

        n = stoi(line);

        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            istringstream iss(line);

            package p;
            iss >> p.catalogue >> p.price;

            memset(p.supply, 0, sizeof(p.supply));
            char size;
            int count;
            while (iss >> size >> count)
                p.supply[size - 'a'] += count;

            packages.push_back(p);
        }

        getline(cin, line);
        int m = stoi(line);
        for (int i = 1; i <= m; i++)
        {
            getline(cin, line);
            istringstream iss(line);

            package need;
            memset(need.supply, 0, sizeof(need.supply));
            
            char size;
            int count;
            while (iss >> size >> count)
                need.supply[size - 'a'] += count;

            dp(need);

            cout << i << ":" << setw(8) << right;
            cout << fixed << setprecision(2) << minPrice;

            for (auto c : counter)
            {
                if (c.second > 0) cout << " " << c.first;
                if (c.second > 1) cout << "(" << c.second << ")";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
