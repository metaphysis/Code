const int MAXN = 1000;

int weight[MAXN][MAXN], n;

for (int k = 1; k <= n; k++)
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			int through = weight[i][k] + weight[k][j];
			if (through < weight[i][j])
				weight[i][j] = through;
		}
