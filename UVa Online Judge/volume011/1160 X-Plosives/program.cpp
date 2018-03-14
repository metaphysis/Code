// X-Plosives
// UVa ID: 1160
// Verdict: Accepted
// Submission Date: 2018-02-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100010;

int parent[MAXV], ranks[MAXV], pairs[MAXV];

void makeSet()
{
    for (int i = 0; i < MAXV; i++) parent[i] = i, ranks[i] = 1, pairs[i] = 0;
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int a, b, refusals;

    makeSet();
    refusals = 0;
    while (cin >> a)
    {
        if (a >= 0)
        {
            cin >> b;
            int x = findSet(a), y = findSet(b);
            if (x != y)
            {
                if (ranks[x] + ranks[y] == pairs[x] + pairs[y] + 1) refusals++;
                else
                {
                    if (ranks[x] > ranks[y])
                    {
                        parent[y] = x, ranks[x] += ranks[y], pairs[x] += pairs[y] + 1;
                    }
                    else 
                    {
                        parent[x] = y, ranks[y] += ranks[x], pairs[y] += pairs[x] + 1;
                    }
                }
            }
            else
            {
                if (ranks[x] == pairs[x] + 1) refusals++;
                else
                {
                    pairs[x]++;
                }
            }
        }
        else
        {
            cout << refusals << '\n';
            makeSet();
            refusals = 0;
        }
    }

    return 0;
}
