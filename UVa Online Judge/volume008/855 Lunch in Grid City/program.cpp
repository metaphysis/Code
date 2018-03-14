// Lunch in Grid City
// UVa ID: 855
// Verdict: Accepted
// Submission Date: 2016-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int T, S, A, F, x[50010], y[50010], bestS, bestA;
    
    cin >> T;
    for (int c = 1; c <= T; c++)
    {
        cin >> S >> A >> F;
        for (int i = 0; i < F; i++) cin >> x[i] >> y[i];
            
        sort(x, x + F); sort(y, y + F);
                
        if (F % 2 == 0)
            bestS = x[F / 2 - 1], bestA = y[F / 2 - 1];
        else
            bestS = x[F / 2], bestA = y[F / 2];
        
        cout << "(Street: " << bestS;
        cout << ", Avenue: " << bestA << ")\n";
    }
    
	return 0;
}
