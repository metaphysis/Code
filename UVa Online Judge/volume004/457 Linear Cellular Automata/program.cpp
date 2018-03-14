// Linear Cellular Automata
// UVa ID: 457
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    vector<int> dna(10);
    
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        
        for (int j = 0; j < 10; j++)
            cin >> dna[j];
        
        vector<int> culture(42, 0), next(42, 0);
        culture[20] = 1;
        
        bool use_orginal = true;
        for (int j = 1; j <= 50; j++)
        {
            for (int k = 1; k <= 40; k++)
            {
                if (culture[k] == 0) cout << ' ';
                else if (culture[k] == 1) cout << '.';
                else if (culture[k] == 2) cout << 'x';
                else cout << 'W';
                
                next[k] = dna[culture[k - 1] + culture[k] + culture[k + 1]];
            }
            cout << '\n';
            
            culture.assign(next.begin(), next.end());
            fill(next.begin(), next.end(), 0);
        }
    }
    
	return 0;
}
