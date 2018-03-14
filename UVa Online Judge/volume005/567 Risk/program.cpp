// Risk
// UVa ID: 567
// Verdict: Accepted
// Submission Date: 2016-08-10
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    while (true)
    {
        int country[21][21] = { 0 };
        int borders, edge, start, end;

        for (int i = 1; i <= 20; i++)
            for (int j = 1; j <= 20; j++)
                country[i][j] = 100000;
        
        bool readed = true;
        for (int i = 1; i <= 19; i++)
        {
            if (cin >> borders)
            {
                for (int j = 1; j <= borders; j++)
                {
                    cin >> edge;
                    country[i][edge] = 1;
                    country[edge][i] = 1;
                }
            }
            else
            {
                readed = false;
                break;
            }
            
            country[i][i] = 0;
        }

        if (readed == false)
            break;

        cout << "Test Set #" << ++cases << '\n';
        
        for (int k = 1; k <= 20; k++)
            for (int i = 1; i <= 20; i++)
                for (int j = 1; j <= 20; j++)
                    if (country[i][k] + country[k][j] < country[i][j])
                        country[i][j] = country[i][k] + country[k][j];
                        
        cin >> borders;
        for (int i = 1; i <= borders; i++)
        {
            cin >> start >> end;
            cout << setw(2) << start << " to " << setw(2) << end << ": " << country[start][end] << '\n';
        }
        cout << '\n';
    }
    
	return 0;
}
