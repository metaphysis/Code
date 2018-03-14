// Ferry Loading （渡船装载）
// PC/UVa IDs: 111106/10261, Popularity: B, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-15
// UVa Run Time: 0.536s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 使用暴力法在这里显然是行不通的（如果测试数据弱的话，可以一试），但是本题车辆可达两百辆之多，指
// 数级的计算时间够你受的（但是很有意思，使用回溯法竟然可以勉强通过，可见测试数据并不是很强，若
// 使用回溯法，当车辆的长度小于某一车道的空余空间时，可以放置于该条车道，继续回溯，不过使用这种方法
// 一定要有效的记录已经访问过的状态，要不然是无法在规定时间内 AC 的，这可以通过使用 STL 中的 set
// 来实现）。
//
// 贪心法在这里也不适用，如果使用总是把车辆放到空间比较大的车道里的策略的话，反例如下：
//
// 50
// 2000
// 3000
// 1000
// 1000
// 1500
// 700
// 800
//
// 若先放置在车道 A，放置不下放置在另外一条车道 B，后续车辆如果车身长度小于车道 A 的空余长度，则
// 继续放置在 A 车道，反例如下：
//
// 6
// 200
// 200
// 400
// 400
//
// 动态规划行不行？题目要求用两个固定长度的车道尽可能的装载更多的车辆，车辆的长度和不能超过车道的
// 长度，每个车道的车辆长度和都是一个整数。设车道长为 length，车辆共有 n 辆，则要求最大的登船数
// 量 j（0 <= j <= n），使得 j 辆车能放置到两条长为 length 的车道内。假设当前已登船的车辆数量
// 已经达到了最大数量 j，前 j 辆车的长度和为 sum[j]，左侧车道内车辆长度和为 l，若 sum[j] == l，
// 则表明这 j 辆车可以全部放置在一个车道里，否则长度为 sum[j] - l 的车辆必须放置在另一个车道内。
// 那么可以设立一个数组记录当登船了 i 辆车辆后，左侧车辆的长度为 m，记为 memo[i][m]，右侧的车辆
// 长度为必定为 sum[i] - m，记为 memo[i][sum[i] - m]，若都能放置，则都为 true，初始条件为
// memo[0][0] = true，从下往上 DP 求 memo[i][length] = true 时最大可能的 i。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 201
#define MAXL 100001
#define EMPTY (-1)

// 车道状态类，current 表示当前已经登船的车辆数，left 表示左侧车道剩余空间，right 表示右侧车道
// 剩余空间数。
class state
{
public:
	int current, left, right;
	state() {}
	state(int incurrent, int inleft, int inright)
	{ current = incurrent; left = inleft; right = inright; }
	~state() { }

	bool operator<(const state & other) const
	{
		return (current == other.current ?
			(left == other.left ? right < other.right :
			left < other.left) : current < other.current);
	}

	bool operator==(const state & other) const
	{
		return (current == other.current && left == other.left
			&& right == other.right);
	}
};

set < state > cache;
bool port[MAXN + 1], answer[MAXN + 1];
int cars[MAXN + 1], nCars, maxCars;

// 回溯法解题，c 表示当前需要登船的车辆编号，left 表示左侧车道剩余的空间，right 表示右侧车道剩余
// 的空间。
void backtrack(int current, int left, int right)
{
	// 若当前缓存不存在该状态，则将该状态放入缓存。
	if (cache.count(state(current, left, right)) > 0)
		return;
	cache.insert(state(current, left, right));

	// 取第 c 辆车的车身长度。若当前全部车辆都已经登船，则表明车道可容纳所有车辆，若当前车
	// 辆的长度大于两个车道的剩余空间，则比较当前登船的数量是否大于当前发现的最大登船车辆数。
	int carLength = cars[current];
	if (current > nCars || carLength > max(left, right))
	{
		if ((current - 1) > maxCars)
		{
			maxCars = current - 1;
			memcpy(answer, port, sizeof(port));
		}

		return;
	}

	// 回溯。
	if (carLength <= left)
	{
		port[current] = true;
		backtrack(current + 1, left - carLength, right);
	}

	if (carLength <= right)
	{
		port[current] = false;
		backtrack(current + 1, left, right - carLength);
	}
}

void solve_by_backtrack(void)
{
	int cases, ferryLength, carLength;
	bool printBoredBlankLine = false;

	cin >> cases;
	while (cases--)
	{
		if (printBoredBlankLine)
			cout << endl;
		else
			printBoredBlankLine = true;

		cin >> ferryLength;
		ferryLength *= 100;

		nCars = 1;
		while (cin >> carLength, carLength)
		{
			if (nCars < MAXN)
				cars[nCars++] = carLength;
		}
		nCars--;

		maxCars = 0;
		cache.clear();
		backtrack(1, ferryLength, ferryLength);

		cout << maxCars << endl;
		for (int i = 1; i <= maxCars; i++)
			cout << (answer[i] ? "port" : "starboard") << endl;
	}
}

bool memo[MAXN + 1][MAXL + 1];
int choice[MAXN + 1][MAXL + 1];
int sumLength[MAXN + 1];

void solve_by_dynamic_programming(void)
{
	int cases, ferryLength, carLength;
	bool printBoredBlankLine = false;
	
	cin >> cases;
	while (cases--)
	{
		if (printBoredBlankLine)
			cout << endl;
		else
			printBoredBlankLine = true;
			
		cin >> ferryLength;
		ferryLength *= 100;
		
		nCars = 1;
		sumLength[0] = 0;
		while (cin >> carLength, carLength)
		{
			if (nCars < MAXN)
			{
				cars[nCars] = carLength;
				sumLength[nCars] = sumLength[nCars - 1] + carLength;
				nCars++;
			}
		}
		nCars--;

		pair < int, int > longest;

		memset(memo, false, sizeof(memo));
		memset(choice, EMPTY, sizeof(choice));

		memo[0][0] = true;
		for (int i = 0; i < nCars; i++)
			for (int j = 0; j <= ferryLength; j++)
				if (memo[i][j])
				{
					if ((j + cars[i + 1]) <= ferryLength)
					{
						memo[i + 1][j + cars[i + 1]] = true;
						choice[i + 1][j + cars[i + 1]] = 1;
						longest = make_pair(i + 1, j + cars[i + 1]);
					}

					if ((sumLength[i] - j + cars[i + 1]) <= ferryLength)
					{
						memo[i + 1][j] = true;
						choice[i + 1][j] = 0;
						longest = make_pair(i + 1, j);
					}
				}

		cout << longest.first << endl;
		string solution;
		for (int i = longest.first, j = longest.second; i > 0 && choice[i][j] != EMPTY; i--)
		{
			solution = (choice[i][j] ? "port\n" : "starboard\n" ) + solution;
			if (choice[i][j])
				j -= cars[i];
		}
		cout << solution;
	}
}

int main(int ac, char *av[])
{
	// 回溯法，差强人意，UVa RT：2.404s。
	// solve_by_backtrack();
	
	// 动态规划，UVa RT：0.536s。
	solve_by_dynamic_programming();

	return 0;
}
