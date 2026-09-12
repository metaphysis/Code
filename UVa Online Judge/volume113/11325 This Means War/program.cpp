#include <bits/stdc++.h>
using namespace std;

int getRank(char ch) {
    if (ch >= '2' && ch <= '9') return ch - '0';
    if (ch == 'T') return 10;
    if (ch == 'J') return 11;
    if (ch == 'Q') return 12;
    if (ch == 'K') return 13;
    return 14;
}

bool canMatch(const int myCnt[], const int sameCnt[], const vector<int>& need) {
    int leftCnt[15] = {};
    vector<int> cards;
    for (int rank = 2; rank <= 14; rank++) {
        if (sameCnt[rank] > myCnt[rank]) return false;
        leftCnt[rank] = myCnt[rank] - sameCnt[rank];
        for (int i = 0; i < leftCnt[rank]; i++) cards.push_back(rank);
    }
    vector<int> req = need;
    sort(cards.begin(), cards.end());
    sort(req.begin(), req.end());
    int p = 0;
    for (int x : req) {
        while (p < (int)cards.size() && cards[p] < x) p++;
        if (p == (int)cards.size()) return false;
        p++;
    }
    return true;
}

bool dfs(int pos, const vector<int>& enemy, const int myCnt[], int sameCnt[], vector<int>& need) {
    if (pos == 26) return canMatch(myCnt, sameCnt, need);
    if (enemy[pos] < 14) {
        need.push_back(enemy[pos] + 1);
        if (dfs(pos + 1, enemy, myCnt, sameCnt, need)) return true;
        need.pop_back();
    }
    if (pos < 25) {
        sameCnt[enemy[pos]]++;
        if (sameCnt[enemy[pos]] <= myCnt[enemy[pos]]) {
            int nextPos = min(pos + 4, 25);
            if (dfs(nextPos, enemy, myCnt, sameCnt, need)) return true;
        }
        sameCnt[enemy[pos]]--;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        vector<int> enemy;
        int enemyCnt[15] = {}, myCnt[15] = {}, sameCnt[15] = {};
        string card;
        for (int i = 0; i < 26; i++) {
            cin >> card;
            int rank = getRank(card[0]);
            enemy.push_back(rank);
            enemyCnt[rank]++;
        }
        for (int rank = 2; rank <= 14; rank++) myCnt[rank] = 4 - enemyCnt[rank];
        vector<int> need;
        cout << (dfs(0, enemy, myCnt, sameCnt, need) ? "yes" : "no") << '\n';
    }
    return 0;
}
