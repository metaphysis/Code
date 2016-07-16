// Double Trouble
// UVa ID: 268
// Verdict: Accepted
// Submission Date: 2016-05-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    // p, the base of number
    int p;
    while (cin >> p)
    {
        // find the number of digits and last digit
        int d = 2, n, pow = p * p;
        
        while (true)
        {
            bool found = false;
            for (n = 1; n <= (p - 1); n++)
            {
                int m = n * (pow - 1) % (2 * p - 1);
                if (m == 0)
                {
                    found = true;
                    break;
                }
            }
            
            if (found)
                break;
                
            pow = (pow * p) % (2 * p - 1);
            d++;
        }
        
        // calculate other digits
        vector < int > digits(d);
        int carry = 0;
        for (int i = 0; i < digits.size(); i++)
        {
            int temp = (p - 1) * n + carry;
            digits[i] = temp % p;
            carry = temp / p;
        }
        if (carry)
            digits.push_back(carry);
        
        int borrow = 0;
        for (int i = digits.size() - 1; i >= 0; i--)
        {
            int temp = borrow * p + digits[i];
            digits[i] = temp / (2 * p - 1);
            borrow = temp % (2 * p - 1);
        }
        
        while (digits.size() > d)
            digits.erase(digits.end() - 1);
            
        cout << "For base " << p << " the double-trouble number is" << endl;
        for (int i = digits.size() - 1; i >= 0; i--)
            cout << digits[i] << " ";
        cout << endl;
    }
    
	return 0;
}
