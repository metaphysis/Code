#include <bits/stdc++.h>
using namespace std;

struct Result {
    long long wins, loses;
};

int tileA[4][7] = {
    {0, 1, 3, 1, 0, 0, 4},
    {3, 4, 0, 2, 1, 3, 0},
    {1, 2, 6, 2, 1, 5, 4},
    {3, 2, 0, 5, 2, 0, 1}
};

int tileB[4][7] = {
    {3, 1, 4, 5, 2, 6, 6},
    {3, 4, 5, 4, 2, 6, 0},
    {3, 6, 6, 3, 6, 6, 5},
    {5, 2, 4, 5, 5, 1, 4}
};

int scoreTable[4][128];
unordered_map<unsigned long long, Result> dp;

unsigned long long makeKey(int bobMask, int aliceMask, int peterMask, int mikeMask, int leftValue, int rightValue, int player, int passCount) {
    unsigned long long key = 0;
    key |= bobMask;
    key |= (unsigned long long)aliceMask << 7;
    key |= (unsigned long long)peterMask << 14;
    key |= (unsigned long long)mikeMask << 21;
    key |= (unsigned long long)leftValue << 28;
    key |= (unsigned long long)rightValue << 31;
    key |= (unsigned long long)player << 34;
    key |= (unsigned long long)passCount << 36;
    return key;
}

void addResult(Result &target, const Result &source) {
    target.wins += source.wins;
    target.loses += source.loses;
}

Result dfs(int bobMask, int aliceMask, int peterMask, int mikeMask, int leftValue, int rightValue, int player, int passCount) {
    unsigned long long key = makeKey(bobMask, aliceMask, peterMask, mikeMask, leftValue, rightValue, player, passCount);
    unordered_map<unsigned long long, Result>::iterator it = dp.find(key);
    if (it != dp.end()) return it->second;
    int masks[4] = {bobMask, aliceMask, peterMask, mikeMask};
    Result answer = {0, 0};
    bool hasMove = false;
    for (int slot = 0; slot < 7; slot++) {
        if ((masks[player] & (1 << slot)) == 0) continue;
        int x = tileA[player][slot], y = tileB[player][slot];
        int nextLeft[2], nextRight[2], moveCount = 0;
        if (x == leftValue || y == leftValue) {
            nextLeft[moveCount] = x == leftValue ? y : x;
            nextRight[moveCount] = rightValue;
            if (nextLeft[moveCount] > nextRight[moveCount]) swap(nextLeft[moveCount], nextRight[moveCount]);
            moveCount++;
        }
        if (x == rightValue || y == rightValue) {
            int newLeft = leftValue, newRight = x == rightValue ? y : x;
            if (newLeft > newRight) swap(newLeft, newRight);
            if (moveCount == 0 || newLeft != nextLeft[0] || newRight != nextRight[0]) {
                nextLeft[moveCount] = newLeft;
                nextRight[moveCount] = newRight;
                moveCount++;
            }
        }
        if (moveCount == 0) continue;
        hasMove = true;
        int nextMasks[4] = {bobMask, aliceMask, peterMask, mikeMask};
        nextMasks[player] ^= 1 << slot;
        if (nextMasks[player] == 0) {
            if (player == 0) answer.wins++;
            else answer.loses++;
            continue;
        }
        int nextPlayer = (player + 1) % 4;
        for (int move = 0; move < moveCount; move++) {
            Result current = dfs(nextMasks[0], nextMasks[1], nextMasks[2], nextMasks[3], nextLeft[move], nextRight[move], nextPlayer, 0);
            addResult(answer, current);
        }
    }
    if (!hasMove) {
        if (passCount == 3) {
            int totalScore[4] = {
                scoreTable[0][bobMask],
                scoreTable[1][aliceMask],
                scoreTable[2][peterMask],
                scoreTable[3][mikeMask]
            };
            bool bobWins = true;
            for (int i = 1; i < 4; i++)
                if (totalScore[0] >= totalScore[i]) bobWins = false;
            if (bobWins) answer.wins++;
            else answer.loses++;
        } else {
            int nextPlayer = (player + 1) % 4;
            answer = dfs(bobMask, aliceMask, peterMask, mikeMask, leftValue, rightValue, nextPlayer, passCount + 1);
        }
    }
    dp[key] = answer;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int player = 0; player < 4; player++) {
        scoreTable[player][0] = 0;
        for (int mask = 1; mask < 128; mask++) {
            int bit = __builtin_ctz(mask);
            scoreTable[player][mask] = scoreTable[player][mask ^ (1 << bit)] + tileA[player][bit] + tileB[player][bit];
        }
    }
    char leftBracket, comma, rightBracket;
    int x, y;
    while (cin >> leftBracket >> x >> comma >> y >> rightBracket) {
        int firstSlot = -1;
        for (int slot = 0; slot < 7; slot++)
            if ((tileA[0][slot] == x && tileB[0][slot] == y) || (tileA[0][slot] == y && tileB[0][slot] == x)) firstSlot = slot;
        dp.clear();
        int firstLeft = x, firstRight = y;
        if (firstLeft > firstRight) swap(firstLeft, firstRight);
        int bobMask = 127 ^ (1 << firstSlot);
        Result answer = dfs(bobMask, 127, 127, 127, firstLeft, firstRight, 1, 0);
        cout << "wins " << answer.wins << "; loses " << answer.loses << '\n';
    }
    return 0;
}
