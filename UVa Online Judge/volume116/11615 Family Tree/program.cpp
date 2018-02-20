// Family Tree
// UVa ID: 11615
// Verdict: Accepted
// Submission Date: 2018-02-20
// UVa Run Time: 0.000s
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

int generations[21] = {0, 1};

int getGeneration(int number)
{
    for (int i = 20; i >= 1; i--)
        if (number >= generations[i])
            return i;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i <= 20; i++)
        generations[i] = 2 * generations[i - 1];

    int cases, N, A, B;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> A >> B;
        int total = pow(2, N) - 1;
        total -= pow(2, N - getGeneration(max(A, B)) + 1) - 2;
        cout << total << '\n';
    }

    return 0;
}
