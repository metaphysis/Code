#include <bits/stdc++.h>
using namespace std;

struct HandInfo {
    unsigned long long mask;
    signed char type;
};

vector<HandInfo> allHands;
long long combValue[53][6];

int getRank(char ch) {
    if (ch >= '2' && ch <= '9') return ch - '2';
    if (ch == 'T') return 8;
    if (ch == 'J') return 9;
    if (ch == 'Q') return 10;
    if (ch == 'K') return 11;
    return 12;
}

int getSuit(char ch) {
    if (ch == 'c') return 0;
    if (ch == 'd') return 1;
    if (ch == 'h') return 2;
    return 3;
}

int getType(unsigned long long mask) {
    int rankCount[13] = {}, suitCount[4] = {}, rankMask = 0;
    unsigned long long bits = mask;
    while (bits) {
        int card = __builtin_ctzll(bits);
        int rank = card / 4, suit = card % 4;
        rankCount[rank]++;
        suitCount[suit]++;
        rankMask |= 1 << rank;
        bits &= bits - 1;
    }
    bool isFlush = false, isStraight = false, isRoyal = false;
    for (int suit = 0; suit < 4; suit++)
        if (suitCount[suit] == 5) isFlush = true;
    int aceLowMask = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 12);
    int royalMask = (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 12);
    if (rankMask == aceLowMask) isStraight = true;
    if (rankMask == royalMask) {
        isStraight = true;
        isRoyal = true;
    }
    for (int start = 0; start <= 8; start++) {
        int straightMask = ((1 << 5) - 1) << start;
        if (rankMask == straightMask) isStraight = true;
    }
    if (isFlush && isRoyal) return 8;
    if (isFlush && isStraight) return 7;
    bool hasFour = false, hasThree = false;
    int pairCount = 0;
    for (int rank = 0; rank < 13; rank++) {
        if (rankCount[rank] == 4) hasFour = true;
        if (rankCount[rank] == 3) hasThree = true;
        if (rankCount[rank] == 2) pairCount++;
    }
    if (hasFour) return 6;
    if (hasThree && pairCount == 1) return 5;
    if (isFlush) return 4;
    if (isStraight) return 3;
    if (hasThree) return 2;
    if (pairCount == 2) return 1;
    if (pairCount == 1) return 0;
    return -1;
}

void buildHands(int nextCard, int depth, unsigned long long mask) {
    if (depth == 5) {
        allHands.push_back({mask, static_cast<signed char>(getType(mask))});
        return;
    }
    for (int card = nextCard; card <= 52 - (5 - depth); card++)
        buildHands(card + 1, depth + 1, mask | (1ULL << card));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i <= 52; i++) {
        combValue[i][0] = 1;
        for (int j = 1; j <= 5 && j <= i; j++)
            combValue[i][j] = i == j ? 1 : combValue[i - 1][j - 1] + combValue[i - 1][j];
    }
    buildHands(0, 0, 0);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int payout[9];
        for (int i = 0; i < 9; i++) cin >> payout[i];
        int handCount;
        cin >> handCount;
        while (handCount--) {
            int cardPosition[52];
            fill(cardPosition, cardPosition + 52, -1);
            unsigned long long startMask = 0;
            for (int i = 0; i < 5; i++) {
                string cardText;
                cin >> cardText;
                int card = getRank(cardText[0]) * 4 + getSuit(cardText[1]);
                startMask |= 1ULL << card;
                cardPosition[card] = i;
            }
            long long rewardSum[32] = {};
            for (const HandInfo &hand : allHands) {
                unsigned long long bits = hand.mask;
                int keepMask = 0;
                while (bits) {
                    int card = __builtin_ctzll(bits);
                    if ((startMask >> card) & 1ULL) keepMask |= 1 << cardPosition[card];
                    bits &= bits - 1;
                }
                if (hand.type >= 0) rewardSum[keepMask] += payout[hand.type];
            }
            double answer = 0.0;
            for (int keepMask = 0; keepMask < 32; keepMask++) {
                int keepCount = __builtin_popcount(static_cast<unsigned int>(keepMask));
                double current = static_cast<double>(rewardSum[keepMask]) / combValue[47][5 - keepCount];
                answer = max(answer, current);
            }
            cout << fixed << setprecision(10) << answer << '\n';
        }
    }
    return 0;
}
