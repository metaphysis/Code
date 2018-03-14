// Expressions （括号表达式）
// PC/UVa IDs: 110604/10157, Popularity: C, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-03
// UVa Run Time: 0.668s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 如何得到相应的递推关系？翻看了 Catalan 数的推导过程得到了一些启发。首先，括号的数目必须是
// 偶数才可能得到合法的表达式，当 n 为奇数时，不能得到任何深度的正确表达式，同时若深度超过 n
// 个括号所能得到的合法表达式的最大深度时，结果也将是 0 。所有深度为 1 的表示式都只有 1 种，假
// 设 T（m，d） 表示括号对数为 m （n = 2 * m），深度不超过 d 的合法括号表达式的总数，则有：
//
// T（0，d） = 1
//
// 对于其他情况，假设 E 是一个深度为 d ，括号对数为 m 的合法表达式，则表达式 E 的最左边的括号
// l 一定和某个右括号 r 配对，他们合在一起把表达式划分为两个合法的括号表达式，在 l 和 r 之间的
// 部分以及 r 右边的部分，即：
//
// E = （X）Y
//
// 假设左边部分有 k 对括号，则右边部分有 n - k - 1 对括号，因为 l 和 r 已经用了一对括号，则括号
// 表达式 X 的深度最大为 d - 1 ，括号表达式 Y 的深度最大为 d 。则括号对数为 m，深度为 d 的合法
// 表达式数量为 T（m，d） - T（m，d - 1）。
//
// T（m，d） = T（0，d - 1） * T（m - 1，d） + T（1，d - 1） * T（m - 2，d） + …… + T（k，
// d - 1） * T（m - k - 1，d），0 <= k <= m - 1。
//
// 看起来像是 Catalan 数的二维版本。
//
// 用于 How Many Pieces of Land? 问题的大数类在这个问题上，显然效率不够高，于是我改进了一下，以
// 10000为基数，数位改用模10000的值，用无符号整数来保存数位。
	
#include <bits/stdc++.h>

using namespace std;
	
#define MAXM	151
#define MAXD	151
	
class integer
{
	friend ostream & operator<<(ostream &, const integer &);
	
public:
	integer() { };
	
	integer(unsigned int a)
	{
		while (a)
		{
			digits.push_back(a % base);
			a /= base;
		}
	};
	
	~integer() { };
	
	integer operator+(integer);
	integer operator-(integer);
	integer operator*(integer);
	
private:
	void zero_justify(void);
	// 表示大数的结构。数位按模 10000 从低位到高位每 4 位为一组，作为一个 int 型数存放。
	vector < unsigned int > digits;
	static unsigned int const base = 10000;
	static unsigned int const length = 4;
};
	
// 重载输出符号 <<。
ostream& operator<<(ostream& os, const integer& n)
{
	os << n.digits[n.digits.size() - 1];
	for (int i = n.digits.size() - 2; i >= 0; i--)
		os << setw(n.length) << setfill('0') << n.digits[i];
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
	
// 加法运算。
integer integer::operator+(integer b)
{
	integer c;
	c.digits.resize(max(digits.size(), b.digits.size()) + 1);
	
	int carry = 0;		// 进位。
	int marker = 0;
	
	// 为两数添加前导 0，以使得数位相同，便于计算。
	while (digits.size() < c.digits.size())
		digits.push_back(0);
	while (b.digits.size() < c.digits.size())
		b.digits.push_back(0);
	
	// 逐位相加。
	while (marker < c.digits.size())
	{
		int t = digits[marker] + b.digits[marker] + carry;
		carry = t / base;
		c.digits[marker] = t % base;

		marker++;
	}
	
	c.zero_justify();
	
	return c;
}
	
// 减法。
integer integer::operator-(integer b)
{
	integer c;
	
	int borrow = 0;	// 借位。
	int marker = 0;	// 计数器。
	
	// 为减数添加前导0，便于计算。
	while (b.digits.size() < digits.size())
		b.digits.push_back(0);
	
	// 从低位开始逐位相减，不够的向高位借位。
	while (marker < digits.size())
	{
		int v = digits[marker] - borrow - b.digits[marker];
		if (v < 0)
		{
			v += base;
			borrow = 1;
		}
		else
			borrow = 0;

		c.digits.push_back(v % base);

		marker++;
	}
	
	c.zero_justify();
	
	return c;
}
	
// 乘法。
integer integer::operator*(integer b)
{
	integer c;
	c.digits.resize(digits.size() + b.digits.size());
	fill(c.digits.begin(), c.digits.end(), 0);

	for (int i = 0; i < b.digits.size(); i++)
		for (int j = 0; j < digits.size(); j++)
		{
			c.digits[i + j] += digits[j] * b.digits[i];
			c.digits[i + j + 1] += c.digits[i + j] / base;
			c.digits[i + j] %= base;
		}

	c.zero_justify();

	return c;
}
	
integer result[MAXM][MAXD];
	
void init()
{
	for (int m = 0; m < MAXM; m++)
		for (int d = 0; d < MAXD; d++)
			result[m][d] = integer(0);
	
	for (int d = 0; d < MAXD; d++)
		result[0][d] = integer(1);
	
	for (int m = 1; m < MAXM; m++)
		for (int d = 1; d < MAXD; d++)
			for (int k = 0; k <= m - 1; k++)
				result[m][d] =
					result[m][d] + result[k][d -
					1] * result[m - k - 1][d];
}

int main(int ac, char *av[])
{
	int n, d;
	
	init();
	
	while (cin >> n >> d)
		cout << (result[n / 2][d] - result[n / 2][d - 1]) << endl;
	
	return 0;
}
