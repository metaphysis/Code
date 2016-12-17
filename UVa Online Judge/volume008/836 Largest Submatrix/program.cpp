// Largest Submatrix
// UVa ID: 836
// Verdict: Accepted
// Submission Date: 2016-12-15
// UVa Run Time: 0.000s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int matrix[30][30], md[30][30], n, cases;
    string line;

    getline(cin, line);
    cases = stoi(line);

    getline(cin, line);
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        n = 0;
        while (getline(cin, line), line.length() > 0)
        {
            for (int i = 0; i < line.length(); i++)
                matrix[n + 1][i + 1] = line[i] - '0';
            n++;
        }
        
        // 矩阵中存储的元素下标从1开始，这样便于计算。
        memset(md, 0, sizeof(md));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                md[i][j] = md[i][j - 1] + md[i - 1][j] - md[i - 1][j - 1] + matrix[i][j];

                
        int largest = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                for (int h = 0; h <= n - i; h++)
                {
                    for (int w = 0; w <= n - j; w++)
                    {
                        int s = md[i + h][j + w] - md[i - 1][j + w] - md[i + h][j - 1] + md[i - 1][j - 1];
                        if (s == (w + 1) * (h + 1))
                        {
                            if (s > largest) largest = s;
                        }
                        else break;
                    }
                }
            }
            
        cout << largest << '\n';
    }

	return 0;
}
