// Double Trouble
// UVa ID: 268
// Verdict: Accepted
// Submission Date: 2016-05-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{         
    int base;
    while (cin >> base)
    {
        int n = 2, x, pow = base * base;

        while (true)
        {
            bool found = false;
            for (x = 1; x <= (base - 1); x++)
            {
                int r = x * (pow - 1) % (2 * base - 1);
                if (r == 0)
                {
                    found = true;
                    break;
                }
            }

            if (found)
                break;

            pow = (pow * base) % (2 * base - 1);
            n++;
        }

        vector<int> digits(n);
        int carry = 0;
        for (int i = 0; i < digits.size(); i++)
        {
            int temp = (base - 1) * x + carry;
            digits[i] = temp % base;
            carry = temp / base;
        }
        if (carry)
            digits.push_back(carry);

        int borrow = 0;
        for (int i = digits.size() - 1; i >= 0; i--)
        {
            int temp = borrow * base + digits[i];
            digits[i] = temp / (2 * base - 1);
            borrow = temp % (2 * base - 1);
        }

        while (digits.size() > n)
            digits.erase(digits.end() - 1);

        cout << "For base " << base << " the double-trouble number is" << endl;
        for (int i = digits.size() - 1; i >= 0; i--)
            cout << digits[i] << " ";
        cout << endl;
    }

	return 0;
}
