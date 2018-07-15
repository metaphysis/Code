// Eight
// UVa ID: 652
// Verdict: Accepted
// Submission Date: 2018-07-15
// UVa Run Time: 0.750s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int SQUARES = 3, STEPS_BOUND = 40;
const int MOVE_NONE = 0, MOVE_LEFT = -1, MOVE_RIGHT = 1, MOVE_UP = -SQUARES, MOVE_DOWN = SQUARES;

// 表示当前布局相关数据的一个结构。
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
    int sum = 0;
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i] == 0) continue;
        for (int j = 0; j < i; j++)
            if (tiles[j] > tiles[i])
                sum++;
    }
    return !(sum % 2);
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
        highDepth = highDepth < lowDepth ? lowDepth : highDepth + 1;
        lowDepth = INT_MAX;

        stack<state> open; open.push(copy);
        while (!open.empty())
        {
            state current = open.top(); open.pop();
            getMoves(current);
            for (int i = 0; i < 4; i++)
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

    IDAStar(tiles, dir);

    for (int i = 0; i < STEPS_BOUND; i++)
    {
        if (dir[i] == MOVE_NONE) break;
        switch (dir[i])
        {
            case MOVE_LEFT:  cout << "l"; break;
            case MOVE_RIGHT: cout << "r"; break;
            case MOVE_UP:    cout << "u"; break;
            case MOVE_DOWN:  cout << "d"; break;
        }
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    getManhattan();

    int cases;
    vector<int> tiles;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        tiles.clear();
        char digit;
        for (int i = 0; i < SQUARES * SQUARES; i++)
        {
            cin >> digit;
            if (digit == 'x') tiles.push_back(0);
            else tiles.push_back(digit - '0');
        }

        if (cs > 1) cout << '\n';
        if (solvable(tiles)) solvePuzzle(tiles);
        else cout << "unsolvable\n";
    }

    return 0;
}
