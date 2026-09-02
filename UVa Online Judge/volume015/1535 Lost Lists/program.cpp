#include <bits/stdc++.h>
using namespace std;

bool removeValue(map<int, int> &remain, int value) {
    map<int, int>::iterator it = remain.find(value);
    if (it == remain.end()) return false;
    it->second--;
    if (it->second == 0) remain.erase(it);
    return true;
}

bool restoreList(int n, const vector<int> &sums, int firstPair, vector<int> &answer) {
    int base = sums[0] + sums[1] - firstPair;
    if (base <= 0 || base % 2 != 0) return false;
    int first = base / 2;
    map<int, int> remain;
    for (int value : sums) remain[value]++;
    answer.clear();
    answer.push_back(first);
    while ((int)answer.size() < n) {
        if (remain.empty()) return false;
        int next = remain.begin()->first - first;
        if (next <= answer.back()) return false;
        for (int value : answer)
            if (!removeValue(remain, value + next))
                return false;
        answer.push_back(next);
    }
    return remain.empty();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int sumCount = n * (n - 1) / 2;
        vector<int> sums(sumCount);
        for (int &value : sums) cin >> value;
        // 在线测试数据中有未排序数据，如果自行排序，会 Wrong Answer。
        sort(sums.begin(), sums.end());
        vector<int> answer;
        bool found = false;
        for (int value : sums) {
            if (restoreList(n, sums, value, answer)) {
                found = true;
                break;
            }
        }
        if (!found) cout << -1 << '\n';
        else {
            for (int i = 0; i < n; i++) {
                if (i > 0)
                    cout << ' ';
                cout << answer[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
