// Ouroboros Snake
// UVa ID: 10040
// Verdict: Accepted
// Submission Date: 2017-08-21
// UVa Run Time: 0.150s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int used[1 << 20][2], sequence[22][1 << 21];

void hierholzer(int n)
{
    int mask = (1 << (n - 2)) - 1, u = 0;

    stack<int> path;
    vector<int> circuit;

    memset(used, 0, sizeof(int) * (1 << (n - 1)) * 2);
    path.push(u);

    while (!path.empty())
    {
        int v = 0;
        for (v = 0; v <= 1; v++)
            if (!used[u][v])
                break;

        if (v <= 1)
        {
            path.push(u);
            used[u][v] = 1;
            u = ((u & mask) << 1) + v;
        }
        else
        {
            circuit.push_back(u);
            u = path.top();
            path.pop();
        }
    }

    int bits = circuit.back();
    mask = (1 << (n - 1)) - 1;
    for (int i = circuit.size() - 2, j = 0; i >= 0; i--, j++)
    {
        sequence[n][j] = ((bits & mask) << 1) + (circuit[i] & 1);
        bits = sequence[n][j];
    }
}

void trick()
{
    sequence[1][0] = 0, sequence[1][1] = 1;
    for (int i = 2; i <= 21; i++)
        hierholzer(i);
}

int main(int argc, char *argv[])
{
    int cases, n, k;

    trick();

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k;
        cout << sequence[n][k] << '\n';
    }

    return 0;
}
