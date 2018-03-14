// Shippint Routes
// UVa ID: 383
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_LEGS = 100000;

int main(int argc, char *argv[])
{
    int datasets = 0, cases = 0;
    cin >> datasets;
    
    cout << "SHIPPING ROUTES OUTPUT" << endl << endl;
    
    while (datasets--)
    {
        int M, N, P;
        cin >> M >> N >> P;
        
        map<string, int> warehouses;
        for (int i = 1; i <= M; i++)
        {
            string codes;
            cin >> codes;
            warehouses[codes] = i;
        }
        
        int legs[M + 1][M + 1];
        for (int i = 1; i <= M; i++)
        {
            for (int j = 1; j <= M; j++)
                legs[i][j] = MAX_LEGS;
            legs[i][i] = 0;
        }
                
        for (int i = 1; i <= N; i++)
        {
            string start, next;
            cin >> start >> next;
            legs[warehouses[start]][warehouses[next]] = 1;
            legs[warehouses[next]][warehouses[start]] = 1;
        }
        
        // floyd-warshall
        for (int k = 1; k <= M; k++)
            for (int i = 1; i <= M; i++)
                for (int j = 1; j <= M; j++)
                    if (legs[i][k] + legs[k][j] < legs[i][j])
                        legs[i][j] = legs[i][k] + legs[k][j];
        
        cout << "DATA SET  " << ++cases << endl << endl;
                        
        for (int i = 1; i <= P; i++)
        {
            int size;
            string start, next;
            cin >> size >> start >> next;
            
            if (legs[warehouses[start]][warehouses[next]] >= MAX_LEGS)
            {
                cout << "NO SHIPMENT POSSIBLE" << endl;
                continue;
            }
            
            cout << "$" << size * legs[warehouses[start]][warehouses[next]] * 100 << endl;
        }
        
        cout << endl;
    }
    
    cout << "END OF OUTPUT" << endl;
    
	return 0;
}
