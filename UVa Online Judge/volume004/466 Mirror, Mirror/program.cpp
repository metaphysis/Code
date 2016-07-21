// Mirror, Mirror
// UVa ID: 466
// Verdict: Accepted
// Submission Date: 2016-07-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

string rotateCW90(string matrix, int n)
{
    string newMatrix;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            newMatrix += matrix[(n - 1) * n + (i - 1) - (j - 1) * n];
    return newMatrix;
}

string rotateCCW90(string matrix, int n)
{
    string newMatrix;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            newMatrix += matrix[(n - 1) - (i - 1) + (j - 1) * n];
    return newMatrix;
}

string rotate180(string matrix)
{
    reverse(matrix.begin(), matrix.end());
    return matrix;
}

string reflect(string matrix, int n)
{
    string newMatrix;
    for (int i = 1; i <= n; i++)
        for (int j = 1;j <= n; j++)
            newMatrix += matrix[(n - i) * n + (j - 1)];
    return newMatrix;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n)
    {
        cout << "Pattern " << ++cases << " was ";

        string original, transformed;
        char letter;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> letter;
                original.push_back(letter);
            }

            for (int j = 1; j <= n; j++)
            {
                cin >> letter;
                transformed.push_back(letter);
            }
        }
        
        if (original == transformed)
        {
            cout << "preserved.\n";
            continue;
        }
        
        if (rotateCW90(original, n) == transformed)
        {
            cout << "rotated 90 degrees.\n";
            continue;
        }
        
        if (rotate180(original) == transformed)
        {
            cout << "rotated 180 degrees.\n";
            continue;
        }
        
        if (rotateCCW90(original, n) == transformed)
        {
            cout << "rotated 270 degrees.\n";
            continue;
        }
        
        original = reflect(original, n);
        if (original == transformed)
        {
            cout << "reflected vertically.\n";
            continue;
        }
        
        if (rotateCW90(original, n) == transformed)
        {
            cout << "reflected vertically and rotated 90 degrees.\n";
            continue;
        }
        
        if (rotate180(original) == transformed)
        {
            cout << "reflected vertically and rotated 180 degrees.\n";
            continue;
        }
        
        if (rotateCCW90(original, n) == transformed)
        {
            cout << "reflected vertically and rotated 270 degrees.\n";
            continue;
        }
        
        cout << "improperly transformed.\n";
    }
    
	return 0;
}
