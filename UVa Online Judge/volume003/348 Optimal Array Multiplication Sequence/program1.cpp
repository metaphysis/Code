// Optimal Array Multiplication Sequence
// UVa ID: 348
// Verdict: Accepted
// Submission Date: 2016-06-29
// UVa Run Time: 0.040s
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
#include <string>
#include <vector>

using namespace std;

const int MAX_INTEGER = numeric_limits<int>::max();

int dimensions[15];
int multiplications[15][15], selectedK[15][15];

int findOptimalMultiplication(int i, int j)
{
    if (multiplications[i][j] < MAX_INTEGER)
        return multiplications[i][j];
    
    if (i == j)
        multiplications[i][j] = 0;
    else
    {
        for (int k = i; k <= j - 1; k++)
        {
            int times = findOptimalMultiplication(i, k);
            times += findOptimalMultiplication(k + 1, j);
            times += dimensions[i - 1] * dimensions[k] * dimensions[j];
                
            if (times < multiplications[i][j])
            {
                multiplications[i][j] = times;
                selectedK[i][j] = k;
            }
        }
    }

    return multiplications[i][j];
}

void printOptimalSequence(int i, int j)
{
    if (i == j)
        cout << "A" << i;
    else
    {
        cout << "(";
        printOptimalSequence(i, selectedK[i][j]);
        cout << " x ";
        printOptimalSequence(selectedK[i][j] + 1, j);
        cout << ")";
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int n, cases = 0;
    while (cin >> n, n)
    {
        for (int i = 1; i <= n; i++)
        {
            int row, column;
            cin >> row >> column;
            dimensions[i - 1] = row;
            if (i == n) dimensions[i] = column;
        }

        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++)
                multiplications[i][j] = MAX_INTEGER;
        
        findOptimalMultiplication(1, n);
        cout << "Case " << ++cases << ": ";
        printOptimalSequence(1, n);
        cout << endl;
    }

	return 0;
}
