// Hexagon
// UVa ID: 317
// Verdict: Accepted
// Submission Date: 2016-11-23
// UVa Run Time: 0.010s
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

    int pieces[2][3] = {{5, 6, 8}, {5, 7, 7}};
    int number[3][3], cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Test #" << c << '\n';
        
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                cin >> number[i][j];
            sort(number[i], number[i] + 3);
        }

        // 找最优解的结构可以得到下述快速的解决方法。
        int max_scores = 0;
        for (int k = 0; k < 3; k++)
        {
            int scores = 0;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    scores += number[i][j] * pieces[(i == k ? 0 : 1)][j];
            max_scores = max(max_scores, scores);
        }
        
        cout << max_scores << "\n\n";
    }
    
	return 0;
}
