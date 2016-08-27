// How Many Knights
// UVa ID: 696
// Verdict: Accepted
// Submission Date: 2016-08-25
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int m, n;
    while (cin >> m >> n)
    {
        if (m == 0 && n == 0)
            break;
        
        int maxCounter = 0;
        
        if (m == 0 || n == 0)
            maxCounter = 0;
        else if (m == 1 || n == 1)
            maxCounter = max(m, n);
        else if (m == 2 || n == 2)
        {
            int next_m = max(m, n);
            maxCounter = next_m / 4 * 4;
            next_m = next_m % 4;
            if (next_m > 2)
                next_m = 2;
            maxCounter += next_m * 2;
        }
        else if (m == 3 || n == 3)
        {
            int next_m = max(m, n);
            maxCounter = next_m / 2 * 3;
            if (next_m % 2 == 1)
                maxCounter += 2;
        }
        else
        {
            int row_counter = 0, column_counter = 0;
            if (m % 2 == 1)
            {
                row_counter = n / 2 * m;
                if (n % 2 == 1)
                    row_counter += (m + 1) / 2;
            }
            else
                row_counter = n * ((m + 1) / 2);

            if (n % 2 == 1)
            {
                column_counter = m / 2 * n;
                if (m % 2 == 1)
                    column_counter += (n + 1) / 2;
            }
            else
                column_counter = m * ((n + 1) / 2);

            maxCounter = max(row_counter, column_counter);
        }
        
        cout << maxCounter << " knights may be placed on a " << m << " row " << n << " column board.\n";
    }
    
	return 0;
}
