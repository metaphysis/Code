// Yahtzee （Yahtzee 游戏）
// PC/UVa IDs: 110208/10149, Popularity: C, Success rate: average Level: 3
// 版权所有（C），邱秋，2011。metaphysis at yeah dot net
// Verdict: Accepted
// Submission Date: 2011-05-16
// UVa Run Time: 0.088s
//
// 每组色子可以选择13种计分方式中的任意一种，已选择的计分方式不能再次选取。如果将每组色子按每种计
// 分方式进行计分，并将分值排列如下，则可以得到一个矩阵。
// 
//       C1 C2 C3 C4 C5 C6 C7 C8 C9 C10 C11 C12 C13
//       ------------------------------------------
// R1  | a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12 a13
// R2  | b1 b2 b3 b4 b5 b6 b7 b8 b9 b10 b11 b12 b13
// R3  | c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13
// R4  | d1 d2 d3 d4 d5 d6 d7 d8 d9 d10 d11 d12 d13
// R5  | e1 e2 e3 e4 e5 e6 e7 e8 e9 e10 e11 e12 e13
// R6  | f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 f12 f13
// R7  | g1 g2 g3 g4 g5 g6 g7 g8 g9 g10 g11 g12 g13
// R8  | h1 h2 h3 h4 h5 h6 h7 h8 h9 h10 h11 h12 h13
// R9  | i1 i2 i3 i4 i5 i6 i7 i8 i9 i10 i11 i12 i13
// R10 | j1 j2 j3 j4 j5 j6 j7 j8 j9 j10 j11 j12 j13
// R11 | k1 k2 k3 k4 k5 k6 k7 k8 k9 k10 k11 k12 k13
// R12 | l1 l2 l3 l4 l5 l6 l7 l8 l9 l10 l11 l12 l13
// R13 | m1 m2 m3 m4 m5 m6 m7 m8 m9 m10 m11 m12 m13
//
// 其中 Ci(i = 1，..，13)，表示计分种类。Ri(i = 1，..，13)，表示色子组数。a1 - a13 表示第一
// 组色子按各种计分方式所得到的分数，其余的类推。题目的要求实际上可以转化为下列问题（暂时不考虑奖
// 励分的情况）：从上述 13 行 13 列的矩阵中，每一行和每一列只取一个数并将取出的数相加，求出能取到的
// 最大值和取法，有多种取法可以只举出一种。直观的，第一行可以取 13 种取法，第二行有 12 种取法，类似
// 的，总共有 13！ = 6227020800 种取法，如果用穷举算法，肯定是可以找到最大值的，但是程序运行
// 时间超出要求。穷举算法在计算过程中多次重复计算，这是导致程序运行时间大大增加的原因，为了提高效
// 率，必须减少重复计算量。有算法基础的人应该可以意识到应该使用动态规划（Dynamic Programming）
// 算法来解决该问题。
//
// Yahtzee 问题实际上就是一个典型的应用动态规划算法的问题。在应用动态规划时，一个技巧是使用位掩码
// （bitmask）来构建所有的组合情况，如上例所示，13种计分方式总共有 2^13 = 8192 种不同的组合
// 方式，对于每种组合方式求取最大值，逐步得到结果。对于上面给出的矩阵，假设第一组色子选取了第一种计
// 分方案，分值为a1，则第二组色子只能在 2 - 13 种计分方式中任选一种，怎样表示这种状态呢？如果把各次
// 选择计分方式的状态表示下列形式：
//
// C1  C2  C3  C4  C5  C6  C7  C8  C9  C10  C11  C12  C13
// 1   1   0   0   0   0   0   0   0   0    0    0    0
//
// 当某种计分方式已经使用，则该种计分方式下面为 1，否则为 0。第一组色子选择了第一种计分方式，则 C1 为
// 1，假设第二组色子使用了第二种计分方式，则 C2 为 1，将 C1 到 C13 的 1 和 0 的状态转换为 1 个
// 二进制数（C13 在最前，C1 在最末尾）则为：
//
// 0000000000011 （b）
//
// 该二进制数为 10 进制数的 3。若相反，第一组色子选择第二种计分方式，第二组色子选择第一种计分方式，这
// 样得到的二进制数仍然是：
//
// 0000000000011 （b）
//
// 那么该状态表示的是不管第一组和第二组色子选择第一或第二种计分方式的顺序如何，只要比较两种选择下
// 那种选择的分值大，此时我们设立一个数组sum，将该二进制数即十进制的 3 作为数组的序号，则该数组元素
// 所表示的就是当第一和第二组色子选择第一或第二种计分方式时的最大值。同理，对于以下二进制数：
//
// 0000000000101 （b）
//
// 表示的是第一组色子和第三组色子各取第一或第三种计分方式，同样以该二进制数即十进制下的 5 作为数组
// 序号，将所得计分和的最大值储存到 sum[5] 中。考虑以下二进制数所表示的状态：
//
// 0000000000111 （b）
//
// 前三组色子选择了前三种计分方式，此二进制数可能为 0000000000011 （b）与 0000000000100 （b）
// 相加而来，也可以是 0000000000101 （b） 与0000000000010 （b） 相加而来，两种操作的含义第
// 一种是当第一组和第二组色子取遍第一种和第二种计分方式得到的最大值与第三组色子取第三种计分方式得
// 到的分值相加，第二种表示第一组和第三组色子取遍第一种和第三种计分方式所得到的最大值与第二组色子
// 取第二种计分方式得到的分值相加，如果比较两种操作的所得到的分值，并将较大值储存到二进制数
// 0000000000111 （b） 即十进制数7为序数的数组元素 sum[7] 中，则 sum[7] 的含义就是前三组色子取
// 前三种计分方式，不管选取顺序如何，所得到的最大值。以此类推下去，当为下列状态时：
//
// 1111111111111 （b）
//
// 即求得了最大值。在求最大值的过程中需要一个数组来保存各个策略状态最大值所采取的计分方式，以便在
// 最后根据该数组来回溯得到各个策略状态所采取的计分方式。对于奖励分的处理，因为是前六项计分大于或
// 等于 63 分时给予 35 分的奖励分，所以在计算过程中，需将同策略的不同前六项得分的总分区分开来，因为大
// 于等于63的前六项得分效果是等同的，故只需考虑 0 ~ 63 这 64 种情况，一个总分，如果前六项总分大于等于
// 63，则将该总分放在数组序号为 63 的总分元素中，小于 63 的则放在相应分数为序号的元素中，在比较
// 时，对前六项总分相同的元素比较总分大小，总分大的替代原来的元素项，那么数组的每一项储存的是前六
// 项分数和等于数组元素序号时的最大总分。如 sum[1111011100011 （b）][25] 表示的是采用策略
// 1111011100011 （b） 时前六项分数为 25 时的最大总分，可能采用该策略的前六项分数为 25 的情况并不存在，则
// 数组元素值设为 -1。同样的需要在替换时记录替换前后的所采用的计分策略和前六项得分以便回溯得到解的过
// 程。本算法时间复杂度为 O（n * （2^n）），空间复杂度为 O（2^n）。
	
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
	
using namespace std;
	
#define NDICES	5		// 每组色子的数量。
#define NROUNDS	13		// 掷色子的轮数。
#define NCOMBINATIONS	8192	// 1 << 13，计分种类的不同组合方式种数。
#define NCATEGORIES	13	// 计分种类。
#define NUPPER	64		// 63（奖励分条件） + 1
#define NBOUNS	35		// 奖励分
	
// 为计算一个二进制数中 1 的位数定义的宏。
#define POW(c) (1<<(c))
#define MASK(c) (((unsigned long)-1) / (POW(POW(c)) + 1))
#define ROUND(n, c) (((n) & MASK(c)) + ((n) >> POW(c) & MASK(c)))
	
// 计算整数 n 表示为二进制数时位为 1 的个数。
int bits(int n)
{
	n = ROUND(n, 0);
	n = ROUND(n, 1);
	n = ROUND(n, 2);
	n = ROUND(n, 3);
	n = ROUND(n, 4);

	return n;
}
	
// 根据不同计分方式计算一组色子的分值，对于后6种计分方式，需要先判断
// 是否符合该种计分方式的要求，符合则返回相应的分数，否则计 0 分。
int scoring(int dices[NDICES], int category)
{
	// 计一到计六。
	int ret = 0;
	if (category < 6)
	{
		for (int i = 0; i < NDICES; i++)
			if (dices[i] == (category + 1))
				ret += dices[i];
	}
	else
	{
		switch (category)
		{
				// 机会。
			case 6:
				for (int i = 0; i < NDICES; i++)
					ret += dices[i];
				break;
				// 三同。
			case 7:
				if (dices[0] == dices[2] || dices[1] == dices[3]
				 || dices[2] == dices[4])
					for (int i = 0; i < NDICES; i++)
						ret += dices[i];
				break;
				// 四同。
			case 8:
				if (dices[0] == dices[3] || dices[1] == dices[4])
					for (int i = 0; i < NDICES; i++)
						ret += dices[i];
				break;
				// 五同。
			case 9:
				if (dices[0] == dices[4])
					ret = 50;
				break;
				// 小顺。
			case 10:
				bool value[6];
				memset(value, 0, sizeof(value));

				for (int i = 0; i < 5; i++)
					value[dices[i] - 1] = true;

				for (int i = 0; i < 3; i++)
					if (value[i] && value[i + 1] && 
					value[i + 2] && value[i + 3])
						ret = 25;
				break;
				// 大顺。
			case 11:
				if (dices[1] == (dices[0] + 1) &&
					dices[2] == (dices[1] + 1) &&
					dices[3] == (dices[2] + 1) &&
					dices[4] == (dices[3] + 1))
					
					ret = 35;
				break;
				// 葫芦。
			case 12:
				if (dices[0] == dices[1] &&
					dices[2] == dices[4] ||
					dices[0] == dices[2] &&
					dices[3] == dices[4])
					ret = 40;
				break;
		}
	}
	
	return ret;
}
	
void dynamic_programming(int yahtzee[NROUNDS][NDICES])
{
	int score[NROUNDS][NROUNDS];	// 保存各组色子按不同计分方式所得分。
	int sum[NCOMBINATIONS][NUPPER];	// 保存每种策略的总分数。
	// memo[NCOMBINATIONS][NUPPER][0] 记录每种策略所使用的计分方式，memo[NCOMBINATIONS][NUPPER][1] 记录前六项分数。
	int memo[NCOMBINATIONS][NUPPER][2];
	
	// 计算第（i + 1）组色子使用第（j + 1）种计分方式时的得分。
	for (int i = 0; i < NROUNDS; i++)
		for (int j = 0; j < NCATEGORIES; j++)
			score[i][j] = scoring(yahtzee[i], j);

	
	// 初始化总分数组为 -1，未选择策略时总分为 0。
	memset(sum, -1, sizeof(sum));
	sum[0][0] = 0;
	
	int b, s, t, d, a;
	// 遍历所有可能的计分组合方式，并计算每种组合方式下的最大分值，
	for (int m = 0; m < NCOMBINATIONS; m++)
		for (int c = 0; c < NCATEGORIES; c++)
			// 必须保证第（c + 1）种计分方式尚未使用。
			if (!(m & (1 << c)))
			{
				// 计算当 m 表示为二进制数时，位为 1 的个数，表示当前是为第（b + 1）组色子选择计分方式。
				b = bits(m);

				// 第（b + 1）组色子的第（c + 1）种计分方式得分。
				s = score[b][c];
				
				// 当前使用策略的二进制标志。
				t = m | (1 << c);
				
				// 如果所选计分方式为前六种方式之一，则加上该组色子此种计分方式得分。
				a = (c < 6) ? s : 0;	
				for (int u = 0; u < NUPPER; u++)
					if (sum[m][u] > -1)
					{
						d = ((u + a) < (NUPPER - 1) ? (u + a) : (NUPPER - 1));
						if (sum[t][d] < (sum[m][u] + s))
						{
							memo[t][d][0] = c;
							memo[t][d][1] = u;
							sum[t][d] = sum[m][u] + s;
						}
					}
			}
	
	// 判断最大总分是否包含奖励分。
	int max = 0, bouns = 0, upper, total;
	
	// 无奖励分的最大总分值。
	for (int u = 0; u < NUPPER - 1; u++)
		if (sum[NCOMBINATIONS - 1][u] > max)
		{
			max = sum[NCOMBINATIONS - 1][u];
			upper = u;
		}
	
	// 有奖励分的最大总分值。
	total = max;
	if (sum[NCOMBINATIONS - 1][NUPPER - 1] > -1)
	{
		bouns = NBOUNS;
		total = sum[NCOMBINATIONS - 1][NUPPER - 1] + bouns;
	}
	
	// 比较两种总分值的大小。
	if (max < total)
	{
		max = total;
		upper = NUPPER - 1;
	}
	
	// 根据 memo 数组回溯得到解的过程。
	int last = NCOMBINATIONS - 1;
	int category[NROUNDS];
	for (int i = NROUNDS - 1; i >= 0; i--)
	{
		category[i] = memo[last][upper][0];
		upper = memo[last][upper][1];
		last ^= (1 << category[i]);
	}
	
	// 根据解输出结果。
	for (int i = 0; i < NCATEGORIES; i++)
		for (int j = 0; j < NROUNDS; j++)
			if (category[j] == i)
				cout << score[j][i] << " ";
	
	cout << bouns << " " << max << endl;
}
	
bool cmp(int a, int b)
{
	return a < b;
}
	
int main(int ac, char *av[])
{
	int yahtzee[NROUNDS][NDICES];
	string line;
	int count = 0;
	
	while (getline(cin, line))
	{
		istringstream iss(line);
		for (int i = 0; i < NDICES; i++)
			iss >> yahtzee[count % NROUNDS][i];

		sort(yahtzee[count % NROUNDS], yahtzee[count % NROUNDS] + NDICES, cmp);

		if (++count % NROUNDS == 0)
			dynamic_programming(yahtzee);
	}
	
	return 0;
}
