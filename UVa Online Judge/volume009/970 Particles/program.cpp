// Particles
// UVa ID: 970
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string sequences;
char result[110][110];

char getResult(char a, char b)
{
    if (a == 'X' && b == 'X') return 'Y';
    if (a == 'Y' && b == 'Y') return 'X';
    if (a == 'Z' && b == 'Z') return 'X';
    if ((a == 'X' && b == 'Y') || (a == 'Y' && b == 'X')) return 'X';
    if ((a == 'X' && b == 'Z') || (a == 'Z' && b == 'X')) return 'Z';
    if ((a == 'Y' && b == 'Z') || (a == 'Z' && b == 'Y')) return 'Y';
}

char merge(int i, int j)
{
    if (i + 1 == j)
    {
        if (!result[i][j])
            result[i][j] = getResult(sequences[i], sequences[j])
        return getResult(sequences[i], sequences[j]);
    }
    
    if (result[i][j]) return result[i][j];
    
    char value = 'X';
    for (int k = i + 1; k < j; k++)
    {
        char current = getResult(merge(i, k), merge(k + 1, j));
    }
    
    return value;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> sequences;
        memset(result, 0, sizeof(result));
        cout << dfs(0, sequences.length() - 1) << '\n';
    }
    
    return 0;
}
