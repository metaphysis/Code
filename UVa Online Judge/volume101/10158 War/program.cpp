// War （战争）
// PC/UVa IDs: 111005/10158, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-07
// UVa Run Time: 0.272s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// 一场战争在 A 国和 B 国之间开始了。作为一位 C 国的好公民，你决定为你的国家秘密的参加 A 国与 B
// 国之间的和谈。和谈中还有 n 个人，但你不知道他们分别属于哪个国家。你可以看到他们互相交谈，并能通
// 过观察双方在一对一交谈时的表现猜测他们是敌人还是朋友。
//
// 你的国家需要知道某些特定的两个人之间的关系：到底是属于同一国，还是互相敌对，因此需要你在和谈期间
// 接收政府传来的问题，并根据你当前的观察做出回答。
//
// 正式的来说，考虑一个可以进行如下操作的黑盒：
//
//      setFriends（x，y）   x 和 y 属于同一国家
//      setEnemies（x，y）   x 和 y 属于不同国家
//      areFriends（x，y）   仅当你确信 x 和 y 为朋友时返回 true
//      areEnemies（x，y）   仅当你确信 x 和 y 为敌人时返回 false
//
// 若前两种操作与你现有的结论相冲突，你应该报错。“朋友” 关系（符号为 ～）和 “敌对” 关系（符号为 *）
// 具有如下性质：
//
//      ～ 是等价关系，即：
//      1. 若 x ～ y 且 y ~ z，则 x ～ z（朋友的朋友也是朋友）
//      2. 若 x ～ y，则 y ～ x（朋友是相互的）
//      3. x ～ x（每个人都是他自己的朋友）
//
//      * 满足对称性和反自反性：
//      1. 若 x * y，则 y * x（敌对是相互的）
//      2. x * x 总为假（没有人和自己敌对）
//      3. 若 x * y，且 y * z，则 x ～ z（敌人的敌人是朋友）
//      4. 若 x ～ y，且 y * z，则 x * z（敌人的朋友是敌人）
//
// 操作 setFriends（x，y） 和 setEnemies（x，y） 不能破坏上述性质。
//
// [输入]
// 输入每一行包含一个整数 n，表示人数。接下来第一行有三个数，c x y，其中 c 为操作编号。
//
//      c = 1，setFriends
//      c = 2，setEnemies
//      c = 3，areFriends
//      c = 4，areEnemies
//
// x 和 y 分别为操作的参数，它们都是区间 [0，n） 内的整数，表示两个不同的人。最后一行为 0 0 0。
//
// 输入中所有整数由至少一个空格或换行符隔开。最多可有 10 000 个人，但操作总数没有限制。
//
// [输出]
// 对于每个 areFriends 和 areEnemies 操作，输出 “0” （表示假）或者 “1” （表示真）。对于每个
// 与当前结论冲突的 setFriends 或 setEnemies 操作，你的程序应当输出 “-1”，但该指令不应对后续
// 操作的执行产生任何影响。成功的 setFriends 或 setEnemies 不产生输出。
//
// 输出中的相邻整数间应换行。
//
// [样例输入]
// 10
// 1 0 1
// 1 1 2
// 2 0 5
// 3 0 2
// 3 8 9
// 4 1 5
// 4 1 2
// 4 8 9
// 1 8 9
// 1 5 2
// 3 5 2
// 0 0 0
//
// [样例输出]
// 1
// 0
// 1
// 0
// 0
// -1
// 0
//
// [解题方法]
// 此题可以应用不相交集合数据结构（并查集）来解决。数组 root 的元素从 [0，N - 1] 存放的是国家
// [0，N - 1] 的朋友，元素 [N，2 * N - 1] 存放的是国家 [0，N - 1] 的敌人，x 和 x + n
// 均标记 x，x + n 的作用是放置在敌对国家下的副本以便记录敌对关系。

#include <iostream>

using namespace std;

#define MAXV 20000

#define SET_FRIENDS 1
#define SET_ENEMIES 2
#define ARE_FRIENDS 3
#define ARE_ENEMIES 4

#define NO 0
#define YES 1
#define ERROR (-1)

int root[MAXV], n;

// 查找操作。
int findSet(int x)
{
	return (root[x] == x) ? x : (root[x] = findSet(root[x]));
}

// 初始化集合。
void makeSet()
{
	for (int i = 0; i < n * 2; i++) root[i] = i;
}

// 设置朋友关系。
void setFriends(int x, int y)
{
	int xRoot = findSet(x);
	int yRoot = findSet(y);
	int xEnemyRoot = findSet(x + n);
	int yEnemyRoot = findSet(y + n);

	if (xRoot == yEnemyRoot || yRoot == xEnemyRoot)
		cout << ERROR << endl;
	else
	{
		// 朋友的朋友是朋友。
		root[yRoot] = xRoot;
		// 朋友的敌人是敌人。
		root[yEnemyRoot] = xEnemyRoot;
	}
}

// 设置敌对关系。
void setEnemies(int x, int y)
{
	int xRoot = findSet(x);
	int yRoot = findSet(y);
	int xEnemyRoot = findSet(x + n);
	int yEnemyRoot = findSet(y + n);

	if (xRoot == yRoot)
		cout << ERROR << endl;
	else
	{
		// 敌对是相互的。
		root[xEnemyRoot] = yRoot;
		root[yEnemyRoot] = xRoot;
	}
}

// 判读朋友关系。
void areFriends(int x, int y)
{
	cout << (findSet(x) == findSet(y) ? YES : NO) << endl;
}

// 判断敌对关系。
void areEnemies(int x, int y)
{
	int xRoot = findSet(x);
	int yRoot = findSet(y);
	int xEnemyRoot = findSet(x + n);
	int yEnemyRoot = findSet(y + n);

	if (xRoot == yEnemyRoot || yRoot == xEnemyRoot)
		cout << YES << endl;
	else
		cout << NO << endl;
}

int main(int ac, char *av[])
{
	int n, c, x, y;

	cin >> n;

	makeSet();

	while (cin >> c >> x >> y, c || x || y)
	{
		switch (c)
		{
			case SET_FRIENDS:
				setFriends(x, y);
				break;

			case SET_ENEMIES:
				setEnemies(x, y);
				break;

			case ARE_FRIENDS:
				areFriends(x, y);
				break;

			case ARE_ENEMIES:
				areEnemies(x, y);
				break;
		}
	}

	return 0;
}
