// Generating Fast, Sorted Permutation
// UVa ID: 10098
// Verdict: Accepted
// Submission Date: 2017-12-23
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    cin >> n;
    
    string line;
    for (int i = 0; i < n; i++)
    {
        cin >> line;
        sort(line.begin(), line.end());
        do cout << line << '\n'; while (next_permutation(line.begin(), line.end()));
        cout << '\n';
    }

    return 0;
}
