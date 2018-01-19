// Dynamic Frog
// UVa ID: 11157
// Verdict: Accepted
// Submission Date: 2018-01-19
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

int getMax(vector<int> &numbers)
{
    int minMax = 0, top = numbers.size();
    for (int i = 1, j = 0; i < top; j = i, i + 2 < top ? i += 2 : i += 1)
        minMax = max(minMax, numbers[i] - numbers[j]);
    for (int i = 2, j = 0; i < top; j = i, i + 2 < top ? i += 2 : i += 1)
        minMax = max(minMax, numbers[i] - numbers[j]);
    return minMax;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, D, M, minMax;
    char S, dash;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> D;

        minMax = 0;
        vector<int> numbers; numbers.push_back(0);
        for (int i = 0; i < N; i++)
        {
            cin >> S >> dash >> M;
            numbers.push_back(M);
            if (S == 'B')
            {
                minMax = max(minMax, getMax(numbers));
                numbers.clear();
                numbers.push_back(M);
            }
        }
        numbers.push_back(D);
        minMax = max(minMax, getMax(numbers));

        cout << "Case " << c << ": " << minMax << '\n';
    }

    return 0;
}
