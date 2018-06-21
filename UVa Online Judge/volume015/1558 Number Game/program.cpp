// Number Game
// UVa ID: 1558
// Verdict: Accepted
// Submission Date: 2018-06-21
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cache[1 << 20];

vector<int> getKnockout(int n)
{
    vector<int> outs;
    for (int i = 2; i <= 20; i++)
        if (!(n & (1 << (i - 1))))
        {
            bool ok = true;
            for (auto o : outs)
                if (i % o == 0)
                {
                    ok = false;
                    break;
                }
            if (ok) outs.push_back(i);
        }
    return outs;
}

int knockout(int n, int i)
{
    int next = n;
    vector<int> outs = getKnockout(n);
    for (int j = i; j <= 20; j += i)
    {
        next &= (~(1 << (j - 1)));
        for (auto o : outs)
            for (int x = j + o; x <= 20; x += o)
                next &= (~(1 << (x - 1)));
    }
    return next;
}

int dfs(int n)
{
    if (~cache[n]) return cache[n];
    for (int i = 2; i <= 20; i++)
        if (n & (1 << (i - 1)))
        {
            if (!dfs(knockout(n, i)))
                return cache[n] = 1;
        }
    return cache[n] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, a, ai;
    cin >> cases;
    memset(cache, -1, sizeof(cache));
    cache[0] = 0;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> a;
        int bit = 0;
        for (int i = 0; i < a; i++)
        {
            cin >> ai;
            bit |= (1 << (ai - 1));
        }
        vector<int> moves;
        for (int i = 2; i <= 20; i++)
            if (bit & (1 << (i - 1)))
            {
                if (!dfs(knockout(bit, i)))
                    moves.push_back(i);
            }
        cout << "Scenario #" << cs << ":\n";
        if (moves.size() > 0)
        {
            cout << "The winning moves are:";
            for (auto m : moves) cout << ' ' << m;
            cout << ".\n\n";
        }
        else
            cout << "There is no winning move.\n\n";
    }

    return 0;
}
