// Magic Square Palindromes
// UVa ID: 11221
// Verdict: Accepted
// Submission Date: 2017-04-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    
    cin.ignore(1024, '\n');
    
    string line;
    char grid[110][110];
    
    for (int c = 1;  c <= cases; c++)
    {
        cout << "Case #" << c << ":\n";
        getline(cin, line);
        
        string letters;
        for (auto c : line)
            if (isalpha(c))
                letters.push_back(c);
        
        int root = sqrt((int)letters.size());
        int K = 0;
        bool isSquare = false;
        
        for (int i = root - 1; i <= root + 1; i++)
            if (i * i == letters.size())
            {
                isSquare = true;
                K = i;
                break;
            }
            
        if (!isSquare)
        {
            cout << "No magic :(\n";
            continue;
        }
        
        memset(grid, 0, sizeof(grid));
        
        for (int i = 0; i < K; i++)
            for (int j = 0; j < K; j++)
                grid[i][j] = letters[i * K + j];
                
        string reading;
        for (int i = 0; i < K; i++)
            for (int j = 0; j < K; j++)
                reading += grid[j][i];
                
        if (reading != letters)
        {
            cout << "No magic :(\n";
            continue;
        }
        
        reading.clear();
        for (int i = K - 1; i >= 0; i--)
            for (int j = K - 1; j >= 0; j--)
                reading += grid[i][j];
                
        if (reading != letters)
        {
            cout << "No magic :(\n";
            continue;
        }
        
        reading.clear();
        for (int i = K - 1; i >= 0; i--)
            for (int j = K - 1; j >= 0; j--)
                reading += grid[j][i];
                
        if (reading != letters)
        {
            cout << "No magic :(\n";
            continue;
        }
        
        cout << K << '\n';
    }
    
    return 0;
}
