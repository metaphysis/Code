// Count on Cantor
// UVa ID: 264
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

int numerator[10001628], denominator[10001628];

void initialize()
{
    bool fromLeftToRight = true;
    
    int left = 1, right = 1, index = 0;
    while (index < 10001628)
    {
        if (fromLeftToRight)
        {
            for (int i = left, j = 1; i >= 1; i--, j++)
            {
                numerator[index] = i;
                denominator[index] = j;
                index++;
            }
        }
        else
        {
            for (int i = 1, j = right; i <= left; i++, j--)
            {
                numerator[index] = i;
                denominator[index] = j;
                index++;
            }
        }
        
        fromLeftToRight = !fromLeftToRight;
        left++;
        right++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    initialize();
    
    int number;
    while (cin >> number)
    {
        cout << "TERM " << number << " IS ";
        cout << numerator[number - 1] << "/" << denominator[number - 1] << "\n";
    }
             
	return 0;
}
