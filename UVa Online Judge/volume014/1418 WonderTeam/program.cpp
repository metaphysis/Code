// WonderTeam
// UVa ID: 1418
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net
//
// https://blog.csdn.net/metaphysis/article/details/155611987
//

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n and n != 0) {
        if (n <= 3) cout << 1 << endl;
        else if (n == 4) cout << 2 << endl;
        else cout << n << endl;
    }
    return 0;
}

