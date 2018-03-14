// Blowing Fuses
// UVa ID: 661
// Verdict: Accepted
// Submission Date: 2016-08-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, used[25], devices[25], n, m, c;
    
    while (cin >> n >> m >> c)
    {
        if (n == 0 && m == 0 && c == 0)
            break;
            
        for (int i = 1; i <= n; i++)
            cin >> devices[i];
           
        bool blown = false;
        int amperes = 0, max_amperes = 0;
        memset(used, 0, sizeof(used));
        
        int number;
        for (int i = 1; i <= m; i++)
        {
            cin >> number;
            used[number] = !used[number];

            if (used[number])
                amperes += devices[number];
            else
                amperes -= devices[number];
            
            if (amperes > c)
                blown = true;
            
            max_amperes = max(max_amperes, amperes);
        }
        
        cout << "Sequence " << ++cases << '\n';
        if (blown)
            cout << "Fuse was blown.\n";
        else
        {
            cout << "Fuse was not blown.\n";
            cout << "Maximal power consumption was " << max_amperes << " amperes.\n";
        }
        
        cout << '\n';
    }
    
	return 0;
}
