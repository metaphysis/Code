// Reverse and Add （反转相加）
// PC/UVa IDs: 110502/10018, Popularity: A, Success rate: low Level: 1
// Verdict: Accepted
// Submission Date: 2016-03-04
// UVa Run Time: 0.028s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>

using namespace std;

bool isPalindrome(string& number)
{
    for (int i = 0, j = number.length() - 1; i < j; i++, j--)
        if (number[i] != number[j])
            return false;

    return true;
}

void reverseAdd(string number)
{
    int step = 0;
    do
    {
        step++;
        string newNumber;
        int carry = 0;
        for (int i = 0, j = number.length() - 1; i < number.length(); i++, j--)
        {
            int sum = (number[i] - '0') + (number[j] - '0') + carry;
            carry = sum >= 10 ? 1 : 0;
            newNumber.push_back((char)('0' + sum % 10));
        }

        if(carry)
            newNumber.push_back((char)('0' + carry));

        number.assign(newNumber);
    } while (!isPalindrome(number));

    cout << step << " " << number << "\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int cases;
    cin >> cases;
    while (cases--)
    {
        string number;
        cin >> number;
        reverseAdd(number);
    }

    return 0;
}
