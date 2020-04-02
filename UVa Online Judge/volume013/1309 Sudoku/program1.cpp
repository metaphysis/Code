// Sudoku
// UVa ID: 1309
// Verdict: Accepted
// Submission Date: 2019-08-14
// UVa Run Time: 0.190S
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net
//
// 使用舞蹈链（dancing links）X算法求解数独问题。
// 代码实现参考: 
// https://github.com/morris821028/UVa/blob/master/volume013/1309%20-%20Sudoku.cpp

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 17000, INF = 0x3f3f3f3f;

int n, idx, root;
int L[MAXV], R[MAXV], U[MAXV], D[MAXV], T[MAXV], CH[MAXV], RH[MAXV];
int S[MAXV], O[MAXV];

void cover(int c)
{
	L[R[c]] = L[c];
    R[L[c]] = R[c];
	for (int i = D[c]; i != c; i = D[i])
		for (int j = R[i]; j != i; j = R[j])
		{
			U[D[j]] = U[j];
			D[U[j]] = D[j];
			S[CH[j]]--;
		}
}

void uncover(int c)
{
	for (int i = U[c]; i != c; i = U[i])
		for (int j = L[i]; j != i; j = L[j])
		{
			U[D[j]] = j;
			D[U[j]] = j;
			S[CH[j]]++;
		}
	L[R[c]] = R[L[c]] = c;
}

void render(int k)
{
	static int cache[MAXV];
	for (int i = 0; i < k; i++)
		cache[T[O[i]]] = RH[O[i]];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		    cout << (char)(cache[i * 16 + j] + 'A');
		cout << '\n';
	}
}

bool dfs(int k)
{
	if (R[root] == root) { render(k); return true; }
	int c;
	for (int i = R[root], tmp = INF; i != root; i = R[i])
		if (S[i] < tmp)
			tmp = S[i], c = i;
	cover(c);
	for (int i = D[c]; i != c; i = D[i])
	{
		O[k] = i;
		for (int j = R[i]; j != i; j = R[j]) cover(CH[j]);
		if (dfs(k + 1)) return true;
		for (int j = L[i]; j != i; j = L[j]) uncover(CH[j]);
	}
	uncover(c);
	return false;
}

int addNode(int up, int down, int left, int right)
{
	U[idx] = up, D[idx] = down, L[idx] = left, R[idx] = right;
	D[up] = U[down] = R[left] = L[right] = idx;
	return idx++;
}

void addRow(int tot, int cln[], int rh, int data)
{
	for (int i = 0, c, row = -1, next; i < tot; i++)
	{
		c = cln[i];
		CH[idx] = c, T[idx] = data, S[c]++;
		if (row == -1)
		{
			row = addNode(U[CH[c]], CH[c], idx, idx);
			RH[row] = rh;
		}
		else
		{
			next = addNode(U[CH[c]], CH[c], L[row], row);
			RH[next] = rh;
		}
	}
}

void initialize()
{
	n = 16;
	idx = 0;
	root = addNode(0, 0, 0, 0);
	for (int i = 1; i <= 4 * n * n; i++)
	{
		addNode(i, i, L[root], root);
		CH[i] = i, S[i] = 0;
	}
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

	int cln[256], cases = 0;
	char letter, grid[20][20];

	while (cin >> letter)
	{
	    cin.putback(letter);
		initialize();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
			    cin >> grid[i][j];
				if (grid[i][j] == '-')
				{
					for (int c = 0; c < n; c++)
					{
						int tot = 0;
						cln[tot++] = i * n + j + 1;
						cln[tot++] = n * n + i * n + c + 1;
						cln[tot++] = 2 * n * n + j * n + c + 1;
						cln[tot++] = 3 * n * n + (i / 4 * 4 + j / 4) * n + c + 1;
						addRow(tot, cln, c, i * n + j);
					}
				}
				else
				{
					int c = grid[i][j] - 'A', tot = 0;
					cln[tot++] = i * n + j + 1;
					cln[tot++] = n * n + i * n + c + 1;
					cln[tot++] = 2 * n * n + j * n + c + 1;
					cln[tot++] = 3 * n * n + (i / 4 * 4 + j / 4) * n + c + 1;
					addRow(tot, cln, c, i * n + j);
				}
			}
		if (cases++) cout << '\n';
		dfs(0);
	}
	return 0;
}
