// The code is CORRECT (by Professor Krzysztof Stencel), but it's not being accepted. 

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000003;
int limitM;

struct Poly {
    int shift = 0;
    vector<int> a;
};

Poly multiply(const Poly& a, const Poly& b) {
    Poly c;
    c.shift = a.shift + b.shift;
    if (a.a.empty() || b.a.empty() || c.shift > limitM) return c;
    int length = min(limitM - c.shift + 1, int(a.a.size() + b.a.size() - 1));
    c.a.assign(length, 0);
    for (int i = 0; i < int(a.a.size()) && i < length; ++i)
        if (a.a[i])
            for (int j = 0; j < int(b.a.size()) && i + j < length; ++j)
                if (b.a[j])
                    c.a[i + j] = (c.a[i + j] + 1LL * a.a[i] * b.a[j]) % MOD;
    return c;
}

void add(Poly& a, const Poly& b, int extra) {
    if (b.a.empty() || b.shift + extra > limitM) return;
    int start = b.shift + extra, end = min(limitM + 1, start + int(b.a.size()));
    if (a.a.empty()) {
        a.shift = start;
        a.a.assign(b.a.begin(), b.a.begin() + end - start);
        return;
    }
    int lo = min(a.shift, start), hi = max(a.shift + int(a.a.size()), end);
    if (lo < a.shift) {
        a.a.insert(a.a.begin(), a.shift - lo, 0);
        a.shift = lo;
    }
    a.a.resize(hi - lo);
    for (int i = start; i < end; ++i) {
        int& value = a.a[i - lo];
        value += b.a[i - start];
        if (value >= MOD) value -= MOD;
    }
}

Poly fromCounts(const vector<int>& counts) {
    Poly result;
    int first = 0, last = int(counts.size()) - 1;
    while (first <= last && counts[first] == 0) ++first;
    while (last >= first && counts[last] == 0) --last;
    if (first <= last) {
        result.shift = first;
        result.a.assign(counts.begin() + first, counts.begin() + last + 1);
    }
    return result;
}

struct Factor {
    vector<int> vars;
    vector<Poly> table;
};
typedef pair<vector<int>, int> Rule;

Poly exactFallback(int unknown, const vector<Rule>& rules, const vector<bool>& involved, int& freeCells) {
    vector<set<int>> graph(unknown);
    for (auto& r : rules)
        for (int x : r.first)
            for (int y : r.first)
                if (x != y) graph[x].insert(y);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < unknown; ++i)
        if (involved[i]) pq.push({graph[i].size(), i});
    vector<int> order, rank(unknown, -1);
    vector<bool> removed(unknown);
    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        int u = p.second;
        if (removed[u] || p.first != (int)graph[u].size()) continue;
        rank[u] = order.size();
        order.push_back(u);
        removed[u] = true;
        vector<int> neighbors(graph[u].begin(), graph[u].end());
        for (int x : neighbors) {
            graph[x].erase(u);
            for (int y : neighbors)
                if (x != y) graph[x].insert(y);
            pq.push({graph[x].size(), x});
        }
        graph[u].clear();
    }
    int V = order.size();
    freeCells = unknown - V;
    vector<vector<Factor>> bucket(V);
    for (auto& r : rules) {
        Factor f;
        for (int x : r.first) f.vars.push_back(rank[x]);
        sort(f.vars.begin(), f.vars.end());
        f.table.resize(1 << f.vars.size());
        for (int mask = 0; mask < (int)f.table.size(); ++mask)
            if (__builtin_popcount((unsigned)mask) == r.second)
                f.table[mask].a = {1};
        bucket[f.vars[0]].push_back(move(f));
    }
    Poly answer;
    answer.a = {1};
    for (int u = 0; u < V; ++u) {
        auto& factors = bucket[u];
        vector<int> all;
        for (auto& f : factors)
            all.insert(all.end(), f.vars.begin(), f.vars.end());
        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());
        int width = all.size();
        if (width == 0 || width >= 31 || all.front() != u) throw runtime_error("factor width");
        Factor out;
        out.vars.assign(all.begin() + 1, all.end());
        out.table.resize(1 << (width - 1));
        vector<vector<int>> project;
        for (auto& f : factors) {
            vector<int> positions;
            for (int x : f.vars)
                positions.push_back(lower_bound(all.begin(), all.end(), x) - all.begin());
            vector<int> map(1 << width);
            for (int mask = 0; mask < (1 << width); ++mask) {
                int code = 0;
                for (int j = 0; j < (int)positions.size(); ++j)
                    if (mask >> positions[j] & 1) code |= 1 << j;
                map[mask] = code;
            }
            project.push_back(move(map));
        }
        for (int mask = 0; mask < (1 << width); ++mask) {
            bool zero = false;
            for (int i = 0; i < (int)factors.size(); ++i)
                if (factors[i].table[project[i][mask]].a.empty()) {
                    zero = true;
                    break;
                }
            if (zero) continue;
            Poly product;
            product.a = {1};
            for (int i = 0; i < (int)factors.size(); ++i) {
                product = multiply(product, factors[i].table[project[i][mask]]);
                if (product.a.empty()) break;
            }
            add(out.table[mask >> 1], product, mask & 1);
        }
        factors.clear();
        factors.shrink_to_fit();
        if (out.vars.empty()) answer = multiply(answer, out.table[0]);
        else bucket[out.vars[0]].push_back(move(out));
    }
    return answer;
}

struct Board {
    int n, m, mines, unknown;
    vector<string> cells;
    vector<vector<int>> id;
    vector<Rule> rules;
    vector<bool> involved;
    bool inside(int x, int y) const {
        return x >= 0 && x < n && y >= 0 && y < m;
    }
};

// For a legal one-click board, each positive-number component has its own
// boundary, which is a four-neighbour path at the board edge, or a cycle.
// A number observes at most five consecutive cells of that path/cycle.
bool contourComponent(const Board& board, const vector<pair<int,int>>& numbers, const vector<int>& boundary, Poly& result) {
    int length = boundary.size();
    vector<int> local(board.unknown, -1);
    for (int i = 0; i < length; ++i) local[boundary[i]] = i;
    vector<Rule> rules;
    for (auto position : numbers) {
        vector<int> vars;
        for (int x = position.first - 1; x <= position.first + 1; ++x)
            for (int y = position.second - 1; y <= position.second + 1; ++y)
                if (board.inside(x,y) && board.id[x][y] >= 0) vars.push_back(local[board.id[x][y]]);
        rules.push_back({vars, board.cells[position.first][position.second]-'0'});
    }
    vector<int> count(min(length, board.mines) + 1, 0);
    if (length <= 8) {
        for (int mask = 0; mask < (1 << length); ++mask) {
            int k = __builtin_popcount(unsigned(mask));
            if (k >= int(count.size())) continue;
            bool good = true;
            for (const auto& rule : rules) {
                int sum = 0;
                for (int variable : rule.first) sum += (mask >> variable) & 1;
                if (sum != rule.second) {
                    good = false;
                    break;
                }
            }
            if (good && ++count[k] == MOD) count[k] = 0;
        }
        result = fromCounts(count);
        return true;
    }
    vector<pair<int,int>> locations(board.unknown);
    for (int x = 0; x < board.n; ++x)
        for (int y = 0; y < board.m; ++y)
            if (board.id[x][y] >= 0) locations[board.id[x][y]] = {x,y};
    vector<vector<int>> edges(length);
    const int dx[] = {-1,0,1,0}, dy[] = {0,1,0,-1};
    int start = 0, ends = 0;
    for (int i = 0; i < length; ++i) {
        auto p = locations[boundary[i]];
        for (int d = 0; d < 4; ++d) {
            int x = p.first + dx[d], y = p.second + dy[d];
            if (board.inside(x,y) && board.id[x][y] >= 0) {
                int j = local[board.id[x][y]];
                if (j >= 0) edges[i].push_back(j);
            }
        }
        if (edges[i].size() == 1) {
            ++ends;
            start = i;
        } else if (edges[i].size() != 2) return false;
    }
    if (ends != 0 && ends != 2) return false;
    vector<int> order, rank(length, -1);
    for (int current = start; rank[current] < 0; ) {
        rank[current] = order.size();
        order.push_back(current);
        int next = -1;
        for (int neighbor : edges[current])
            if (rank[neighbor] < 0) {
                next = neighbor;
                break;
            }
        if (next < 0) break;
        current = next;
    }
    if (int(order.size()) != length) return false;
    vector<vector<pair<int,int>>> check(length);
    vector<Rule> closing;
    for (auto rule : rules) {
        for (int& v : rule.first) v = rank[v];
        sort(rule.first.begin(), rule.first.end());
        if (rule.first.empty()) {
            if (rule.second != 0) {
                result = Poly();
                return true;
            }
            continue;
        }
        int lo = rule.first.front(), hi = rule.first.back();
        if (hi - lo <= 4) {
            int mask = 0;
            for (int v : rule.first) mask |= 1 << (hi - v);
            check[hi].push_back({mask,rule.second});
        } else {
            // Only a cyclic rule crossing the chosen cut may use the first
            // four and last four cells at the same time.
            if (ends != 0) return false;
            int maxGap = 0;
            for (int i = 0; i < int(rule.first.size()); ++i) {
                int j = (i + 1) % rule.first.size();
                int gap = (rule.first[j] - rule.first[i] + length) % length;
                maxGap = max(maxGap,gap);
            }
            if (length - maxGap > 4) return false;
            for (int v : rule.first)
                if (v >= 4 && v < length - 4) return false;
            closing.push_back(rule);
        }
    }
    vector<array<bool,32>> allowed(length);
    for (int i = 0; i < length; ++i)
        for (int mask = 0; mask < 32; ++mask) {
            allowed[i][mask] = true;
            for (auto rule : check[i])
                if (__builtin_popcount(unsigned(mask & rule.first)) != rule.second) allowed[i][mask] = false;
        }
    int maximum = min(length,board.mines);
    vector<array<int,16>> dp(maximum+1), next(maximum+1);
    for (int first = 0; first < 16; ++first) {
        bool good = true;
        for (int i = 0; i < 4; ++i)
            if (!allowed[i][first >> (3-i)]) good = false;
        int initial = __builtin_popcount(unsigned(first));
        if (!good || initial > maximum) continue;
        for (auto& row : dp) row.fill(0);
        dp[initial][first] = 1;
        for (int i = 4; i < length; ++i) {
            for (auto& row : next) row.fill(0);
            for (int k = initial; k <= min(i,maximum); ++k)
                for (int mask = 0; mask < 16; ++mask) if (dp[k][mask])
                        for (int mine = 0; mine < 2 && k+mine <= maximum; ++mine) {
                            int window = (mask << 1) | mine;
                            if (!allowed[i][window]) continue;
                            int& value = next[k+mine][window & 15];
                            value += dp[k][mask];
                            if (value >= MOD) value -= MOD;
                        }
            dp.swap(next);
        }
        for (int last = 0; last < 16; ++last) {
            good = true;
            for (const auto& rule : closing) {
                int sum = 0;
                for (int v : rule.first)
                    sum += v < 4 ? (first >> (3-v)) & 1 : (last >> (length-1-v)) & 1;
                if (sum != rule.second) {
                    good = false;
                    break;
                }
            }
            if (!good) continue;
            for (int k = initial; k <= maximum; ++k) {
                count[k] += dp[k][last];
                if (count[k] >= MOD) count[k] -= MOD;
            }
        }
    }
    result = fromCounts(count);
    return true;
}

bool contour(const Board& board, Poly& answer, int& freeCells) {
    const int dx[] = {-1,0,1,0}, dy[] = {0,1,0,-1};
    vector<vector<bool>> visited(board.n, vector<bool>(board.m,false));
    vector<int> owner(board.unknown,-1);
    answer = Poly();
    answer.a.push_back(1);
    int component = 0, constrained = 0;
    for (int x = 0; x < board.n; ++x)
        for (int y = 0; y < board.m; ++y) {
            if (board.cells[x][y] == '0') {
                // This cannot occur after the blank expansion of one click.
                for (int u = x-1; u <= x+1; ++u)
                    for (int v = y-1; v <= y+1; ++v)
                        if (board.inside(u,v) && board.id[u][v] >= 0) return false;
            }
            if (board.cells[x][y] < '1' || board.cells[x][y] > '8' || visited[x][y]) continue;
            vector<pair<int,int>> numbers(1, {x,y});
            visited[x][y] = true;
            vector<int> boundary;
            for (int i = 0; i < int(numbers.size()); ++i) {
                auto p = numbers[i];
                for (int d = 0; d < 4; ++d) {
                    int u = p.first+dx[d], v = p.second+dy[d];
                    if (board.inside(u,v) && !visited[u][v] && board.cells[u][v] >= '1' && board.cells[u][v] <= '8') {
                        visited[u][v] = true;
                        numbers.push_back({u,v});
                    }
                }
                for (int u = p.first-1; u <= p.first+1; ++u)
                    for (int v = p.second-1; v <= p.second+1; ++v)
                        if (board.inside(u,v) && board.id[u][v] >= 0) {
                            int variable = board.id[u][v];
                            if (owner[variable] >= 0 && owner[variable] != component) return false;
                            if (owner[variable] < 0) {
                                owner[variable] = component;
                                boundary.push_back(variable);
                                ++constrained;
                            }
                        }
            }
            Poly counts;
            if (!contourComponent(board,numbers,boundary,counts)) return false;
            answer = multiply(answer,counts);
            ++component;
        }
    freeCells = board.unknown-constrained;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    if (!(cin >> tests)) return 0;
    for (int tc = 1; tc <= tests; ++tc) {
        Board board;
        cin >> board.n >> board.m >> board.mines;
        limitM = board.mines;
        board.cells.assign(board.n,string(board.m,'.'));
        for (string& row : board.cells) cin >> row;
        board.id.assign(board.n,vector<int>(board.m,-1));
        board.unknown = 0;
        for (int x = 0; x < board.n; ++x)
            for (int y = 0; y < board.m; ++y)
                if (board.cells[x][y] == '.') board.id[x][y] = board.unknown++;
        board.involved.assign(board.unknown,false);
        bool valid = board.mines >= 0 && board.mines <= board.unknown;
        for (int x = 0; x < board.n; ++x)
            for (int y = 0; y < board.m; ++y) if (board.cells[x][y] != '.') {
                    vector<int> vars;
                    for (int u = x-1; u <= x+1; ++u)
                        for (int v = y-1; v <= y+1; ++v)
                            if (board.inside(u,v) && board.id[u][v] >= 0) {
                                vars.push_back(board.id[u][v]);
                                board.involved[board.id[u][v]] = true;
                            }
                    int need = board.cells[x][y]-'0';
                    if (need < 0 || need > int(vars.size())) valid = false;
                    if (!vars.empty()) board.rules.push_back({vars,need});
                }
        int result = 0;
        if (valid) {
            Poly answer;
            int freeCells = 0;
            if (!contour(board,answer,freeCells)) answer = exactFallback(board.unknown,board.rules,board.involved,freeCells);
            vector<int> choose(min(freeCells,board.mines)+1,1), inverse(choose.size(),1);
            for (int i = 2; i < int(inverse.size()); ++i)
                inverse[i] = MOD - 1LL*(MOD/i)*inverse[MOD%i]%MOD;
            for (int i = 1; i < int(choose.size()); ++i)
                choose[i] = 1LL*choose[i-1]*(freeCells-i+1)%MOD*inverse[i]%MOD;
            for (int i = 0; i < int(answer.a.size()); ++i) {
                int remaining = board.mines-answer.shift-i;
                if (remaining >= 0 && remaining < int(choose.size()))
                    result = (result + 1LL*answer.a[i]*choose[remaining])%MOD;
            }
        }
        cout << "Case #" << tc << ": " << result << '\n';
    }
}
