// UVa Problem 113 - Power of Cryptography
// Verdict: Accepted
// Submission Date: 2011-11-25
// UVa Run Time: 0.312s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本题可以归类为高精度算术题。
//
// 简单的大数运算，使用模板代码即可。使用二分法来搜索 k 值。使用 Java 来解是不是更好
// 些？有高精度算术的支持，不过，我比较喜欢 C++。
//
// AC 后和别人的代码比较，发现还有更巧妙的方法自己没有想到。虽然最初看到代码有点不相
// 信可以 AC，但是分析后确信在本题条件下是可以的。
//
// 以下是别人使用 pow 的 AC 代码，为什么可行呢？从第一感觉好像 pow 并不是精确的计算，
// 只是一个近似值，可为什么会得到正确的答案呢？都是因为底数是整数的关系，因为任意两个
// 整数之间至少相差 1，加上幂次的关系，只要两个数不等，其幂在值上的差可以在 double
// 数值的精度上反映出来，为什么？因为题目限定了 1 <= k <= 10^9，则有：
//
// (k + 1)^n - k^n > n * k^(n - 1)
//
// 而 n * k^(n - 1) / k^n = n / k，由于 1 <= k <= 10^9，则只要两个数相差 1，其 n
// 次幂之间的差能够通过 double 数的精度反映出来，因为 double 数有 15 位的精度，对于
// 任何 n 值，在题目给定的 1 <= k <= 10^9 范围内，只要其底数不等，其幂在用 double
// 表示后必定不等。所以可以使用 pow 加二分法来确定底数是哪个整数。但是当 k 增大时，
// 这个方法必定会失效，可以预见，当 k 的位数超过 double 数的精度位数时，这个方法就不
// 一定能求出正确的底数了。而使用大数运算仍然是可行的。
//
// #include <stdio.h>
// #include <math.h>
// #include <float.h>
//
// int main()
// {
// 	double n, p;
//
// 	while (scanf("%lf%lf", &n, &p) != EOF)
// 	{
// 		int begin = 1;
// 		int end = 1000000000;
// 		int mid;
//
// 		// 二分查找。
// 		while (begin <= end)
// 		{
// 			mid = (begin + end) / 2;
// 			double temp = pow(mid, n);
// 			if (temp == p)
// 			{
// 				printf("%d\n", mid);
// 				break;
// 			}
// 			else if (temp > p)
// 				end = mid - 1;
// 			else
// 				begin = mid + 1;
// 		}
// 	}
//
// 	return 0;
// }

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;
	
class integer
{
	friend ostream& operator<<(ostream&, const integer&);
	
public:
	integer() { };
	
	// 将整数转换为大整数。
	integer(long long a)
	{
		if (a == 0)
			digits.push_back(0);
		else
		{
			while (a)
			{
				digits.push_back(a % base);
				a /= base;
			}
		}
	};

	// 将字符串转换为大整数，不作格式的检查，默认格式是正确的。
	integer(string line)
	{
		while (line.length() >= width)
		{
			digits.push_back(atoi(line.substr(line.length() - width).data()));
			line = line.substr(0, line.length() - width);
		}
		
		if (line.length())
			digits.push_back(atoi(line.data()));
	};

	~integer() { };
	
	integer operator*(const integer&);
	integer& operator*=(const integer&);

	bool operator<(integer&);
	bool operator==(integer&);
	
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

// 重载小于符号。
bool integer::operator<(integer& b)
{
	if (digits.size() < b.digits.size())
		return true;
	if (digits.size() > b.digits.size())
		return false;
	for (int i = digits.size() - 1; i >= 0; i--)
		if (digits[i] != b.digits[i])
			return digits[i] < b.digits[i];
		
	return false;
}

// 重载等于符号。
bool integer::operator==(integer& b)
{
	if (digits.size() != b.digits.size())
		return false;
	for (int i = 0; i < digits.size(); i++)
		if (digits[i] != b.digits[i])
			return false;
	return true;
}

// 二分查找。
int binarySearch(int n, string p)
{
	int down = 1, up = 1000000000, middle;
	integer target = integer(p);
	
	while (down <= up)
	{
		middle = (down + up) / 2;
		
		integer m = integer(middle);
		integer tmp = integer(1);
		for (int i = 1; i <= n; i++)
			tmp *= m;

		if (tmp == target)
			return middle;
		else if (tmp < target)
			down = middle + 1;
		else
			up = middle - 1;
	}
}
	
int main(int ac, char *av[])
{
	int n;
	string p;
	
	while (cin >> n >> p)
		cout << binarySearch(n, p) << endl;
	
	return 0;
}
