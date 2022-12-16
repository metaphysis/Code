// Coffee Central
// UVa ID: 1105
// Verdict: Accepted
// Submission Date: 2022-11-30
// UVa Run Time: 1.200s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2048;

int sum[MAXN][MAXN];

void rotate(int x, int y, int &tx, int &ty, int dx, int dy)
{
	tx = x - y + dy, ty = x + y;
}

void query(int m, int dx, int dy)
{
	int ret = 0, ret_x = 1, ret_y = 1, tx, ty;
	for (int j = 1; j <= dy; j++) {
		for (int i = 1; i <= dx; i++) {
			rotate(i, j, tx, ty, dx, dy);
			int lx, rx, ly, ry, cnt;
			lx = max(tx - m, 1);
			ly = max(ty - m, 1);
			rx = min(tx + m, dx + dy);
			ry = min(ty + m, dx + dy);
			cnt = sum[rx][ry] - sum[rx][ly - 1] - sum[lx - 1][ry] + sum[lx - 1][ly - 1];
			if (cnt > ret) { ret = cnt, ret_x = i, ret_y = j; }
		}
	}
	cout << ret << " (" << ret_x << ',' << ret_y << ")\n";
}

int main(int argc, char *argv[])
{
	int dx, dy, n, q;
	int x, y, tx, ty, m, cases = 0;
	while (cin >> dx >> dy >> n >> q, dx) {
		memset(sum, 0, sizeof(sum));
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			rotate(x, y, tx, ty, dx, dy);
			sum[tx][ty]++;
		}
		for (int i = 1; i <= dx + dy; i++) {
			for (int j = 1, s = 0; j <= dx + dy; j++) {
				s += sum[i][j];
				sum[i][j] = sum[i - 1][j] + s;
			}
		}
		cout << "Case " << ++cases << ":\n";
		for (int i = 0; i < q; i++) {
			cin >> m;
			query(m, dx, dy);
		}
	}
	return 0;
}
