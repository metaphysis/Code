// Arbitrage (II)
// UVa ID: 436
// Verdict: Accepted
// Submission Date: 2016-07-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    double matrix[40][40];
    
    int n, m, cases = 0;
    while (cin >> n, n)
    {
        for (int i = 0; i < 40; i++)
            for (int j = 0; j < 40; j++)
                matrix[i][j] = -1.0;

        map<string, int> currency;
        
        string currency_name;
        for (int i = 1; i <= n; i++)
        {
            cin >> currency_name;
            currency[currency_name] = i;
        }
        
        cin >> m;
        string start_currency, end_currency;
        double rate;
        for (int i = 1; i <= m; i++)
        {
            cin >> start_currency >> rate >> end_currency;
            matrix[currency[start_currency]][currency[end_currency]] = rate;
        }
        
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                {
                    if (matrix[i][k] > 0.0 && matrix[k][j] > 0.0)
                    {
                        if (matrix[i][k] * matrix[k][j] > matrix[i][j] + EPSILON)
                            matrix[i][j] = matrix[i][k] * matrix[k][j];
                    }
                }
        
        bool arbitrage = false;  
        for (int i = 1; i <= n; i++)
            if (matrix[i][i] > 1.0 + EPSILON)
            {
                arbitrage = true;
                goto skip;
            }
        
        skip:    
        cout << "Case " << ++cases << ": " << (arbitrage ? "Yes" : "No") << '\n';
    }
    
	return 0;
}
