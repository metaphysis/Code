#include <bits/stdc++.h>
using namespace std;

const long long inf = (long long)4e18;

struct State {
    int year;
    long long debt, pay;
    bool operator==(const State &other) const {
        return year == other.year && debt == other.debt && pay == other.pay;
    }
};

struct StateHash {
    size_t operator()(const State &state) const {
        uint64_t x = (uint64_t)state.debt;
        x ^= (uint64_t)state.pay + 0x9e3779b97f4a7c15ULL + (x << 6) + (x >> 2);
        x ^= (uint64_t)state.year + 0x9e3779b97f4a7c15ULL + (x << 6) + (x >> 2);
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
};

long long loan;
int rate, years;
vector<long long> ans;
unordered_set<State, StateHash> bad;

long long nextDebt(long long debt) {
    __int128 val = (__int128)debt * rate + 50;
    __int128 res = (__int128)debt + val / 100;
    if (res > inf) return inf;
    return (long long)res;
}

bool rangeOk(long long debt, long long pay, int year) {
    long long low = debt, high = debt;
    int i;
    for (i = year; i <= years; i++) {
        low = nextDebt(low) - pay;
        if (low < 0) low = 0;
        high = nextDebt(high) - max(0LL, pay - (i - year));
        if (high < 0) return false;
        if (high > inf) high = inf;
    }
    return low == 0;
}

bool dfs(int year, long long debt, long long pay) {
    State state = {year, debt, pay};
    long long cur;
    if (bad.find(state) != bad.end()) return false;
    if (!rangeOk(debt, pay, year)) {
        bad.insert(state);
        return false;
    }
    cur = nextDebt(debt) - pay;
    if (cur < 0) {
        bad.insert(state);
        return false;
    }
    ans.push_back(pay);
    if (year == years) {
        if (cur == 0) return true;
        ans.pop_back();
        bad.insert(state);
        return false;
    }
    if (dfs(year + 1, cur, pay)) return true;
    if (pay > 0 && dfs(year + 1, cur, pay - 1)) return true;
    ans.pop_back();
    bad.insert(state);
    return false;
}

bool finishWith(long long pay) {
    long long debt = loan;
    int i;
    for (i = 1; i <= years; i++) {
        debt = nextDebt(debt) - pay;
        if (debt <= 0) return true;
    }
    return false;
}

long long getLower() {
    long long left = 0, right = nextDebt(loan);
    while (left < right) {
        long long mid = (left + right) / 2;
        if (finishWith(mid)) right = mid;
        else left = mid + 1;
    }
    return left;
}

long long parseMoney(string str) {
    long long val;
    int pos, dec;
    pos = str.find('.');
    if (pos == -1) return stoll(str) * 100;
    val = stoll(str.substr(0, pos)) * 100;
    dec = 0;
    if (pos + 1 < (int)str.size()) dec += (str[pos + 1] - '0') * 10;
    if (pos + 2 < (int)str.size()) dec += str[pos + 2] - '0';
    return val + dec;
}

void printMoney(long long val) {
    cout << "$" << val / 100 << "." << setw(2) << setfill('0') << val % 100 << setfill(' ');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test, tc;
    string str;
    cin >> test;
    bad.max_load_factor(0.7);
    bad.reserve(8192);
    for (tc = 0; tc < test; tc++) {
        long long start;
        int i, cnt;
        bool ok = false;
        cin >> str >> rate >> years;
        loan = parseMoney(str);
        start = getLower();
        for (i = 0; i < years; i++) {
            bad.clear();
            ans.clear();
            if (dfs(1, loan, start + i)) {
                ok = true;
                break;
            }
        }
        if (tc) cout << "\n";
        if (!ok) {
            cout << "Impossible\n";
            continue;
        }
        for (i = 0; i < (int)ans.size();) {
            cnt = 1;
            while (i + cnt < (int)ans.size() && ans[i + cnt] == ans[i]) cnt++;
            printMoney(ans[i]);
            cout << " for " << cnt << " year(s)\n";
            i += cnt;
        }
    }
    return 0;
}
