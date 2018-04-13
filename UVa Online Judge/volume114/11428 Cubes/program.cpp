// Cubes
// UVa ID: 11428
// Verdict: Accepted
// Submission Date: 2018-04-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<int, int> cubes;
    for (int i = 1; i <= 100; i++)
        cubes[i * i * i] = i;
    int n;
    while (cin >> n, n > 0)
    {
        bool found = false;
        for (int y = 1; y <= 100; y++)
        {
            int t = y * y * y + n;
            if (cubes.find(t) != cubes.end())
            {
                cout << cubes[t] << ' ' << y << '\n';
                found = true;
                break;
            }
        }
        if (!found) cout << "No solution\n";
    }

    return 0;
}
