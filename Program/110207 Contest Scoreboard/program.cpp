// Contest Scoreboard （比赛计分板）
// PC/UVa IDs: 110207/10258, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-23
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
	
using namespace std;
	
#define MAXSIZE 100
	
struct team
{
	bool submit;	// 该队是否至少有一次提交。
	int solved[9];	// 对9道题目的解决情况。
	int time[9];	// 每道题目的罚时。
	int problem;	// 解决的问题总数目。
	int penalty;	// 总的罚时。
	int index;	// 该队伍的编号。
};
	
// 比较函数，按照解决问题数、罚时、队伍编号相应排序。
bool cmp(team x, team y)
{
	// 解决问题较多的排在前面。
	if (x.problem != y.problem)
		return x.problem > y.problem;
	// 罚时较少的排前面。
	if (x.penalty != y.penalty)
		return x.penalty < y.penalty;
	// 前两者都相同，按队伍序号排序。
	return x.index < y.index;
}
	
// 统计各队解决问题数目和罚时。
void add(team t[])
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		// 至少有一次提交的队伍才予以计算。
		if (!t[i].submit)
			continue;
			
		for (int j = 0; j < 9; j++)
			if (t[i].solved[j])
			{
				t[i].penalty += t[i].time[j];
				t[i].problem++;
			}
	}
}
	
// 初始化结构数组。
void init(team t[])
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		t[i].submit = false;
		t[i].index = (i + 1);
		t[i].penalty = 0;
		t[i].problem = 0;
		memset(t[i].solved, 0, sizeof(t[i].solved));
		memset(t[i].time, 0, sizeof(t[i].time));
	}
}
	
int main(int ac, char * av[])
{
	string line;
	team t[MAXSIZE];
	int cases;
	istringstream iss;
	
	cin >> cases;
	cin.get();
	getline(cin, line);
	
	for (int i = 0; i < cases; i++)
	{
		init(t);
		
		while(getline(cin, line), line.length() > 0)
		{
			// c 为队伍编号，p 为题目编号，n 为提交时间，r 为评测结果。
			int c, p, n;
			char r;
			iss.clear();
			iss.str(line);
			cin >> c >> p >> n >> r;
			
			// 有至少一次提交。
			t[c - 1].submit = true;
			
			switch(r)
			{
				case 'C':
					// 对未正确提交的题目才予计算解题数和计罚时。
					if (!t[c - 1].solved[p - 1])
					{
						t[c - 1].solved[p - 1] = 1;
						t[c - 1].time[p - 1] += n;
					}
					break;
				case 'I':
					// 对未正确提交的才计算罚时。
					if (!t[c - 1].solved[p - 1])
						t[c - 1].time[p - 1] += 20;
					break;
				// 其他情况忽略。
				default:
					break;
			}
		}
		
		// 统计各队解题数目和罚时。
		add(t);
		
		// 按题意排序。
		sort(t, t + MAXSIZE, cmp);
		
		// 输出。
		for (int j = 0; j < MAXSIZE; j++)
			if (t[j].submit)
				cout << t[j].index << " " << t[j].problem;
				cout << " " << t[j].penalty << endl;
		
		// 两组测试数据有一个空格。
		if (i < (cases - 1))
			cout << endl;
	}
	
	return 0;
}
