// Dart-a-Mania
// UVa ID: 735
// Verdict: Accepted
// Submission Date: 2017-10-27
// UVa Run Time: 0.320s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, sequence[62];
    
    for (int i = 1; i <= 20; i++)
        sequence[i - 1] = i, sequence[i + 19] = 2 * i, sequence[39 + i] = 3 * i;
    sequence[60] = 50, sequence[61] = 0;
    sort(sequence, sequence + 62);
    
    int t = unique(sequence, sequence + 62) - sequence;
    
    while (cin >> n, n > 0)
    {
        int c = 0, p = 0;
        if (n <= 180)
        {
            for (int i = 0; i < t; i++)
                for (int j = 0; j < t; j++)
                    for (int k = 0; k < t; k++)
                        if (sequence[i] + sequence[j] + sequence[k] == n)
                        {
                            if (i < j && j < k) p += 6, c++;
                            else if (i == j && j < k || i < j && j == k) p += 3, c++;
                            else if (i == j && j == k) p += 1, c++;
                        }
        }

        if (c == 0)
        {
            cout << "THE SCORE OF " << n << " CANNOT BE MADE WITH THREE DARTS.\n";
            cout << "**********************************************************************\n";
        }
        else
        {
            cout << "NUMBER OF COMBINATIONS THAT SCORES " << n << " IS " << c << ".\n";
            cout << "NUMBER OF PERMUTATIONS THAT SCORES " << n << " IS " << p << ".\n";
            cout << "**********************************************************************\n";
        }
    }
    cout << "END OF OUTPUT\n";
    return 0;
}
