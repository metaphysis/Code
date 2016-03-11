// How Many Pieces of Land? （土地分割）
// PC/UVa IDs: 110602/10213, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-01
// UVa Run Time: 0.888s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 一个圆被圆上 n 个点的连线所划分，能得到的最大区域数是 1 + C(n, 2) + C(n, 4)。
// 具体可参见维基网页 http://en.wikipedia.org/wiki/Dividing_a_circle_into_areas，
// 以及 http://www.arbelos.co.uk/Papers/Chords-regions.pdf 。
	
#include <iostream>
#include <vector>
#include <algorithm>
	
using namespace std;
	
#define PLUS 	1	// 正数。
#define MINUS 	-1	// 负数。
	
// 大数类。
class integer
{
	friend ostream& operator<<(ostream&, const integer&);
	friend istream& operator>>(istream&, integer&);
	
	friend int compare(const integer, const integer);
	friend bool operator<(const integer, const integer);
	friend bool operator<=(const integer, const integer);
	
	friend integer operator<<(integer, int);
	
	friend integer operator+(integer, integer);
	friend integer operator-(integer, integer);
	friend integer operator*(integer, integer);
	friend integer operator/(integer, integer);
	friend integer operator^(integer, int);
	
public:
	integer() { };
	
	integer(int a)
	{
		signbit = (a >= 0 ? PLUS : MINUS);
		a = abs(a);
		while (a)
		{
			digits.push_back(a % 10);
			a /= 10;
		}
	};
	
	~integer() { };
	
	void zero_justify(void);
	
private:
	// 表示大数的结构。数位按低位到高位的顺序存放。存储的是数位值，而不是数位的字符值。
	// 数字 1 用 ASCII 码为 1 的字符，而不是 ‘1’ 来表示。
	vector < char > digits;	// 存放数位值。
	int signbit;		// 符号位。
};
	
integer operator+(integer, integer);
integer operator-(integer, integer);
	
// 重载输出符号<<。
ostream& operator<<(ostream& os, const integer& n)
{
	// 当为自然数时，不输出“+”号。
	os << (n.signbit > 0 ? "" : "-");
	for (int i = n.digits.size() - 1; i >= 0; i--)
		// 存放的是数位值，输出时要转换为数位的字符值。
		os << (char)('0' + n.digits[i]);
	return os;
}
	
// 重载输入符号>>。
istream& operator>>(istream& in, integer& n)
{
	// 读入表示大整数的字符串。
	string s;
	in >> s;
	
	if (s.length() == 0)
	{
		// 若长度为0，表示读入的是一个空字符串，应该要给予错误提示，但对于本题来说，不
		// 存在这种情况，故不考虑。若要完善，需要进一步处理此种情况。
	}
	
	// 在解析之前，理应判断该字符串是否是一个合法的大数表示，即开始一位为符号位，为“+”或
	// “-”，正整数“+”可以忽略，后面应该全部是数字字符，且不包含前导0。由于本题不存在此种情
	// 况，故不考虑，若要完善需进一步处理此种情况。
	
	// 解析符号位。
	if (isdigit(s[0]))
		n.signbit = PLUS;
	else
	{
		n.signbit = (s[0] == '+' ? PLUS : MINUS);
		s.erase(s.begin());
	}
	
	// 解析数字位，从低位到高位存放于动态数组中。
	n.digits.clear();
	for (int i = s.length() - 1; i >= 0; i--)
		n.digits.push_back((char)(s[i] - '0'));
	
	return in;
}
	
// 移除大数运算产生的前导0。
void integer::zero_justify(void)
{
	for (int i = digits.size() - 1; i >= 1; i--)
		if (digits[i] == 0)
			digits.erase(digits.begin() + i);
		else
			break;
	
	if (digits.size() == 1 && digits[0] == 0)
		signbit = PLUS;
}
	
// 比较两个数的大小，若相等，返回 0，若 a 大于 b，返回 1，若 a 小于 b，返回 -1。
int compare(const integer a, const integer b)
{
	// 若 a 为正，b 为负，则有 a 大于 b。
	if (a.signbit == PLUS && b.signbit == MINUS)
		return PLUS;
	
	// 若 a 为负，b 为正，则 a 小于 b。
	if (a.signbit == MINUS && b.signbit == PLUS)
		return MINUS;
	
	// 若两数符号相同，则 a 的数位长度大于 b 的数位长度，若 a 为正数，则有 a 大于 b，若 a
	// 为负数，有 a 小于 b，则将 a 的符号位乘以1作为结果返回即可。  
	if (a.digits.size() > b.digits.size())
		return PLUS * a.signbit;
	
	// 若两数符号相同，若a的数位长度小于b的数位长度，若 a 为正数，则 a 小于 b，若 a 为负数，
	// 则 a 大于 b，则将 a 的符号位乘以 -1 作为结果返回即可。    
	if (a.digits.size() < b.digits.size())
		return MINUS * a.signbit;
	
	// 两个数的数位长度相等，符号相等，则从低位到高位逐个比较数位值的大小。
	int marker = a.digits.size() - 1;
	while (marker >= 0)
	{
		if (a.digits[marker] > b.digits[marker])
			return PLUS * a.signbit;

		if (a.digits[marker] < b.digits[marker])
			return MINUS * a.signbit;

		marker--;
	}
	
	return 0;
}
	
// 小于比较符。
bool operator<(const integer a, const integer b)
{
	return compare(a, b) < 0;
}
	
// 小于等于比较符。
bool operator<=(const integer a, const integer b)
{
	return compare(a, b) <= 0;
}
	
// 左移操作。b 表示左移的位数。即将 a 乘以 10^b。
integer operator<<(integer a, int b)
{
	integer c = a;
	
	// 若 a 等于 0，则移位后仍为 0。
	if (a.digits.size() == 1 && a.digits[0] == 0)
		return c;

	// 向左移动 b 位，相当于在数位数组前插入 b 个 0。
	for (int i = 0; i < b; i++)
		c.digits.insert(c.digits.begin(), (char)(0));
	
	return c;
}
	
// 加法运算。从低位往高位进行，每一位相加产生的进位向高位传递，注意负数的处理，可以相应的
// 转变为减法来简化操作。
integer operator+(integer a, integer b)
{
	integer c;
	
	// 两数符号位相等，则最终符号位和原来的加数符号位相同。
	if (a.signbit == b.signbit)
		c.signbit = a.signbit;
	else
	{
		// 若两个加数为一正一负，则将其转换为减法操作。
		if (a.signbit == MINUS)
		{
			a.signbit = PLUS;
			c = b - a;
		}
		else
		{
			b.signbit = PLUS;
			c = a - b;
		}

		return c;
	}
	
	// 从动态数组的开始即低位开始相加，逐渐往前进位，如果有的话。
	int carry = 0;		// 进位。
	int maxsize = max(a.digits.size(), b.digits.size());
	int marker = 0;
	
	// 为两数添加前导 0，以使得数位相同，便于计算。
	while (a.digits.size() < maxsize)
		a.digits.push_back(char(0));
	while (b.digits.size() < maxsize)
		b.digits.push_back(char(0));
		
	// 逐位相加。
	while (marker < maxsize)
	{
		int t = a.digits[marker] + b.digits[marker] + carry;
		carry = t / 10;
		c.digits.push_back((char)(t % 10));

		marker++;
	}
	
	// 若最后一次进位为 1，则需在最高位加 1。
	if (carry)
		c.digits.push_back((char)(1));
	
	c.zero_justify();
	
	return c;
}
	
// 减法。为了保证借位能够成功终止，最好确保被减数不小于减数。同样可以在适当情况转变为加法来简化操作。
integer operator-(integer a, integer b)
{
	integer c;
	
	// 当某一个数为负数时，转换为加法。
	if (a.signbit == MINUS || b.signbit == MINUS)
	{
		b.signbit = MINUS * b.signbit;
		c = a + b;

		return c;
	}
	
	// 两个都为正数，若 a < b，则尽量保证被减数大于减数。
	if (a < b)
	{
		c = b - a;
		c.signbit = MINUS;

		return c;
	}
	else
		c.signbit = PLUS;
	
	int borrow = 0;		// 借位。
	int maxsize = a.digits.size();	// 被减数大于减数。
	int marker = 0;		// 计数器。
	
	// 为减数添加前导 0，便于计算。因为先前已经使得 a > b 且 a 和 b 均为正数。
	while (b.digits.size() < maxsize)
		b.digits.push_back(char(0));

	// 从低位开始逐位相减，不够的向高位借位。
	while (marker < maxsize)
	{
		int v = a.digits[marker] - borrow - b.digits[marker];
		if (v < 0)
		{
			v += 10;
			borrow = 1;
		}
		else
			borrow = 0;
	
		c.digits.push_back((char)(v % 10));
	
		marker++;
	}
	
	c.zero_justify();
	
	return c;
}
	
// 乘法，采用一行一行算的方法比单纯的反复加法更快且编写代码不会变复杂许多。每次操作都把第一个
// 乘数左移一个数位，然后把左移后的数乘以x的积加到最终结果中，其中x是第二个乘数对应的数字。尽
// 管用反复加法来实现这一步看起来不够精巧，但由于对于第二个乘数的每个数字，内层循环最多执行 9
// 次，实际上并没有浪费太多的时间，左移一个数位等价于用它乘以进位制的基数，在十进制里就是乘以 10。
integer operator*(integer a, integer b)
{
	integer c = integer(0), row = a;
	row.signbit = PLUS;
	
	for (int i = 0; i < b.digits.size(); i++)
	{
		for (int j = 0; j < b.digits[i]; j++)
			c = (c + row);

		row = row << 1;
	}
	
	c.signbit = a.signbit * b.signbit;
	c.zero_justify();

	return c;
}
	
// 除法运算。将余数和商不断左移，余数加上被除数的下一个数字，然后尝试减去除数。
integer operator/(integer a, integer b)
{
	integer c, row;
	row.signbit = PLUS;

	// 商的符号为 a 的符号乘以 b 的符号。
	c.signbit = a.signbit * b.signbit;
 	
	int v;
	// 从数a的最高位开始除。
	for (int i = a.digits.size() - 1; i >= 0; i--)
	{
		row = row << 1;
		row.digits[0] = a.digits[i];

		// 当除数小于被除数，减去除数，对应位的商增 1。
		v = 0;
		while (b <= row)
		{
			v++;
			row = row - b;
		}
 	
		// 将商左移 1 位，刚得到的商即为最低位。
		c = c << 1;
		c.digits[0] = (char)(v);
	}
 	
	c.zero_justify();
 	
	return c;
}
 	
// 幂计算。幂就是反复作乘法，利用：a^n = a^(n / 2) * a^(n / 2) * a^(n mod 2)，可以减少乘
// 的次数。
integer operator^(integer a, int b)
{
	if (b == 0)
		return integer(1);
 	
	if (b == 1)
		return a;
 	
	if (b == 2)
		return a * a;
 	
	return ((a ^ (b / 2)) ^ 2) * (a ^ (b % 2));
}
	
int main(int ac, char *av[])
{
	int cases;
	integer a;
 	
	cin >> cases;
	while (cases--)
	{
		cin >> a;
 	
		cout << ((a ^ 4) - integer(6) * (a ^ 3) +
			integer(23) * (a ^ 2) - integer(18) * a +
			integer(24)) / integer(24) << endl;
	}
 	
	return 0;
}
