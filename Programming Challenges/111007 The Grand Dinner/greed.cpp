// The Grand Dinner （丰盛的晚餐）
// PC/UVa IDs: 111007/10249, Popularity: C, Success rate: high Level: 4
// Verdict: Accepted
// Submission Date: 2011-10-08
// UVa Run Time: 0.092s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [Problem Description]
// Each team participating in this year’s ACM World Finals is expected to attend
// the grand banquet arranged for after the award ceremony. To maximize the amount
// of interaction between members of different teams, no two members of the same
// team will be allowed to sit at the same table.
//
// Given the number of members on each team (including contestants, coaches,
// reserves, and guests) and the seating capacity of each table, determine whether
// it is possible for the teams to sit as described. If such an arrangement is
// possible, output one such seating assignment. If there are multiple possible
// arrangements, any one is acceptable.
//
// [Input]
// The input file may contain multiple test cases. The first line of each test
// case contains two integers, 1 ≤ M ≤ 70 and 1 ≤ N ≤ 50, denoting the number of
// teams and tables, respectively. The second line of each test case contains M
// integers, where the ith integer mi indicates the number of members of team i.
// There are at most 100 members of any team. The third line contains N integers,
// where the jth integer nj , 2 ≤ nj ≤ 100, indicates the seating capacity of
// table j.
//
// A test case containing two zeros for M and N terminates the input.

// [Output]
// For each test case, print a line containing either 1 or 0, denoting whether
// there exists a valid seating arrangement of the team members. In case of a
// successful arrangement, print M additional lines where the ith line contains
// a table number (from 1 to N ) for each of the members of team i.
//
// [Sample Input]
// 4 5
// 4 5 3 5
// 3 5 2 6 4
// 4 5
// 4 5 3 5
// 3 5 2 6 3
// 0
//
// [Sample Output]
// 1
// 1 2 4 5
// 1 2 3 4 5
// 2 4 5
// 1 2 3 4 5
//
// [解题方法]
// 此题有两种解法，一种是简单的贪心法，一种是较复杂的图论网络最大流法。
//
// 贪心法采用如下策略：先将人数按降序排列，从编号为 1 的桌子开始安排座位，安排完后，
// 安排下一队。若能安排完所有人，则输出 1 和安排方案，若不能安排则输出 0，其中明显不
// 能安排的，如某队人数大于桌子数，参赛队伍数或桌子数为 0 等特殊情况，可以预先处理（
// 虽然可以得到正确答案，但是贪心法的正确性如何证明？可以通过网络最大流来证明吗？）。
//
// 网络流解法：源点 source 和每支参赛队伍之间边的容量为参赛队伍人数，每支队伍到桌子之
// 间边的容量为1，每张桌子到汇点 sink 边的容量为桌子的座位数，然后使用网络流算法求最
// 大流，如果最大流等于参赛队伍总人数，则满足条件，输出方案，否则不满足条件，输出 0。
// 可以使用宽度优先遍历的 Ford-Fullerson增广路方法，又名 Edmonds-Karp 算法，算法效
// 率为 O（V*E*E），后续博文会给出。

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAXTEAMS 70		    // 最大参赛队伍数。
#define MAXTABLES 50		// 桌子最大数。

#define UNSOLVABLE 0
#define SOLVABLE 1

struct team
{
	int number;		        // 参赛队伍编号。
	int nmembers;		    // 参赛队伍人数。
};

// 比较函数，参数队伍人数多的排前面。
bool cmp(team x, team y)
{
	return x.nmembers > y.nmembers;
}

int main(int ac, char *av[])
{
	team teams[MAXTEAMS];		    // 各参赛队编号，人数。
	int capacity[MAXTABLES];	    // 桌子的座位数。
	int nteams, ntables, ntemp;	    // 队伍数，桌子数，总人数。
	bool seat[MAXTABLES][MAXTEAMS];	// 记录座位安排方案。

	while (cin >> nteams >> ntables, nteams || ntables)
	{
		// 读入参赛队人数并找参赛队的最大人数。
		int maxMembers = 0;
		for (int i = 0; i < nteams; i++)
		{
			cin >> ntemp;
			if (maxMembers < ntemp)
				maxMembers = ntemp;
			teams[i].number = i;
			teams[i].nmembers = ntemp;
		}

		// 读入桌子座位数量。
		for (int i = 0; i < ntables; i++)
			cin >> capacity[i];

		// 若参赛队伍数为 0，则直接输出存在，但是不用输出具体方案，因为所有桌子无人坐。
		if (nteams == 0)
		{
			cout << SOLVABLE << "\n";
			continue;
		}

		// 若桌子数为 0 或者参赛队伍中某队人数超过桌子数，则无法安排。
		if (ntables == 0 || maxMembers > ntables)
		{
			cout << UNSOLVABLE << "\n";
			continue;
		}

		// 将参赛队伍按人数多少从大到小排列。
		sort(teams, teams + nteams, cmp);

		// 贪心法安排座位，若某队无法安排，则无安排方案。
		bool sitting = true;
		memset(seat, false, sizeof(seat));
		for (int i = 0; i < nteams; i++)
		{
			ntemp = teams[i].nmembers;
			for (int j = 0; j < ntables && ntemp; j++)
				if (capacity[j])
				{
					ntemp--;
					capacity[j]--;
					seat[j][teams[i].number] = true;
				}

			// 若经过一轮安排后，剩余人数不为 0 则无法安排。
			if (ntemp)
			{
				sitting = false;
				break;
			}
		}

		cout << (sitting ? SOLVABLE : UNSOLVABLE) << "\n";
		if (sitting)
		{
			for (int i = 0; i < nteams; i++)
			{
				int blank = 0;
				for (int j = 0; j < ntables; j++)
					if (seat[j][i])
						cout << (blank++ ? " " : "") <<
							(j + 1);
				cout << "\n";
			}
		}
	}

	return 0;
}
