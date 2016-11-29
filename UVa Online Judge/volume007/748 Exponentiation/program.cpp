// Exponentiation
// UVa ID: 748
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

// 十进制下的四则运算。
const int BASE = 10;

// 移除计算结果的前导0。
void zeroJustify(string &number)
{
    while (number.front() == '0' && number.length() > 1)
        number.erase(number.begin());
}

// 两个非负整数的乘法。
string multiplicate(string number1, string number2)
{
    // 预分配存储空间。
    string number3(number1.length() + number2.length(), 0);
    
    // 从最低位开始相乘。
    int length1 = number1.length() - 1, length2 = number2.length() - 1;
    for (int i = length1; i >= 0; i--)
		for (int j = length2; j >= 0; j--)
		{
		    int k = number3.length() - 1 - (length1 - i + length2 - j);
			number3[k] += (number2[j] - '0') * (number1[i] - '0');
			number3[k - 1] += number3[k] / BASE;
			number3[k] %= BASE;
		}

    // 将数值转换为对应的数字字符。
	for (int i = 0; i < number3.length(); i++)
        number3[i] += '0';
        
    zeroJustify(number3);
    
    return number3;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string R;
    int n;
    
    while (cin >> R >> n)
    {
        int period = 0;
        for ( ; period < R.length(); period++)
            if (R[period] == '.')
                break;
        period = R.length() - 1 - period;
        
        string number1;
        for (int i = 0; i < R.length(); i++)
            if (R[i] != '.')
                number1 += R[i];
                
        string result = number1;
        for (int i = 2; i <= n; i++)
            result = multiplicate(result, number1);
            
        while (result.length() < period * n)
            result.insert(result.begin(), '0');
        
        period = result.length() - period * n;
        result = result.substr(0, period) + '.' + result.substr(period);
        
        while (result.front() == '0' && result.length() > 1)
            result.erase(result.begin());
        while (result.back() == '0' && result.length() > 1)
            result.erase(result.end() - 1);
        if (result.back() == '.')
            result.erase(result.end() - 1);
            
        cout << result << '\n';
    }
    
	return 0;
}
