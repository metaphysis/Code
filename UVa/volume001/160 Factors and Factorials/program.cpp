// Factors and Factorials
// UVa IDs: 160
// Verdict: Accepted
// Submission Date: 2016-02-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int primes[25] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
};

int main(int argc, char* argv[])
{
    int n;
    while (cin >> n, n)
    {
        cout << setw(3) << right << n;
        cout << "! =";
        int counter[26] = { 0 };
        for (int i = 2; i <= n; i++)
        {
            int m = i;
            while (m > 1)
            {
                for (int j = 0; j < 26; j++)
                {
                    if (m % primes[j] == 0)
                    {
                        counter[j]++;
                        m /= primes[j];
                        break;
                    }
                }
            }
        }
        
        int last;
        for (last = 25; last >= 0; last--)
            if (counter[last] > 0)
                break;
                
        int start = 0;
        while (start <= min(14, last))
            cout << setw(3) << right << counter[start++];
        if (start <= last)
            cout << endl << string(6, ' ');
        while (start <= last)
            cout << setw(3) << right << counter[start++];
        cout << endl;
    }
    
	return 0;
}
