// Population Explosion
// UVa ID: 447
// Verdict: Accepted
// Submission Date: 2016-07-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    getline(cin, line);
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << '\n';
        
        getline(cin, line);
        int years = stoi(line);

        int population[20][20], next[20][20], x, y;
        
        memset(population, 0, sizeof(population));
        while (getline(cin, line), line.length() > 0)
        {
            istringstream iss(line);
            iss >> x >> y;
            population[x - 1][y - 1] = 1;
        }
        
        for (int j = 1; j <= years; j++)
        {
            cout << "********************\n";
            for (int r = 0; r < 20; r++)
            {
                for (int c = 0; c < 20; c++)
                    if (population[r][c])
                        cout << 'O';
                    else
                        cout << ' ';
                cout << '\n';
            }
            
            memset(next, 0, sizeof(next));            
            for (int r = 0; r < 20; r++)
                for (int c = 0; c < 20; c++)
                {
                    int living = 0;
                    for (int offsetx = -1; offsetx <= 1; offsetx++)
                        for (int offsety = -1; offsety <= 1; offsety++)
                        {
                            if (offsetx == 0 && offsety == 0)
                                continue;
                                
                            int nextr= r + offsetx, nextc = c + offsety;
                            if (nextr >= 0 && nextr < 20 && nextc >= 0 && nextc < 20 && population[nextr][nextc])
                                living++;
                        }
                    
                    if (population[r][c])
                    {
                        if (living >= 4 || living <= 1)
                            next[r][c] = 0;
                        else
                            next[r][c] = 1;
                    }
                    else
                    {
                        if (living == 3)
                            next[r][c] = 1;
                    }
                }
                
            memcpy(population, next, sizeof(next));
        }
        cout << "********************\n";
    }
    
	return 0;
}
