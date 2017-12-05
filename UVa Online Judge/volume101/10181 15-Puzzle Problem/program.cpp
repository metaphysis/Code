// 15-Puzzle Problem （15 数码）
// PC/UVa IDs: 110802/10181, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted 
// Submission Date: 2011-06-22
// UVa Run Time: 0.320s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// You can fool some of the people all of the time, and all of the people
// some of the time, but you can not fool all of the people all of the time.
//      Abraham Lincoln, 16th president of US (1809 - 1865).
//
// 关于给定一个局面判断是否有解的方法可以参考 http://mathworld.wolfram.com/15Puzzle.html 。
// 设 e 表示空滑块所在的行，n 为在当前滑块之后出现小于当前滑块数值的滑块数目，N 为：
//
//       15        15
// N =   ∑  ni =   ∑  ni
//     i = 1     i = 2
//
// 如果 N + e 为偶数，则当前局面有解，否则无解。如以下局面：
//
// 13 10 11 6
// 5  7  4  8
// 1  12 14 9 
// 3  15 2  0 
//
// 则有小于 13 并在之后出现滑块的数目为 12，小于 10 并在之后出现的滑块数目为 9，类似的，可以得到
// 其他滑块的 n 值分别为 9（11），5（6），4（5），4（7），3（4），3（8），0（1），3（12），
// 3（14），2（9），1（3），1（15），0（2）。所有 n 值的和为 N = 59，空滑块在第 4 行，故 e =
// 4，则 N + e = 63，为奇数，则以上局面不可解。
//
// [深度优先搜索解题（Depth-First Search）]
// [参考 George T. Heineman, Gary Pollice, and Stanley Selkow, ALGORITHMS In a 
// Nutshell, O‘Reilly Media, Inc. 2008]
//
// 深度优先搜索不断的向前寻找可行状态，试图一次找到通向目标状态的道路，它并不会两次访问一个状态，
// 由于某些搜索树包含大量的棋面状态，因此深度优先搜索只是在最大搜索深度固定的情况下才具有可行性，
// 深度优先搜索维护一个栈，保存未访问过的棋面状态。在每次迭代时，深度优先搜索从栈中弹出一个未访问
// 的棋面状态，然后从这个棋面状态开始扩展，根据走法计算其后继棋面状态。如果达到了目标棋面状态，搜
// 索终止。如果没有达到的话，任何在闭合集中后继棋面状态都会被抛弃。剩余的未访问棋面状态被压入栈中，
// 然后继续搜索。伪代码如下：
//
// search (initial, goal)
//      if (initial = goal) then return "Solution"
//      initial.depth = 0
//      open = new Stack
//      closed = new Set
//      insert(open, copy(initial))
//      while (open is not empty) do
//              n = pop(open)
//              insert(closed, n)
//              foreach valid move m at n do
//                      next = state when playing m at n
//                      if (closed doesn't contain next) then
//                              next.depth = n.depth + 1
//                              if (next = goal) then return "Solution"
//                              if (next.depth < maxDepth) then
//                                      insert(open, next)
//      return "No Solution"
// end
//
// 深度优先搜索是属于盲目的搜索，题目给定条件是所有可解的局面都可在 45 步之内解决，解的长度不应超
// 过 50 步，则设最大搜索深度为 50。此算法关键是如何高效地得知一个棋面状态是否已经访问，因为整个
// 算法的大部分时间都会用于在闭合集中搜索一个元素是否存在的过程中，如果能够为每一个棋面状态生成一
// 个唯一键值，换句话说，如果两个棋面状态有着相同的键值，那么这两个棋面状态是等价的，等价的意思也
// 包括其他的情况，比如对称。另外搜索深度的设定在一定程度上影响是否能得到解，因为某些情况下，一个
// 状态离最终解局面只差几步的情况下，由于达到了最大搜索深度而被放到了闭合集中，则不可能再次对此棋
// 面状态进行扩展了，即使之后深度优先搜索在较早的等级访问到这个状态，它也不会继续搜索，因为这个状
// 态已经在闭合集中。
//
// 考虑第一个问题，如何高效判断两个棋面的状态是等价的。将棋盘的数值考虑为一个 16 进制的系统，则可
// 以将每个滑块作为一个数位，按从左到右，从上至下的顺序来将滑块组成一个 16 进制数，则先前给出的棋
// 面状态可以表示成这样一个整数：
//
// 13 * 16^15 + 10 * 16^14 + 11 * 16^13 + 6 * 16^12 + 5 * 16^11 + 7 * 16^10 + 
// 4 * 16^9 + 8 * 16^8 + 1 * 16^7 + 12 * 16^6 + 14 * 16^5 + 9 * 16^4 + 
// 3 * 16^3 + 15 * 16^2 + 2 * 16^1 + 0 * 16^1 = DAB657481CE93F20(hex) = 
// 15759879913263939360(dec)
//
// 则可以通过将棋面表示成一个整数来唯一表示该种局面状态。
//
// [广度优先搜索解题（Breadth-First Search）]
//
// 广度优先搜索尝试在不重复访问状态的情况下，寻找一条最短路径。广度优先搜索保证如果存在一条到目标
// 状态的路径，那么找到的肯定是最短路径。深度优先搜索和广度优先搜索的唯一不同就是广度优先搜索使用
// 队列来保存开放集，而深度优先搜索使用栈。每次迭代时，广度优先搜索从队列头拿出一个未访问的状态，
// 然后从这个状态开始，计算后继状态，如果达到了目标状态，那么搜索结束，任何已经在闭合集中的后继状
// 态会被抛弃。剩余的未访问棋面状态将会放入开放集队列尾部，然后继续搜索。伪代码如下：
//
// search (initial, goal)
//      if (initial = goal) then return "Solution"
//      open = new Queue
//      closed = new Set
//      insert(open, copy(initial))
//      while (open is not empty) do
//              n = head(open)
//              insert(closed, n)
//              foreach valid move m at n do
//                      next = state when playing m at n
//                      if (closed doesn't contain next) then
//                              if (next = goal) then return "Solution"
//                              insert(open, next)
//      return "No Solution"
// end
//
// [A* 搜索解题]
// [参考 George T. Heineman, Gary Pollice, and Stanley Selkow, ALGORITHMS In a 
// Nutshell, O‘Reilly Media, Inc. 2008]
//
// 广度优先搜索能够找到一个最优解（如果存在），但是可能需要访问大量的节点，它并没有尝试对候选走法
// 进行排序，相反，深度优先搜索是尽可能地向前探测路径，不过，深度优先搜索的搜索深度必须得到限制，
// 要不然它很可能会在没有任何结果的路径上花费大量的时间。A* 搜索在搜索时能够利用启发式信息，智能
// 地调整搜索策略。A*搜索是一种迭代的有序搜索，它维护一个棋面状态的开放集合。在每次迭代时，A* 搜
// 索使用一个评价函数 f*（n）评价开放集合中的所有棋面状态，选择最小的棋面状态。定义：
//
// f*（n） = g*（n） + h*（n）
// g*（n） 估算从初始状态到状态 n 的最短走法序列。
// h*（n） 估算从状态 n 到目标状态的最短走法序列。
// f*（n） 估算从初始状态开始，经过状态 n，到达目标状态的最短走法序列。
//
// 星号 * 表示使用了启发式信息（自从1968年开发出此算法后，这个记法被广泛接受），因此 f*（n），
// g*（n），h*（n） 是对实际开销 f（n），g（n），h（n）的估算，这些实际开销只能在得到解之后才能
// 够知道。f*（n） 越低，表示状态 n 越接近目标状态。f*（n） 最关键的部分是启发式的计算h*（n），
// 因为 g*（n） 能够在搜索的过程中，通过记录状态 n 的深度计算出来。如果 h*（n） 不能够准确地区
// 分开有继续搜索价值的状态和没有价值的状态，那么 A* 搜索不会表现得比深度优先搜素更好。如果能够准
// 确地估算 h*（n），那么使用 f*（n） 就能够得到一个开销最小的解。伪代码如下：
//
// search (initial, goal)
//      initial.depth = 0
//      open = new PriorityQueue
//      closed = new Set
//      insert(open, copy(initial))
//      while (open is not empty) do
//              n = minimum(open)
//              insert(closed, n)
//              if (n = goal) then return "Solution"
//              foreach valid move m at n do
//                      next = state when playing m at n
//                      next.depth = n.depth + 1
//                      if (closed contains next) then
//                              prior = state in closed matching next
//                              if (next.score < prior.score) then
//                                      remove(closed, prior)
//                                      insert(open, next)
//                      else
//                              insert(open, next)
//      return "No Solution"
// end
//
// [迭代加深 A*（Iterative-Deepening A* Search，IDA*）搜索解题]
// [参考 Richard E. Korf, "Recent Progress in the Design and Analysis of Admissible
// Heuristic Functions," Proceeding, Abstraction, Reformulation, and Approximation:
// 4th International Symposium (SARA), Lecture notes in Computer Science #1864:
// 45 - 51, 2000]
//
// IDA* 依赖于一系列逐渐扩展的有限制的深度优先搜索。对于每次后继迭代，搜索深度限制都会在前次的基
// 础上增加。IDA* 比单独的深度优先搜索或广度优先搜索要高效得多，因为每次计算出的开销值都是基于实
// 际的走法序列而不是启发式函数的估计。
	
#include <iostream>
#include <cstring>
#include <limits>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
	
using namespace std;
	
#define SQUARES 4		// 局面横向格子数。
#define BASE 16			// 将局面转换为整数的基数。
#define DEPTHBOUND 30		// 使用深度优先搜索时的最大搜索深度。
#define STEPSBOUND 50		// 解的最大长度。
	
#define MOVE_LEFT (-1)
#define MOVE_RIGHT 1
#define MOVE_UP (-SQUARES)
#define MOVE_DOWN SQUARES
#define MOVE_NONE 0
	
int manhattan[SQUARES * SQUARES][SQUARES * SQUARES];	// 预先计算的曼哈顿距离表。
int move[SQUARES];	// 后续移动。
	
// 当前棋面状态相关数据的一个结构。
struct node
{
	vector < int > state;		// 表示当前棋盘状态。
	int moves[STEPSBOUND];		// 从初始状态到达该状态的走法序列。
	int depth;			// 当前深度。
	int score;			// 当前节点的评分。
	int blank;			// 空格位置。
};
	
// 优先队列的比较函数。分值较小的在优先队列的前端。
bool operator<(node x, node y)
{
	return x.score > y.score;
}
	
// 求绝对值。
int absi(int x)
{
	return x >= 0 ? x : (-x);
}
	
// 判断给定局面是否可解。
bool solvable(vector < int > tiles)
{
	int sum = 0, row;
	for (int i = 0; i < tiles.size(); i++)
	{
		int tile = tiles[i];
		if (tile == 0)
		{
			row = (i / SQUARES + 1);
			continue;
		}

		for (int m = i; m < tiles.size(); m++)
			if (tiles[m] < tile && tiles[m] != 0)
				sum++;
	}
	
	return !((sum + row) % 2);
}
	
// 得到当前局面的后继走法。MOVE_LEFT = 向左移动空滑块，MOVE_RIGHT = 向右移动空滑块，
// MOVE_UP = 向上移动空滑块，MOVE_DOWN = 向下移动空滑块。
void valid_moves(node &current)
{
	// 获取后继走法，但除去退回到该状态的上一步的走法。
	int last_move = MOVE_NONE;
	if (current.depth)
		last_move = current.moves[current.depth - 1];
	
	memset(move, MOVE_NONE, sizeof(move));
	if (current.blank % SQUARES > 0 && last_move != MOVE_RIGHT)
		move[0] = MOVE_LEFT;;
	if (current.blank % SQUARES < (SQUARES - 1) && last_move != MOVE_LEFT)
		move[1] = MOVE_RIGHT;
	if (current.blank / SQUARES > 0 && last_move != MOVE_DOWN)
		move[2] = MOVE_UP;
	if (current.blank / SQUARES < (SQUARES - 1) && last_move != MOVE_UP)
		move[3] = MOVE_DOWN;
}
	
// 将棋面状态转换为一个整数。
unsigned long long key(vector < int > &tiles)
{
	unsigned long long key = 0;
	for (int i = 0; i < tiles.size(); i++)
		key = key * BASE + tiles[i];
	return key;
}
	
// 从局面 current 执行 move 所指定的走法。
node execute(node &current, int move)
{
	node successor;
	
	// 走法步骤设定。
	memcpy(successor.moves, current.moves, sizeof(current.moves));
	successor.depth = current.depth + 1;
	successor.moves[current.depth] = move;
	
	// 局面状态设定。按 move 指定方向移动，交换空滑块位置。
	successor.state = current.state;
	successor.blank = current.blank + move;
	successor.state[current.blank] = successor.state[successor.blank];
	successor.state[successor.blank] = 0;
	
	return successor;
}

// 由于 h*（n） 在算法中非常关键，而且它是高度特化的，根据问题的不同而不同，所以需要找到一个合适
// 的 h*（n） 函数是比较困难的，在这里使用的是每个方块到其目标位置的曼哈顿距离之和，曼哈顿距离是
// 该状态要达到目标状态至少需要移动的步骤数。g*（n） 为到达此状态的深度，在这里采用了如下评估函
// 数： f*（n） = g*（n） + 4 / 3 * h*（n），h*（n） 为当前状态与目标状态的曼哈顿距离，亦可
// 以考虑计算曼哈顿配对距离。本题中实验了一下，效率比单纯曼哈顿距离要高，但比曼哈顿距离乘以适当系
// 数的方法低。可参考：
// [Bernard Bauer，The Manhattan Pair Distance Heuristic for the 15-Puzzle，1994]
int score(vector < int > &state, int depth)
{
	int hn = 0;
	
	for (int i = 0; i < state.size(); i++)
		if (state[i] > 0)
			hn += manhattan[state[i] - 1][i];
	
	return (depth + 4 * hn / 3);
}
	
// 判断是否已达到目标状态。
bool solved(vector < int > &state)
{
	if (state[SQUARES * SQUARES - 1] != 0)
		return false;
	
	for (int i = 0; i < SQUARES * SQUARES - 1; i++)
		if (state[i] != (i + 1))
			return false;
	
	return true;
}
	
// 找到局面状态的空滑块位置。
int find_blank(vector < int > &state)
{
	for (int i = 0; i < SQUARES * SQUARES; i++)
		if (state[i] == 0)
			return i;
}
	
// [深度优先搜索]
// 与广度优先搜索不同的是使用栈来保存开放集。对于移动步数较少（15步左右）时可以较快的得到解，但是
// 随着解移动步数的增加，得到解的时间及使用的内存都会大大增加，所以对于本题来说，不是有效的解决办
// 法。是否能得到解和解的深度限制有关，如果选择的深度不够大，可能不会得到解，若过大，将导致搜索时
// 间成倍增加。
bool solve_puzzle_by_depth_first_search(vector < int > tiles, int directions[])
{
	node copy;
	copy.state = tiles;
	copy.depth = 0;
	copy.blank = find_blank(tiles);
	memset(copy.moves, MOVE_NONE, sizeof(copy.moves));
	
	// 检测当前局面是否为已解决状态。
	if (solved(copy.state))
	{
		memcpy(directions, copy.moves, sizeof(copy.moves));
		return true;
	}
	
	// 将初始状态放入开放集中。
	stack < node > open;	// 深度优先搜索使用栈来存储开放集。
	open.push(copy);
	
	// 闭合集。
	set < unsigned long long > closed;
	while (!open.empty())
	{
		// 处理开放集中的局面，并将该局面放入闭合集中。
		node current = open.top();
		open.pop();
		closed.insert(key(current.state));
	
		// 获取该局面的后继走法，后继走法都会加入开放集中。
		valid_moves(current);
		for (int i = 0; i < SQUARES; i++)
		{
			if (move[i] == MOVE_NONE)
				continue;
	
			// 在当前局面上执行走法。
			node successor = execute(current, move[i]);
			
			// 如果已经访问，尝试另外一种走法。
			if (closed.find(key(successor.state)) != closed.end())
				continue;
	
			// 记录求解中前一步走法，如果找到解，那么立即退出。否则的话在限制的
			// 深度内将其加入开放集。    
			if (solved(successor.state))
			{
				memcpy(directions, successor.moves, 
					sizeof(successor.moves));
				return true;
			}
	
			// 将当前局面放入开放集中。
			if (successor.depth < DEPTHBOUND)
				open.push(successor);
		}
	}
	
	return false;
}
	
// [广度优先搜索]
// 对于移动步数较少（15步左右）时可以较快的得到解，但是随着解移动步数的增加，得到解的时间及使用的
// 内存都会大大增加，所以对于本题来说，不是有效的解决办法。
bool solve_puzzle_by_breadth_first_search(vector < int > tiles, int directions[])
{
	node copy;
	copy.state = tiles;
	copy.depth = 0;
	copy.blank = find_blank(tiles);
	memset(copy.moves, MOVE_NONE, sizeof(copy.moves));
	
	// 检测当前局面是否为已解决状态。
	if (solved(copy.state))
	{
		memcpy(directions, copy.moves, sizeof(copy.moves));
		return true;
	}
	
	// 将初始状态放入开放集中。
	queue < node > open;	// 广度优先搜索使用队列存储开放集。
	open.push(copy);
	
	// 闭合集。
	set < unsigned long long > closed;
	while (!open.empty())
	{
		// 处理开放集中的局面，并将该局面放入闭合集中。
		node current = open.front();	// 广度优先搜索。
		open.pop();
		closed.insert(key(current.state));
	
		// 获取该局面的后继走法，后继走法都会加入开放集中。
		valid_moves(current);
		for (int i = 0; i < SQUARES; i++)
		{
			if (move[i] == MOVE_NONE)
				continue;
	
			// 在当前局面上执行走法。
			node successor = execute(current, move[i]);
	
			// 如果已经访问，尝试另外一种走法。
			if (closed.find(key(successor.state)) != closed.end())
				continue;
	
			// 记录求解中前一步走法，如果找到解，那么立即退出。   
			if (solved(successor.state))
			{
				memcpy(directions, successor.moves, 
					sizeof(successor.moves));
				return true;
			}
	
			// 将当前局面放入开放集中。
			open.push(successor);
		}
	}
	
	return false;
}
	
// [A* 搜索]
// 深度优先搜索和宽度优先搜索都是盲目的搜索，并没有对搜索空间进行剪枝，导致大量的状态必须被检测，
// A* 搜索在通过对局面进行评分，对评分低的局面优先处理（评分越低意味着离目标状态越近），这样充分
// 利用了时间，在尽可能短的时间内搜索最有可能达到目标状态的局面，从而效率比单纯的 DFS 和 BFS 要
// 高，不过由于需要计算评分，故启发式函数的效率对于 A* 搜索至关重要，值得注意的是，即使较差的启
// 发式函数，也能较好地剪枝搜索空间。对于复杂的局面状态，必须找到优秀的启发式函数才可能在给定时间
// 和内存限制下得到解，如果给定复杂的初始局面，而没有优秀的启发式函数，则由于 A* 搜索会存储产生的
// 节点，大多数情况下，在能找到解之前会由于问题的巨大状态数而导致内存耗尽。
bool solve_puzzle_by_a_star(vector < int > tiles, int directions[])
{
	node copy;
	copy.state = tiles;
	copy.depth = 0;
	copy.blank = find_blank(tiles);
	copy.score = score(copy.state, 0);
	memset(copy.moves, MOVE_NONE, sizeof(copy.moves));
	
	priority_queue < node > open;	// A* 搜索使用优先队列存储开放集。
	open.push(copy);
	
	map < unsigned long long, int > closed;
	while (!open.empty())
	{
		// 删除评价值最小的节点，标记为已访问过。
		node current = open.top();
		open.pop();
		
		// 将状态特征值和状态评分存入闭合集中。
		closed.insert(make_pair< unsigned long long, int >
			(key(current.state), current.score));
		
		// 如果是目标状态，返回。
		if (solved(current.state))
		{
			memcpy(directions, current.moves, 
				sizeof(current.moves));
			return true;
		}
			
		// 计算后继走法，更新开放集和闭合集。
		valid_moves(current);
		for (int i = 0; i < SQUARES; i++)
		{
			if (move[i] == MOVE_NONE)
				continue;
	
			// 移动滑块，评价新的状态。
			node successor = execute(current, move[i]);
			
			// 根据启发式函数对当前状态评分。
			successor.score = score(successor.state, successor.depth);
			
			// 如果当前状态已经访问过，查看是否能够以更小的代价达到此状态，如果没
			// 有，继续，否则从闭合集中提出并处理。在深度优先搜索中，由于可能后面
			// 生成的局面评分较高导致进入闭合集，从栈的底端生成同样的局面，评分较
			// 低，但是由于较高评分的局面已经在闭合集中，评分较低的等同局面将不予
			// 考虑，这可能会导致深度搜索 “漏掉” 解。
			map <  unsigned long long, int >::iterator it = 
				closed.find(key(successor.state));

			if (it != closed.end())
			{
				if (successor.score >= (*it).second)
					continue;
				closed.erase(it);
			}
	
			// 将当前局面放入开放集中。
			open.push(successor);
		}
	}
	
	return false;
}
	
// [IDA* 搜索]
// 深度优先在内存占用方面占优势，但是由于没有剪枝，导致搜索空间巨大，A* 搜索虽然剪枝，但是由于存
// 储了产生的每个节点，内存消耗较大。IDA* 搜索结合了两者的优势。IDA* 实质上就是在深度优先搜索的
// 算法上使用启发式函数对搜索深度进行限制。
bool solve_puzzle_by_iterative_deepening_a_star(vector < int > tiles, int directions[])
{
	node copy;
	copy.state = tiles;
	copy.depth = 0;
	copy.blank = find_blank(tiles);
	memset(copy.moves, MOVE_NONE, sizeof(copy.moves));
	
	// 检测当前局面是否为已解决状态。
	if (solved(copy.state))
	{
		memcpy(directions, copy.moves, sizeof(copy.moves));
		return true;
	}
	
	// 设定初始搜索深度为初始状态的评分。
	int depth_limit = 0, min_depth = score(copy.state, 0);
	
	while (true)
	{
		// 获取迭代后的评分。
		if (depth_limit < min_depth)
			depth_limit = min_depth;
		else
			depth_limit++;
	
		numeric_limits< int > t;
		min_depth = t.max();
	
		// 开始新的深度优先搜素，深度为 depth_limit。
		stack < node > open;
		open.push(copy);
		while (!open.empty())
		{
			node current = open.top();
			open.pop();
			
			// 获取该局面的后继走法，后继走法都会加入开放集中。
			valid_moves(current);
			for (int i = 0; i < SQUARES; i++)
			{
				if (move[i] == MOVE_NONE)
					continue;
	
				// 在当前局面上执行走法。
				node successor = execute(current, move[i]);
	
				// 记录求解中前一步走法，如果找到解，那么立即退出。否则的
				// 话在限制的深度内将其加入开放集。    
				if (solved(successor.state))
				{
					memcpy(directions, successor.moves, 
						sizeof(successor.moves));
					return true;
				}
	
				// 计算当前节点的评分，若小于限制，加入栈中，否则找超过的
				// 最小值。
				successor.score = score(successor.state, 
					successor.depth);
	
				if (successor.score < depth_limit)
					open.push(successor);
				else
				{
					if (successor.score < min_depth)
						min_depth = successor.score;
				}
			}			
		}
	}
	
	return false;
}
	
void solve_puzzle(vector < int > tiles)
{
	int moves[STEPSBOUND];
	
	// 深度优先搜索。
	// solve_puzzle_by_depth_first_search(tiles, moves);
	
	// 宽度优先搜索。
	// solve_puzzle_by_breadth_first_search(tiles, moves);
	
	// A* 搜索。解长度在 30 - 50 步之间的局面平均需要 7 s。UVa RT 1.004 s。
	// solve_puzzle_by_a_star(tiles, moves);
	
	// IDA* 搜索。解长度在 30 - 50 步之间的局面平均需要 1.5 s。UVa RT 0.320 s。
	solve_puzzle_by_iterative_deepening_a_star(tiles, moves);
	
	// 输出走法步骤。
	for (int i = 0; i < STEPSBOUND; i++)
	{
		if (moves[i] == MOVE_NONE)
			break;
	
		switch (moves[i])
		{
			case MOVE_LEFT:
				cout << "L";
				break;
			case MOVE_RIGHT:
				cout << "R";
				break;
			case MOVE_UP:
				cout << "U";
				break;
			case MOVE_DOWN:
				cout << "D";
				break;
		}
	}
	
	cout << endl;
}
	
// 预先计算曼哈顿距离填表。
void cal_manhattan(void)
{
	for (int i = 0; i < SQUARES * SQUARES; i++)
		for (int j = 0; j < SQUARES * SQUARES; j++)
		{
			int tmp = 0;
			tmp += (absi(i / SQUARES - j / SQUARES) + 
				absi(i % SQUARES - j % SQUARES));
			manhattan[i][j] = tmp;
		}	
}
	
int main(int ac, char *av[])
{	
	// 计算曼哈顿距离，填表。
	cal_manhattan();
	
	int n, tile;
	vector < int > tiles;	// 表示给定局面滑块。
	
	cin >> n;
	
	while (n--)
	{
		// 读入局面状态。
		tiles.clear();
		for (int i = 0; i < SQUARES * SQUARES; i++)
		{
			cin >> tile;
			tiles.push_back(tile);
		}

		// 判断是否有解，无解则输出相应信息，有解则使用相应算法解题。
		if (solvable(tiles))
			solve_puzzle(tiles);
		else
			cout << "This puzzle is not solvable." << endl;
	}
	
	return 0;
}

