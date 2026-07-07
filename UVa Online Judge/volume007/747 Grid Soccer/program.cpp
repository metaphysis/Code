// Grid Soccer
// UVa ID: 747
// Verdict: Accepted
// Submission Date: 2026-07-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct state {
	int x, y, kick, dist;
	bool operator>(const state& o) const {
		if (kick != o.kick) return kick > o.kick;
		return dist > o.dist;
	}
};

int s, g, p, n;
vector<pair<int,int>> players;

int bestKick[32][32], bestDist[32][32];
pair<int,int> parent[32][32];

bool covered(int x, int y) {
	for (auto &pl : players) {
		int a = pl.first, b = pl.second;
		if (abs(x - a) <= p && abs(y - b) <= p)
			return true;
	}
	return false;
}

bool valid(int x, int y) {
	return x >= 0 && x <= 2 * s && y >= 0 && y <= 2 * s;
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
	int scenario = 0;
	while (cin >> s, s) {
		cin >> g >> p >> n;
		players.clear();
		for (int i = 0; i < n; ++i) {
			int a, b;
			cin >> a >> b;
			players.push_back({a + s, b});
		}
		for (int i = 0; i < 32; i++)
			for (int j = 0; j < 32; j++) {
				bestKick[i][j] = bestDist[i][j] = INT_MAX;
				parent[i][j] = {0, 0};
			}
		priority_queue<state, vector<state>, greater<state>> pq;
		int sx = s, sy = 0;
		bestKick[sx][sy] = bestDist[sx][sy] = 0;
		pq.push({s, 0, 0, 0});
		bool found = false;
		state target;
		int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
		while (!pq.empty()) {
			state now = pq.top();
			pq.pop();
			int cx = now.x, cy = now.y;
			int cKick = now.kick, cDist = now.dist;
			if (cKick != bestKick[cx][cy] || cDist != bestDist[cx][cy]) continue;
			if (cy == 2 * s && abs(cx - s) <= g) {
				found = true;
				target = now;
				break;
			}
			if (cKick == n + 1) continue;
			for (int d = 0; d < 4; ++d) {
				int nx = cx, ny = cy, step = 0;
				while (true) {
					nx += dx[d], ny += dy[d];
					if (!valid(nx, ny)) break;
					if (covered(nx, ny)) break;
					step++;
					int nk = cKick + 1, nd = cDist + step;
					if (nk > n + 1) break;
					if (nk < bestKick[nx][ny] || (nk == bestKick[nx][ny] && nd < bestDist[nx][ny])) {
						bestKick[nx][ny] = nk;
						bestDist[nx][ny] = nd;
						parent[nx][ny] = {cx, cy};
						pq.push({nx, ny, nk, nd});
					}
				}
			}
		}
		if (scenario) cout << "\n";
		cout << "Scenario " << ++scenario << ".\n";
		if (!found) cout << "Situation Impossible\n";
		else {
			vector<pair<int,int>> path;
			int cx = target.x, cy = target.y;
			while (!(cx == s && cy == 0)) {
				path.push_back({cx, cy});
				auto p = parent[cx][cy];
				cx = p.first, cy = p.second;
			}
			path.push_back({s, 0});
			reverse(path.begin(), path.end());
			cout << "Goal with " << target.kick << " kicks: ";
			for (size_t i = 0; i < path.size(); ++i) cout << "(" << path[i].first - s << "," << path[i].second << ")";
			cout << "\n";
		}
	}
	return 0;
}
