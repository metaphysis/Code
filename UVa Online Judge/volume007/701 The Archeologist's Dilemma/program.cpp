// The Archeologist's Dilemma （考古学家的烦恼）
// PC/UVa IDs: 110503/701, Popularity: A, Success rate: low Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-29
// UVa Run Time: 0.212s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void find_smallest_exponent_by_brute_force(long number)
{
    long long unsigned exponent = 7;

    string first;
    while (number)
    {
        first.append(1, '0' + number % 10);
        number /= 10;
    }

    string result = "821";

    while (result.rfind(first) != (string::size_type)(result.length() - first.length())
            || result.length() < (2 * first.length() + 1))
    {
        int carry = 0;
        for (int i = 0; i < result.length(); i++)
        {
            carry = 2 * (result[i] - '0') + carry;
            result[i] = '0' + carry % 10;
            carry = carry / 10;
        }

        if (carry)
            result.append(1, '1');
        exponent++;
    }

    cout << exponent << endl;
}

void find_smallest_exponent_by_log(long number)
{
    int digits = 0;
    long original = number;
    while (original)
    {
        digits++;
        original /= 10;
    }

    for (int k = (digits + 1); ; k++)
    {
        long long down = floor((log10(number) + k) / log10(2));
        long long up = floor((log10(number + 1) + k) / log10(2));

        if (up > down)
        {
            cout << up << endl;
            return;
        }
    }
}

int main(int ac, char *av[])
{
    long number;

    while (cin >> number)
        find_smallest_exponent_by_log(number);

    return 0;
}
