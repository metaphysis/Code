// 
// UVa ID: 
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string add(string, string);

// 十进制下的四则运算。
const int BASE = 10;

// 移除计算结果的前导0。
void zeroJustify(string &number)
{
    while (number.front() == '0' && number.length() > 1)
        number.erase(number.begin());
}

// 将两个字符串形式表示的非负整数进行相加操作，返回字符串表示的结果。
string add(string number1, string number2)
{  
    // 将结果保存在字符串number1中，为了相加方便，调整加数，使得第一个加数的数位
    // 总是大于第二个加数的数位。由于两个正数相加，和的数位最多为两个加数数位较大值
    // 加一，可以预先分配存储空间以方便计算。
    if (number1.length() < number2.length())
        number1.swap(number2);
    number1.insert(number1.begin(), '0');

    // 相加时从低位开始加。初始时进位为0。由于字符串中保存的是数位的ASCII码字符，
    // 需要做相应的转换，使之成为对应的数字值。当前的数位为模基数的值，进位则为除
    // 基数的值。
    int carry = 0, i = number1.length() - 1, j = number2.length() - 1;
    for (; i >= 0; i--, j--)
    {
        int sum = number1[i] - '0' + (j >= 0 ? (number2[j] - '0') : 0) + carry;
        number1[i] = sum % BASE + '0';
        carry = sum / BASE;
    }

    // 移除前导0。
    zeroJustify(number1);

    return number1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string dp[101][130];
    int B, N;

    while (cin >> B >> N)
    {
        if (B == 0) break;
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= B; j++)
                dp[i][j] = "0";
        for (int i = 0; i < B; i++)
        {
            if (i == 0 || (i % 100 == 13)) continue;
            dp[1][i] = "1";
        }
        for (int i = 2; i <= N; i++)
            for (int j = 0; j < B; j++)
            {
                if (j % 100 == 13) continue;
                for (int k = 0; k < B; k++)
                {
                    if (k % 100 == 13) continue;
                    //if (k == 1 && j == 3) continue;
                    dp[i][j] = add(dp[i][j], dp[i - 1][k]);
                }
            }
        string T = "0";
        for (int i = 0; i < B; i++) T = add(T, dp[N][i]);
        cout << T << '\n';
    }

    return 0;
}
