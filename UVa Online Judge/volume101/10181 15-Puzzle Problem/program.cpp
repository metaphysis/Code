// 15-Puzzle Problem （15 数码）
// PC/UVa IDs: 110802/10181, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted 
// Submission Date: 2018-07-12
// UVa Run Time: 0.120s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define SQUARES 4               // 局面横向格子数。
#define BASE 16                 // 将局面转换为整数的基数。
#define DEPTH_BOUND 30          // 使用深度优先搜索时的最大搜索深度。
#define STEPS_BOUND 50          // 解的最大长度。

#define MOVE_LEFT (-1)
#define MOVE_RIGHT 1
#define MOVE_UP (-SQUARES)
#define MOVE_DOWN SQUARES
#define MOVE_NONE 0

int manhattan[SQUARES * SQUARES][SQUARES * SQUARES];    // 预先计算的曼哈顿距离表。
int moves[SQUARES];             // 后续移动。

// 当前棋面状态相关数据的一个结构。
struct node
{
    vector<int> state;          // 表示当前棋盘状态。
    int moves[STEPS_BOUND];     // 从初始状态到达该状态的走法序列。
    int depth;                  // 当前深度。
    int scores;                 // 当前节点的评分。
    int blank;                  // 空格位置。
    bool operator<(const node &x) const
    {
        return scores > x.scores;
    }
};

// 判断给定局面是否可解。
bool solvable(vector<int> tiles)
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
void getMoves(node &current)
{
    // 获取后继走法，但除去退回到该状态的上一步的走法。
    int lastMove = MOVE_NONE;
    if (current.depth) lastMove = current.moves[current.depth - 1];

    memset(moves, MOVE_NONE, sizeof(moves));
    if (current.blank % SQUARES > 0 && lastMove != MOVE_RIGHT) moves[0] = MOVE_LEFT;;
    if (current.blank % SQUARES < (SQUARES - 1) && lastMove != MOVE_LEFT) moves[1] = MOVE_RIGHT;
    if (current.blank / SQUARES > 0 && lastMove != MOVE_DOWN) moves[2] = MOVE_UP;
    if (current.blank / SQUARES < (SQUARES - 1) && lastMove != MOVE_UP) moves[3] = MOVE_DOWN;
}

// 将棋面状态转换为一个整数。
unsigned long long getKey(vector<int> &tiles)
{
    unsigned long long key = 0;
    for (int i = 0; i < tiles.size(); i++)
        key = key * BASE + tiles[i];
    return key;
}

// 从局面 current 执行 moves 所指定的走法。
node execute(node &current, int moves)
{
    node successor;

    // 走法步骤设定。
    memcpy(successor.moves, current.moves, sizeof(current.moves));
    successor.depth = current.depth + 1;
    successor.moves[current.depth] = moves;

    // 局面状态设定。按 moves 指定方向移动，交换空滑块位置。
    successor.state = current.state;
    successor.blank = current.blank + moves;
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
int getScore(vector<int> &state, int depth)
{
    int hn = 0;
    for (int i = 0; i < state.size(); i++)
        if (state[i] > 0)
            hn += manhattan[state[i] - 1][i];
    return (depth + 4 * hn / 3);
}

// 判断是否已达到目标状态。
bool isSolved(vector<int> &state)
{
    if (state[SQUARES * SQUARES - 1] != 0)
        return false;

    for (int i = 0; i < SQUARES * SQUARES - 1; i++)
        if (state[i] != (i + 1))
            return false;

    return true;
}

// 找到局面状态的空滑块位置。
int findEmptyTile(vector<int> &state)
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
bool dfs(vector<int> tiles, int directions[])
{
    node copy;
    copy.state = tiles;
    copy.depth = 0;
    copy.blank = findEmptyTile(tiles);
    memset(copy.moves, MOVE_NONE, sizeof(copy.moves));

    // 检测当前局面是否为已解决状态。
    if (isSolved(copy.state))
    {
        memcpy(directions, copy.moves, sizeof(copy.moves));
        return true;
    }

    // 将初始状态放入开放集中。
    stack<node> open;        // 深度优先搜索使用栈来存储开放集。
    open.push(copy);

    // 闭合集。
    set < unsigned long long >closed;
    while (!open.empty())
    {
        // 处理开放集中的局面，并将该局面放入闭合集中。
        node current = open.top();
        open.pop();
        closed.insert(getKey(current.state));

        // 获取该局面的后继走法，后继走法都会加入开放集中。
        getMoves(current);
        for (int i = 0; i < SQUARES; i++)
        {
            if (moves[i] == MOVE_NONE)
                continue;

            // 在当前局面上执行走法。
            node successor = execute(current, moves[i]);

            // 如果已经访问，尝试另外一种走法。
            if (closed.find(getKey(successor.state)) != closed.end())
                continue;

            // 记录求解中前一步走法，如果找到解，那么立即退出。否则的话在限制的
            // 深度内将其加入开放集。    
            if (isSolved(successor.state))
            {
                memcpy(directions, successor.moves, sizeof(successor.moves));
                return true;
            }

            // 将当前局面放入开放集中。
            if (successor.depth < DEPTH_BOUND)
                open.push(successor);
        }
    }

    return false;
}

// [广度优先搜索]
// 对于移动步数较少（15步左右）时可以较快的得到解，但是随着解移动步数的增加，得到解的时间及使用的
// 内存都会大大增加，所以对于本题来说，不是有效的解决办法。
bool bfs(vector<int> tiles, int directions[])
{
    node copy;
    copy.state = tiles;
    copy.depth = 0;
    copy.blank = findEmptyTile(tiles);
    memset(copy.moves, MOVE_NONE, sizeof(copy.moves));

    // 检测当前局面是否为已解决状态。
    if (isSolved(copy.state))
    {
        memcpy(directions, copy.moves, sizeof(copy.moves));
        return true;
    }

    // 将初始状态放入开放集中。
    queue<node> open;        // 广度优先搜索使用队列存储开放集。
    open.push(copy);

    // 闭合集。
    set < unsigned long long >closed;
    while (!open.empty())
    {
        // 处理开放集中的局面，并将该局面放入闭合集中。
        node current = open.front();    // 广度优先搜索。
        open.pop();
        closed.insert(getKey(current.state));

        // 获取该局面的后继走法，后继走法都会加入开放集中。
        getMoves(current);
        for (int i = 0; i < SQUARES; i++)
        {
            if (moves[i] == MOVE_NONE)
                continue;

            // 在当前局面上执行走法。
            node successor = execute(current, moves[i]);

            // 如果已经访问，尝试另外一种走法。
            if (closed.find(getKey(successor.state)) != closed.end())
                continue;

            // 记录求解中前一步走法，如果找到解，那么立即退出。   
            if (isSolved(successor.state))
            {
                memcpy(directions, successor.moves, sizeof(successor.moves));
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
bool AStar(vector<int> tiles, int directions[])
{
    node copy;
    copy.state = tiles;
    copy.depth = 0;
    copy.blank = findEmptyTile(tiles);
    copy.scores = getScore(copy.state, 0);
    memset(copy.moves, MOVE_NONE, sizeof(copy.moves));

    priority_queue<node> open;       // A* 搜索使用优先队列存储开放集。
    open.push(copy);

    map<unsigned long long, int> closed;
    while (!open.empty())
    {
        // 删除评价值最小的节点，标记为已访问过。
        node current = open.top();
        open.pop();

        // 将状态特征值和状态评分存入闭合集中。
        closed[getKey(current.state)] = current.scores;

        // 如果是目标状态，返回。
        if (isSolved(current.state))
        {
            memcpy(directions, current.moves, sizeof(current.moves));
            return true;
        }

        // 计算后继走法，更新开放集和闭合集。
        getMoves(current);
        for (int i = 0; i < SQUARES; i++)
        {
            if (moves[i] == MOVE_NONE)
                continue;

            // 移动滑块，评价新的状态。
            node successor = execute(current, moves[i]);

            // 根据启发式函数对当前状态评分。
            successor.scores = getScore(successor.state, successor.depth);

            // 如果当前状态已经访问过，查看是否能够以更小的代价达到此状态，如果没
            // 有，继续，否则从闭合集中提出并处理。在深度优先搜索中，由于可能后面
            // 生成的局面评分较高导致进入闭合集，从栈的底端生成同样的局面，评分较
            // 低，但是由于较高评分的局面已经在闭合集中，评分较低的等同局面将不予
            // 考虑，这可能会导致深度搜索 “漏掉” 解。
            map<unsigned long long, int>::iterator it = closed.find(getKey(successor.state));

            if (it != closed.end())
            {
                if (successor.scores >= (*it).second) continue;
                closed.erase(it);
            }

            // 将当前局面放入开放集中。
            open.push(successor);
        }
    }

    return false;
}

// [IDAStar 搜索]
// 深度优先在内存占用方面占优势，但是由于没有剪枝，导致搜索空间巨大，A* 搜索虽然剪枝，但是由于存
// 储了产生的每个节点，内存消耗较大。IDAStar 搜索结合了两者的优势。IDAStar 实质上就是在深度优先搜索的
// 算法上使用启发式函数对搜索深度进行限制。
bool IDAStar(vector<int> tiles, int directions[])
{
    node copy;
    copy.state = tiles;
    copy.depth = 0;
    copy.blank = findEmptyTile(tiles);
    memset(copy.moves, MOVE_NONE, sizeof(copy.moves));

    // 检测当前局面是否为已解决状态。
    if (isSolved(copy.state))
    {
        memcpy(directions, copy.moves, sizeof(copy.moves));
        return true;
    }

    // 设定初始搜索深度为初始状态的评分。
    int maxDepth = 0, minimalDepth = getScore(copy.state, 0);

    while (true)
    {
        // 获取迭代后的评分。
        if (maxDepth < minimalDepth) maxDepth = minimalDepth;
        else maxDepth++;

        minimalDepth = INT_MAX;

        // 开始新的深度优先搜素，深度为 maxDepth。
        stack<node> open;
        open.push(copy);
        while (!open.empty())
        {
            node current = open.top();
            open.pop();

            // 获取该局面的后继走法，后继走法都会加入开放集中。
            getMoves(current);
            for (int i = 0; i < SQUARES; i++)
            {
                if (moves[i] == MOVE_NONE) continue;

                // 在当前局面上执行走法。
                node successor = execute(current, moves[i]);

                // 记录求解中前一步走法，如果找到解，那么立即退出。否则的
                // 话在限制的深度内将其加入开放集。    
                if (isSolved(successor.state))
                {
                    memcpy(directions, successor.moves, sizeof(successor.moves));
                    return true;
                }

                // 计算当前节点的评分，若小于限制，加入栈中，否则找超过的
                // 最小值。
                successor.scores = getScore(successor.state, successor.depth);
                if (successor.scores < maxDepth) open.push(successor);
                else
                {
                    if (successor.scores < minimalDepth)
                        minimalDepth = successor.scores;
                }
            }
        }
    }

    return false;
}

void solve_puzzle(vector<int> tiles)
{
    int moves[STEPS_BOUND];

    // 深度优先搜索。
    // dfs(tiles, moves);

    // 宽度优先搜索。
    // bfs(tiles, moves);

    // A*搜索。解长度在30-50 步之间的局面平均需要7s。UVa RT 1.004s。
    // AStar(tiles, moves);

    // IDA*搜索。解长度在30-50步之间的局面平均需要1.5 s。UVa RT 0.320 s。
    IDAStar(tiles, moves);

    // 输出走法步骤。
    for (int i = 0; i < STEPS_BOUND; i++)
    {
        if (moves[i] == MOVE_NONE) break;
        switch (moves[i])
        {
            case MOVE_LEFT:  cout << "L"; break;
            case MOVE_RIGHT: cout << "R"; break;
            case MOVE_UP:    cout << "U"; break;
            case MOVE_DOWN:  cout << "D"; break;
        }
    }

    cout << endl;
}

// 预先计算曼哈顿距离填表。
void getManhattan(void)
{
    for (int i = 0; i < SQUARES * SQUARES; i++)
        for (int j = 0; j < SQUARES * SQUARES; j++)
        {
            int tmp = 0;
            tmp += (abs(i / SQUARES - j / SQUARES) + abs(i % SQUARES - j % SQUARES));
            manhattan[i][j] = tmp;
        }
}

int main(int ac, char *av[])
{
    // 计算曼哈顿距离，填表。
    getManhattan();

    int cases, tile;
    vector<int> tiles;        // 表示给定局面滑块。

    cin >> cases;
    while (cases--)
    {
        // 读入局面状态。
        tiles.clear();
        for (int i = 0; i < SQUARES * SQUARES; i++)
        {
            cin >> tile;
            tiles.push_back(tile);
        }

        // 判断是否有解，无解则输出相应信息，有解则使用相应算法解题。
        if (solvable(tiles)) solve_puzzle(tiles);
        else cout << "This puzzle is not solvable." << endl;
    }

    return 0;
}
