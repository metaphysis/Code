// ASCII Mandelbrot
// UVa ID: 918
// Verdict: Accepted
// Submission Date: 2017-03-13
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

    int cases;
    string chars;
    double mini, maxi, preci, minr, maxr, precr, epsilon = 1e-7;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        cin >> chars >> mini >> maxi >> preci >> minr >> maxr >> precr;
        
        for (double i = mini; i <= maxi + epsilon; i += preci)
        {
            for (double j = minr; j <= maxr + epsilon; j += precr)
            {
                double real = 0.0, imag = 0.0;
                bool plotted = false;
                
                for (int k = 1; k <= 12; k++)
                {
                    double next_real = real * real - imag * imag;
                    double next_imag = 2.0 * real * imag;
                    
                    real = next_real, imag = next_imag;
                    real += j, imag += i;
                    
                    if (sqrt(real * real + imag * imag) > 2 + epsilon)
                    {
                        plotted = true;
                        cout << chars[k];
                        break;
                    }
                }
                
                if (!plotted) cout << ' ';
            }
            
            cout << '\n';
        }
    }
    
    return 0;
}
