// Fun Coloring
// UVa ID: 12348
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m, Si[128], Ci[128], xi;
    string line;
    
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m;
        
        cin.ignore(256, '\n');

        for (int i = 0; i < m; i++)
        {
            getline(cin, line);
            Si[i] = Ci[i] = 0;
            istringstream iss(line);
            while (iss >> xi)
            {
                Si[i] |= (1 << (xi - 1));
                Ci[i]++;
            }
        }

        bool flag;
        for (int B = 0; B < (1 << n); B++)
        {
            flag = true;
            for (int j = 0; j < m; j++)
            {
                if (Ci[j] == 1) continue;
                int r = B & Si[j];
                if (!r || r == Si[j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag) break;
        }

        cout << (flag ? 'Y' : 'N');
    }
    
    return 0;
}
