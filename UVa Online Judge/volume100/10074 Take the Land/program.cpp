// Take the Land
// UVa ID: 10074
// Verdict: Accepted
// Submission Date: 2017-11-02
// UVa Run Time: 0.000s
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

struct rectangle { int height, left; };

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int m, n, matrix[110][110];
    while (cin >> m >> n, m > 0)
    {
        int area = 0;
        for (int i = 0; i < m; i++)
        {
            matrix[i][n] = 0;
            for (int j = 0; j < n; j++)
            {
                cin >> matrix[i][j];
                matrix[i][j] ^= 1;
                if (i && matrix[i][j]) matrix[i][j] += matrix[i - 1][j];
            }
            
            stack<rectangle> s;
            for (int j = 0; j <= n; j++)
            {
                rectangle rect = rectangle{matrix[i][j], j};
                if (s.empty() || s.top().height < rect.height) s.push(rect);
                else
                {
                    if (s.top().height > rect.height)
                    {
                        int last = j;
                        while (!s.empty() && s.top().height >= rect.height)
                        {
                            rectangle previous = s.top(); s.pop();
                            area = max(area, previous.height * (j - previous.left));
                            last = previous.left;
                        }
                        rect.left = last;
                        s.push(rect);
                    }
                }
            }
        }
        
        cout << area << '\n';
    }
    
    return 0;
}
