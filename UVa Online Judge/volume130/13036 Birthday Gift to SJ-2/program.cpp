#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const ull maxVal = 1000000000000000000ULL;

struct Key {
    ull val;
    int pos;
    bool operator==(const Key &other) const {
        return val == other.val && pos == other.pos;
    }
};

struct KeyHash {
    size_t operator()(const Key &key) const {
        ull x = key.val + 0x9e3779b97f4a7c15ULL;
        x ^= x >> 30;
        x *= 0xbf58476d1ce4e5b9ULL;
        x ^= x >> 27;
        x *= 0x94d049bb133111ebULL;
        x ^= x >> 31;
        x ^= (ull)key.pos * 0x9e3779b97f4a7c15ULL;
        return (size_t)x;
    }
};

vector<ull> fib, gen, ans;
unordered_map<Key, bool, KeyHash> memo;

void initFib() {
    ull x, y, z;
    x = 2;
    y = 3;
    while (x <= maxVal) {
        fib.push_back(x);
        if (y > maxVal - x) break;
        z = x + y;
        x = y;
        y = z;
    }
}

bool canMake(ull val, int pos) {
    if (val == 1) return true;
    Key key = {val, pos};
    unordered_map<Key, bool, KeyHash>::iterator it = memo.find(key);
    if (it != memo.end()) return it->second;
    for (int i = pos; i < (int)gen.size(); ++i) {
        if (gen[i] > val) break;
        if (val % gen[i] != 0) continue;
        if (canMake(val / gen[i], i)) return memo[key] = true;
    }
    memo[key] = false;
    return false;
}

void initGen() {
    for (int i = 0; i < (int)fib.size(); ++i) {
        memo.clear();
        if (!canMake(fib[i], 0)) gen.push_back(fib[i]);
    }
}

void dfs(int pos, ull val) {
    ans.push_back(val);
    for (int i = pos; i < (int)gen.size(); ++i) {
        if (val > maxVal / gen[i]) break;
        dfs(i, val * gen[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    ull a, b;
    initFib();
    initGen();
    dfs(0, 1);
    sort(ans.begin(), ans.end());
    cin >> t;
    while (t--) {
        cin >> a >> b;
        vector<ull>::iterator it = upper_bound(ans.begin(), ans.end(), b);
        if (it == ans.begin()) {
            cout << -1 << '\\n';
            continue;
        }
        --it;
        if (*it < a) cout << -1 << '\\n';
        else cout << *it << '\\n';
    }
    return 0;
}
