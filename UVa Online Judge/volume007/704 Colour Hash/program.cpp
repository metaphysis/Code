// Colour Hash （色彩缤纷游戏）
// PC/UVa IDs: 110807/704, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-08-28
// UVa Run Time: 0.048s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 若从给定状态进行单向搜索，由于状态较多，容易 TLE，故采用双向搜索的办法，逆向搜索：从目标状态
// 搜索 8 步，把所有得到的结果记录在集合 A 中；正向搜索：从给定状态搜索 9 步，若在搜索过程中生成
// 的某个状态在集合 A 中，则表明在 16 步内能找到解，否则无法找到解。
//
// 这里较为关键的是如何表示游戏的当前状态，以避免在集合 A 中添加重复的状态，可以使用字符串来表示
// 当前的滑块状态。集合 A 可以使用 map 来判断是否已经有重复的状态产生。

#include <iostream>
#include <queue>
#include <map>

using namespace std;

#define LEFT_CLOCKWISE 1		// 左侧顺时针。
#define RIGHT_CLOCKWISE 2		// 右侧顺时针。
#define LEFT_COUNTERCLOCKWISE 3		// 左侧逆时针。
#define RIGHT_COUNTERCLOCKWISE 4	// 右侧逆时针。

#define NWHEEL 24		// 滑块总数目。
#define HALF_WHEEL 9		// 左侧滑块的数目。
#define MIDDLE_WHEEL 3		// 中间滑块的数目。
#define BACKWARD_DEPTH 8	// 逆向搜索深度。

// 目标状态。存储方式为左侧滑块-右侧滑块-中间滑块，因为编号为 10 的滑块占两个字符，故用 10 的英
// 文（ten）首字母 T 来表示。
string target = "034305650078709T90121";

// 逆向搜索的缓存，使用字符串来表示状态和旋转序列。
map < string, string > cache;

// 旋转操作的逆。1 的逆为 3，2 的逆为 4，依此类推。
int reverse[4] = { 3, 4, 1, 2 };

// 表示滑块当前状态的结构。
struct node
{
	string config;		// 滑块状态。
	string sequences;	// 到达此位置的旋转序列。
};

// 按指定的方向旋转滑块。
void rotate(string &config, int direction)
{
	// 获取中间滑块部分。
	string middle = config.substr(HALF_WHEEL * 2);

	switch (direction)
	{
			// 左侧滑块顺时针旋转。
		case LEFT_CLOCKWISE:

			config[HALF_WHEEL * 2] = config[HALF_WHEEL - 2];
			config[HALF_WHEEL * 2 + 1] = config[HALF_WHEEL - 1];
			config[HALF_WHEEL * 2 + 2] = middle[0];

			for (int i = HALF_WHEEL - 1; i >= 2; i--)
				config[i] = config[i - 2];
			config[1] = middle[2];
			config[0] = middle[1];

			break;

			// 右侧滑块顺时针旋转。
		case RIGHT_CLOCKWISE:

			config[HALF_WHEEL * 2] = middle[2];
			config[HALF_WHEEL * 2 + 1] = config[HALF_WHEEL];
			config[HALF_WHEEL * 2 + 2] = config[HALF_WHEEL + 1];

			for (int i = HALF_WHEEL; i <= (HALF_WHEEL * 2 - 3); i++)
				config[i] = config[i + 2];
			config[HALF_WHEEL * 2 - 2] = middle[0];
			config[HALF_WHEEL * 2 - 1] = middle[1];

			break;

			// 左侧滑块逆时针旋转。
		case LEFT_COUNTERCLOCKWISE:

			config[HALF_WHEEL * 2] = middle[2];
			config[HALF_WHEEL * 2 + 1] = config[0];
			config[HALF_WHEEL * 2 + 2] = config[1];

			for (int i = 0; i <= HALF_WHEEL - 3; i++)
				config[i] = config[i + 2];
			config[HALF_WHEEL - 2] = middle[0];
			config[HALF_WHEEL - 1] = middle[1];

			break;

			// 右侧滑块逆时针旋转。
		case RIGHT_COUNTERCLOCKWISE:

			config[HALF_WHEEL * 2] = config[HALF_WHEEL * 2 - 2];
			config[HALF_WHEEL * 2 + 1] = config[HALF_WHEEL * 2 - 1];
			config[HALF_WHEEL * 2 + 2] = middle[0];

			for (int i = 2 * HALF_WHEEL - 1; i >= HALF_WHEEL + 2; i--)
				config[i] = config[i - 2];
			config[HALF_WHEEL + 1] = middle[2];
			config[HALF_WHEEL] = middle[1];

			break;
	}
}

// 从目标状态生成 8 步内所有可能产生的状态，使用宽度优先搜索的方法，用 map 存储生成的状态和相应
// 的旋转序列。
void backward_search(string config)
{
	queue<node> open;

	node tmp;
	tmp.config = config;
	tmp.sequences = "";

	open.push(tmp);

	while (!open.empty())
	{
		node copy = open.front();
		open.pop();

		// 当扩展的深度达到 8 层后停止在此状态上继续扩展。
		if (copy.sequences.length() >= BACKWARD_DEPTH)
			continue;

		for (int i = LEFT_CLOCKWISE; i <= RIGHT_COUNTERCLOCKWISE; i++)
		{
			// 跳过无效的移动，例如前一步采用了左侧顺时针旋转，则当前若使用
			// 左侧逆时针旋转会回到上一步的状态。
			if (copy.sequences.length() > 0)
			{
				// 注意使用的是旋转操作的逆，故需还原后判断。
				int last_rotate = reverse[copy.sequences[0] - '0' - 1];
				if (last_rotate != i && ((last_rotate + i) == 4 || (last_rotate + i) == 6))
					continue;
			}
			
			string t = copy.config;
			rotate(t, i);

			if (cache.find(t) == cache.end())
			{
				node successor;
				successor.config = t;
				// 记录逆向搜索的旋转序列时，使用当前旋转的逆。
				successor.sequences = (char)('0' + reverse[i - 1]) + copy.sequences;
				open.push(successor);

				cache.insert(make_pair<string, string>(t, successor.sequences));
			}
		}
	}
}

// 进行正向搜索，采用宽度优先搜索模式。
bool forward_search(string config)
{
	queue <node> open;

	node tmp;
	tmp.config = config;
	tmp.sequences = "";

	open.push(tmp);

	while (!open.empty())
	{
		node copy = open.front();
		open.pop();

		// 已经找到在缓存中的状态，输出旋转序列。
		if (cache.find(copy.config) != cache.end())
		{
			cout << copy.sequences;
			map <string, string>::iterator it = cache.find(copy.config);
			cout << (*it).second << endl;

			return true;
		}

		// 搜索深度为 9。
		if (copy.sequences.length() >= (BACKWARD_DEPTH + 1))
			continue;
			
		for (int i = LEFT_CLOCKWISE; i <= RIGHT_COUNTERCLOCKWISE; i++)
		{
			// 若前后两步构成互补状态则跳过。
			if (copy.sequences.length() > 0)
			{
				int size = copy.sequences.length();
				int last_rotate = copy.sequences[size - 1] - '0';
				if (last_rotate != i && ((last_rotate + i) == 4 || (last_rotate + i) == 6))
					continue;
			}
			
			string t = copy.config;
			rotate(t, i);

			node successor;
			successor.config = t;
			successor.sequences = copy.sequences + (char)('0' + i);

			open.push(successor);
		}
	}

	return false;
}

// 和目标状态比较，确定是否为已解决状态。
bool solved(string config)
{
	for (int i = 0; i < target.length(); i++)
		if (config[i] != target[i])
			return false;

	return true;
}

int main(int ac, char *av[])
{
	string config;
	int c;
	int cases;
	
	// 先生成逆向搜索的结果以备查。
	backward_search(target);
	
	cin >> cases;
	while (cases--)
	{
		// 读入初始状态。
		config.clear();
		for (int i = 0; i < NWHEEL; i++)
		{
			cin >> c;
			if (c == 10)
				config.append(1, 'T');
			else
				config.append(1, c + '0');
		}

		// 调整表示形式。
		config = config.substr(0, HALF_WHEEL) +
			config.substr(HALF_WHEEL + MIDDLE_WHEEL, HALF_WHEEL) +
			config.substr(2 * HALF_WHEEL + MIDDLE_WHEEL);
		
		// 先判断是否已经为解决状态。
		if (solved(config))
		{
			cout << "PUZZLE ALREADY SOLVED" << endl;
			continue;
		}

		// 进行正向搜索查找。
		if (!forward_search(config))
			cout << "NO SOLUTION WAS FOUND IN 16 STEPS" << endl;
	}

	return 0;
}
