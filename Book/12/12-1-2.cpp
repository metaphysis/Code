const int MAX_SIZE = 100;

int grid[MAX_SIZE][MAX_SIZE], m, n;

void flood_fill(int i, int j, char old, char target)
{
    if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == old)
    {
        grid[i][j] = target;

        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
                flood_fill(i + x, j + y, old, target);
    }
}
