// Let Me Count The Ways
// UVa ID: 357
// Verdict: Accepted
// Submission Date: 2016-06-25
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> cents = {1, 5, 10, 25, 50};
    
    long long int ways[6][30010] = { 0 };
    ways[0][0] = 1;
        
    for (int i = 1; i <= 5; i++)
        for (int j = 0; j <= 30000; j++)
        {
            ways[i][j] = ways[i - 1][j];
            if (j - cents[i - 1] >= 0)
                ways[i][j] += ways[i][j - cents[i - 1]];
        }
    
    int n;                    
    while (cin >> n)
    {    
        if (ways[5][n] == 1)
            cout << "There is only 1 way to produce " << n << " cents change." << endl;
        else
            cout << "There are " << ways[5][n] << " ways to produce " << n << " cents change." << endl;
    }
    
	return 0;
}
