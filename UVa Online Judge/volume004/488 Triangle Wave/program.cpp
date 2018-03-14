// Triangle Wave
// UVa ID: 488
// Verdict: Accepted
// Submission Date: 2016-07-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int amplitude, frequency, cases;
    cin >> cases;
    for (int i = 1; i <= cases; i++)
    {
        cin >> amplitude >> frequency;
        
        // it is a trick.
        if (frequency == 0) continue;
        
        if (i > 1) cout << endl;
        for (int j = 1; j <= frequency; j++)
        {
            if (j > 1) cout << endl;

            for (int k = 1; k <= amplitude; k++)
                cout << string(k, '0' + k) << endl;
            
            for (int k = amplitude - 1; k >= 1; k--)
                cout << string(k, '0' + k) << endl;
        }
    }
    
	return 0;
}
