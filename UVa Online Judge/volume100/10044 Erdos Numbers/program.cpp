// Erdos Numbers （Erdos 数）
// PC/UVa IDs: 110206/10044, Popularity: B, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2011-05-27
// UVa Run Time: 0.680s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
struct erdos_number
{
	string name;	// 作者姓名
	int number;	// 作者的 Erdos 数。
};
	
vector < erdos_number > erdos;	// 记录结果集的一个类型为 erdos_number 的动态数组。
vector < string > author;	// 记录一篇论文中出现的作者姓名。
map < string, int > exist;	// 查询指定作者是否在结果集中的字典，用于提高程序性能。
vector < bool > processed;
	
// 从字典中找到姓名为 name 的作者的序号。如果找不到，则返回-1。
int find_index(string &name)
{
	map < string, int >::iterator it = exist.find(name);
	if (it != exist.end())
		return (*it).second;
	return -1;
}
	
// 从论文的作者部分提取每位作者的姓名。
// 由于作者部分格式为：[作者名][,][空格][作者姓首字母][.][,][空格]，故可
// 根据该格式截取。
vector < string > extract_name(string &line)
{
	vector < string > list;
	string::size_type begin(0);
	string::size_type end = line.find(".,", begin);
	
	while (end != string::npos)
	{
		list.push_back(line.substr(begin, end - begin + 1));
		
		begin = end + 3;
		end = line.find(".,", begin);
	}
	
	if (begin < (line.length() - 1))
		list.push_back(line.substr(begin));

	return list;
}
	
// 将作者按指定 Erdos 数添加到结果集中。作者列表 author 中的每个作者其 Erdos 数不
// 高于 （number + 1）。
void set_erdos_number(string &author, int number)
{
	// 从论文的作者部分提取出每个作者的姓名。
	vector <string> list = extract_name(author);
	
	// 逐个将尚未添加到结果集中的作者添加到结果集中。
	// 在结果集中已存在的作者不需添加，因为是在之前的
	// 扫描中已经添加了，其 Erdos 数要小。
	for (int i = 0; i < list.size(); i++)
		if (find_index(list[i]) < 0)
		{
			erdos_number tmp;
			tmp.name = list[i];
			tmp.number = (number + 1);
			erdos.push_back(tmp);
			// 将值对（作者姓名，数组序号）添加到字典中，方便查询。
			exist.insert(make_pair< string, int >(list[i], (erdos.size() - 1)));
		}
}
	
// 计算 Erdos 数。
void cal_erdos_number()
{
	// 由于是用动态数组实现 BFS，故需要两个指针来指示一次搜索所得到的结果
	// 集的开始位置和结束位置。第一次的结果已经预先添加到了 erdos 数组中。
	int begin = 0, end = 0;
	erdos.clear();
	erdos_number tmp;
	tmp.name = "Erdos, P.";
	tmp.number = 0;
	erdos.push_back(tmp);
	
	// 将数组 erdos 中的元素以 name 为 Key，元素序号为 mapped value，建立
	// 一个字典来减少查询某位作者是否在结果集中的时间。
	exist.clear();
	exist.insert(make_pair< string, int >("Erdos, P.", 0));
	
	// 一个 bool 类型的向量，用来表示某篇论文是否已经处理并添加到了结果集中，并将其初始化。
	processed.clear();
	processed.resize(author.size());
	fill(processed.begin(), processed.end(), false); 
	
	// 处理论文数据库直到无任何作者可添加到结果集中。
	while (1)
	{
		// 对一篇未标记处理的论文进行处理。
		for (int i = 0; i < author.size(); i++)
		{
			if (processed[i])
				continue;
			
			for (int j = begin; j <= end; j++)
			{
				// 若某篇论文中包含具有 Erdos 数为 erdos[j].number 的
				// 作者 erdos[j].name，该篇论文中的所有作者的 Erdos 数
				// 不会高于 （erdos[j].number + 1）。
				if (author[i].find(erdos[j].name) != string::npos)
				{
					// 设置Erdos数。
					set_erdos_number(author[i], erdos[j].number);
					processed[i] = true;
					break;
				}
			}
		}
		
		// 假如搜索一次，无作者添加到结果集中，结束扫描。否则更新起始和结束标记。
		if (end == (erdos.size() - 1))
			return;
		else
		{
			begin = end + 1;
			end = erdos.size() - 1;
		}
	}
}
	
int main(int ac, char *av[])
{
	string line;
	int scenario;	// 测试数据组数。
	int p;		// 单组测试数据中论文篇数。
	int n;		// 需要输出 Erdos 数的作者个数。
	
	// 读入测试数据组数。
	cin >> scenario;
	
	// 循环读入并处理每组测试数据。
	for (int i = 1; i <= scenario; i++)
	{
		cin >> p >> n;
		cin.ignore();
	
		// 读取论文数据库，将作者部分截取添加到动态数组中。
		author.clear();
		for (int j = 0; j < p; j++)
		{
			getline(cin, line);
			author.push_back(line.substr(0, line.find_first_of(':')));
		}
		
		// 使用 BFS 算法得到结果集。
		cal_erdos_number();
		
		// 根据结果集输出。	
		cout << "Scenario " << i << endl;
		for (int j = 0; j < n; j++)
		{
			// 读入需要显示 Erdos 的作者姓名并回显。
			getline(cin, line);
			cout << line << " ";
			
			// 在结果集中寻找相应作者姓名，若能找到，输出其 Erods 数，未找到，
			// 则其 Erdos 为无穷大。
			int pos = find_index(line);
			if (pos >= 0)
				cout << erdos[pos].number << endl;
			else
				cout << "infinity" << endl;
		}
	}
	
	return 0;
}
