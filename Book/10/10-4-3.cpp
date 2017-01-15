const int MAXV = 1000;

int weight[MAXV][MAXV], n;

for (int k = 1; k <= n; k++)
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int through = weight[i][k] + weight[k][j];
			if (weight[i][j] > through) weight[i][j] = through;
		}
