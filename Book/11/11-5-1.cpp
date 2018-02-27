int med(string S, string T)
{
    int cells[16][16];

    // 为每个字符串起始位置增加一个空格，将字符串序号和表格序号对齐，方便处理。
    S = ' ' + S, T = ' ' + T;
    int M = S.length() - 1, N = T.length() - 1;

    // 初始化表格。
    cells[0][0] = 0;
    for (int i = 1; i <= M; i++) cells[i][0] = i;
    for (int j = 1; j <= N; j++) cells[0][j] = j;

    // 自底向上动态规划求解。
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
        {
            cells[i][j] = min(cells[i - 1][j], cells[i][j - 1]) + 1;
            if (S[i] == T[j])
                cells[i][j] = min(cells[i][j], cells[i - 1][j - 1]);
            else
                cells[i][j] = min(cells[i][j], cells[i - 1][j - 1] + 1);
        }

    return cells[M][N];
}
