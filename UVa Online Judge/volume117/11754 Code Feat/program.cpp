// Code Feat
// UVa ID: 11754
// Verdict: Accepted
// Submission Date: 2018-12-24
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int C, S, ki[16];
long long Xi[16], Yi[16][128];
long long O, M, a[16];

vector<long long> xs;

void extgcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0) x = 1, y = 0;
    else
    {
        extgcd(b, a % b, x, y);
        long long t = x - a / b * y;
        x = y, y = t;
    }
}

long long CRT()
{
    long long r = 0;
    for (int i = 0; i < C; i++)
    {
        long long Mi = M / Xi[i], x, y;
        extgcd(Mi, Xi[i], x, y);
        r = (r + a[i] * Mi * x) % M;
    }
    if (r <= 0) r += M;
    return r;
}

void dfs(int i)
{
    if (i == C)
    {
        xs.push_back(CRT());
        return;
    }
    for (int j = 0; j < ki[i]; j++)
    {
        a[i] = Yi[i][j];
        dfs(i + 1);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> C >> S)
    {
        if (C == 0) break;

        O = 1, M = 1;
        for (int i = 0; i < C; i++)
        {
            cin >> Xi[i] >> ki[i];
            M *= Xi[i], O *= ki[i];
            for (int j = 0; j < ki[i]; j++)
            {
                cin >> Yi[i][j];
            }
            sort(Yi[i], Yi[i] + ki[i]);
        }

        if (O < 10000)
        {
            xs.clear();
            dfs(0);
            sort(xs.begin(), xs.end());
            for (int i = 0, t = 0; i < S; t++)
                for (int j = 0; j < xs.size() && i < S; j++)
                {
                    if ((xs[j] + t * M) == 0) continue;
                    cout << (xs[j] + t * M) << '\n';
                    i++;
                }
        }
        else
        {
            int base = 0;
            for (int i = 1; i < C; i++)
                if (ki[i] * Xi[base] < ki[base] * Xi[i])
                    base = i;
            set<long long> rs[16];
            for (int i = 0; i < C; i++)
                for (int j = 0; j < ki[i]; j++)
                    rs[i].insert(Yi[i][j]);
            for (int i = 0, t = 0; i < S; t++)
                for (int j = 0; j < ki[base] && i < S; j++)
                {
                    long long xx = t * Xi[base] + Yi[base][j];
                    if (xx == 0) continue;
                    bool satisfied = true;
                    for (int k = 0; k < C; k++)
                    {
                        if (k != base && rs[k].find(xx % Xi[k]) == rs[k].end())
                        {
                            satisfied = false;
                            break;
                        }
                    }  
                    if (satisfied)
                    {
                        cout << xx << '\n';
                        i++;
                    }
                }
        }
        cout << '\n';
    }

    return 0;
}
