// String Distance and Transform Process
// UVa IDs: 526
// Verdict: Accepted
// Submission Date: 2016-02-13
// UVa Run Time: 0.009s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>

using namespace std;

const int NONE = -1, DELETE = 0, INSERT = 1, CHANGE = 2, MATCH = 3;

// 定义动态规划表格单元。
struct cell
{
    int cost, operation;
};

cell cells[100][100];
string S, T, operationCode[3] = {" Delete ", " Insert ", " Replace "};
int M, N, deletions, insertions, index;

// 显示操作步骤，注意删除操作其序号会因为已有的删除和插入操作而发生变化。
void displayPath(int i, int j)
{
    if (cells[i][j].operation >= DELETE && cells[i][j].operation <= CHANGE)
    {
        cout << index++;
        cout << operationCode[cells[i][j].operation];

        if (cells[i][j].operation == CHANGE)
        {
            cout << j << "," << T[j] << "\n";
        }
        else if (cells[i][j].operation == DELETE)
        {
            cout << (i + insertions - deletions) << "\n";
            deletions++;
        }
        else if (cells[i][j].operation == INSERT)
        {
            cout << j << "," << T[j] << "\n";
            insertions++;
        }
    }
}

// 利用递归构建操作步骤。
void findPath(int i, int j)
{
    if (cells[i][j].operation != NONE)
    {
        if (cells[i][j].operation == DELETE)
            findPath(i - 1, j);
        else if (cells[i][j].operation == INSERT)
            findPath(i, j - 1);
        else
            findPath(i - 1, j - 1);
    }
    
    displayPath(i, j);
}

void minimumEditDistance()
{
    // 为每个字符串起始位置增加一个空格，将字符串序号和表格序号对齐，方便处理。
    // 因此其长度需要相应减去 1。
    S = ' ' + S;
    T = ' ' + T;
    M = S.length() - 1;
    N = T.length() - 1;

    // 初始化表格。
    cells[0][0] = (cell){0, NONE};
    for (int i = 1; i <= M; i++)
        cells[i][0] = (cell){i, DELETE};
    for (int j = 1; j <= N; j++)
        cells[0][j] = (cell){j, INSERT};

    // 自底向上动态规划求解。
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
        {
            cells[i][j] = (cell){cells[i - 1][j].cost + 1, DELETE};

            if (cells[i][j].cost > (cells[i][j - 1].cost + 1))
                cells[i][j] = (cell){cells[i][j - 1].cost + 1, INSERT};

            if (S[i] == T[j])
            {
                if (cells[i][j].cost > cells[i - 1][j - 1].cost)
                    cells[i][j] = (cell){cells[i - 1][j - 1].cost, MATCH};
            }
            else
            {
                if (cells[i][j].cost > (cells[i - 1][j - 1].cost + 1))
                    cells[i][j] = (cell){cells[i - 1][j - 1].cost + 1, CHANGE};
            }
        }

    // 反向构建操作步骤。
    deletions = 0;
    insertions = 0;
    index = 1;
    cout << cells[M][N].cost << "\n";
    findPath(M, N);
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    bool printBlankLine = false;
    while (getline(cin, S) && getline(cin, T))
    {
        if (printBlankLine == false)
            printBlankLine = true;
        else
            cout << "\n";
        minimumEditDistance();
    }
    
    return 0;
}
