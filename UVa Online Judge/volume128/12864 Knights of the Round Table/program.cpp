#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;

int findStart(vector<int>& val) {
    int n = val.size(), sum = 0, head = 0, tail = 0;
    vector<int> pre(n * 2), que(n * 2);
    for (int i = 0; i < n; i++) {
        sum += val[i] - 1;
        pre[i] = sum;
    }
    for (int i = 0; i < n; i++) {
        sum += val[i] - 1;
        pre[n + i] = sum;
    }
    que[tail++] = 0;
    for (int i = 0; i < n; i++) {
        while (head < tail && pre[i] < pre[que[tail - 1]]) tail--;
        que[tail++] = i;
    }
    for (int i = 0; i < n; i++) {
        int cur = pre[n + i] - pre[que[head]];
        if (cur <= 0) return (i + 1) % n;
        if (que[head] == i) head++;
        while (head < tail && pre[n + i] < pre[que[tail - 1]]) tail--;
        que[tail++] = n + i;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int kNum, dNum;
    while (cin >> kNum >> dNum) {
        vector<int> entered(kNum), taken(kNum), nxt(kNum), cnt(kNum);
        for (int i = 0; i < dNum; i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            entered[a] = 1;
            taken[b] = 1;
        }
        if (kNum == dNum) {
            cout << 1 << '\n';
            continue;
        }
        int empty = 0;
        while (taken[empty]) empty++;
        nxt[empty] = empty;
        for (int step = 1; step < kNum; step++) {
            int pos = empty - step;
            if (pos < 0) pos += kNum;
            if (taken[pos]) nxt[pos] = nxt[(pos + 1) % kNum];
            else nxt[pos] = pos;
        }
        for (int i = 0; i < kNum; i++)
            if (!entered[i]) cnt[nxt[i]]++;
        vector<int> val;
        val.reserve(kNum - dNum);
        for (int i = 0; i < kNum; i++)
            if (!taken[i]) val.push_back(cnt[i]);
        int n = val.size(), first = findStart(val);
        long long ans = val[first];
        val[(first + 1) % n] += val[first] - 1;
        for (int i = (first + 1) % n; i != first; i = (i + 1) % n) {
            ans = ans * val[i] % mod;
            val[(i + 1) % n] += val[i] - 1;
        }
        cout << ans << '\n';
    }
    return 0;
}
