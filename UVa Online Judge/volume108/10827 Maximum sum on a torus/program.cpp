// Maximum sum on a torus
// UVa ID: 10827
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const int INF = 0x3fffffff;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int matrix[80][80], md[80][80], n, cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> matrix[i][j];
        
        // 矩阵中存储的元素下标从1开始，这样便于计算。
        memset(md, 0, sizeof(md));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                md[i][j] = md[i][j - 1] + md[i - 1][j] - md[i - 1][j - 1] + matrix[i][j];

                
        int largest = -INF;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                for (int h = 0; h <= n - i; h++)
                {
                    for (int w = 0; w <= n - j; w++)
                    {
                        int s = md[i + h][j + w] - md[i - 1][j + w] - md[i + h][j - 1] + md[i - 1][j - 1];
                        largest = max(largest, s);
                    }
                }
            }
            
        cout << largest << '\n';
    }

	return 0;
}
