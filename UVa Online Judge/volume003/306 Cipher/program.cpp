// Cipher
// UVa ID: 306
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 2.610s
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

bool isSame(int a[], int b[], int n)
{
    for (int i = 1; i <= n; i++)
        if (a[i] != b[i])
            return false;
    return true;
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

            int cycle = 1, current = 2, next = 1;
            bool repeated = false, startSetted = false;

            while (cycle <= k)
            {
                swap(current, next);
                for (int j = 1; j <= n; j++)
                    permutation[next][key[j]] = permutation[current][j];

                if (!repeated && startSetted && isSame(start, permutation[next], n))
                {
                    k = (k - cycle) % (cycle - 1);
                    cycle = 1;
                    repeated = true;
                    continue;
                }

                if (!startSetted)
                {
                    for (int j = 1; j <= n; j++)
                        start[j] = permutation[next][j];
                    startSetted = true;
                }

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
