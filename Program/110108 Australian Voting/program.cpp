// Australian Voting （澳大利亚投票）
// PC/UVa IDs: 110108/10142, Popularity: B, Success rate: low Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-22
// UVa Run Time: 0.844s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
	
using namespace std;
	
void voting(int current, int ncandidates, vector < string > &candidate,
			vector < int > &vote, vector < vector < int > > &choice)
{
	// 统计首选候选人的选票数量。
	for (int c = 0; c < choice.size(); c++)
		vote[choice[c][0] - 1]++;
	
	int nchoices = choice.size();		// 选票总数。
	while (1)
	{
		bool tied = true;	// 候选人票数是否相同。
		int min = 1000;		// 用于寻找选票最少的候选人，最多 1000 张选票。
		int first = -1;
		for (int c = 0; c < ncandidates; c++)
		{
			// 如果有某人票数过半，则判定此人赢得选举，否则继续统计选票。
			if (vote[c] > (nchoices / 2))
			{
				cout << candidate[c] << endl;
				return;
			}
			
			// 得到未出局第一个候选人的票数。
			if (vote[c] >= 0 && first == -1)
				first = vote[c];
				
			// 若其他候选人与当前找到的未出局候选人票数不同，不是平局。
			if (first >=0 && vote[c] >= 0 && vote[c] != first)
				tied = false;
				
			// 查找选票最少的候选人。
			if (vote[c] >= 0 && vote[c] < min)
				min = vote[c];
		}
		
		// 检查所有候选人是否票数相同。
		if (tied)
		{
			for (int i = 0; i < ncandidates; i++)
				if (vote[i] >= 0)
					cout << candidate[i] << endl;
			return;
		}
		
		// 根据 min 值剔除选票最少的候选人及其在选票的位置。
		for (int i = 0; i < choice.size(); i++)
		{
			// 是否需要重新计算该张选票。
			bool recount = vote[choice[i][0] - 1] == min;
			for (int j = choice[i].size() - 1; j >= 0; j--)
				if (vote[choice[i][j] - 1] == min)
					choice[i].erase(choice[i].begin() + j);
			if (recount)
				vote[choice[i][0] - 1]++;
		}
		
		// 选票数为 -1 表示出局。		
		for (int n = 0; n < ncandidates; n++)
			if (vote[n] == min)
				vote[n] = -1;
	}
}
	
int main(int ac, char *av[])
{
	vector < string > candidate;		// 候选人。
	vector < int > vote;			// 候选人所得选票数。
	vector < vector < int > > choice;	// 记录选票。
	int cases;				// 测试数据组数。
	int current = 0;			// 当前处理的数据组数。
	int ncandidates;			// 每组数据候选人总数。
	string line;				// 读入数据用。
	
	// 读取测试数据组数。
	cin >> cases;
	
	// 读取各组数据。
	while (current < cases)
	{
		cin >> ncandidates;
	
		// 候选人个数是否大于0。
		if (ncandidates > 0)
		{
			cin.ignore();
			
			candidate.clear();
			candidate.resize(ncandidates);

			// 读取候选人列表。
			for (int i = 0; i < ncandidates; i++)
			{
				getline(cin, line);
				candidate[i] = line;
			}
	
			// 读取选票。
			choice.clear();
			while((getline(cin, line), line.length() > 0))
			{
				istringstream iss(line);
				vector < int > tmp;
				tmp.resize(ncandidates);
				for (int i = 0; i < ncandidates; i++)
					iss >> tmp[i];
				choice.push_back(tmp);
			}
			
			// 初始化候选人的选票数为0。
			vote.clear();
			vote.resize(ncandidates);
			fill(vote.begin(), vote.end(), 0);
			
			// 模拟选票统计过程。
			voting(current, ncandidates, candidate, vote, choice);
		}
	
		current++;
		
		// 处理输入的空行。
		if (current < cases && ncandidates > 0)
			cout << '\n';
	}
	
	return 0;
}
