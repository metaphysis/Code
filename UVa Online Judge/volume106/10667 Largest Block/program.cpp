// Largest Block
// UVa ID: 10667
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

const int MAXV = 110;

struct rectangle { int height, left; };

int m, n, matrix[MAXV][MAXV];
    
int getMaxArea()
{
    int area = 0;
    stack<rectangle> s;

    for (int i = 0; i < m; i++)
    {
        matrix[i][n] = 0;
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

    return area;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int p, s, b;

    cin >> p;
    for (int c = 1; c <= p; c++)
    {
        cin >> s;
        m = n = s;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                matrix[i][j] = 1;
                
        cin >> b;
        int r1, c1, r2, c2;
        for (int d = 1; d <= b; d++)
        {
            cin >> r1 >> c1 >> r2 >> c2;
            r1--, c1--, r2--, c2--;
            for (int i = r1; i <= r2; i++)
                for (int j = c1; j <= c2; j++)
                    matrix[i][j] = 0;
        }
        
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (i && matrix[i][j])
                    matrix[i][j] += matrix[i - 1][j];
                    
        cout << getMaxArea() << '\n';
    }

    return 0;
}
