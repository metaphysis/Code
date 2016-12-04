const int MAX_SIZE = 100;

char grid[MAX_SIZE][MAX_SIZE], rows, columns;

void flood_fill(int i, int j, char old, char replaced)
{
    if (i >= 0 && i < rows && j >= 0 && j < columns && grid[i][j] == old)
    {
        grid[i][j] = replaced;
        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
                flood_fill(i + x, j + y, old, replaced);
    }
}
