// How Many Fibs? （斐波那契计数）
// PC/UVa IDs: 110601/10183, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-30
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define UPBOUND 101

vector < string > fibs;

// 比较两个斐波那契数的大小，数位存放在f1和f2中，其中f1的数位是按高位到低位存放，
// f2的数位是按低位到高位存放。f1大于f2返回1，小于返回-1，等于返回0。
int fibs_compare(string f1, string f2)
{
	if (f1.length() != f2.length())
		return f1.length() > f2.length() ? 1 : (-1);
	
	for (int i = 0, j = f2.length() - 1; i < f1.length(); i++, j--)
		if (f1[i] != f2[j])
			return f1[i] > f2[j] ? 1 : (-1);
	
	return 0;
}

// 根据前两个斐波那契数产生下一个斐波那契数，数位逆序存放于字符串变量f1和f2，
// 最终结果也逆序存放。
string fibs_add(string f1, string f2)
{
	// 前后两个斐波那契数有以下长度关系：f1.length() <= f2.length()。
	string tmp;
	int carry = 0;
	
	for (int i = 0; i < f1.length(); i++)
	{
		carry = (f1[i] - '0') + (f2[i] - '0') + carry;
		char c = '0' + carry % 10;
		tmp.append(1, c);
		carry = carry / 10;
	}
	
	for (int i = f1.length(); i < f2.length(); i++)
	{
		carry = (f2[i] - '0') + carry;
		char c = '0' + carry % 10;
		tmp.append(1, c);
		carry = carry / 10;
	}
	
	if (carry)
		tmp.append(1, '1');
		
	return tmp;
}

// 填充斐波那契数表，直到计算出具有101位数的斐波那契数为止。
void fill_fibs()
{
	string f1 = "1", f2 = "2";
	
	fibs.push_back(f1);
	fibs.push_back(f2);
	
	while (f2.length() < UPBOUND)
	{
		string tmp = fibs_add(f1, f2);
		f1 = f2;
		f2 = tmp;
		fibs.push_back(f2);
	}
}

int main(int ac, char *av[])
{
	// 填充斐波那契数表。
	fill_fibs();

	string a, b, line;
	while (getline(cin, line), line.length())
	{
		istringstream iss(line);
		iss >> a >> b;
		
		if (a == "0" && b == "0")
			break;
		else
		{
			// 找到大于等于a的斐波那契数在fibs数组的位置。
			int start, end;
			for (int i = 0; i < fibs.size(); i++)
			{
				if (a.length() > fibs[i].length())
					continue;
					
				if (fibs_compare(a, fibs[i]) <= 0)
				{
					start = i;
					break;
				}
			}
			
			// 找到小于等于b的斐波那契数在fibs数组的位置。
			for (int i = fibs.size() - 1; i >= 0; i--)
			{
				if (b.length() < fibs[i].length())
					continue;

				if (fibs_compare(b, fibs[i]) >= 0)
				{
					end = i;
					break;
				}
			}

			// 输出总个数。
			cout << (end - start + 1) << endl;
		}
	}
		
	return 0;
}
