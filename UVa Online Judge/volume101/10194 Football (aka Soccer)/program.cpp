// Football (aka Soccer) （足球）
// PC/UVa IDs: 110408/10194, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-27
// UVa Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
#define TEAM_SIZE 30
	
// 定义一个结构保存队伍的相关信息。
struct team
{
	string name;	// 队伍名称。
	int points;	// 得分。
	int wins;	// 赢的场次。
	int ties;	// 平局的场次。
	int losses;	// 输的场次。
	int goals_scored;	// 进球数。
	int goals_lossed;	// 失球数。
	int games;		// 参加的比赛场次。实际上等于 wins + ties + losses。
};
	
// 根据各种条件排序。
bool cmp(team x, team y)
{
	if (x.points != y.points)
		return x.points > y.points;
		
	if (x.wins != y.wins)
		return x.wins > y.wins;
		
	if ((x.goals_scored - x.goals_lossed) != (y.goals_scored - y.goals_lossed))
		return (x.goals_scored - x.goals_lossed) > (y.goals_scored - y.goals_lossed);
		
	if (x.goals_scored != y.goals_scored)
		return x.goals_scored > y.goals_scored;
		
	if (x.games != y.games)
		return x.games < y.games;
		
	for (int i = 0; i < min(x.name.length(), y.name.length()); i++)
	{
		if (isalpha(x.name.at(i)) && isalpha(y.name.at(i)))
		{
			if (x.name.at(i) != y.name.at(i))
				return tolower(x.name.at(i)) < tolower(y.name.at(i));
		}
		else
			return x.name.at(i) < y.name.at(i);
	}
	
	return x.name.length() < y.name.length();
}
	
int find_index(string name, team teams[], int capacity)
{
	for (int i = 0; i < capacity; i++)
		if (teams[i].name == name)
			return i;
	return -1;
}
	
void init(team teams[])
{
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		teams[i].name = "";
		teams[i].points = 0;
		teams[i].wins = 0;
		teams[i].ties = 0;
		teams[i].losses = 0;
		teams[i].goals_scored = 0;
		teams[i].goals_lossed = 0;
		teams[i].games = 0;		
	}
}
	
int main(int ac, char *av[])
{
	int cases, capacity;
	team teams[TEAM_SIZE];
	string line;
	
	cin >> cases;
	cin.ignore();
	
	while (cases--)
	{
		// 初始化结构数组。
		init(teams);
		
		// 读入竞赛名称并回显。
		getline(cin, line);
		cout << line << endl;
		
		// 读入队名。
		int number;
		cin >> number;
		cin.ignore();
		capacity = 0;
		while (number--)
			getline(cin, teams[capacity++].name);
		
		// 读入并解析竞赛数据。
		cin >> number;
		cin.ignore();
		while (number--)
		{
			getline(cin, line);
			
			int begin = line.find_first_of('#');
			int end = line.find_last_of('#');
			
			string namex = line.substr(0, begin);
			string namey = line.substr(end + 1);
			string result = line.substr(begin + 1, end - begin - 1);
			
			int middle = result.find_first_of('@', 0);
			int goalsx = atoi(result.substr(0, middle).data());
			int goalsy = atoi(result.substr(middle + 1).data());

			int indexx = find_index(namex, teams, capacity);
			int indexy = find_index(namey, teams, capacity);
			
			teams[indexx].goals_scored += goalsx;
			teams[indexy].goals_scored += goalsy;
			
			teams[indexx].goals_lossed += goalsy;
			teams[indexy].goals_lossed += goalsx;
			
			teams[indexx].wins += ((goalsx > goalsy) ? 1 : 0);
			teams[indexy].wins += ((goalsy > goalsx) ? 1 : 0);
			
			teams[indexx].ties += ((goalsx == goalsy) ? 1 : 0);
			teams[indexy].ties += ((goalsx == goalsy) ? 1 : 0);
			
			teams[indexx].losses += ((goalsx < goalsy) ? 1 : 0);
			teams[indexy].losses += ((goalsy < goalsx) ? 1 : 0);
			
			teams[indexx].games += 1;
			teams[indexy].games += 1;
			
			if (goalsx == goalsy)
			{
				teams[indexx].points += 1;
				teams[indexy].points += 1;
			}
			else
			{
				teams[indexx].points += ((goalsx > goalsy) ? 3 : 0);
				teams[indexy].points += ((goalsy > goalsx) ? 3 : 0);
			}
		}
	
		// 排序。
		sort(teams, teams + capacity, cmp);
		
		// 输出。
		for (int i = 0; i < capacity; i++)
		{
			cout << (i + 1) << ") " << teams[i].name << " ";
			cout << teams[i].points << "p, ";
			cout << teams[i].games << "g (";
			cout << teams[i].wins << "-";
			cout << teams[i].ties << "-";
			cout << teams[i].losses << "), ";
			cout << (teams[i].goals_scored - teams[i].goals_lossed) << "gd (";
			cout << teams[i].goals_scored << "-";
			cout << teams[i].goals_lossed << ")" << endl;
		}
		
		if (cases)
			cout << endl;
	}
	
	return 0;
}
