// Little Bishops （棋盘上的象）
// PC/UVa IDs: 110801/861, Popularity: C, Success rate: high Level: 2
// Verdict: Accepted 
// Submission Date: 2011-06-19
// UVa Run Time: 0.024s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// n * n 的棋盘可以最多放置多少个象而不互相冲突？我是这样考虑的，因为象的吃子方式为
// 对角线吃子，则在棋盘上放置一个象后，它要么占据一条对角线，要么占据两条。当然先放置
// 占据一条对角线的象，可以将放置象的数量最大化，在棋盘的主、副主对角线上各放置一个
// 象，则象的总数目为 2，这样，主、副对角线将棋盘区域划分为四个等同的区域，无论在哪
// 个区域放置象，都因为棋盘的对称性会产生相同的效果，故只考虑一个区域的放置方法，然后
// 通过对称来求得总的放置数目。假设一个 8 * 8 的棋盘，已经在主、副对角线各放置了一个
// 象，已占据的位置用 * 号表示，未占据的位置用大写字母 O 表示。
//
//   1 2 3 4 5 6 7 8
// 1 B O-O-O-O-O-O B
// 2 O * O-O-O-O * O
// 3 O#O * O-O * O&O
// 4 O#O#O * * O&O&O
// 5 O#O#O * * O&O&O
// 6 O#O * O+O * O&O
// 7 O * O+O+O+O * O
// 8 * O+O+O+O+O+O *
//
// 如上图所示，有 - 符号连接的未占据位置和 + 符号连接的未占据位置，坐标 (1, 1) 和
// 坐标 (8, 1) 已经放置了象。先考虑 - 符号连接的区域，在此区域内，任意选一个位置放置
// 象将占据两条对角线（非主、副对角线），而且在此区域任意放置象，必将导致左右两个可以
// 放置象的区域被占据而不能再放置象（即有 # 符号和 & 符号的区域），则在有 - 符号的区
// 域所能放置的象的数目是由对角线的交叉点数目所确定的，即最多能再放置 6 个象而不互相
// 冲突，则总共能放置的象数目为 8 个，棋盘状态变为以下状态：
//
//   1 2 3 4 5 6 7 8
// 1 B B B B B B B B
// 2 * * * * * * * *
// 3 * * * * * * * *
// 4 * * * * * * * *
// 5 * * * * * * * *
// 6 * * * O+O * * *
// 7 * * O+O+O+O * *
// 8 * O+O+O+O+O+O *
//
// 则对于有 + 符号的区域来说，同样可以放置 6 个象而不互相冲突。则 8 * 8 的棋盘最大
// 可放置象的数目为 14 个。
//
//   1 2 3 4 5 6 7 8
// 1 B B B B B B B B
// 2 * * * * * * * *
// 3 * * * * * * * *
// 4 * * * * * * * *
// 5 * * * * * * * *
// 6 * * * * * * * *
// 7 * * * * * * * *
// 8 * B B B B B B *
//
// 则总结以下，n * n 的棋盘最大能放置象的数目为 n + (n - 2) 个，即 2 * (n - 1)
// 个象，n >= 2。对于 1 * 1 的棋盘来说，是特殊情况，只能放置 1 个象。那么是否可以通
// 过组合的方法解决本题呢？答案是肯定的。国际象棋的棋盘一般都分为白色和黑色区域，在白色
// 区域的象是无法攻击黑色区域内的象的，将黑白格子相间的棋盘顺时针旋转 45 度，则原来呈
// 斜线的主、副对角线成为垂直和水平的了，此时象的走法和车的走法是一样的了，问题转换为在
// 这样的 n * n 棋盘上放置 k 个车有多少种方法。假设这样的棋盘第 i 行的格子数为 r[i]，
// 用 t[i][j] 表示在前 i 行放置 j 个车而互不冲突的方法，可以得到以下的递推关系：
//
// t[i][j] = t[i - 1][j] + t[i - 1][j - 1] * (r[i] - (j - 1))
//
// 边界条件是：
//
// t[i][0] = 1, 0 <= i <= n
// t[0][j] = 0, 1 <= j <= k
//
// 递推关系的意义可以这样理解：因为每一行只能放置一个车，则 j 个车要么全在前 i - 1 行，
// 要么第 i 行有一个车，j 个车全在前 i - 1 行的放置方法为 t[i - 1][j]，第 i 行放置
// 一个车，前 i - 1 行放置 j - 1 个车，那么前 i - 1 行在放置 j - 1 个车时已经占用
// 了第 i 行的 j - 1 个格子，剩余的格子数为 r[i] - (j - 1)，则根据乘法原理，第二种
// 放置方法是两者的乘积，又根据加法原理，总的放置方法为第一种和第二种方法数量的和。边界
// 情形也容易理解，前 i 行放置 0 个车的方法有 1 种，前 0 行放置 j 个车的方法有 0 种。
// 由于将棋盘分成了两个区域，故在最后计算总的放置数时，应该是两个区域的累积。
//
// 那么如何通过借鉴八皇后问题通过回溯来解决本问题呢？通过观察分析，可以知道，构造候选集
// 的方法是其中关键不同的地方，八皇后问题在构建候选集时，因为皇后不能放置在同一行和同一
// 列，所以可以减少搜索的空间，而放置象时，象可以在同一行或者同一列，搜索的数量因此会增大
// 不过当棋盘较少时，还是可以完成的，当棋盘进一步增大时，回溯方法就显得吃力了，需要借助
// 组合数学的方法来计算放置方案数。在表示棋盘上的象的位置时，由于可以处于同一行或同一列
// 故需要不同的表示方法，一个方法是将棋盘的每个格子编号，从 1 - n^2。
//
// /* 八皇后问题构建候选集的过程。  */
// construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
// {
//      int i,j;
//      bool legal_move;
//      
//      *ncandidates = 0;
//      for (i=1; i<=n; i++)
//      {
//              legal_move = TRUE;
//              /* 对于放置象来说，需要考虑除已有象的对角线外的每一个位置，因为不存 */
//              /* 在像放置皇后时一行或一列只能放置一个这样的限制条件。 */
//              for (j=1; j<k; j++)
//              {
//                      if (abs((k)-j) == abs(i-a[j])) 
//                      legal_move = FALSE;
//                      
//                      /* 对于放置象来说，并不需要检测来自行或者列的威胁，只需检 */
//                      /* 测对角线上的威胁。*/
//                      if (i == a[j])                  
//                      legal_move = FALSE;
//              }
//              
//              if (legal_move == TRUE) 
//              {
//                      c[*ncandidates] = i;
//                      *ncandidates = *ncandidates + 1;
//              }
//      }
// }
//
// 对于构建候选集的过程，尽管不需要考虑来自行或者列的威胁，但需要考虑除对角线外的每一个
// 位置，且并不存在一行只能放一个象的限制条件，这是搜索时间增加的原因。如果在放置象时，
// 不考虑位置的编号，会产生重复的放置方案，这个可以通过每次选择象时都选择比当前已选择的
// 象的位置序号大的位置来避免。尽管采用了相应的剪枝措施，对于较大的 n 和 k 来说，仍容易
// 得到 TLE。相对而言通过组合方法解题还是有优势的，除非用回溯法先生成给定范围内的所
// 有解，然后填表根据具体的 n 和 k 输出，否则当 n 和 k 进一步增大，计算时间将很长。
//
// UVa 10237 Bishops 和本题是类似的，但是 n 和 k 已经足够大，通过回溯已经不可能在
// 规定时间内找到答案，使用组合方法和大数运算成为必须。
	
#include <iostream>
#include <algorithm>
	
using namespace std;
	
#define MAXN 8
	
long long solution_count;
	
void construct_candidates(int bishops[], int c, int n, int candidates[], 
	int *ncandidates)
{
	bool legal_move;	// 合法放置位置的标记。
	
	// 对于放置象来说，需要考虑每一个位置，因为不存在像放置皇后时一行只能放置
	// 一个的情况。只考虑比当前象的位置标记大的位置，避免重复解的生成。因为保证
	// 了后一位置的象的编号大于前一位置象的编号，故可以从具有最大编号的象的位置
	// 开始搜索可放置象的位置，这样可以减少搜索量。
	int start = 0;
	if (c)
		start = bishops[c - 1];
	
	*ncandidates = 0;
	for (int p = start; p < n * n; p++)
	{
		legal_move = true;
	
		// 已放置象的对角线上不能放置。需要检查已放置象的对角线。
		// 不满足条件，尽早退出循环。
		for (int j = 0; j < c; j++)
			if (abs(bishops[j] / n - p / n) ==
				abs(bishops[j] % n - p % n))
			{
				legal_move = false;
				break;
			}
	
		// 若该位置合法，添加到候选集中。
		if (legal_move == true)
			candidates[(*ncandidates)++] = p;
	}
}
	
// 回溯寻找所有可能的方案。
void backtracking(int bishops[], int c, int n, int k)
{
	if (c == k)
		solution_count++;
	else
	{
		int ncandidates;
		int candidates[MAXN * MAXN];
			
		// 构建候选集。
		construct_candidates(bishops, c, n, candidates, &ncandidates);

		for (int i = 0; i < ncandidates; i++)
		{
			bishops[c] = candidates[i];
			backtracking(bishops, c + 1, n, k);
		}
	}
}

long long little_bishops_by_backtracking(int n, int k)
{
	int bishops[2 * (MAXN - 1) + 1];
	
	solution_count = 0;
	backtracking(bishops, 0, n, k);
	
	return solution_count;
}

long long little_bishops_by_combinatorics(int n, int k)
{
	// 假设棋盘左上角第一个格子为白色格子。
	long long white[9];
	long long black[9];
	
	// 得到每一列白色格子的数目。格子数按从小到大排列。
	for (int i = 1; i <= n; i++)
		white[i] = ((i % 2) ? i : white[i - 1]);
	// 得到每一列黑色格子的数目。格子数按从小到大排列。
	for (int i = 1; i <= n - 1; i++)
		black[i] = ((i % 2) ? (i + 1) : black[i - 1]);
	
	// 存储前 i 列放置 j 个象的方法。白色格子和黑色格子的放置方法数分别计算。
	// 因为给定最多 8 * 8 的棋盘，则最大能放置象的数目为 14 个。	
	long long white_solutions[9][15] = { {0} };
	long long black_solutions[9][15] = { {0} };
	// 初始化边界条件。
	for (int i = 0; i <= n; i++)
		white_solutions[i][0] = 1;
	for (int j = 1; j <= k; j++)
		white_solutions[0][j] = 0;
	// 根据递推公式计算白色格子放置方案数。
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k && j <= i; j++)
			white_solutions[i][j] =
				white_solutions[i - 1][j] + 
				white_solutions[i - 1][j - 1] * (white[i] - j + 1);
	// 初始化边界条件。
	for (int i = 0; i <= n - 1; i++)
		black_solutions[i][0] = 1;
	for (int j = 1; j <= k; j++)
		black_solutions[0][j] = 0;
	// 根据递推公式计算黑色格子放置方案数。
	for (int i = 1; i <= n - 1; i++)
		for (int j = 1; j <= k && j <= i; j++)
			black_solutions[i][j] =
				black_solutions[i - 1][j] + 
				black_solutions[i - 1][j - 1] * (black[i] - j + 1);
	
	// 统计总的放置方案数。根据乘法原理和加法原理，总的方案数等于 n * n 的棋盘
	// n 行白色格子放置 0 个象的方案乘以 n - 1 行黑色格子放置 k 个象的方案数，
	// 加上 n 行白色格子放置 1 个象的方案乘以 n - 1 行黑色格子放置 k - 1 个
	// 象的方案数，加上 n 行白色格子放置 2 个象的方案乘以 n - 1 行黑色格子放
	// 置 k - 2 个象的方案数......
	long long total = 0;
	for (int i = 0; i <= k; i++)
		total += white_solutions[n][i] * black_solutions[n - 1][k - i];
	return total;
}
	
long long little_bishops(int n, int k)
{
	// 处理特殊情况的解。
	// k == 0，即棋盘上不放置象，只有一种方法。
	if (k == 0)
		return 1LL;
	
	// 当棋盘为 1 * 1 时，最多只能放置放置 1 个象。
	if (n == 1)
		return k;
	
	// 当 n >= 2 时，由分析可知，最多只能放置 2 * (n - 1) 个象。
	// 当大于 2 * (n - 1) 时无解。
	if (k > 2 * (n - 1))
		return 0LL;
	
	// 一般情况的解。
	//return little_bishops_by_backtracking(n, k);
	return little_bishops_by_combinatorics(n, k);
}
	
int main(int ac, char *av[])
{
	int n, k;
	
	while (cin >> n >> k, n || k)
		cout << little_bishops(n, k) << endl;
	
	return 0;
}
