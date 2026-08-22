#include <bits/stdc++.h>
using namespace std;

struct Card {
    int col, val;
};

Card getCard(const string &s) {
    Card card;
    string cols = "BRYG";
    card.col = (int)cols.find(s[0]);
    if (s[1] == 'P')
        card.val = 0;
    else if (s[1] == 'C')
        card.val = 1;
    else
        card.val = s[1] - '0' + 2;
    return card;
}

vector<Card> readCards() {
    int n;
    cin >> n;
    vector<Card> cards(n);
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        cards[i] = getCard(s);
    }
    return cards;
}

vector<Card> readPile() {
    vector<Card> pile = readCards();
    reverse(pile.begin(), pile.end());
    return pile;
}

bool canPlay(const Card &a, const Card &b) {
    return a.col == b.col || a.val == b.val;
}

bool betterCard(const Card &a, const Card &b) {
    if (a.col != b.col) return a.col < b.col;
    return a.val < b.val;
}

int nextPlayer(int cur, int dir, int step) {
    return (cur + dir * step + 8) % 4;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string dir;
    int first, caseNo = 0;
    while (cin >> dir >> first) {
        vector<Card> hand[4], discard, draw;
        for (int i = 0; i < 4; i++)
            hand[i] = readCards();
        discard = readPile();
        draw = readPile();
        int cur = first - 1, step = dir == "clockwise" ? 1 : -1, winner = -1;
        while (winner == -1) {
            int choose = -1;
            Card top = discard.back();
            for (int i = 0; i < (int)hand[cur].size(); i++) {
                if (canPlay(hand[cur][i], top)) {
                    if (choose == -1 || betterCard(hand[cur][i], hand[cur][choose]))
                        choose = i;
                }
            }
            if (choose == -1 && draw.empty() && discard.size() > 1) {
                Card topCard = discard.back();
                for (int i = (int)discard.size() - 2; i >= 0; i--)
                    draw.push_back(discard[i]);
                discard.clear();
                discard.push_back(topCard);
            }
            if (choose == -1 && !draw.empty()) {
                Card card = draw.back();
                draw.pop_back();
                if (canPlay(card, discard.back()))
                    hand[cur].push_back(card), choose = (int)hand[cur].size() - 1;
                else
                    hand[cur].push_back(card);
            }
            if (choose == -1) {
                cur = nextPlayer(cur, step, 1);
                continue;
            }
            Card card = hand[cur][choose];
            hand[cur].erase(hand[cur].begin() + choose);
            discard.push_back(card);
            if (hand[cur].empty()) {
                winner = cur;
                continue;
            }
            if (card.val == 1)
                step = -step;
            int skip = card.val == 0 ? 2 : 1;
            cur = nextPlayer(cur, step, skip);
        }
        if (caseNo++ > 0)
            cout << '\n';
        cout << winner + 1 << " is the winner\n";
        for (int i = 0; i < 4; i++)
            cout << i + 1 << ": " << hand[i].size() << '\n';
    }
    return 0;
}
