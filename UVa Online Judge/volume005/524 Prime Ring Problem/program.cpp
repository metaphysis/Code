// Prime Ring Problem
// UVa ID: 524
// Verdict: Accepted
// Submission Date: 2016-08-07
// UVa Run Time: 0.110s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int ring[20], visited[20], n;
int primes[32] = {
    0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0,
    1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 1, 0, 1
};
    
void backtrack(int depth)
{
    if (depth == n - 1)
    {
        if (primes[ring[depth] + 1])
        {
            for (int i = 0; i < n; i++)
                cout << (i > 0 ? " " : "") << ring[i];
            cout << '\n';
        }
    }
    else
    {
        for (int i = 2; i <= n; i++)
            if (!visited[i] && primes[ring[depth] + i])
            {
                visited[i] = true;
                ring[depth + 1] = i;
                backtrack(depth + 1);
                visited[i] = false;
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n)
    {
        if (cases)
            cout << '\n';

        cout << "Case " << ++cases << ":\n";

        ring[0] = 1;
        backtrack(0);
    }
    
	return 0;
}
