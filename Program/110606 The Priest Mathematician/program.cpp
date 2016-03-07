// The Priest Mathematician （牧师数学家）
// PC/UVa IDs: 110606/10254, Popularity: C, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-07
// UVa Run Time: 0.048s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 设 N 个盘子在 4 柱情况下的移动最小步数为 T（N），在 3 柱子情况下的最小移动步数为 H（N），则
// 通过下列方法可以得到最小移动步数 T（N）。假设第一次先将 1 个盘子通过 4 根柱子移动到非目标柱子，
// 然后将 N - 1 个盘子通过 3 根柱子移动到目标柱子，最后把最先移动的盘子移动到目标柱子上，则总步
// 数为 H（N - 1） + 2 * T（1），若第一次移动两个盘子，则步数为 H（N - 2） + 2 * T（2），依
// 此类推，所求的就是当 N 一定时，2 * T（M） + H（N - M）（0 <= M <= N） 的最小值。由于最多
// 可有 10000 个盘子，移动方法数将是一个大整数，超出 long long 型的表示范围。实际上，也可以不
// 需要计算比较最小移动步数，可以观察到 T（N） 的后一项与前一项的差形成以下数列 （N >= 1）：
//
// 1 2 2 4 4 4 8 8 8 8 16 16 16 16 16 32 32 32 32 32 32 …… 
//
// 2 的 m 次幂出现 （m + 1） 次，m >= 0。
	
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class integer
{
	friend ostream& operator<<(ostream&, const integer&);
	
public:
	integer() { };
	
	// 将无符号整数转换为大整数。
	integer(unsigned int orginal)
	{
		do
		{
			digits.push_back(orginal % base);
			orginal /= base;
		} while (orginal);
	};
	
	~integer() { };
	
	integer operator*(const integer&);
	integer& operator*=(unsigned int);
	integer& operator*=(const integer&);
	integer operator+(integer&);
	integer& operator+=(const integer&);

private:
	void zero_justify(void);
	
	vector < unsigned int > digits;		// 数位。
	static unsigned int const base = 10000;	// 基数。
	static unsigned int const width = 4;	// 数位宽度。
};
	
// 重载输出符号 <<。
ostream& operator<<(ostream& os, const integer& number)
{
	os << number.digits[number.digits.size() - 1];
	for (int i = number.digits.size() - 2; i >= 0; i--)
		os << setw(number.width) << setfill('0') << number.digits[i];
	return os;
}
	
// 移除大数运算产生的前导 0。
void integer::zero_justify(void)
{
	for (int i = digits.size() - 1; i >= 1; i--)
	{
		if (digits[i] == 0)
			digits.erase(digits.begin() + i);
		else
			break;
	}
}
	
integer& integer::operator*=(const integer& b)
{
	return *this = *this * b;
}
	
// 大数乘以无符号整数。
integer& integer::operator*=(unsigned int b)
{
	if (b >= base)
	{
		*this *= integer(b);
		return *this;
	}
	
	int carry = 0;
	for (int i = 0; i < digits.size(); i++)
	{
		digits[i] = digits[i] * b + carry;
		carry = digits[i] / base;
		digits[i] %= base;
	}
	
	if (carry)
		digits.push_back(carry);
	
	return *this;
}
	
// 乘法。
integer integer::operator*(const integer& b)
{
	integer c;
	
	// 预先分配足够空间。
	c.digits.resize(digits.size() + b.digits.size());
	fill(c.digits.begin(), c.digits.end(), 0);
	
	// 一行一行算，逐行相加。
	for (int i = 0; i < b.digits.size(); i++)
		for (int j = 0; j < digits.size(); j++)
		{
			c.digits[i + j] += digits[j] * b.digits[i];
			c.digits[i + j + 1] += c.digits[i + j] / base;
			c.digits[i + j] %= base;
		}
	
	// 去掉前导0。
	c.zero_justify();
	return c;
}
	
integer& integer::operator+=(const integer &b)
{
	return *this = *this + b;
}

// 加法。
integer integer::operator+(const integer &b)
{
	integer c;
	
	int carry = 0;
	for (int i = 0; i < digits.size() || i < b.digits.size() || carry; i++)
	{
		if (i < digits.size())
			carry += digits[i];
		if (i < b.digits.size())
			carry += b.digits[i];

		c.digits.push_back(carry % base);		
		carry /= base;
	}

	return c;
}
	
#define MAXDISKS 10001
	
// 利用最少步骤数前后项相差所形成的数列特点。2 的 m 次幂出现 （m + 1） 次。
void hanoi(vector < int > disks)
{	
	// 求出相应盘子数的最少移动步骤数。
	vector < integer > steps(MAXDISKS);
	steps[0] = 0;
	integer exponent(1);
	for (int index = 1, sequence = 1; index < MAXDISKS; sequence++)
	{
		for (int start = 1; start <= sequence && index < MAXDISKS; start++, index++)
			steps[index] = steps[index - 1] + exponent;
		exponent *= 2;
	}
	
	// 输出结果。
	for (int i = 0; i < disks.size(); i++)
		cout << steps[disks[i]] << endl;
}

int main(int ac, char *av[])
{
	vector < int > disks;
	int d;
	
	// 读入盘子数。
	while (cin >> d)
		disks.push_back(d);
	
	// 求最少移动步骤数。
	hanoi(disks);
	
	return 0;
}
