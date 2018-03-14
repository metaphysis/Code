// Koerner's Pub
// UVa ID: 10882
// Verdict: Accepted
// Submission Date: 2018-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// Inclusion-Exclusion Principle.

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, x, y, z;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case #" << c << ": ";
        cin >> x >> y >> z;
        int higher = min(min(x, y), z);
        int lower = 0;
        if (x + y + z > 100) lower = (x + y + z - 99) / 2;
        if (lower > higher)
            cout << "The records are faulty.\n";
        else
            cout << "Between " << lower << " and " << higher << " times.\n";
    }

    return 0;
}
