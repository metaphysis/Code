// Spiral of Numbers
// UVa ID: 903
// Verdict: Accepted
// Submission Date: 2017-03-10
// UVa Run Time: 0.020s
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
    
    int center, g[3][3];
    while (cin >> center)
    {
        if (center <= 9)
        {
            switch (center)
            {
                case 1: cout << "7;8;9;\n6;1;2;\n5;4;3;\n"; break;
                case 2: cout << "8;9;10;\n1;2;11;\n4;3;12;\n"; break;
                case 3: cout << "1;2;11;\n4;3;12;\n15;14;13;\n"; break;
                case 4: cout << "6;1;2;\n5;4;3;\n16;15;14;\n"; break;
                case 5: cout << "19;6;1;\n18;5;4;\n17;16;15;\n"; break;
                case 6: cout << "20;7;8;\n19;6;1;\n18;5;4;\n"; break;
                case 7: cout << "21;22;23;\n20;7;8;\n19;6;1;\n"; break;
                case 8: cout << "22;23;24;\n7;8;9;\n6;1;2;\n"; break;
                case 9: cout << "23;24;25;\n8;9;10;\n1;2;11;\n"; break;
                default: break;
            }

            continue;
        }
        
        int n = (int)sqrt(center);
        if (center > (n * n))
        {
            if (n % 2 == 1) n += 2;
            else n += 1;
        }
        else
        {
            if (n % 2 == 0) n += 1;
        }

        if (center > (n * n - (n - 1)))
        {
            int topRight = n * n;

            if (center == topRight)
            {
                g[0][1] = topRight + 4 * n + 3, g[0][0] = g[0][1] - 1, g[0][2] = g[0][1] + 1;
                g[1][1] = topRight, g[1][0] = topRight - 1, g[1][2] = topRight + 1;
                g[2][1] = topRight - (4 * n - 5), g[2][0] = g[2][1] - 1, g[2][2] = g[1][2] + 1;
            }
            else if (center > (topRight - (n - 1) + 1))
            {
                g[0][1] = center + 4 * n + 3, g[0][0] = g[0][1] - 1, g[0][2] = g[0][1] + 1;
                g[1][1] = center, g[1][0] = center - 1, g[1][2] = center + 1;
                g[2][1] = center - (4 * n - 5), g[2][0] = g[2][1] - 1, g[2][2] = g[2][1] + 1;
            }
            else
            {
                g[0][1] = center + 4 * n + 3, g[0][0] = g[0][1] - 1, g[0][2] = g[0][1] + 1;
                g[1][1] = center, g[1][0] = center - 1, g[1][2] = center + 1;
                g[2][1] = center - (4 * n - 5), g[2][0] = g[1][0] - 1, g[2][2] = g[2][1] + 1;
            }
        }
        else if (center > (n * n - 2 * (n - 1)))
        {
            int topLeft = n * n - (n - 1);
            int bottomLeft = n * n - 2 * (n - 1);
            
            if (center == topLeft)
            {
                g[0][1] = topLeft + 4 * n + 3, g[0][0] = g[0][1] - 1, g[0][2] = g[0][1] + 1;
                g[1][1] = center, g[1][0] = g[0][0] - 1, g[1][2] = center + 1;
                g[2][1] = g[1][1] - 1, g[2][0] = g[1][0] - 1, g[2][2] = g[1][2] - (4 * n - 5);
            }
            else if (center == topLeft - 1)
            {
                g[0][0] = topLeft + 4 * n + 1, g[0][1] = center + 1, g[0][2] = center + 2;
                g[1][0] = g[0][0] - 1, g[1][1] = center, g[1][2] = center - (4 * n - 7);
                g[2][0] = g[1][0] - 1, g[2][1] = g[1][1] - 1, g[2][2] = g[1][2] - 1;
            }
            else if (center == bottomLeft + 1)
            {
                g[0][1] = center + 1, g[0][0] = g[0][1] + 4 * n + 1, g[0][2] = g[0][1] - (4 * n - 7);
                g[1][1] = center, g[1][0] = g[0][0] - 1, g[1][2] = g[0][2] - 1;
                g[2][1] = center - 1, g[2][0] = g[1][0] - 1, g[2][2] = g[2][1] - 1;
            }
            else
            {
                g[0][1] = center + 1, g[0][0] = g[0][1] + 4 * n + 1, g[0][2] = g[0][1] - (4 * n - 7);
                g[1][1] = center, g[1][0] = g[0][0] - 1, g[1][2] = g[0][2] - 1;
                g[2][1] = center - 1, g[2][0] = g[1][0] - 1, g[2][2] = g[1][2] - 1;
            }
        }
        else if (center > (n * n - 3 * (n - 1)))
        {
            int bottomLeft = n * n - 2 * (n - 1);
            int bottomRight = n * n - 3 * (n - 1);
            
            if (center == bottomLeft)
            {
                g[0][1] = center + 1, g[0][0] = g[0][1] + 4 * n + 1, g[0][2] = (n - 3) * (n - 3) + 1;
                g[1][1] = center, g[1][0] = g[0][0] - 1, g[1][2] = center - 1;
                g[2][1] = g[1][0] - 2, g[2][0] = g[1][0] - 1, g[2][2] = g[1][0] - 3;
            }
            else if (center == (bottomLeft - 1))
            {
                g[0][0] = center + 2, g[0][1] = (n - 3) * (n - 3) + 1, g[0][2] = g[0][1] - 1;
                g[1][0] = center + 1, g[1][1] = center, g[1][2] = center - 1;
                g[2][0] = (n + 1) * (n + 1), g[2][1] = g[2][0] - 1, g[2][2] = g[2][0] - 2;
            }
            else if (center == bottomRight + 1)
            {
                g[0][1] = center - (4 * n - 9), g[0][0] = g[0][1] + 1, g[0][2] = center - 2;
                g[1][1] = center, g[1][0] = g[1][1] + 1, g[1][2] = g[1][1] - 1;
                g[2][1] = g[1][1] + (4 * (n + 2) - 9), g[2][0] = g[2][1] + 1 , g[2][2] = g[2][1] - 1;
            }
            else
            {
                g[0][1] = center - (4 * n - 9), g[0][0] = g[0][1] + 1, g[0][2] = g[0][1] - 1;
                g[1][1] = center, g[1][0] = g[1][1] + 1, g[1][2] = g[1][1] - 1;
                g[2][1] = g[1][1] + (4 * (n + 2) - 9), g[2][0] = g[2][1] + 1, g[2][2] = g[2][1] - 1;
            }
        }
        else
        {
            int bottomRight = n * n - 3 * (n - 1);
            int square = (n - 2) * (n - 2);
            
            if (center == bottomRight)
            {
                g[0][1] = center - 1, g[0][0] = g[0][1] - (4 * (n - 2) - 3), g[0][2] = center + (4 * (n + 2) - 9) - 3;
                g[1][1] = center, g[1][0] = g[1][1] + 1, g[1][2] = center + (4 * (n + 2) - 9) - 2;
                g[2][1] = g[1][1] + (4 * (n + 2) - 9), g[2][0] = g[2][1] + 1, g[2][2] = g[2][1] - 1;
            }
            else if (center == square + 1)
            {
                g[0][1] = n * n, g[0][0] = g[0][1] - 1, g[0][2] = g[0][1] + 1;
                g[1][1] = center, g[1][0] = g[1][1] - 1, g[1][2] = g[1][1] + (4 * n - 3);
                g[2][1] = center + 1, g[2][0] = g[2][1] - (4 * (n - 2) - 3), g[2][2] = g[1][2] + 1;
            }
            else if (center == bottomRight - 1)
            {
                g[0][1] = center - 1, g[0][0] = g[0][1] - (4 * (n - 2) - 3), g[0][2] = g[0][1] + (4 * n - 3);
                g[1][1] = center, g[1][0] = g[1][1] - (4 * (n - 2) - 3), g[1][2] = g[1][1] + (4 * n - 3);
                g[2][1] = center + 1, g[2][0] = g[2][1] + 1, g[2][2] = g[2][1] + (4 * n - 3);
            }
            else if (center == square + 2)
            {
                g[0][1] = center - 1, g[0][0] = g[0][1] - 1, g[0][2] = g[0][1] + (4 * n - 3);
                g[1][1] = center, g[1][0] = g[1][1] - (4 * (n - 2) - 3), g[1][2] = g[0][2] + 1;
                g[2][1] = center + 1, g[2][0] = g[2][1] - (4 * (n - 2) - 3), g[2][2] = g[1][2] + 1;
            }
            else
            {
                g[0][1] = center - 1, g[0][0] = g[0][1] - (4 * (n - 2) - 3), g[0][2] = g[0][1] + (4 * n - 3);
                g[1][1] = center, g[1][0] = g[0][0] + 1, g[1][2] = g[0][2] + 1;
                g[2][1] = center + 1, g[2][0] = g[1][0] + 1, g[2][2] = g[1][2] + 1;
            }
        }
        
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
                cout << g[i][j] << ';';
            cout << '\n';
        }
    }
    
    return 0;
}
