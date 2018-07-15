// 15-Puzzle Problem （15 数码）
// PC/UVa IDs: 110802/10181, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted 
// Submission Date: 2018-07-12
// UVa Run Time: 0.120s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int SQUARES = 4, DEPTH_BOUND = 30, STEPS_BOUND = 50;
const int MOVE_NONE = 0, MOVE_LEFT = -1, MOVE_RIGHT = 1, MOVE_UP = -SQUARES, MOVE_DOWN = SQUARES;

// 当前棋面状态相关数据的一个结构。
struct state
{
    vector<int> board;
    int moves[STEPS_BOUND], depth, scores, blank;
    bool operator<(const state &x) const
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

// 后续移动。
int moves[4];

// 得到当前局面的后继走法。
inline void getMoves(state &current)
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
inline unsigned long long getKey(vector<int> &tiles)
{
    unsigned long long key = 0;
    for (int i = 0; i < tiles.size(); i++)
        key = (key << 4) | tiles[i];
    return key;
}

// 从局面current执行m所指定的走法。
state execute(state &current, int m)
{
    state successor;

    // 走法步骤设定。
    memcpy(successor.moves, current.moves, sizeof(current.moves));
    successor.depth = current.depth + 1;
    successor.moves[current.depth] = m;

    // 局面状态设定。按指定方向移动，交换空滑块位置。
    successor.board = current.board;
    successor.blank = current.blank + m;
    successor.board[current.blank] = successor.board[successor.blank];
    successor.board[successor.blank] = 0;

    return successor;
}

// 判断是否已达到目标状态。
inline bool isSolved(vector<int> &board)
{
    if (board[SQUARES * SQUARES - 1] != 0) return false;
    for (int i = 0; i < SQUARES * SQUARES - 1; i++)
        if (board[i] != (i + 1))
            return false;
    return true;
}

// 找到局面状态的空滑块位置。
inline int findEmptyTile(vector<int> &board)
{
    for (int i = 0; i < SQUARES * SQUARES; i++)
        if (board[i] == 0)
            return i;
}

// [深度优先搜索]
bool dfs(vector<int> tiles, int dir[])
{
    state copy;
    copy.board = tiles;
    copy.depth = 0;
    copy.blank = findEmptyTile(tiles);
    memset(copy.moves, MOVE_NONE, sizeof(copy.moves));

    if (isSolved(copy.board))
    {
        memcpy(dir, copy.moves, sizeof(copy.moves));
        return true;
    }

    stack<state> open;
    open.push(copy);

    set<unsigned long long> closed;
    while (!open.empty())
    {
        state current = open.top(); open.pop();
        closed.insert(getKey(current.board));
        getMoves(current);
        for (int i = 0; i < SQUARES; i++)
        {
            if (moves[i] == MOVE_NONE) continue;
            state successor = execute(current, moves[i]);
            if (closed.find(getKey(successor.board)) != closed.end()) continue;  
            if (isSolved(successor.board))
            {
                memcpy(dir, successor.moves, sizeof(successor.moves));
                return true;
            }
            if (successor.depth < DEPTH_BOUND) open.push(successor);
        }
    }

    return false;
}

// [广度优先搜索]
bool bfs(vector<int> tiles, int dir[])
{
    state copy;
    copy.board = tiles;
    copy.depth = 0;
    copy.blank = findEmptyTile(tiles);
    memset(copy.moves, MOVE_NONE, sizeof(copy.moves));

    if (isSolved(copy.board))
    {
        memcpy(dir, copy.moves, sizeof(copy.moves));
        return true;
    }

    queue<state> open;
    open.push(copy);

    set<unsigned long long> closed;
    while (!open.empty())
    {

        state current = open.front(); open.pop();
        closed.insert(getKey(current.board));

        getMoves(current);
        for (int i = 0; i < 4; i++)
        {
            if (moves[i] == MOVE_NONE) continue;
            state successor = execute(current, moves[i]);
            if (closed.find(getKey(successor.board)) != closed.end()) continue;   
            if (isSolved(successor.board))
            {
                memcpy(dir, successor.moves, sizeof(successor.moves));
                return true;
            }
            open.push(successor);
        }
    }

    return false;
}

int manhattan[SQUARES * SQUARES][SQUARES * SQUARES];

void getManhattan()
{
    for (int i = 0; i < SQUARES * SQUARES; i++)
        for (int j = 0; j < SQUARES * SQUARES; j++)
        {
            int tmp = 0;
            tmp += (abs(i / SQUARES - j / SQUARES) + abs(i % SQUARES - j % SQUARES));
            manhattan[i][j] = tmp;
        }
}

inline int getScore(vector<int> &board, int depth)
{
    int gn = depth, hn = 0;
    for (int i = 0; i < board.size(); i++)
        if (board[i] > 0)
            hn += manhattan[board[i] - 1][i];
    return (gn + 4 * hn / 3);
}

// [A*搜索]
bool AStar(vector<int> tiles, int dir[])
{
    state copy;
    copy.board = tiles;
    copy.depth = 0;
    copy.blank = findEmptyTile(tiles);
    copy.scores = getScore(copy.board, 0);
    memset(copy.moves, MOVE_NONE, sizeof(copy.moves));

    priority_queue<state> open; open.push(copy);

    map<unsigned long long, int> closed;
    while (!open.empty())
    {
        state current = open.top(); open.pop();
        closed[getKey(current.board)] = current.scores;
        if (isSolved(current.board))
        {
            memcpy(dir, current.moves, sizeof(current.moves));
            return true;
        }
        getMoves(current);
        for (int i = 0; i < SQUARES; i++)
        {
            if (moves[i] == MOVE_NONE) continue;
            state successor = execute(current, moves[i]);
            successor.scores = getScore(successor.board, successor.depth);
            auto it = closed.find(getKey(successor.board));
            if (it != closed.end())
            {
                if (successor.scores >= (*it).second) continue;
                closed.erase(it);
            }
            open.push(successor);
        }
    }

    return false;
}

// [IDA*搜索]
bool IDAStar(vector<int> tiles, int dir[])
{
    state copy;
    copy.board = tiles;
    copy.depth = 0;
    copy.blank = findEmptyTile(tiles);
    memset(copy.moves, MOVE_NONE, sizeof(copy.moves));

    if (isSolved(copy.board))
    {
        memcpy(dir, copy.moves, sizeof(copy.moves));
        return true;
    }

    int highDepth = 0, lowDepth = getScore(copy.board, 0);

    while (true)
    {
        if (highDepth < lowDepth) highDepth = lowDepth;
        else highDepth = highDepth + 1;

        lowDepth = INT_MAX;

        stack<state> open; open.push(copy);
        while (!open.empty())
        {
            state current = open.top(); open.pop();
            getMoves(current);
            for (int i = 0; i < SQUARES; i++)
            {
                if (moves[i] == MOVE_NONE) continue;
                state successor = execute(current, moves[i]);
                if (isSolved(successor.board))
                {
                    memcpy(dir, successor.moves, sizeof(successor.moves));
                    return true;
                }
                successor.scores = getScore(successor.board, successor.depth);
                if (successor.scores < highDepth)
                    open.push(successor);
                else
                    lowDepth = min(lowDepth, successor.scores);
            }
        }
    }

    return false;
}

void solvePuzzle(vector<int> tiles)
{
    int dir[STEPS_BOUND] = {};

    // 深度优先搜索。
    // dfs(tiles, moves);

    // 宽度优先搜索。
    // bfs(tiles, moves);

    // A*搜索。解长度在30-50步之间的局面平均需要7s。UVa RT 1.004s。
    // AStar(tiles, moves);

    // IDA*搜索。解长度在30-50步之间的局面平均需要1.5s。UVa RT 0.120s。
    IDAStar(tiles, moves);

    // 输出走法步骤。
    for (int i = 0; i < STEPS_BOUND; i++)
    {
        if (dir[i] == MOVE_NONE) break;
        switch (dir[i])
        {
            case MOVE_LEFT:  cout << "L"; break;
            case MOVE_RIGHT: cout << "R"; break;
            case MOVE_UP:    cout << "U"; break;
            case MOVE_DOWN:  cout << "D"; break;
        }
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    // 计算曼哈顿距离，填表。
    getManhattan();

    int cases, tile;
    vector<int> tiles;

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
        if (solvable(tiles)) solvePuzzle(tiles);
        else cout << "This puzzle is not solvable.\n";
    }

    return 0;
}
