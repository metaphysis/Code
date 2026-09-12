// Substring Sorting
// UVa ID: 13280
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.170s

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n = 0) {
        init(n);
    }
    void init(int nValue) {
        n = nValue;
        bit.assign(n + 1, 0);
    }
    void add(int pos, int value) {
        for (int i = pos + 1; i <= n; i += i & -i)
            bit[i] += value;
    }
    int sum(int pos) {
        int res = 0;
        for (int i = pos + 1; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }
    int total() {
        return sum(n - 1);
    }
    int kth(int value) {
        int pos = 0, step = 1;
        while ((step << 1) <= n)
            step <<= 1;
        for (int k = step; k > 0; k >>= 1) {
            int next = pos + k;
            if (next <= n && bit[next] < value) {
                pos = next;
                value -= bit[next];
            }
        }
        return pos;
    }
};

struct SparseTable {
    int n;
    vector<int> logs;
    vector<vector<int>> st;
    void build(const vector<int> &arr) {
        n = (int)arr.size();
        logs.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i)
            logs[i] = logs[i >> 1] + 1;
        int level = logs[n] + 1;
        st.assign(level, vector<int>(n));
        st[0] = arr;
        for (int j = 1; j < level; ++j) {
            int len = 1 << j;
            int half = len >> 1;
            for (int i = 0; i + len <= n; ++i)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + half]);
        }
    }
    int query(int left, int right) {
        int len = right - left + 1;
        int level = logs[len];
        return min(st[level][left], st[level][right - (1 << level) + 1]);
    }
};

vector<int> buildSa(const string &str) {
    int n = (int)str.size();
    vector<int> sa(n), rankValue(n), nextRank(n), temp(n);
    vector<int> count(max(n, 256) + 2, 0);
    for (int i = 0; i < n; ++i)
        count[(unsigned char)str[i] + 1]++;
    for (int i = 1; i <= 256; ++i)
        count[i] += count[i - 1];
    for (int i = 0; i < n; ++i)
        sa[count[(unsigned char)str[i]]++] = i;
    rankValue[sa[0]] = 0;
    int classCount = 1;
    for (int i = 1; i < n; ++i) {
        if (str[sa[i]] != str[sa[i - 1]])
            classCount++;
        rankValue[sa[i]] = classCount - 1;
    }
    for (int len = 1; len < n; len <<= 1) {
        int keyCount = classCount + 1;
        vector<int> key(keyCount + 1, 0);
        for (int i = 0; i < n; ++i) {
            int value = i + len < n ? rankValue[i + len] + 1 : 0;
            key[value]++;
        }
        for (int i = 1; i <= keyCount; ++i)
            key[i] += key[i - 1];
        for (int i = n - 1; i >= 0; --i) {
            int value = i + len < n ? rankValue[i + len] + 1 : 0;
            temp[--key[value]] = i;
        }
        fill(key.begin(), key.end(), 0);
        for (int i = 0; i < n; ++i)
            key[rankValue[i] + 1]++;
        for (int i = 1; i <= keyCount; ++i)
            key[i] += key[i - 1];
        for (int i = n - 1; i >= 0; --i) {
            int pos = temp[i];
            int value = rankValue[pos] + 1;
            sa[--key[value]] = pos;
        }
        nextRank[sa[0]] = 0;
        int newClassCount = 1;
        for (int i = 1; i < n; ++i) {
            int cur = sa[i], pre = sa[i - 1];
            int curFirst = rankValue[cur], preFirst = rankValue[pre];
            int curSecond = cur + len < n ? rankValue[cur + len] : -1;
            int preSecond = pre + len < n ? rankValue[pre + len] : -1;
            if (curFirst != preFirst || curSecond != preSecond)
                newClassCount++;
            nextRank[cur] = newClassCount - 1;
        }
        rankValue.swap(nextRank);
        classCount = newClassCount;
        if (classCount == n)
            break;
    }
    return sa;
}

vector<int> buildLcp(const string &str, const vector<int> &sa, vector<int> &rankPos) {
    int n = (int)str.size();
    vector<int> lcp(n, 0);
    rankPos.assign(n, 0);
    for (int i = 0; i < n; ++i)
        rankPos[sa[i]] = i;
    int common = 0;
    for (int i = 0; i < n; ++i) {
        int pos = rankPos[i];
        if (pos == 0)
            continue;
        int j = sa[pos - 1];
        while (i + common < n && j + common < n && str[i + common] == str[j + common])
            common++;
        lcp[pos] = common;
        if (common > 0)
            common--;
    }
    return lcp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        string str;
        cin >> str;
        int n = (int)str.size();
        vector<int> sa = buildSa(str);
        vector<int> rankPos;
        vector<int> lcp = buildLcp(str, sa, rankPos);
        SparseTable rmq;
        rmq.build(sa);
        vector<vector<pair<int, int>>> queries(n + 1);
        int queryCount;
        cin >> queryCount;
        for (int i = 0; i < queryCount; ++i) {
            int k, m;
            cin >> k >> m;
            queries[k].push_back({m, i});
        }
        vector<string> answer(queryCount);
        vector<vector<int>> removeList(n + 1);
        for (int i = 1; i < n; ++i)
            if (lcp[i] >= 1 && lcp[i] <= n)
                removeList[lcp[i]].push_back(i);
        Fenwick fenwick(n);
        for (int k = n; k >= 1; --k) {
            int start = n - k;
            int pos = rankPos[start];
            fenwick.add(pos, 1);
            for (int index : removeList[k])
                fenwick.add(index, -1);
            int total = fenwick.total();
            for (auto query : queries[k]) {
                int m = query.first, id = query.second;
                if (m > total) {
                    answer[id] = "Not found";
                    continue;
                }
                int left = fenwick.kth(m);
                int right = n;
                if (m < total)
                    right = fenwick.kth(m + 1);
                answer[id] = to_string(rmq.query(left, right - 1));
            }
        }
        for (const string &res : answer)
            cout << res << '\n';
    }
    return 0;
}
