#include <bits/stdc++.h>
using namespace std;

struct State {
    int mug[2][4], score[2], cool[4], swapCnt[2], turn;
};

int mugNum;
unordered_map<unsigned long long, int> memo;

unsigned long long getKey(const State &s) {
    unsigned long long key = 0;
    int i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < mugNum; j++)
            key = key * 16 + s.mug[i][j];
    for (i = 0; i < 2; i++)
        key = key * 16 + s.score[i];
    for (i = 0; i < mugNum; i++)
        key = key * 5 + s.cool[i];
    for (i = 0; i < 2; i++)
        key = key * 4 + s.swapCnt[i];
    key = key * 2 + s.turn;
    return key;
}

bool hasMug(const State &s, int player) {
    int i;
    for (i = 0; i < mugNum; i++)
        if (s.mug[player][i] > 0) return true;
    return false;
}

void decCool(State &s) {
    int i;
    for (i = 0; i < mugNum; i++)
        if (s.cool[i] > 0) s.cool[i]--;
}

int searchGame(const State &s) {
    unsigned long long key = getKey(s);
    unordered_map<unsigned long long, int>::iterator it = memo.find(key);
    if (it != memo.end()) return it->second;
    int player = s.turn, other = 1 - player;
    bool selfHas = hasMug(s, player), otherHas = hasMug(s, other);
    if (!selfHas && !otherHas) {
        int result = s.score[0] - s.score[1];
        memo[key] = result;
        return result;
    }
    if (!selfHas) {
        State next = s;
        decCool(next);
        next.turn = other;
        int result = searchGame(next);
        memo[key] = result;
        return result;
    }
    int best = player == 0 ? -1000000000 : 1000000000;
    int i, j;
    for (i = 0; i < mugNum; i++) {
        if (s.mug[player][i] == 0) continue;
        State base = s;
        int stones = base.mug[player][i];
        int ringLen = 2 * mugNum + 2;
        base.mug[player][i] = 0;
        for (j = 1; j <= stones; j++) {
            int pos = (i + j) % ringLen;
            if (pos < mugNum)
                base.mug[player][pos]++;
            else if (pos == mugNum)
                base.score[player]++;
            else if (pos < 2 * mugNum + 1)
                base.mug[other][pos - mugNum - 1]++;
            else
                base.score[other]++;
        }
        int lastPos = (i + stones) % ringLen;
        bool extra = lastPos == mugNum;
        bool capture = lastPos < mugNum && s.mug[player][lastPos] == 0 && base.mug[player][lastPos] > 0 && base.mug[other][mugNum - 1 - lastPos] > 0;
        if (capture) {
            base.score[player] += base.mug[player][lastPos] + base.mug[other][mugNum - 1 - lastPos];
            base.mug[player][lastPos] = 0;
            base.mug[other][mugNum - 1 - lastPos] = 0;
        }
        if (!extra) {
            decCool(base);
            base.turn = other;
        }
        if (lastPos > mugNum && lastPos < 2 * mugNum + 1) {
            int oppIndex = lastPos - mugNum - 1;
            bool canSwap = s.swapCnt[player] < 3 && s.cool[oppIndex] == 0 && base.mug[player][oppIndex] > 0;
            int value = searchGame(base);
            if (player == 0)
                best = max(best, value);
            else
                best = min(best, value);
            if (canSwap) {
                State swapped = base;
                swap(swapped.mug[player][oppIndex], swapped.mug[other][oppIndex]);
                swapped.cool[oppIndex] = 4;
                swapped.swapCnt[player]++;
                value = searchGame(swapped);
                if (player == 0)
                    best = max(best, value);
                else
                    best = min(best, value);
            }
        } else {
            int value = searchGame(base);
            if (player == 0)
                best = max(best, value);
            else
                best = min(best, value);
        }
    }
    memo[key] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testNum;
    cin >> testNum;
    while (testNum--) {
        cin >> mugNum;
        State start = {};
        int i;
        for (i = 0; i < mugNum; i++)
            cin >> start.mug[0][i];
        cin >> start.score[0];
        for (i = 0; i < mugNum; i++)
            cin >> start.mug[1][i];
        cin >> start.score[1];
        start.turn = 1;
        memo.clear();
        cout << searchGame(start) << '\n';
    }
    return 0;
}
