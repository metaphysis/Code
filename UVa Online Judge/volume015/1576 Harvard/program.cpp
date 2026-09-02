#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);
const int MAXV = 13;

struct Info {
    int first = -1, last = -1;
    long long refs = 0;
    long long edge[MAXV][MAXV] = {};
};

vector<string> tok;
int pos, n;

vector<Info> leaf(int x) {
    int all = 1 << n, bit = 1 << x;
    vector<Info> res(all);
    for (int mask = 0; mask < all; ++mask) {
        if (!(mask & bit)) {
            res[mask].first = res[mask].last = x;
            res[mask].refs = 1;
        }
    }
    return res;
}

vector<Info> concat(const vector<Info>& a, const vector<Info>& b) {
    int all = 1 << n;
    vector<Info> res(all);
    for (int mask = 0; mask < all; ++mask) {
        res[mask] = a[mask];
        res[mask].refs += b[mask].refs;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                res[mask].edge[i][j] += b[mask].edge[i][j];
        if (a[mask].last == -1) {
            res[mask] = b[mask];
        } else if (b[mask].first != -1) {
            ++res[mask].edge[a[mask].last][b[mask].first];
            res[mask].last = b[mask].last;
        }
    }
    return res;
}

vector<Info> repeat(const vector<Info>& body, long long times) {
    int all = 1 << n;
    vector<Info> res(all);
    if (times == 0) return res;
    for (int mask = 0; mask < all; ++mask) {
        res[mask].first = body[mask].first;
        res[mask].last = body[mask].last;
        res[mask].refs = body[mask].refs * times;
        if (body[mask].first == -1) continue;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                res[mask].edge[i][j] = body[mask].edge[i][j] * times;
        if (times > 1)
            res[mask].edge[body[mask].last][body[mask].first] += times - 1;
    }
    return res;
}

vector<Info> parse() {
    vector<Info> res;
    bool hasValue = false;
    while (pos < (int)tok.size() && tok[pos] != "E") {
        string s = tok[pos++];
        vector<Info> cur;
        if (s[0] == 'V') {
            cur = leaf(stoi(s.substr(1)) - 1);
        } else {
            cur = parse();
            ++pos; // skip E
            cur = repeat(cur, stoll(s.substr(1)));
        }
        if (!hasValue) {
            res.swap(cur);
            hasValue = true;
        } else {
            res = concat(res, cur);
        }
    }
    if (!hasValue) res.assign(1 << n, Info());
    return res;
}

long long solve(int banks, int capacity, vector<string> input) {
    bool used[MAXV] = {};
    vector<int> vars;
    for (const string& s : input) {
        if (s[0] == 'V') used[stoi(s.substr(1)) - 1] = true;
    }
    for (int i = 0; i < MAXV; ++i)
        if (used[i]) vars.push_back(i);
    n = vars.size();
    for (string& s : input) {
        if (s[0] == 'V') {
            int x = stoi(s.substr(1)) - 1;
            int id = find(vars.begin(), vars.end(), x) - vars.begin();
            s = "V" + to_string(id + 1);
        }
    }
    tok = input;
    pos = 0;
    vector<Info> summary = parse();
    int all = 1 << n;
    long long totalRefs = summary[0].refs;
    int maxGroups = min(banks - 1, n);
    vector<int> bits(all, 0);
    for (int mask = 1; mask < all; ++mask)
        bits[mask] = bits[mask >> 1] + (mask & 1);
    vector<long long> inside(all), dp((maxGroups + 1) * all), nextDp(all);
    long long answer = INF;
    for (int zero = 0; zero < all; ++zero) {
        if (bits[zero] > capacity) continue;
        const Info& info = summary[zero];
        int remain = (all - 1) ^ zero;
        // inside[mask]：mask 内所有变量之间的无向相邻转移次数。
        inside[0] = 0;
        for (int mask = 1; mask < all; ++mask) {
            int bit = mask & -mask;
            int i = __builtin_ctz((unsigned)bit);
            int rest = mask ^ bit;
            inside[mask] = inside[rest];

            for (int x = rest; x; x &= x - 1) {
                int j = __builtin_ctz((unsigned)(x & -x));
                inside[mask] += info.edge[i][j] + info.edge[j][i];
            }
        }
        fill(dp.begin(), dp.end(), INF);
        dp[0] = 0;
        for (int groups = 1; groups <= maxGroups; ++groups) {
            fill(nextDp.begin(), nextDp.end(), INF);
            for (int mask = 1; mask < all; ++mask) {
                if ((mask & ~remain) || bits[mask] < groups ||
                    bits[mask] > groups * capacity)
                    continue;
                int low = mask & -mask;
                // 枚举包含最低位的最后一组，避免重复枚举组的排列。
                for (int group = mask; group; group = (group - 1) & mask) {
                    if (!(group & low) || bits[group] > capacity) continue;
                    int previous = mask ^ group;
                    if (dp[(groups - 1) * all + previous] == INF) continue;
                    long long cut = inside[mask] - inside[group] - inside[previous];
                    nextDp[mask] = min(
                        nextDp[mask],
                        dp[(groups - 1) * all + previous] + cut
                    );
                }
            }
            copy(nextDp.begin(), nextDp.end(), dp.begin() + groups * all);
        }
        long long firstSet = info.refs ? 1 : 0;
        for (int groups = 0; groups <= maxGroups; ++groups) {
            long long partition = dp[groups * all + remain];
            if (partition != INF)
                answer = min(answer, totalRefs + firstSet + partition);
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int banks, capacity;
    while (cin >> banks >> capacity) {
        string line, s;
        getline(cin, line); // consume header remainder
        getline(cin, line); // read program
        stringstream ss(line);
        vector<string> program;
        while (ss >> s) program.push_back(s);
        cout << solve(banks, capacity, program) << '\n';
    }
    return 0;
}
