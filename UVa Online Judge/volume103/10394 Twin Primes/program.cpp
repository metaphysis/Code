// Twin Primes
// UVa ID: 10394
// Verdict: Accepted
// Submission Date: 2018-03-08
// UVa Run Time: 0.270s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXN = 20000010;

int visited[MAXN] = {0};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i * i < MAXN; i++)
        if (!visited[i])
            for (int j = i * i; j < MAXN; j += i)
                visited[j] = 1;

    int previous = 0;
    vector<pair<int, int>> twins;
    for (int i = 2; i < MAXN; i++)
        if (!visited[i])
        {
            if (previous && i - previous == 2)
            {
                twins.push_back(make_pair(previous, i));
            }
            previous = i;
        }

    int S;
    while (cin >> S)
        cout << '(' << twins[S - 1].first << ", " << twins[S - 1].second << ")\n";

    return 0;
}
