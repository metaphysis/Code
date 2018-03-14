// Word-Search Wonder
// UVa ID: 422
// Verdict: Accepted
// Submission Date: 2016-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        char matrix[110][110];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> matrix[i][j];
                
        string word;
        while (cin >> word, word != "0")
        {
            bool found = false;
            int startx, starty, endx, endy;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (matrix[i][j] == word.front())
                    {
                        startx = i, starty = j;
                        for (int x = -1; x <= 1; x++)
                            for (int y = -1; y <= 1; y++)
                            {
                                if (x == 0 && y == 0) continue;
                                if (x == -1 && y == 0) continue;
                                
                                int nexti = i, nextj = j;
                                
                                bool same = true;
                                for (int k = 0; k < word.length(); k++)
                                {
                                    if (nexti < 1 || nexti > n || nextj < 1 || nextj > n || word[k] != matrix[nexti][nextj])
                                    {
                                        same = false;
                                        break;
                                    }
                                    nexti += x, nextj += y;
                                }

                                if (same)
                                {
                                    endx = i + (word.length() - 1) * x, endy = j + (word.length() - 1) * y;
                                    found = true;
                                    goto skip;
                                }
                            }
                    }
                    
            skip:
            if (found) cout << startx << ',' << starty << ' ' << endx << ',' << endy << '\n';
            else cout << "Not found\n";
        }
    }
    
	return 0;
}
