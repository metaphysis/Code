// Count on Cantor
// UVa ID: 264
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int number, n, distance, numerator, denominator;
    while (cin >> number)
    {
        n = (int)sqrt(2 * number) - 1;
        
        while (number > n * (n + 1) / 2)
            n++;
           
        distance = n * (n + 1) / 2 - number;
        
        cout << "TERM " << number << " IS ";
        
        if ((n & 1) == 0)
        {
            numerator = n - distance;
            denominator = 1 + distance;
        }
        else
        {
            numerator = 1 + distance;
            denominator = n - distance;
        }
        
        cout << numerator << "/" << denominator << "\n";
    }
             
	return 0;
}
