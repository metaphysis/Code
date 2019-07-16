// Piotr's Ants
// UVa ID: 10881
// Verdict: Accepted
// Submission Date: 2019-07-16
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct ant
{
    int location, id;
    string direction;
} ants[10010];

bool cmp1(ant a, ant b)
{
    return a.location < b.location;
}

bool cmp2(ant a, ant b)
{
    return a.id < b.id;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, mapping[10010];
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int L, T, n;
        cin >> L >> T >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ants[i].location >> ants[i].direction;
            ants[i].id = i;
        }
        sort(ants, ants + n, cmp1);
        for (int i = 0; i < n; i++)
            mapping[ants[i].id] = i;
        for (int i = 0; i < n; i++)
        {
            if (ants[i].direction == "L") ants[i].location -= T;
            else ants[i].location += T;
        }
        sort(ants, ants + n, cmp1);
        cout << "Case #" << cs << ":\n";
        for (int i = 0; i < n; i++)
        {
            if (ants[i].location < 0 || ants[i].location > L) ants[i].direction = "Fell off";
            else
            {
                if ((i && ants[i].location == ants[i - 1].location) ||
                    (i < n - 1 && ants[i].location == ants[i + 1].location))
                        ants[i].direction = "Turning";
            }
        }
        for (int i = 0; i < n; i++)
        {
            int tid = mapping[i];
            if (ants[tid].location >= 0 && ants[tid].location <= L)
                cout << ants[tid].location << ' ';
            cout << ants[tid].direction << '\n';
        }
        cout << '\n';
    }

    return 0;
}
