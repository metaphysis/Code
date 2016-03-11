// Counting （数数）
// PC/UVa IDs: 110603/10198, Popularity: B, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-02
// UVa Run Time: 0.032s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
	
using namespace std;
	
#define MAXN 1000
	
// 由前三项计算下一项。
string next(string a, string b, string c)
{
	string d, e;
	
	int carry = 0;
	for (int i = 0; i < a.length(); i++)
	{
		int v = carry + 2 * (a[i] - '0');
		carry = v / 10;
		d.append(1, char('0' + v % 10));
	}
	
	if (carry)
		d.append(1, char('0' + carry));
	
	// 为数b和c添加前导0，使得数位和d的数位相同，便于计算。
	while (b.length() < d.length())
		b.append(1, '0');
	while (c.length() < d.length())
		c.append(1, '0');
	
	carry = 0;	
	for (int i = 0; i < d.length(); i++)
	{
		int v = carry + (b[i] - '0') + (c[i] - '0') + (d[i] - '0');
		carry = v / 10;
		e.append(1, char('0' + v % 10));	
	}
	
	if (carry)
		e.append(1, char('0' + carry));
		
	return e;
}
	
// 初始化数组，直到计算出 MAXN 指定的数序列总数，数位逆序存放。
void init(vector < string > &counting)
{
	counting.push_back("2");
	counting.push_back("5");
	counting.push_back("31");
	
	for (int i = 3; i <= MAXN; i++)
		counting.push_back(next(counting[i - 1], counting[i - 2],
								counting[i - 3]));
}
	
int main(int ac, char *av[])
{
	int n;
	vector < string > counting;
	
	init(counting);
	
	while (cin >> n)
	{
		reverse_copy(counting[n - 1].begin(), counting[n - 1].end(),
					ostream_iterator < char >(cout, ""));
		cout << endl;
	}
	
	return 0;
}
