// Complete Tree Labeling （完全树标号）
// PC/UVa IDs: 110605/10247, Popularity: C, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-06
// UVa Run Time: 0.172s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 如何得到递推关系？设 T（K，D）表示分支因子为 K，深度为 D 的 K 叉树标号的方案数。又设
// N（K，D）表示分支因子为 K，深度为 D 的完全 K 叉树所包含的节点数。根据完全 K 叉树的定义，
// 深度为 D 的完全 K 叉树包含了 K 个深度为 （D - 1） 的完全 K 叉数，其包含的节点数可以
// 表示为 N（K，D - 1），有 K * N（K，D - 1） + 1 = N（K，D）。每个子树的标号方案数为
// T（K，D - 1），则问题转化为下面的问题：N（K，D） - 1 个节点，编号为 1 - （N（K，D） - 1），
// 划分为 K 个子集，每个子集有 N（K，D - 1）个节点，这种划分方法有多少？因为只要确定了划分
// 方法数，则由于知道了 T（K，D - 1），只要将每种划分方法得到的子集和每棵子树一一对应，每个
// 子集的元素可以与 T（K，D - 1） 中的标号形成一一映射，设总的划分方法数为X，则有以下关系：
//
// T（K，D） = X * (T（K，D - 1) ^ K)	（1）
//
// 而集合的划分种数 X 相当与每次从 N（K，D） - 1 个节点中取 N（K，D - 1）个节点，共取 K 次
// 所能得到的不同取法总数。设 A = （N（K，D） - 1），B = N（K，D - 1），A = K * B，有：
//
// X = C（A，B） * C（A - B，B） * …… * C（A - T * B，B），0 <= T <= K - 1	（2）
//
// 根据组合数的定义可将（2）式化简为：
//
// X = （A！） / （（B！） ^ K ）	（3）
//
// 最终有：
//
// T（K，D） = （（（N（K，D） - 1）！ / （（N（K，D - 1）！） ^ K）） * T（K，D - 1)
// ^ K （4）
//
// 容易知道 T（K，0） = 1，N（K，D） = （K ^ （D + 1） - 1） / （K - 1）。则可进一步化简得
// 到：
//
// T（K，D） = （N（K，D） - 1）！ / N（K，D - 1） ^ K / N（K，D - 2） ^ （K ^ 2) /.../ 
// N（K，1） ^ （K ^ （D - 1）） （5）
//
// 可以看出涉及到大数的乘以及除运算。
	
#include <bits/stdc++.h>

using namespace std;
	
class integer
{
	friend ostream& operator<<(ostream&, const integer&);
	
public:
	integer() { };
	
	// 将无符号整数转换为大整数。
	integer(unsigned int a)
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
	
	~integer() { };
	
	integer operator*(const integer&);
	integer& operator*=(unsigned int);
	integer& operator*=(const integer&);
	integer operator/(integer&);
	
	bool is_zero(void)
	{
		return digits.empty();
	};
	
private:
	void zero_justify(void);
	bool less_equal(integer&, unsigned int &, integer&);
	
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
	
	unsigned int carry = 0;
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
	
// 判断 b * v <= row 是否成立，成立返回 true，否则返回 false。
bool integer::less_equal(integer& b, unsigned int &v, integer& row)
{
	// 由于本题中存在关系 row.digits.size() = b.digits.size() + 1，故可以加以利用。
	// 若 b * v 的最高位大于 row，则可确定，b * v > row。
	int carry = b.digits[b.digits.size() - 1] * v;
	if ((carry / base) > row.digits[row.digits.size() - 1])
		return false;
	
	// 逐位比较，当两个数位不等时，记录比较结果，最后一次的比较结果决定了 b * v 和 row 的大小
	// 关系。
	bool flag = true;
	carry = 0;	
	for (int i = 0; i < b.digits.size(); i++)
	{
		int tmp = b.digits[i] * v + carry;
		carry = tmp / base;
		tmp %= base;
		if (row.digits[i] != tmp)
			flag = tmp < row.digits[i];
	}
	
	// 进位需要与 row 的最高位比较。
	if (carry != row.digits[row.digits.size() - 1])
		flag = carry < row.digits[row.digits.size() - 1];
	
	return flag;
}
	
// 除法，使用二分法来试除得到商。
integer integer::operator/(integer& b)
{
	integer c;
	integer row;
	
	// 要为商 c 和表示被减数的 row 分配存储空间。
	c.digits.resize(digits.size() - b.digits.size() + 1);
	row.digits.resize(b.digits.size() + 1);
	
	// 初始化值。
	fill(c.digits.begin(), c.digits.end(), 0);
	fill(row.digits.begin(), row.digits.end(), 0);
	
	for (int i = digits.size() - 1; i >= 0; i--)
	{
		// 获取被除数。
		for (int j = row.digits.size() - 1; j > 0; j--)
			row.digits[j] = row.digits[j - 1];
		row.digits[0] = digits[i];
	
		// 通过二分试除法得到对应位的商。
		int high = base - 1;
		int low = 0;
		unsigned int v = (high + low + 1) >> 1;
		while (high > low)
		{
			if (less_equal(b, v, row))
				low = v;
			else
				high = v - 1;
	
			v = (high + low + 1) >> 1;
		}
	
		// 从 row 中减去 v 个 b。
		int borrow, start = 0;
		for (; start < b.digits.size(); start++)
		{
			// 决定借位的数量。
			int t = row.digits[start] - v * b.digits[start];
			if (t < 0)
				borrow = (base - 1 - t) / base;
			else
				borrow = 0;
				
			// 高位减去借位数量。
			row.digits[start + 1] -= borrow;
			
			// 低位加上借位。
			t += base * borrow;
			row.digits[start] = t % base;
		}
			
		// 将对应位的商存入结果中。
		for (int j = c.digits.size() - 1; j > 0; j--)
			c.digits[j] = c.digits[j - 1];
		c.digits[0] = v;
	
	}
	
	// 清除前导 0。
	c.zero_justify();
	return c;
}
	
#define TREEDEEPTH 22
	
// 计算分支因子为 k，深度为 d 的标号方案数。
void cal_tree(vector < int > kd)
{
	// 存储分支因子为 k，深度为 d 的 k 叉数的完全数标号方案数。
	integer tree[TREEDEEPTH][TREEDEEPTH];
	// 存储分支因子为 k，深度为 d 的 k 叉数的节点数。
	unsigned int nodes[TREEDEEPTH][TREEDEEPTH];
	
	// 计算满足 k * d <= 21 的树的节点数。并找到最大的节点数。
	unsigned int max = 0;
	for (int i = 0; i < kd.size(); i += 2)
	{
		nodes[kd[i]][0] = 1;
		for (int j = 1; j <= kd[i + 1]; j++)
		{
			nodes[kd[i]][j] = nodes[kd[i]][j - 1] * kd[i] + 1;
			if (nodes[kd[i]][j] > max)
				max = nodes[kd[i]][j];
		}
	}
	
	// 计算 1 到节点数 max - 1 的阶乘。
	vector < integer > fact(max);
	fact[0] = integer(1);
	for (unsigned int i = 1; i < max; i++)
		fact[i] = fact[i - 1] * i;
	
	// 根据化简的公式（5）计算标号方案数。
	for (int i = 0; i < kd.size(); i += 2)
	{	
		if (tree[kd[i]][kd[i + 1]].is_zero())
		{
			// 计算 N（K，M） ^ （K ^ （D - M）），v = K ^ （D - M）。
			unsigned int v = 1;
			integer t(1);
			for (int d = kd[i + 1]; d > 0; d--)
			{
				v *= kd[i];
				for (int k = 1; k <= v; k++)
					t *= nodes[kd[i]][d - 1];
			}
			
			tree[kd[i]][kd[i + 1]] =
				fact[nodes[kd[i]][kd[i + 1]] - 1] / t;
		}
	
		cout << tree[kd[i]][kd[i + 1]] << endl;
	}
}
	
int main(int ac, char *av[])
{
	int k, d;
	vector < int > kd;
	
	while (cin >> k >> d)
	{
		kd.push_back(k);
		kd.push_back(d);
	}
	
	cal_tree(kd);
	
	return 0;
}
