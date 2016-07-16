// Chess
// UVa ID: 278
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

int getCount(char piece, int m, int n)
{
    // Rook
    if (piece == 'r')
        return min(m, n);
        
    // Knight
    if (piece == 'k')
    {
        int maxCounter = 0, counter = 0, countPerLine = (m + 1) / 2;
        if (m % 2 == 1)
        {
            for (int i = 1; i <= n; i++)
                counter += ((i % 2 == 1) ? countPerLine : (countPerLine - 1));
        }
        else
        {
            for (int i = 1; i <= n; i++)
                counter += countPerLine;
        }
        
        maxCounter = max(maxCounter, counter);
        
        counter = 0;
        countPerLine = (n + 1) / 2;
        if (n % 2 == 1)
        {
            for (int i = 1; i <= m; i++)
                counter += ((i % 2 == 1) ? countPerLine : (countPerLine - 1));
        }
        else
        {
            for (int i = 1; i <= m; i++)
                counter += countPerLine;
        }
        
        maxCounter = max(maxCounter, counter);
        
        return maxCounter;
    }
    
    // Queen    
    if (piece == 'Q')
        return min(m, n);
    
    // King    
    if (piece == 'K')
        return ((m + 1) / 2) * ((n + 1) / 2);
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int cases, m, n;
    char piece;
    
    cin >> cases;
    while (cases--)
    {
        cin >> piece >> m >> n;
        cout << getCount(piece, m, n) << endl;
    }
    
	return 0;
}
