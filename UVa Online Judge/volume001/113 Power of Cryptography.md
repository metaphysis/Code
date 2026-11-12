[UVa 113 Power of Cryptography](https://blog.csdn.net/metaphysis/article/details/156642010)

## 题目分析

本题要求计算给定整数 $n$ 和 $p$ 的正 $n$ 次根，即寻找整数 $k$ 使得 $k^n = p$ 。题目保证 $k$ 存在且 $1 \leq k \leq 10^9$ ， $1 \leq n \leq 200$ ， $p$ 最大可达 $10^{101}$ ，因此 $p$ 可能是一个非常大的整数，超出了普通整数类型的表示范围。

## 解题思路

由于 $p$ 可能非常大，直接使用内置整数类型计算 $k^n$ 会导致溢出，因此需要采用高精度运算或者利用数学特性避免大数运算。下面分别介绍三种实现方法，它们均通过了测试。

### 方法一：高精度运算 + 二分查找

这种方法使用自定义的高精度整数类 `integer` ，支持大数的乘法、比较等操作。由于 $k$ 的范围已知（$1$ 到 $10^9$），可以采用二分查找在 $[1, 10^9]$ 区间内寻找满足 $k^n = p$ 的 $k$ 。

**算法步骤：**

1. 读取 $n$ 和字符串形式的 $p$ 。
2. 将 $p$ 转换为高精度整数 `target` 。
3. 在区间 $[1, 10^9]$ 内进行二分查找：
   - 计算中间值 $mid$ 。
   - 计算 $mid^n$ 的高精度值。
   - 与 `target` 比较：
     - 若相等，则找到答案。
     - 若小于，则调整查找区间为 $[mid+1, up]$ 。
     - 若大于，则调整查找区间为 $[down, mid-1]$ 。

这种方法虽然正确，但实现较为复杂，且运行时间较长（约 $0.312$ 秒）。

### 方法二：使用 `double` 类型 + 二分查找

这种方法利用了题目中 $k$ 的范围限制（$1 \leq k \leq 10^9$）以及 `double` 类型的高精度特性。由于 $k$ 是整数，且相邻整数的 $n$ 次幂之差在 `double` 精度范围内可以区分，因此可以使用 `pow` 函数计算 $mid^n$ ，并与 $p$ 比较。

**算法步骤：**

1. 读取 $n$ 和 $p$ 为 `double` 类型。
2. 在区间 $[1, 10^9]$ 内进行二分查找：
   - 计算 $temp = pow(mid, n)$ 。
   - 若 $temp$ 等于 $p$ ，则找到答案。
   - 若 $temp > p$ ，则调整查找区间为 $[down, mid-1]$ 。
   - 若 $temp < p$ ，则调整查找区间为 $[mid+1, up]$ 。

这种方法代码简洁，运行速度快（约 $0.000$ 秒），但依赖于 `double` 精度足够高以区分相邻整数的 $n$ 次幂。在本题给定的数据范围内是可行的。

### 方法三：直接使用 `pow` 函数计算 $p^{1/n}$

这是最简洁的实现方法。由于 $k^n = p$ ，那么 $k = p^{1/n}$ 。题目保证 $k$ 是整数，因此可以直接使用 `pow(p, 1/n)` 计算，并将结果四舍五入到整数输出。

**算法步骤：**

1. 读取 $n$ 和 $p$ 为 `long double` 类型以提高精度。
2. 计算 $k = pow(p, 1/n)$ 。
3. 使用 `fixed` 和 `setprecision(0)` 输出整数结果。

这种方法代码极其简洁，运行速度最快（约 $0.000$ 秒），但同样依赖于浮点数运算的精度。在本题数据范围内， `long double` 的精度足以保证正确性。

## 总结

- **方法一** 最为通用和可靠，适用于任意大的 $p$ ，但实现复杂、效率较低。
- **方法二** 在题目限制下利用 `double` 精度进行二分查找，代码简单、效率高。
- **方法三** 利用数学公式直接计算，代码最简、效率最高，但依赖于浮点数精度。

在实际解题中，可根据题目具体要求和数据范围选择合适的方法。本题由于 $k$ 的范围有限，且 $p$ 虽大但 $k$ 的 $n$ 次幂在浮点数精度内可区分，因此方法二和方法三均能正确求解。

## 附：参考代码

### 方法一：高精度运算 + 二分查找

```cpp
// Power of Cryptography
// UVa ID: 113
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

#include <bits/stdc++.h>

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
```

### 方法二：使用 `double` 类型 + 二分查找

```cpp
// Power of Cryptography
// UVa ID: 113
// Verdict: Accepted
// Submission Date: 2017-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

int main()
{
	double n;
	double p;

	while (scanf("%lf%lf", &n, &p) != EOF)
	{
		int begin = 1;
		int end = 1000000000;
		int mid;

		// 二分查找。
		while (begin <= end)
		{
			mid = (begin + end) / 2;
			double temp = pow(mid, n);
			if (temp == p)
			{
				printf("%d\n", mid);
				break;
			}
			else if (temp > p)
				end = mid - 1;
			else
				begin = mid + 1;
		}
	}

	return 0;
}
```

### 方法三：直接使用 `pow` 函数计算 $p^{1/n}$

```cpp
// Power of Cryptography
// UVa ID: 113
// Verdict: Accepted
// Submission Date: 2017-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long double n, p;
    
    while (cin >> n >> p)
    {
        cout << fixed << setprecision(0) << pow(p, 1 / n) << '\n';
    }

    return 0;
}
```
