// Super Lucky Numbers
// UVa ID: 10722
// Verdict: Accepted
// Submission Date: 2018-10-14
// UVa Run Time: 0.210s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int BASE = 10000;

vector<int> add(vector<int> number1, vector<int> number2)
{  
    if (number1.size() < number2.size()) number1.swap(number2);
    int carry = 0;
    for (int i = 0; i < number1.size(); i++)
    {
        number1[i] += (i < number2.size() ? number2[i] : 0) + carry;
        carry = number1[i] / BASE;
        number1[i] %= BASE;
    }
    if (carry) number1.push_back(carry);
    return number1;
}

vector<int> multiply(vector<int> number1, int n)
{
    int carry = 0;
    for (int i = 0; i < number1.size(); i++)
    {
        number1[i] = number1[i] * n + carry;
        carry = number1[i] / BASE;
        number1[i] %= BASE;
    }
    if (carry) number1.push_back(carry);
    return number1;
}

void print(vector<int> number)
{
    cout << number[number.size() - 1];
    for (int i = (int)number.size() - 2; i >= 0; i--)
        cout << setw(4) << setfill('0') << right << number[i];
}

const int LAST_DIGIT_NOT_ONE = 0, LAST_DIGIT_IS_ONE = 1;
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int B, N;
    vector<int> dp[101][2];

    while (cin >> B >> N)
    {
        if (B == 0) break;
        for (int i = 0; i <= N; i++)
            for (int j = 0; j < 2; j++)
            {
                dp[i][j].clear();
                dp[i][j].push_back(0);
            }
        dp[1][LAST_DIGIT_NOT_ONE].front() = B - 2;
        dp[1][LAST_DIGIT_IS_ONE].front() = 1;
        for (int i = 2; i <= N; i++)
        {
            dp[i][LAST_DIGIT_NOT_ONE] = add(multiply(dp[i - 1][LAST_DIGIT_IS_ONE], B - 2), multiply(dp[i - 1][LAST_DIGIT_NOT_ONE], B - 1));
            dp[i][LAST_DIGIT_IS_ONE] = add(dp[i - 1][LAST_DIGIT_IS_ONE], dp[i - 1][LAST_DIGIT_NOT_ONE]);
        }
        print(add(dp[N][0], dp[N][1]));
        cout << '\n';
    }

    return 0;
}
