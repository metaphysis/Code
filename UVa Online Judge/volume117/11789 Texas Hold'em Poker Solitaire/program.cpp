#include <bits/stdc++.h>
using namespace std;

struct Card {
    string text;
    int value;
    char suit;
};

struct Hand {
    int type;
    vector<int> key;
};

int cardValue(char c) {
    if (c >= '2' && c <= '9') return c - '0';
    if (c == 'T') return 10;
    if (c == 'J') return 11;
    if (c == 'Q') return 12;
    if (c == 'K') return 13;
    return 14;
}

Hand handValue(const vector<Card>& cards) {
    int cnt[15] = {};
    bool flush = true;
    int i;
    vector<int> vals;
    for (i = 0; i < 5; i++) {
        cnt[cards[i].value]++;
        vals.push_back(cards[i].value);
        if (i > 0 && cards[i].suit != cards[0].suit) flush = false;
    }
    sort(vals.begin(), vals.end(), greater<int>());
    int straightHigh = 0;
    if (cnt[14] && cnt[2] && cnt[3] && cnt[4] && cnt[5]) straightHigh = 5;
    for (i = 14; i >= 5; i--) {
        if (cnt[i] && cnt[i - 1] && cnt[i - 2] && cnt[i - 3] && cnt[i - 4]) {
            straightHigh = i;
            break;
        }
    }
    int four = 0, three = 0;
    vector<int> pairs;
    for (i = 2; i <= 14; i++) {
        if (cnt[i] == 4) four = i;
        if (cnt[i] == 3) three = i;
        if (cnt[i] == 2) pairs.push_back(i);
    }
    sort(pairs.begin(), pairs.end(), greater<int>());
    if (straightHigh && flush) return {8, {straightHigh}};
    if (four) {
        vector<int> key = {four};
        for (i = 0; i < 5; i++)
            if (cards[i].value != four) key.push_back(cards[i].value);
        return {7, key};
    }
    if (three && pairs.size() == 1) return {6, {three, pairs[0]}};
    if (flush) return {5, vals};
    if (straightHigh) return {4, {straightHigh}};
    if (three) {
        vector<int> key = {three};
        for (i = 0; i < 5; i++)
            if (cards[i].value != three) key.push_back(cards[i].value);
        sort(key.begin() + 1, key.end(), greater<int>());
        return {3, key};
    }
    if (pairs.size() == 2) {
        int single = 0;
        for (i = 0; i < 5; i++)
            if (cards[i].value != pairs[0] && cards[i].value != pairs[1]) single = cards[i].value;
        return {2, {pairs[0], pairs[1], single}};
    }
    if (pairs.size() == 1) {
        vector<int> key = {pairs[0]};
        for (i = 0; i < 5; i++)
            if (cards[i].value != pairs[0]) key.push_back(cards[i].value);
        sort(key.begin() + 1, key.end(), greater<int>());
        return {1, key};
    }
    return {0, vals};
}

bool isBetter(const Hand& a, const Hand& b) {
    if (a.type != b.type) return a.type > b.type;
    int i;
    for (i = 0; i < (int)a.key.size(); i++) {
        if (a.key[i] != b.key[i]) return a.key[i] > b.key[i];
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> names = {
        "High Cards",
        "One Pair",
        "Two Pair",
        "Three of a Kind",
        "Straight",
        "Flush",
        "Full House",
        "Four of a Kind",
        "Straight Flush"
    };
    int testCnt, tc, i, j, k, l, m, n;
    cin >> testCnt;
    for (tc = 0; tc < testCnt; tc++) {
        Card grid[7][7];
        string s;
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                cin >> s;
                grid[i][j] = {s, cardValue(s[0]), s[1]};
            }
        }
        vector<vector<Card>> lines;
        vector<Card> line;
        for (i = 0; i < 7; i++) {
            line.clear();
            for (j = 0; j < 7; j++) line.push_back(grid[i][j]);
            lines.push_back(line);
        }
        for (j = 0; j < 7; j++) {
            line.clear();
            for (i = 0; i < 7; i++) line.push_back(grid[i][j]);
            lines.push_back(line);
        }
        line.clear();
        for (i = 0; i < 7; i++) line.push_back(grid[i][i]);
        lines.push_back(line);
        line.clear();
        for (i = 0; i < 7; i++) line.push_back(grid[6 - i][i]);
        lines.push_back(line);
        bool found = false;
        Hand bestHand;
        vector<Card> bestLine, bestFive;
        for (i = 0; i < 16; i++) {
            for (j = 0; j < 3; j++) for (k = j + 1; k < 4; k++) for (l = k + 1; l < 5; l++) for (m = l + 1; m < 6; m++) for (n = m + 1; n < 7; n++) {
                vector<Card> five = {
                    lines[i][j],
                    lines[i][k],
                    lines[i][l],
                    lines[i][m],
                    lines[i][n]
                };
                Hand curHand = handValue(five);
                if (!found || isBetter(curHand, bestHand)) {
                    found = true;
                    bestHand = curHand;
                    bestLine = lines[i];
                    bestFive = five;
                }
            }
        }
        for (i = 0; i < 7; i++) {
            if (i) cout << " ";
            cout << bestLine[i].text;
        }
        cout << "  ";
        for (i = 0; i < 5; i++) {
            if (i) cout << " ";
            cout << bestFive[i].text;
        }
        cout << "  " << names[bestHand.type] << "\n";
    }
    return 0;
}
