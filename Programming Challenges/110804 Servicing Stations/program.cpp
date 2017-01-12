// Servicing Stations （服务站）
// PC/UVa IDs: 110804/10160, Popularity: B, Success rate: low Level: 3
// Verdict: Accepted 
// Submission Date: 2011-08-10
// UVa Run Time: 0.056s

// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 该题目的实质是求图的最小支配集顶点个数。求图的最小支配集问题是 NP 完全问题，目前无高效的算法。
// 既然要枚举集合的所有子集，那就枚举吧，但是等一等，枚举需要个顺序，先枚举元素数量小的子集，要不
// 然，先枚举元素个数大的子集可能会浪费时间，毕竟从元素个数小的子集枚举到元素个数大的子集可以保证
// 找到最小支配集而不再浪费更多的时间，哎呀，时间是金钱，不是吗？可能什么时候某个强人发现 NP 难问
// 题的 P 时间算法，或者证明 P = NP 那就好了，希望在有生之年能够看到！！
//
// 为了提高效率，压缩程序运行时间，采用了以下优化方法：
// （1）若图可以拆分为多个不相连的子图，则先予拆分，然后对子图求最小支配集的顶点个数相加(之前由
//     于未拆分图，导致了多次 TLE）。
// （2）对于求两个集合的并采用了位操作，事先将某个顶点的邻接表表示为一个整数以便用与操作来代替集合
//     的并。
// （3）枚举时，先考虑度数大的顶点。
//
// 枚举方法参考了 [J. Loughry, J.I. van Hemert, L. Schoofs, Efficiently Enumerating
// the Subsets of a Set, 2000]

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define MAX_TOWN 35

typedef long long unsigned LLUINT;

bool finish;
int minimum;
vector<LLUINT> edge;
LLUINT target_tag, origin_tag;

// 检查顶点集合是否为支配集。
void check(int flag[], int position)
{
	int index = 0;
	LLUINT new_tag = origin_tag, old_tag = origin_tag;

	for (int i = 0; i < edge.size(); i++)
	{
		if ((index < position) && (flag[index] == i))
		{
			new_tag |= edge[i];
			if (new_tag > old_tag)
				old_tag = new_tag;
			else
				return;
			index++;
		}
	}
	
	if (new_tag == target_tag)
	{
		minimum = index;
		finish = true;
	}
}

// 按 Banker’s Sequence 枚举图的子集。
void generate(int flag[], int position, int positions)
{
	if (finish)
		return;

	if (position < positions)
	{
		if (position == 0)
		{
			for (int i = 0; i < edge.size(); i++)
			{
				flag[position] = i;
				generate(flag, position + 1, positions);
			}
		}
		else
		{
			for (int i = flag[position - 1] + 1; i < edge.size(); i++)
			{
				flag[position] = i;
				generate(flag, position + 1, positions);
			}
		}
	}
	else
		check(flag, position);
}

// 枚举图向量的子集以判断是否是一个支配集。
void enumerating_subset()
{
	for (int i = 1; i <= edge.size(); i++)
	{
		int * flag = new int[edge.size()];
		generate(flag, 0, i);
		delete [] flag;
		
		if(finish)
			return;
	}
}

bool cmp(LLUINT x, LLUINT y)
{
	return x > y;
}

// 获取图的最小支配集顶点数（MDSN）。
int mdsn(vector < vector < int > > &vertex)
{
	int base = 0;
	origin_tag = 0;
	target_tag = 0;
	
	vector < bool > dirty(vertex.size());
	fill(dirty.begin(), dirty.end(), false);
	
	// 清掉度为 0 的点。度为 0 的点和其他点都无通路，则该图的最小支配集必须要包括
	// 该顶点。则表示最小支配集顶点个数的变量 base 需增加 1。
	for (int i = 0; i < vertex.size(); i++)
	{
		if (vertex[i].size() == 0)
		{
			base++;
			origin_tag |= ((LLUINT)1 << i);
		}
		
		if (vertex[i].size() == 1 && dirty[i] == false)
		{
			dirty[i] = true;
			if (dirty[vertex[i][0] - 1] == false)
			{
				base++;
				dirty[vertex[i][0] - 1] = true;
			}
		}

		target_tag |= ((LLUINT)1 << i);
	}

	// 清掉度为 1 的点。度为 1 的点表明该顶点 A 只与其他一个顶点 B 相连接，则可
	// 将 B 计入最小支配集中。
	edge.clear();
	for (int i = 0; i < vertex.size(); i++)
	{
		if (dirty[i] == true)
		{
			origin_tag |= ((LLUINT)1 << i);
			for (int j = 0; j < vertex[i].size(); j++)
				origin_tag |= ((LLUINT)1 << (vertex[i][j] - 1));	
		}
		
		if (dirty[i] == false && vertex[i].size() > 0)
		{
			LLUINT t = ((LLUINT)1 << i);
			for (int j = 0; j < vertex[i].size(); j++)
				t |= ((LLUINT)1 << (vertex[i][j] - 1));
			edge.push_back(t);
		}
	}
	
	// 排序，度数大的点首先考虑。
	sort(edge.begin(), edge.end(), cmp);
	
	minimum = 0;
	finish = false;
	enumerating_subset();
	
	return (base + minimum);
}

int servicing_stations(vector < vector < int > > &vertex)
{	
	// 使用宽度优先搜索分离子图，计算子图的最小支配集顶点个数，相
	// 加即为原图的最小支配集顶点个数。
	int total = 0;
	while (vertex.size() > 0)
	{
		vector < vector < int > > open;
		set < int > close;
		
		int size = 0;
		open.push_back(vertex[0]);
		
		close.insert(vertex[0][0]);
		vertex.erase(vertex.begin());
		
		while (open.size() > size)
		{
			int origin = size;
			int current = open.size() - 1;
			size = open.size();
			
			for (int i = origin; i <= current; i++)
			{
				for (int j = 1; j < open[i].size(); j++)
				{
					if (close.find(open[i][j]) == close.end())
					{
						close.insert(open[i][j]);
						for (int m = 0; m < vertex.size(); m++)
						{
							if (vertex[m][0] == open[i][j])
							{
								open.push_back(vertex[m]);
								vertex.erase(vertex.begin() + m);
								break;
							}
						}
					}
				}
			}
		}
		
		// 调整分离出的子图的序号以便后续操作。
		vector < vector < int > > tmp;
		for (int c = 1; c <= MAX_TOWN; c++)
			if (close.find(c) != close.end())
			{
				for (int i = 0; i < open.size(); i++)
					if (open[i][0] == c)
						tmp.push_back(open[i]);
			}
		
		for (int i = 0; i < tmp.size(); i++)
		{
			int current = tmp[i][0];
			for (int m = 0; m < tmp.size(); m++)
				for (int n = 1; n < tmp[m].size(); n++)
					if (tmp[m][n] == current)
						tmp[m][n] = (i + 1);
		}
		
		for (int i = 0; i < tmp.size(); i++)
			tmp[i].erase(tmp[i].begin());
		
		// 计算该子图的最小支配集顶点数。
		total += mdsn(tmp);
	}
	
	return total;
}

int main(int ac, char *av[])
{
	int n;
	int m;
	int x, y;
	vector < vector < int > > vertex;
	
	while (cin >> n >> m, n && m)
	{
		vertex.clear();
		vertex.resize(n);
		
		// 数组的第一个数存放顶点的序号。
		for (int i = 0; i < n; i++)
			vertex[i].push_back((i + 1));
		
		// 读入镇之间的通路。
		for (int i = 0; i < m; i++)
		{
			// 自身连接到自身的通路不添加。
			cin >> x >> y;
			if (x != y)
			{
				vertex[x - 1].push_back(y);
				vertex[y - 1].push_back(x);
			}
		}
		
		cout << servicing_stations(vertex) << endl;
	}

	return 0;
}
