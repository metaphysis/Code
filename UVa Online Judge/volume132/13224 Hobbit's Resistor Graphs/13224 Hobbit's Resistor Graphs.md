 # 题目描述

给定一个无向简单图。对于一对不同的顶点 $u$ 和 $v$，指定它们为最终保留的两个端点，并对它们所在的连通分量反复执行以下操作：

- 如果某个非端点顶点的度数为 $2$，删除该顶点，并将它的两个邻点直接连边。
- 如果两个顶点之间存在多条平行边，只保留其中一条。

如果经过若干次操作后，该连通分量恰好只剩下顶点 $u$ 和 $v$，并且二者之间存在一条边，则称无序顶点对 $(u,v)$ 合法。

求所有合法无序顶点对的数量。

不同连通分量中的顶点不可能组成合法顶点对。图在初始状态下没有重边，但串联删除操作可能产生平行边，平行边可以通过并联删除操作合并。

# 输入格式

输入包含多组数据，每组数据占若干行，读入至文件结束。

每组数据的第一行包含两个整数 $n$ 和 $m$，分别表示顶点数和边数。

接下来 $m$ 行，每行包含两个整数 $x$ 和 $y$，表示一条无向边 $(x,y)$。顶点编号为 $1$ 到 $n$。

# 输出格式

对于每组数据，输出一行一个整数，表示合法无序顶点对的数量。

# 样例输入

```text
6 6
1 2
1 3
1 4
2 3
2 4
5 6
```

# 样例输出

```text
6
```

# 题目分析

固定一对端点 $u$ 和 $v$。由于操作只能删除端点以外的顶点，因此所有最终保留的结构都必须位于 $u$ 和 $v$ 所在的连通分量中。

串联删除一个度数为 $2$ 的顶点，本质上是把经过该顶点的两条边合并为一条边；并联删除则是将多条等价边合并为一条边。因此，能够最终化简为一条边的图，正是可以从一条边出发，通过边细分和增加平行边构造出来的图。这类图属于串并联图，也可以等价描述为树宽不超过 $2$ 的二连通图。

对于固定端点 $u$ 和 $v$，原图需要同时满足以下条件：

- 不能存在无法删除的割点分支，否则某些顶点最终会与主结构分离；
- 每个二连通块都必须能够通过串联和并联操作化简；
- 指定端点不能在化简过程中被删除；
- 化简完成后只能保留指定的两个端点。

直接枚举所有顶点对需要 $O(n^2)$ 的时间，无法满足大规模数据要求。算法需要在分解图结构的同时完成批量计数。

首先使用 $\texttt{Tarjan}$ 算法求出图的点双连通分量，并建立块割树。块割树中的两类节点分别表示：

- 原图顶点；
- 一个点双连通分量。

如果一个连通分量的块割树不是一条路径，则该连通分量一定存在分支结构。无论选择哪两个端点，都至少有一部分结构无法通过度数为 $2$ 的顶点删除，因此该连通分量不会贡献答案。

对于块割树中的每个点双连通分量，代码只保留属于该分量的原图边，并使用邻接表中的当前度数进行串联压缩。压缩过程将一条边抽象为表达式树中的叶节点：

- 串联两个边结构得到一个串联节点；
- 两个端点之间出现多条边时，将它们合并为一个并联节点。

这样，一个点双连通分量被表示为由串联节点、并联节点和原始边组成的表达式树。

在处理某个点双连通分量时，块割树的父节点被记为关键顶点 $key$。表达式树的动态信息包含以下内容：

- 当前结构的两个外部端点；
- 当前结构内部仍需处理的割点数量；
- 当前结构中与关键顶点相关的可计数数量；
- 当前结构是否已经包含关键顶点；
- 当前结构对答案的贡献。

串联合并时，两个子结构共享一个中间顶点。这个中间顶点如果不是最终端点，就可以被串联删除。设两个子结构的外部端点分别经过重排后为 $(l,mid)$ 和 $(mid,r)$，则合并后的结构外部端点为 $(l,r)$。此时，左侧可选顶点数量与右侧可选顶点数量的乘积会产生新的合法顶点对，因此将其加入答案。

并联合并时，两个子结构共享同一对外部端点。两个子结构都表示同一对端点之间的等价连接，因此外部端点对会被重复统计一次，需要先减去重复贡献。对于两个并联子结构内部的可选顶点，只有满足端点条件的组合才能形成新的合法顶点对，代码在并联合并的最后阶段完成相应统计。

点双连通分量处理完成后，得到的 `dw` 值表示该分量向块割树父顶点传递的有效顶点数量。代码将它累加到数组 `w` 中，使父分量在后续合并时能够直接使用子分量的统计结果。

## 样例分析

样例中，顶点 $1$、$2$、$3$、$4$ 构成一个菱形结构，顶点 $5$、$6$ 构成一条独立边。

在第一个连通分量中，除顶点对 $(3,4)$ 外，其余五对顶点都可以合法化简：

- $(1,2)$ 合法；
- $(1,3)$ 合法；
- $(1,4)$ 合法；
- $(2,3)$ 合法；
- $(2,4)$ 合法；
- $(3,4)$ 不合法。

当指定 $(3,4)$ 为端点时，顶点 $1$ 和顶点 $2$ 的度数都为 $3$，没有可以首先删除的非端点顶点，因此该顶点对不合法。

第二个连通分量只有一条边 $(5,6)$，该顶点对本身已经满足最终状态，因此贡献一对。

最终答案为：

$$
5+1=6
$$

# 解题思路

## 建立块割树

使用 $\texttt{Tarjan}$ 算法遍历原图。

对每个顶点 $x$，维护：

- $dfn[x]$：顶点 $x$ 的深度优先搜索编号；
- $low[x]$：从顶点 $x$ 的子树出发能够到达的最小深度优先搜索编号；
- 栈：保存当前深度优先搜索路径上的顶点。

当遍历树边 $(x,y)$ 后满足：

$$
low[y]=dfn[x]
$$

说明以 $y$ 为根的子树对应一个点双连通分量。将栈中顶点 $y$ 到顶点 $x$ 的部分取出，并建立一个新的分量节点，将该分量节点与其中所有原图顶点相连。

原图顶点编号为 $1$ 到 $n$，新建立的分量节点从 $n+1$ 开始编号，因此可以通过编号判断节点类型。

对于每个原图连通分量，记录其根节点，并在后续对对应的块割树执行深度优先遍历。

## 构造每个点双连通块的边结构

块割树建立后，遍历原图中的每条无向边。对于一条边 $(x,y)$，如果它属于同一个点双连通分量，则将它加入对应的 $\texttt{VBCC}$ 对象。

代码通过以下条件避免重复加入无向边：

$$
p[p[x]]=y
$$

或者：

$$
p[x]=p[y]\ \land\ x<y
$$

其中 $p$ 表示块割树中的父节点关系。

每个点双连通分量内部维护一个临时多重图：

- `mp[x][y]` 表示顶点 $x$ 到顶点 $y$ 当前对应的表达式边编号；
- `EdgeNode` 表示一条原始边或合并后的复合边；
- `lc` 和 `rc` 表示复合边的左右子结构；
- `pa` 表示当前边在表达式树中的父节点；
- `series` 表示当前复合边是否由串联合并得到。

## 串联压缩

如果临时多重图中的顶点 $x$ 当前度数为 $2$，设它的两个邻点为 $y$ 和 $z$，则可以删除 $x$，并把两条边 $(y,x)$ 和 $(x,z)$ 合并成一条边 $(y,z)$。

在表达式树中，新边记录为串联节点：

- 左子节点是 $(y,x)$；
- 右子节点是 $(x,z)$；
- 当前节点的两个外部端点是 $y$ 和 $z$；
- 中间顶点 $x$ 会在动态计算中被计入。

代码使用 `todo` 保存当前度数为 $2$ 的顶点。每次删除一个顶点后，只需要检查它的两个邻点是否也变成度数为 $2$，从而避免重复扫描所有顶点。

## 并联合并

当两个端点之间已经存在一条边，又加入一条相同端点的边时，代码会创建并联复合节点。该节点的两个子结构具有相同的外部端点。

并联结构会带来重复计数，因为相同的外部端点对在多个并联分支中表示同一个顶点对。因此在 `parallel_compose` 中先减去外部端点对的重复贡献，然后在最后一个并联分支合并时，根据两个子结构内部的有效数量补回跨分支产生的合法顶点对。

## 动态信息含义

表达式树中的 `EvalResult` 包含以下字段：

- `cut_cnt`：当前结构中仍然参与外部合并的割点数量；
- `dw`：当前结构需要传递给父结构的有效顶点数量；
- `u` 和 `v`：当前结构的两个外部端点；
- `key_cut`：当前结构是否包含关键顶点 `key`。

叶节点对应一条原始边。若原始边的某个端点是 `key`，则该边对父结构的传递数量会包含另一个端点；否则该叶节点不向关键顶点传递额外数量。

串联合并的主要计算为：

$$
ans\mathrel{+}=(w[l]+x.cut\_cnt)(w[r]+y.cut\_cnt)
$$

其中 $l$ 和 $r$ 是合并后的两个外部端点，$x$ 和 $y$ 是左右子结构。该乘积统计左侧和右侧分别选择一个有效顶点形成的顶点对。

并联合并时，先处理外部端点重复计数：

$$
ans\mathrel{-}=w[x.u]\times w[x.v]
$$

当所有并联分支都合并完成后，再根据两个分支内部的有效数量补充跨分支组合：

$$
ans\mathrel{+}=x.cut\_cnt\times y.cut\_cnt
$$

这些操作保证每个合法无序顶点对只被统计一次。

## 处理块割树

对块割树进行后序遍历：

- 先处理所有子节点；
- 再处理当前节点对应的点双连通分量；
- 处理完成后，将有效数量传递给父顶点。

对于一个点双连通分量，块割树父节点就是本次计算的关键顶点 `key`。调用 `calc` 函数时：

- 先执行串联压缩；
- 查找表达式树唯一的根节点；
- 从根节点递归计算动态信息；
- 将结果中的 `dw` 加入关键顶点的权值 `w[key]`。

如果一个 $\texttt{VBCC}$ 对象最终存在多个表达式树根节点，说明该结构无法被合并为一个完整的串并联表达式，此时不对该结构进行统计。

## 正确性说明

对每个点双连通分量，串联压缩只删除当前度数为 $2$ 的内部顶点，完全对应题目允许的串联操作。出现重边时，代码使用并联合并表示平行边的合并，因此表达式树中的每次合并都对应题目中的合法操作。

表达式树的每个叶节点对应原图中的一条边，每个内部节点对应一次串联或并联合并。因此，对表达式树进行后序动态计算，就等价于按照合法化简顺序处理整个点双连通分量。

串联合并时，左右两个子结构中分别选取的有效顶点能够在剩余结构中形成一对最终端点，代码通过乘法统计所有组合。并联合并时，多个分支共享同一对外部端点，代码先删除重复的外部端点贡献，再统计两个分支内部的跨分支组合。因此每个合法顶点对既不会漏计，也不会重复计数。

块割树保证了不同点双连通分量之间的连接关系。后序计算将子分量中能够向割点传递的有效数量加入 `w`，使父分量能够将这些顶点作为整体参与后续组合。若块割树存在分支，则总有一部分结构无法通过度数为 $2$ 的非端点删除，代码不会将这种无法合并的结构计入答案。

因此，算法最终得到的 `ans` 恰好等于所有合法无序顶点对的数量。

## 复杂度分析

设一组数据中有 $n$ 个顶点和 $m$ 条边。

$\texttt{Tarjan}$ 算法、块割树构造、边结构建立和表达式树计算都只对每个顶点和每条边进行常数次处理。使用哈希表后，哈希操作的均摊复杂度为 $O(1)$，因此总时间复杂度为：

$$
O(n+m)
$$

图结构、块割树、表达式节点、临时哈希表以及辅助数组均占用线性空间，总空间复杂度为：

$$
O(n+m)
$$

# 代码实现

```cpp
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
```

# 总结

本题的核心不是枚举端点对，而是把所有可能的化简过程转化为图结构分解和表达式树合并。

关键技巧包括：

- 使用 $\texttt{Tarjan}$ 算法求点双连通分量；
- 使用块割树表示不同双连通块之间的连接关系；
- 使用串联压缩消除度数为 $2$ 的内部顶点；
- 使用并联合并处理化简过程中产生的平行边；
- 在表达式树上维护外部端点、割点数量和关键顶点状态；
- 在合并过程中直接统计顶点对，避免 $O(n^2)$ 枚举；
- 使用哈希表降低块内边结构维护的常数；
- 使用快速输入和 `long long` 分别优化输入效率并保证答案范围安全。

最终算法的均摊时间复杂度为 $O(n+m)$，空间复杂度为 $O(n+m)$。
