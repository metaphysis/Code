// Cipher
// UVa IDs: 306
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 1.700s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int gcd(int a, int b)
{
    int t;
    while (a % b)
        t = a, a = b, b = t % b;
    return b;
}

int findCycle(int permutation[], int n)
{
    int visited[210] = { }, cycle = 1, length = 0;

    for (int i = 1; i <= n; i++)
        if (visited[i] == 0)
        {
            visited[i] = 1, length = 1;
            for (int j = permutation[i]; j != i; j = permutation[j])
                visited[j] = 1, length++;
            cycle = cycle / gcd(cycle, length) * length;
        }

    return cycle;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int key[210], permutation[3][210], start[210], n, k;
    char message[210];

    while (cin >> n, n)
    {
        for (int i = 1; i <= n; i++)
            cin >> key[i];

        while (cin >> k, k)
        {
            for (int i = 1; i <= n; i++)
                permutation[1][i] = i;

            cin.getline(message, 210);

            int number = 1;
            while (message[number] != '\0')
                number++;
            while (number <= n)
                message[number++] = ' ';
            message[number] = '\0';

            int cycle = findCycle(key, n), current = 2, next = 1;
            k %= cycle, cycle = 1;

            while (cycle <= k)
            {
                swap(current, next);
                for (int j = 1; j <= n; j++)
                    permutation[next][key[j]] = permutation[current][j];
                cycle++;
            }

            for (int j = 1; j <= n; j++)
                cout << message[permutation[next][j]];
            cout << endl;
        }

        cout << endl;
    }

    return 0;
}
