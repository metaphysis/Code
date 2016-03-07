// Distinct Subsequences （不同的子序列）
// PC/UVa IDs: 111102/10069, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-11
// UVa Run Time: 0.026s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [Problem Description]
// A subsequence of a given sequence S consists of S with zero or more elements
// deleted. Formally, a sequence Z = z1 z2 . . . zk is a subsequence of X = x1
// x2 . . . xm if there exists a strictly increasing sequence < i1 , i2 , . . . ,
// ik > of indices of X such that for all j = 1, 2, . . . , k, we have xij = zj.
// For example, Z = bcdb is a subsequence of X = abcbdab with corresponding index
// sequence < 2, 3, 5, 7 >.
//
// Your job is to write a program that counts the number of occurrences of Z in
// X as a subsequence such that each has a distinct index sequence.
//
// [Input]
// The first line of the input contains an integer N indicating the number of test
// cases to follow. The first line of each test case contains a string X, composed
// entirely of lowercase alphabetic characters and having length no greater than
// 10,000. The second line contains another string Z having length no greater than
// 100 and also composed of only lowercase alphabetic characters. Be assured that
// neither Z nor any prefix or suffix of Z will have more than 10^100 distinct
// occurrences in X as a subsequence.
//
// [Output]
// For each test case, output the number of distinct occurrences of Z in X as a
// subsequence. Output for each input set must be on a separate line.
//
// [Sample Input]
// 2
// babgbag
// bag
// rabbbit
// rabbit
//
// [Sample Output]
// 5
// 3
//
// [解题方法]
// 此题需要使用大数运算。使用一点 DP 即可。关键是如何得到递推关系，可以这样想，设母串的长度为 j，
// 子串的长度为 i，我们要求的就是长度为 i 的字串在长度为 j 的母串中出现的次数，设为 t[i][j]，若
// 母串的最后一个字符与子串的最后一个字符不同，则长度为 i 的子串在长度为 j 的母串中出现的次数就是
// 母串的前 j - 1 个字符中子串出现的次数，即 t[i][j] = t[i][j - 1]，若母串的最后一个字符与子
// 串的最后一个字符相同，那么除了前 j - 1 个字符出现字串的次数外，还要加上子串的前 i - 1 个字符
// 在母串的前 j - 1 个字符中出现的次数，即 t[i][j] = t[i][j - 1] + t[i - 1][j - 1]。

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXZ 101
 
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

	integer operator+(const integer&);
	integer& operator+=(const integer&);
	
private:
	vector < unsigned int > digits;		// 数位。
	static unsigned int const base = 10000;	// 基数。
	static unsigned int const width = 4;	// 数位宽度。
};
	
// 重载输出符号 <<。
ostream& operator<<(ostream& os, const integer &number)
{
	os << number.digits[number.digits.size() - 1];
	for (int i = number.digits.size() - 2; i >= 0; i--)
		os << setw(number.width) << setfill('0') << number.digits[i];
	return os;
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

void distinctSubsequences(string x, string z)
{
	// 若为二维数组，可能因数据量多而会溢出导致段错误，故使用滚动数组来计算节省空间。
	// 当计算 t[i][j] 时，数组中保存的是 t[i][j - 1] 和 t[i - 1][j - 1] 的数据。
	integer occurrences[MAXZ];

	int xLength = x.length();
	int zLength = z.length();

	// 为 DP 准备初始条件。长度为 0 的子串在长度为 0 的母串中出现次数为 1，长度不为 0 的
	// 子串在长度为 0 的母串中出现次数为 0。
	occurrences[0] = integer(1);	
	for (int i = 1; i <= zLength; i++)
		occurrences[i] = integer(0);

	// DP 求出现次数。
	for (int i = 1; i <= xLength; i++)
		for (int j = zLength; j >= max(int(zLength - xLength + i), 1); j--)
			if (x[i - 1] == z[j - 1])
				occurrences[j] += occurrences[j - 1];

	cout << occurrences[z.length()] << endl;
}

int main(int ac, char *av[])
{
	string x, z;
	int cases;
	
	cin >> cases;
	while (cases--)
	{
		cin >> x >> z;
		
		if (x.length() < z.length())
			cout << 0 << endl;
		else
			distinctSubsequences(x, z);
	}

	return 0;
}
