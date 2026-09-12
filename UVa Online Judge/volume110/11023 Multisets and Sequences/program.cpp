#include <bits/stdc++.h>
using namespace std;

vector<int> parseList(const string &s) {
    vector<int> a;
    string t = s.substr(1, s.size() - 2), cur;
    stringstream ss(t);
    while (getline(ss, cur, ','))
        if (!cur.empty()) a.push_back(stoi(cur));
    return a;
}

void printList(const vector<int> &a, char l, char r) {
    cout << l;
    for (int i = 0; i < (int)a.size(); i++) {
        if (i) cout << ',';
        cout << a[i];
    }
    cout << r << '\n';
}

long long countWays(const vector<int> &cnt, int len) {
    long long c[21][21] = {}, dp[21] = {}, ndp[21] = {};
    for (int i = 0; i <= 20; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
    dp[0] = 1;
    for (int v : cnt) {
        fill(ndp, ndp + 21, 0);
        for (int i = 0; i <= len; i++) {
            if (!dp[i]) continue;
            for (int j = 0; j <= v && i + j <= len; j++) ndp[i + j] += dp[i] * c[i + j][j];
        }
        copy(ndp, ndp + 21, dp);
    }
    return dp[len];
}

void getValues(const vector<int> &a, vector<int> &val, vector<int> &cnt) {
    vector<int> b = a;
    sort(b.begin(), b.end());
    for (int x : b) {
        if (val.empty() || val.back() != x) {
            val.push_back(x);
            cnt.push_back(1);
        } else cnt.back()++;
    }
}

vector<int> unrankSeq(const vector<int> &val, vector<int> cnt, int len, long long r) {
    vector<int> ans;
    for (int p = 0; p < len; p++) {
        for (int i = 0; i < (int)val.size(); i++) {
            if (!cnt[i]) continue;
            cnt[i]--;
            long long ways = countWays(cnt, len - p - 1);
            if (r < ways) {
                ans.push_back(val[i]);
                break;
            }
            r -= ways;
            cnt[i]++;
        }
    }
    return ans;
}

long long rankSeq(const vector<int> &seq, const vector<int> &val, vector<int> cnt) {
    long long ans = 0;
    int len = seq.size();
    for (int p = 0; p < len; p++) {
        for (int i = 0; i < (int)val.size() && val[i] < seq[p]; i++) {
            if (!cnt[i]) continue;
            cnt[i]--;
            ans += countWays(cnt, len - p - 1);
            cnt[i]++;
        }
        for (int i = 0; i < (int)val.size(); i++)
            if (val[i] == seq[p]) {
                cnt[i]--;
                break;
            }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line, cmd, x, y, z;
    while (getline(cin, line)) {
        if (line == "end") break;
        stringstream ss(line);
        ss >> cmd;
        if (cmd == "degrade") {
            ss >> x;
            vector<int> a = parseList(x);
            sort(a.begin(), a.end());
            printList(a, '(', ')');
        } else if (cmd == "promote") {
            ss >> x >> y;
            vector<int> a = parseList(x), val, cnt;
            getValues(a, val, cnt);
            printList(unrankSeq(val, cnt, a.size(), stoll(y)), '{', '}');
        } else if (cmd == "rank") {
            ss >> x;
            vector<int> a = parseList(x), val, cnt;
            getValues(a, val, cnt);
            cout << rankSeq(a, val, cnt) << '\n';
        } else if (cmd == "derive") {
            ss >> x >> y >> z;
            vector<int> a = parseList(x), val, cnt;
            getValues(a, val, cnt);
            printList(unrankSeq(val, cnt, stoi(y), stoll(z)), '{', '}');
        } else {
            ss >> x >> y;
            vector<int> a = parseList(x), b = parseList(y), val, cnt;
            getValues(b, val, cnt);
            cout << rankSeq(a, val, cnt) << '\n';
        }
    }
    return 0;
}
