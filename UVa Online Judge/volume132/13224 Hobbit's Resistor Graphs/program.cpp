// Hobbit's Resistor Graphs
// UVa ID: 13224
// Verdict: Accepted
// Submission Date: 2026-10-31
// UVa Run Time: 0.830s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 200005;
const int BUF_SIZE = 1 << 20;

class FastInput {
private:
	char buffer[BUF_SIZE];
	int index;
	int size;

	inline char get_char() {
		if (index >= size) {
			size = (int)fread(buffer, 1, BUF_SIZE, stdin);
			index = 0;
			if (size == 0) return 0;
		}
		return buffer[index++];
	}

public:
	FastInput(): index(0), size(0) {}

	bool read_int(int& x) {
		char c;
		do {
			c = get_char();
			if (!c) return false;
		} while (c <= ' ');
		int sign = 1;
		if (c == '-') {
			sign = -1;
			c = get_char();
		}
		x = 0;
		while (c >= '0' && c <= '9') {
			x = x * 10 + c - '0';
			c = get_char();
		}
		x *= sign;
		return true;
	}
};

vector<int> graph[N];
vector<int> tree[N];

int n, m;
int ts, dfn[N], low[N], stk[N], tp;
int ccnt, p[N], w[N];
ll ans;

struct VBCC {
	struct EdgeNode {
		int u, v;
		int lc, rc, pa;
		bool series;

		EdgeNode(int u_, int v_, bool series_ = false, int lc_ = -1, int rc_ = -1): u(u_), v(v_), lc(lc_), rc(rc_), pa(-1), series(series_) {}
	};

	typedef unordered_map<int, int> InnerMap;
	typedef unordered_map<int, InnerMap> OuterMap;

	vector<EdgeNode> e;
	OuterMap mp;
	int key;

	void clear() {
		e.clear();
		mp.clear();
		key = 0;
	}

	int add_edge(int x, int y) {
		int id = (int)e.size();
		e.emplace_back(x, y);
		InnerMap& mx = mp[x];
		InnerMap::iterator it = mx.find(y);
		if (it == mx.end()) {
			mx.emplace(y, id);
			mp[y].emplace(x, id);
			return id;
		}
		int nxt = (int)e.size();
		e.emplace_back(x, y, false, it->second, id);
		e[it->second].pa = nxt;
		e[id].pa = nxt;
		it->second = nxt;
		mp[y][x] = nxt;
		return id;
	}

	void compress() {
		mp.reserve(mp.size() * 2 + 1);
		vector<OuterMap::iterator> todo;
		todo.reserve(mp.size());
		for (OuterMap::iterator it = mp.begin(); it != mp.end(); ++it) {
			if (it->second.size() == 2) todo.push_back(it);
		}
		while (!todo.empty()) {
			OuterMap::iterator cur = todo.back();
			todo.pop_back();
			if (cur->second.size() != 2) continue;
			int x = cur->first;
			InnerMap::iterator ity = cur->second.begin();
			InnerMap::iterator itz = ity;
			++itz;
			int y = ity->first;
			int z = itz->first;
			int left_id = ity->second;
			int right_id = itz->second;
			int id = add_edge(y, z);
			e[id].lc = left_id;
			e[id].rc = right_id;
			e[id].series = true;
			e[left_id].pa = id;
			e[right_id].pa = id;
			cur->second.clear();
			mp[y].erase(x);
			mp[z].erase(x);
			OuterMap::iterator iy = mp.find(y);
			if (iy != mp.end() && iy->second.size() == 2) todo.push_back(iy);
			OuterMap::iterator iz = mp.find(z);
			if (iz != mp.end() && iz->second.size() == 2) todo.push_back(iz);
		}
	}

	struct EvalResult {
		int cut_cnt;
		int dw;
		int u;
		int v;
		bool key_cut;
	};

	EvalResult series_compose(EvalResult x, EvalResult y) {
		int l, mid, r;
		if (x.u == y.u) {
			l = x.v;
			mid = x.u;
			r = y.v;
		} else if (x.u == y.v) {
			l = x.v;
			mid = x.u;
			r = y.u;
		} else if (x.v == y.u) {
			l = x.u;
			mid = x.v;
			r = y.v;
		} else {
			l = x.u;
			mid = x.v;
			r = y.u;
		}
		EvalResult ret;
		ret.cut_cnt = x.cut_cnt + y.cut_cnt + w[mid];
		ret.dw = x.dw + y.dw;
		ret.u = l;
		ret.v = r;
		ret.key_cut = x.key_cut || y.key_cut || mid == key;
		ans += (ll)(w[l] + x.cut_cnt) * (w[r] + y.cut_cnt);
		if (l == key || x.key_cut) ret.dw += w[r] + y.cut_cnt;
		if (r == key || y.key_cut) ret.dw += w[l] + x.cut_cnt;
		return ret;
	}

	EvalResult parallel_compose(EvalResult x, EvalResult y, bool last) {
		EvalResult ret;
		ret.cut_cnt = 0;
		ret.dw = x.dw + y.dw;
		ret.u = x.u;
		ret.v = x.v;
		ret.key_cut = false;
		ans -= (ll)w[x.u] * w[x.v];
		if (x.u == key) ret.dw -= w[x.v];
		if (x.v == key) ret.dw -= w[x.u];
		if (last) {
			ans += (ll)x.cut_cnt * y.cut_cnt;
			if (x.key_cut) ret.dw += y.cut_cnt;
			if (y.key_cut) ret.dw += x.cut_cnt;
		}
		return ret;
	}

	EvalResult eval(int x) {
		if (e[x].lc != -1) {
			EvalResult left = eval(e[x].lc);
			EvalResult right = eval(e[x].rc);
			if (e[x].series) return series_compose(left, right);
			return parallel_compose(left, right, e[x].pa == -1);
		}
		ans += (ll)w[e[x].u] * w[e[x].v];
		if (e[x].u == key) {
			EvalResult ret = {0, w[e[x].v], e[x].u, e[x].v, false};
			return ret;
		}
		if (e[x].v == key) {
			EvalResult ret = {0, w[e[x].u], e[x].u, e[x].v, false};
			return ret;
		}
		EvalResult ret = {0, 0, e[x].u, e[x].v, false};
		return ret;
	}

	void calc(int key_) {
		if (e.empty()) return;
		compress();
		int root = -1;
		int root_count = 0;
		for (int i = 0; i < (int)e.size(); ++i) {
			if (e[i].pa == -1) {
				root = i;
				++root_count;
			}
		}
		if (root_count != 1) return;
		key = key_;
		EvalResult result = eval(root);
		w[key] += result.dw;
	}
};

VBCC g[N];

void tarjan(int x) {
	low[x] = dfn[x] = ++ts;
	stk[++tp] = x;
	for (int y: graph[x]) {
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
			if (low[y] == dfn[x]) {
				++ccnt;
				for (int t = 0; t != y; --tp) {
					t = stk[tp];
					tree[ccnt].push_back(t);
					tree[t].push_back(ccnt);
					p[t] = ccnt;
				}
				tree[ccnt].push_back(x);
				tree[x].push_back(ccnt);
				p[ccnt] = x;
			}
		} else {
			low[x] = min(low[x], dfn[y]);
		}
	}
}

void dfs(int x) {
	for (int y: tree[x]) {
		if (y != p[x]) dfs(y);
	}
	if (x > n) g[x].calc(p[x]);
}

int main() {
	FastInput input;
	while (input.read_int(n)) {
		input.read_int(m);
		int limit = 2 * n + 2;
		for (int i = 1; i < limit; ++i) {
			graph[i].clear();
			tree[i].clear();
			g[i].clear();
		}
		fill(dfn, dfn + limit, 0);
		fill(low, low + limit, 0);
		fill(stk, stk + limit, 0);
		fill(p, p + limit, 0);
		fill(w, w + limit, 0);
		ts = 0;
		tp = 0;
		ccnt = n;
		ans = 0;
		for (int i = 0; i < m; ++i) {
			int x, y;
			input.read_int(x);
			input.read_int(y);
			graph[x].push_back(y);
			graph[y].push_back(x);
		}
		vector<int> roots;
		roots.reserve(n);
		for (int x = 1; x <= n; ++x) {
			if (!dfn[x]) {
				tarjan(x);
				--tp;
				roots.push_back(x);
			}
		}
		for (int x = 1; x <= n; ++x) {
			for (int y: graph[x]) {
				if (p[p[x]] == y || (p[x] == p[y] && x < y)) {
					g[p[x]].add_edge(x, y);
				}
			}
		}
		fill(w, w + limit, 1);
		for (int root: roots) dfs(root);
		printf("%lld\n", ans);
	}
	return 0;
}
