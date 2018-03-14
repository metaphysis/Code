// Page Hopping
// UVa ID: 821
// Verdict: Accepted
// Submission Date: 2016-12-02
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, from, to;
    int clicks[110][110], number[110], n;
    
    while (cin >> from >> to, from > 0)
    {
        cout << "Case " << ++cases << ": average length between pages = ";

        for (int i = 1; i <= 100; i++)
            for (int j = 1; j <= 100; j++)
                clicks[i][j] = 100000;

        memset(number, 0, sizeof(number));
        n = 0;

        do
        {
            if (!number[from]) number[from] = ++n;
            if (!number[to]) number[to] = ++n;
            clicks[number[from]][number[to]] = 1;
        } while (cin >> from >> to, from > 0);
        
        for (int i = 1; i <= n; i++)
            clicks[i][i] = 0;

        // Floyd-Warshall
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (clicks[i][j] > clicks[i][k] + clicks[k][j])
                        clicks[i][j] = clicks[i][k] + clicks[k][j];
                
        int totalClicks = 0;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
            {
                totalClicks += clicks[i][j];
                totalClicks += clicks[j][i];
            }

        double averageClicks = (double)totalClicks / (double)(n * n - n);
        cout << fixed << setprecision(3) << averageClicks << " clicks\n";
    }
    
	return 0;
}
