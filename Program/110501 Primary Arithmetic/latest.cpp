// Primary Arithmetic （小学生算术）
// PC/UVa IDs: 110501/10035, Popularity: A, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2016-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    string first, second;

    while (cin >> first >> second, first != "0" || second != "0")
    {
        int carry = 0, counter = 0;
        for (int i = first.length() - 1, j = second.length() - 1;
                i >= 0 || j >= 0; i--, j--)
        {
            int sum =
                carry + (i >= 0 ? (first[i] - '0') : 0) + (j >=
                        0 ? (second[j] - '0') : 0);
            carry = sum >= 10 ? 1 : 0;
            counter += carry;
        }

        if (counter > 1)
            cout << counter << " carry operations.\n";
        else if (counter == 1)
            cout << "1 carry operation.\n";
        else
            cout << "No carry operation.\n";
    }

    return 0;
}
