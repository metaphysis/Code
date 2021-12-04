// A Giveaway
// UVa ID: 13148
// Verdict: Accepted
// Submission Date: 2021-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    //clock_t start = clock();
    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    set<int> special = {
    1, 64, 729, 4096, 15625, 46656, 117649, 262144, 531441,
    1000000, 1771561, 2985984, 4826809, 7529536, 11390625, 16777216, 24137569, 34012224,
    47045881, 64000000, 85766121
    };
    
    int n;
    while (cin >> n, n)
    {
        if (special.count(n)) cout << "Special";
        else cout << "Ordinary";
        cout << '\n';
    }

    //clock_t finish = clock();
    //cout << 1.0 * (finish - start) / CLOCKS_PER_SEC << " seconds.\n";

    return 0;
}
