#include <bits/stdc++.h>
using namespace std;

const int M = 1 << 23;
const int REV_MASK = 0x671C70;
const int MIR_MASK = 0x18E38E;

struct StatusVal {
	int sig;
	int num;
	bool operator==(const StatusVal &val) const {
		return sig == val.sig && num == val.num;
	}
} st[M];

vector<int> ways[64][8];
int dir[8][2] = {1, 0, -1, 0, 0, 1, 0, -1, 1, 1, 1, -1, -1, 1, -1, -1};
bool vis[M], isCheckStatus[M];
int deg[M], q[M], head, tail;

inline void qPush(int x) {
	q[tail++] = x;
}
inline int qPop() {
	return q[head++];
}
inline bool qEmpty() {
	return head == tail;
}

inline void toStatus(int S, int &k0, int &q0, int &k1, int &r1, int &mv) {
	mv = S & 1;
	S >>= 1;
	r1 = S & 63;
	S >>= 6;
	k1 = S & 63;
	S >>= 6;
	q0 = S & 63;
	S >>= 6;
	k0 = S + (S & 12);
}

inline int fromStatus(int k0, int q0, int k1, int r1, int mv) {
	int kk = ((k0 & 24) >> 1) | (k0 & 3);
	int res = (((kk << 6 | q0) << 6 | k1) << 6 | r1) << 1 | mv;
	if (k0 & 32) res ^= REV_MASK;
	if (k0 & 4) res ^= MIR_MASK;
	return res;
}

inline void tryTransfer(int S, const StatusVal &v) {
	if (vis[S]) return;
	if (v.sig == -1) {
		vis[S] = true;
		qPush(S);
		st[S] = {1, v.num + 1};
	} else if (v.sig == 1) {
		st[S] = {-1, v.num + 1};
		if (--deg[S] == 0) {
			vis[S] = true;
			qPush(S);
		}
	}
}

string genMove(char chess, int pos, bool kill, bool check, bool mate) {
	string res(1, chess);
	if (kill) res.push_back('x');
	res.push_back('a' + pos / 8);
	res.push_back('1' + pos % 8);
	if (mate) res.push_back('#');
	else if (check) res.push_back('+');
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	for (int i = 0; i < 64; i++) {
		int x = i / 8, y = i % 8;
		for (int j = 0; j < 8; j++) {
			int xx = x, yy = y;
			while (1) {
				xx += dir[j][0];
				yy += dir[j][1];
				if (xx < 0 || xx >= 8 || yy < 0 || yy >= 8) break;
				ways[i][j].push_back(xx * 8 + yy);
			}
		}
	}
	for (int i = 0; i < M; i++) {
		int k0, q0, k1, r1, mv;
		toStatus(i, k0, q0, k1, r1, mv);
		if (k0 == k1 || k0 == r1 || k1 == q0 || q0 == r1) continue;
		int res = 0;
		bool win = false;
		if (mv == 0) {
			for (int j = 0; j < 8 && !win; j++)
				if (!ways[k0][j].empty()) {
					int nxt = ways[k0][j][0];
					if (nxt == k1) {
						win = true;
						break;
					}
					if (nxt != q0) ++res;
				}
			if (q0 != k0)
				for (int j = 0; j < 8 && !win; j++)
					for (auto s : ways[q0][j]) {
						if (s == k1) {
							win = true;
							break;
						}
						if (s == k0) break;
						++res;
						if (s == r1) break;
					}
		} else {
			for (int j = 0; j < 8 && !win; j++)
				if (!ways[k1][j].empty()) {
					int nxt = ways[k1][j][0];
					if (nxt == k0) {
						win = true;
						break;
					}
					if (nxt != r1) ++res;
				}
			if (r1 != k1)
				for (int j = 0; j < 4 && !win; j++)
					for (auto s : ways[r1][j]) {
						if (s == k0) {
							win = true;
							break;
						}
						if (s == k1) break;
						++res;
						if (s == q0) break;
					}
		}
		if (win) {
			qPush(i);
			vis[i] = true;
			st[i] = {1, 0};
			isCheckStatus[i] = true;
		} else {
			deg[i] = res;
		}
	}
	for (int i = 0; i < M; i++) {
		int k0, q0, k1, r1, mv;
		toStatus(i, k0, q0, k1, r1, mv);
		if (k0 == k1 || k0 == r1 || k1 == q0 || q0 == r1) continue;
		if (isCheckStatus[i ^ 1] || isCheckStatus[i]) continue;
		bool canMove = false;
		if (mv == 0) {
			for (int j = 0; j < 8 && !canMove; j++)
				if (!ways[k0][j].empty()) {
					int nxt = ways[k0][j][0];
					if (nxt != k1 && nxt != q0) {
						int _id = fromStatus(nxt, q0, k1, (r1 == nxt ? k1 : r1), 1);
						canMove |= !isCheckStatus[_id];
					}
				}
			if (q0 != k0)
				for (int j = 0; j < 8 && !canMove; j++)
					for (auto s : ways[q0][j]) {
						if (s == k1 || s == k0) break;
						int _id = fromStatus(k0, s, k1, (r1 == s ? k1 : r1), 1);
						canMove |= !isCheckStatus[_id];
						if (s == r1) break;
					}
		} else {
			for (int j = 0; j < 8 && !canMove; j++)
				if (!ways[k1][j].empty()) {
					int nxt = ways[k1][j][0];
					if (nxt != k0 && nxt != r1) {
						int _id = fromStatus(k0, (q0 == nxt ? k0 : q0), nxt, r1, 0);
						canMove |= !isCheckStatus[_id];
					}
				}
			if (r1 != k1)
				for (int j = 0; j < 4 && !canMove; j++)
					for (auto s : ways[r1][j]) {
						if (s == k0 || s == k1) break;
						int _id = fromStatus(k0, (q0 == s ? k0 : q0), k1, s, 0);
						canMove |= !isCheckStatus[_id];
						if (s == q0) break;
					}
		}
		if (!canMove) vis[i] = true;
	}
	while (!qEmpty()) {
		int S = qPop();
		int k0, q0, k1, r1, mv;
		toStatus(S, k0, q0, k1, r1, mv);
		bool queenDead = (q0 == k0);
		bool rookDead = (r1 == k1);
		if (mv == 1) {
			for (int j = 0; j < 8; j++)
				if (!ways[k0][j].empty()) {
					int nxt = ways[k0][j][0];
					if (nxt != q0 && nxt != k1 && nxt != r1) {
						tryTransfer(fromStatus(nxt, (queenDead ? nxt : q0), k1, r1, 0), st[S]);
						if (rookDead)
							tryTransfer(fromStatus(nxt, (queenDead ? nxt : q0), k1, k0, 0), st[S]);
					}
				}
			if (!queenDead)
				for (int j = 0; j < 8; j++)
					for (auto s : ways[q0][j]) {
						if (s == k0 || s == k1 || s == r1) break;
						tryTransfer(fromStatus(k0, s, k1, r1, 0), st[S]);
						if (rookDead)
							tryTransfer(fromStatus(k0, s, k1, q0, 0), st[S]);
					}
		} else {
			for (int j = 0; j < 8; j++)
				if (!ways[k1][j].empty()) {
					int nxt = ways[k1][j][0];
					if (nxt != q0 && nxt != k0 && nxt != r1) {
						tryTransfer(fromStatus(k0, q0, nxt, (rookDead ? nxt : r1), 1), st[S]);
						if (queenDead)
							tryTransfer(fromStatus(k0, k1, nxt, (rookDead ? nxt : r1), 1), st[S]);
					}
				}
			if (!rookDead)
				for (int j = 0; j < 4; j++)
					for (auto s : ways[r1][j]) {
						if (s == k1 || s == k0 || s == q0) break;
						tryTransfer(fromStatus(k0, q0, k1, s, 1), st[S]);
						if (queenDead)
							tryTransfer(fromStatus(k0, r1, k1, s, 1), st[S]);
					}
		}
	}
	for (int i = 0; i < M; i++)
		if (!vis[i]) st[i] = {0, 0};
	int t;
	cin >> t;
	while (t--) {
		int k0 = -1, q0 = -1, r0 = -1, k1 = -1, q1 = -1, r1 = -1;
		for (int u = 0; u < 4; u++) {
			string s;
			cin >> s;
			int pos = (s[2] - 'a') * 8 + (s[3] - '1');
			if (s[0] == 'W') {
				if (s[1] == 'K') k0 = pos;
				else if (s[1] == 'Q') q0 = pos;
				else r0 = pos;
			} else {
				if (s[1] == 'K') k1 = pos;
				else if (s[1] == 'Q') q1 = pos;
				else r1 = pos;
			}
		}
		char first;
		cin >> first;
		bool rev = false;
		if (q0 == -1) {
			swap(k0, k1);
			q0 = q1;
			r1 = r0;
			rev = true;
		}
		int mv = (first == 'B') ^ rev;
		int id = fromStatus(k0, q0, k1, r1, mv);
		if (st[id].sig == 0)
			puts("Draw");
		else
			printf("%s mates in %d\n", ((st[id].sig == 1) ^ (first == 'B')) ? "White" : "Black", st[id].num / 2);
		if (st[id].num == 1) {
			printf("\n\n");
			continue;
		}
		StatusVal expect = {0, 0};
		if (st[id].sig != 0) expect = {-st[id].sig, st[id].num - 1};
		bool mateIf = (expect.num == 1);
		vector<string> answers;
		if (mv == 0) {
			for (int j = 0; j < 8; j++)
				if (!ways[k0][j].empty()) {
					int nxt = ways[k0][j][0];
					if (nxt != k1 && nxt != q0) {
						int _id = fromStatus(nxt, q0, k1, (r1 == nxt ? k1 : r1), 1);
						if (st[_id] == expect)
							answers.push_back(genMove('K', nxt, r1 == nxt, isCheckStatus[_id ^ 1], mateIf));
					}
				}
			for (int j = 0; j < 8; j++)
				for (auto s : ways[q0][j]) {
					if (s == k1 || s == k0) break;
					int _id = fromStatus(k0, s, k1, (r1 == s ? k1 : r1), 1);
					if (st[_id] == expect)
						answers.push_back(genMove('Q', s, r1 == s, isCheckStatus[_id ^ 1], mateIf));
					if (s == r1) break;
				}
		} else {
			for (int j = 0; j < 8; j++)
				if (!ways[k1][j].empty()) {
					int nxt = ways[k1][j][0];
					if (nxt != k0 && nxt != r1) {
						int _id = fromStatus(k0, (q0 == nxt ? k0 : q0), nxt, r1, 0);
						if (st[_id] == expect)
							answers.push_back(genMove('K', nxt, q0 == nxt, isCheckStatus[_id ^ 1], mateIf));
					}
				}
			for (int j = 0; j < 4; j++)
				for (auto s : ways[r1][j]) {
					if (s == k0 || s == k1) break;
					int _id = fromStatus(k0, (q0 == s ? k0 : q0), k1, s, 0);
					if (st[_id] == expect)
						answers.push_back(genMove('R', s, q0 == s, isCheckStatus[_id ^ 1], mateIf));
					if (s == q0) break;
				}
		}
		sort(answers.begin(), answers.end());
		bool firstAns = true;
		for (auto &ele : answers) {
			if (!firstAns) putchar(' ');
			firstAns = false;
			printf("%s", ele.c_str());
		}
		printf("\n\n");
	}
	return 0;
}
