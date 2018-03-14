// How many nodes?
// UVa ID: 10223
// Verdict: Accepted
// Submission Date: 2017-02-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100;
const long long int MAX_NODES = 4294967295;

long long int catalan[MAX_N] = {0, 1};
map<long long int, int> nodes;

void getCatalan()
{
    nodes[0] = 0, nodes[1] = 1;
    for (int n = 2; n < MAX_N && catalan[n - 1] <= MAX_NODES; n++)
    {
        catalan[n] = 2 * catalan[n - 1] * (2 * n - 1) / (n + 1);
        nodes[catalan[n]] = n;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    getCatalan();
        
    long long int n;
    while (cin >> n) cout << nodes[n] << '\n';

	return 0;
}
