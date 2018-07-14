// 15-Puzzle Problem （15 数码）
// PC/UVa IDs: 110802/10181, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted 
// Submission Date: 2018-07-14
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define SET(B, I, J, II, JJ) ((B & (~(15LL << (4 * (II * 4 + JJ))))) | (((B & (15LL << (4 * (II * 4 + JJ)))) >> (4 * (II * 4 + JJ))) << (4 * (I * 4 + J))))
#define GET(HM, LM, I) (int)(((HM & (1LL << I) ? 1 : 0) << 1) | (LM & (1LL << I) ? 1 : 0))

const int SQUARES = 4;
const unsigned long long SOLVED = 0xFEDCBA987654321;

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// 当前棋面状态相关数据的一个结构。
struct state
{
    unsigned long long board, hmove, lmove;
    int depth, score, blanki, blankj;
    state (unsigned long long board = 0, unsigned long long hmove = 0, unsigned long long lmove = 0, int depth = 0, int score = 0, int blanki = 0, int blankj = 0):
    board(board), hmove(hmove), lmove(lmove), depth(depth), score(score), blanki(blanki), blankj(blankj) {}
    bool operator<(const state &x) const { return score > x.score; }
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

void print(state &current)
{
    for (int i = 0; i < current.depth; i++)
    {
        int dir = ((current.hmove & (1LL << i) ? 1 : 0) << 1) | (current.lmove & (1LL << i) ? 1 : 0);
        switch (dir)
        {
            case 0: cout << "U"; break;
            case 1: cout << "R"; break;
            case 2: cout << "D"; break;
            case 3: cout << "L"; break;
        }
    }
    cout << '\n';
}

static int nexti, nextj;
inline bool getSuccessor(state &current, state &successor, int dir)
{
    nexti = current.blanki + offset[dir][0], nextj = current.blankj + offset[dir][1];
    if (nexti < 0 || nexti > 3 || nextj < 0 || nextj > 3) return false;

    successor.board = SET(current.board, current.blanki, current.blankj, nexti, nextj);
    successor.hmove = current.hmove | ((dir & 2 ? 1LL : 0LL) << (current.depth));
    successor.lmove = current.lmove | ((dir & 1 ? 1LL : 0LL) << (current.depth));
    successor.depth = current.depth + 1;
    successor.blanki = nexti;
    successor.blankj = nextj;

    return true;
}

// [深度优先搜索]
bool dfs(unsigned long long board, int blanki, int blankj)
{
    if (board == SOLVED) { cout << '\n'; return true; }

    stack<state> open;
    open.push(state(board, 0LL, 0LL, 0, 0, blanki, blankj));

    state current, successor;
    unordered_set<unsigned long long> closed;

    while (!open.empty())
    {
        current = open.top();
        open.pop();
        closed.insert(current.board);
        for (int dir = 0; dir < SQUARES; dir++)
        {
            if (current.depth && ((dir + 2) % 4) == GET(current.hmove, current.lmove, (current.depth - 1))) continue;
            if (!getSuccessor(current, successor, dir)) continue;
            if (closed.find(successor.board) != closed.end()) continue;
            if (successor.board == SOLVED) { print(successor); return true; }
            if (successor.depth < 30) open.push(successor);
        }
    }

    return false;
}

// [广度优先搜索]
bool bfs(unsigned long long board, int blanki, int blankj)
{
    if (board == SOLVED) { cout << '\n'; return true; }

    queue<state> open;
    open.push(state(board, 0LL, 0LL, 0, 0, blanki, blankj));

    state current, successor;
    unordered_set<unsigned long long> closed;

    while (!open.empty())
    {
        current = open.front();
        open.pop();
        closed.insert(current.board);
        for (int dir = 0; dir < SQUARES; dir++)
        {
            if (current.depth && ((dir + 2) % 4) == GET(current.hmove, current.lmove, (current.depth - 1))) continue;
            if (!getSuccessor(current, successor, dir)) continue;
            if (closed.find(successor.board) != closed.end()) continue;
            if (successor.board == SOLVED) { print(successor); return true; }
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

inline int getScore(unsigned long long board, int depth)
{
    int gn = depth, hn = 0;
    for (int i = 0; i < 16; i++)
    {
        int bit = (int)((board & (15LL << (4 * i))) >> (4 * i));
        if (bit) hn += manhattan[bit - 1][i];
    }
    return (gn + 4 * hn / 3);
}

// [A*搜索]
bool AStar(unsigned long long board, int blanki, int blankj)
{
    priority_queue<state> open;
    open.push(state(board, 0LL, 0LL, 0, getScore(board, 0), blanki, blankj));

    state current, successor;
    unordered_map<unsigned long long, int> closed;

    while (!open.empty())
    {
        current = open.top(), open.pop();
        closed[current.board] = current.score;

        if (current.board == SOLVED) { print(current); return true; }

        for (int dir = 0; dir < SQUARES; dir++)
        {
            if (current.depth && ((dir + 2) % 4) == GET(current.hmove, current.lmove, (current.depth - 1))) continue;
            if (!getSuccessor(current, successor, dir)) continue;
            successor.score = getScore(successor.board, successor.depth);
            auto it = closed.find(successor.board);
            if (it != closed.end())
            {
                if (successor.score >= (*it).second) continue;
                closed.erase(it);
            }
            open.push(successor);
        }
    }

    return false;
}

// [IDA*搜索]
bool IDAStar(unsigned long long board, int blanki, int blankj)
{
    if (board == SOLVED) { cout << '\n'; return true; }

    state current, successor;
    int highDepth = 0, lowDepth = getScore(board, 0);

    while (true)
    {
        highDepth = ((highDepth < lowDepth) ? lowDepth : (highDepth + 1));
        lowDepth = INT_MAX;

        stack<state> open;
        open.push(state(board, 0LL, 0LL, 0, 0, blanki, blankj));

        while (!open.empty())
        {
            current = open.top(), open.pop();
            for (int dir = 0; dir < SQUARES; dir++)
            {
                if (current.depth && ((dir + 2) % 4) == GET(current.hmove, current.lmove, (current.depth - 1))) continue;
                if (!getSuccessor(current, successor, dir)) continue;
                if (successor.board == SOLVED) { print(successor); return true; }
                successor.score = getScore(successor.board, successor.depth);
                if (successor.score < highDepth) open.push(successor);
                else lowDepth = min(lowDepth, successor.score);
            }
        }
    }

    return false;
}

void solvePuzzle(unsigned long long board, int blanki, int blankj)
{
    // 深度优先搜索。
    //dfs(board, blanki, blankj);

    // 宽度优先搜索。
    //bfs(board, blanki, blankj);

    // A*搜索。解长度在30-50步之间的局面平均需要7s。UVa RT 1.004s。
    //AStar(board, blanki, blankj);

    // IDA*搜索。解长度在30-50步之间的局面平均需要1.5s。UVa RT 0.120s。
    IDAStar(board, blanki, blankj);
}

int main(int argc, char *argv[])
{
    getManhattan();

    int cases, digit, blanki, blankj;
    vector<int> tiles;
    unsigned long long board;

    cin >> cases;
    while (cases--)
    {
        tiles.clear();
        board = 0;
        for (int i = 0; i < SQUARES * SQUARES; i++)
        {
            cin >> digit;
            tiles.push_back(digit);
            board |= ((unsigned long long)(digit) << (4 * i));
            if (digit == 0) blanki = i / 4, blankj = i % 4;
        }

        if (solvable(tiles)) solvePuzzle(board, blanki, blankj);
        else cout << "This puzzle is not solvable.\n";
    }

    return 0;
}
