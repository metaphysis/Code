// City Game
// UVa ID: 1330
// Verdict: Accepted
// Submission Date: 2017-12-02
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct rectangle { int height, left; };

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char symbol;
    int k, m, n, matrix[1010][1010];
    
    cin >> k;
    for (int z = 1; z <= k; z++)
    {
        cin >> m >> n;
    
        int area = 0;
        for (int i = 0; i < m; i++)
        {
            matrix[i][n] = 0;
            for (int j = 0; j < n; j++)
            {
                cin >> symbol;

                if (symbol == 'R') matrix[i][j] = 0;
                else matrix[i][j] = 1;

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
        
        cout << 3 * area << '\n';
    }
    
    return 0;
}
