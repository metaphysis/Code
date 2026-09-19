#include <bits/stdc++.h>
using namespace std;

const string suitText = "HSCD", rankText = "23456789TJQKA";

struct Card {
    int group, order, point;
};

struct Play {
    vector<int> count;
    int group, size, points, high;
};

struct Shape {
    vector<int> need;
    int parts, maxLen, honor;
};

Card cardInfo[54];

int getRank(const string &text) {
    if (text == "10") return 10;
    return (int)rankText.find(text[0]) + 2;
}

int getCardId(const string &text, int pos) {
    if (text[pos] == 'B') return 52;
    if (text[pos] == 'R') return 53;
    return (int)suitText.find(text[pos]) * 13 + (int)rankText.find(text[pos + 1]);
}

void initCards(int mainSuit, int curRank) {
    for (int id = 0; id < 52; id++) {
        int suit = id / 13, rank = id % 13 + 2, order = rank - 2 - (rank > curRank);
        cardInfo[id].point = rank == 5 ? 5 : (rank == 10 || rank == 13 ? 10 : 0);
        if (rank == curRank) {
            cardInfo[id].group = 4;
            cardInfo[id].order = 112 + (suit == mainSuit);
        } else if (suit == mainSuit) {
            cardInfo[id].group = 4;
            cardInfo[id].order = 100 + order;
        } else {
            cardInfo[id].group = suit;
            cardInfo[id].order = order;
        }
    }
    cardInfo[52].group = cardInfo[53].group = 4;
    cardInfo[52].point = cardInfo[53].point = 0;
    cardInfo[52].order = mainSuit == -1 ? 113 : 114;
    cardInfo[53].order = cardInfo[52].order + 1;
}

Play readPlay(const string &text) {
    Play play;
    play.count.assign(54, 0);
    play.group = -2;
    play.size = (int)text.size() / 2;
    play.points = 0;
    play.high = -1;
    for (int pos = 0; pos < (int)text.size(); pos += 2) {
        int id = getCardId(text, pos);
        play.count[id]++;
        play.points += cardInfo[id].point;
        play.high = max(play.high, cardInfo[id].order);
        if (play.group == -2) play.group = cardInfo[id].group;
        else if (play.group != cardInfo[id].group) play.group = -1;
    }
    return play;
}

Shape getShape(const Play &play) {
    Shape shape;
    vector<int> pairCount(128, 0);
    int pairTotal = 0;
    shape.parts = 0;
    shape.maxLen = 1;
    shape.honor = play.high;
    for (int id = 0; id < 54; id++) {
        if (play.count[id] < 2) continue;
        pairCount[cardInfo[id].order]++;
        pairTotal++;
    }
    while (true) {
        int bestLen = 0, bestEnd = -1, runLen = 0;
        for (int order = 0; order < 128; order++) {
            if (pairCount[order] > 0) runLen++;
            else runLen = 0;
            if (runLen > 0 && (runLen > bestLen || (runLen == bestLen && order > bestEnd))) {
                bestLen = runLen;
                bestEnd = order;
            }
        }
        if (bestLen == 0) break;
        if (shape.need.empty()) {
            shape.maxLen = bestLen * 2;
            shape.honor = bestEnd;
        }
        shape.need.push_back(bestLen);
        for (int order = bestEnd - bestLen + 1; order <= bestEnd; order++) pairCount[order]--;
    }
    shape.parts = (int)shape.need.size() + play.size - pairTotal * 2;
    return shape;
}

struct Matcher {
    vector<int> pairOrder, need, bitCount, high, memo;
    vector<char> valid;
    bool search(int step, int rest) {
        if (step == (int)need.size()) return true;
        if (memo[rest] != -1) return memo[rest] == 1;
        int &result = memo[rest];
        result = 0;
        for (int sub = rest; sub > 0; sub = (sub - 1) & rest) {
            if (!valid[sub] || bitCount[sub] != need[step]) continue;
            if (search(step + 1, rest ^ sub)) {
                result = 1;
                return true;
            }
        }
        return false;
    }

    int solve(const Play &play, const Shape &shape) {
        pairOrder.clear();
        need = shape.need;
        if (need.empty()) return play.high;
        for (int id = 0; id < 54; id++) if (play.count[id] == 2) pairOrder.push_back(cardInfo[id].order);
        int pairNum = (int)pairOrder.size(), required = accumulate(need.begin(), need.end(), 0);
        if (pairNum < required) return -1;
        sort(pairOrder.begin(), pairOrder.end());
        int limit = 1 << pairNum;
        bitCount.assign(limit, 0);
        high.assign(limit, -1);
        memo.assign(limit, -1);
        valid.assign(limit, 0);
        vector<int> candidates;
        for (int mask = 1; mask < limit; mask++) {
            int lowOrder = -1, lastOrder = -1;
            bool unique = true;
            bitCount[mask] = bitCount[mask >> 1] + (mask & 1);
            for (int pos = 0; pos < pairNum; pos++) {
                if ((mask & (1 << pos)) == 0) continue;
                if (lowOrder == -1) lowOrder = pairOrder[pos];
                if (lastOrder == pairOrder[pos]) unique = false;
                lastOrder = pairOrder[pos];
            }
            high[mask] = lastOrder;
            valid[mask] = unique && lastOrder - lowOrder + 1 == bitCount[mask];
            if (valid[mask] && bitCount[mask] == need[0]) candidates.push_back(mask);
        }
        sort(candidates.begin(), candidates.end(), [&](int left, int right) {
            return high[left] > high[right];
        });
        for (int mask : candidates) if (search(1, (limit - 1) ^ mask)) return high[mask];
        return -1;
    }
};

int getHonor(const Play &play, const Play &lead, const Shape &shape) {
    if (play.group == -1) return -1;
    if (shape.parts > 1) {
        if (lead.group == 4 || play.group != 4) return -1;
    } else {
        if (play.group != lead.group && play.group != 4) return -1;
    }
    Matcher matcher;
    return matcher.solve(play, shape);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    vector<string> names = {"Alice", "Bob", "Charles", "David"};
    for (int caseId = 1; caseId <= testCount; caseId++) {
        string mainText, dealerName, firstRank, secondRank;
        cin >> mainText >> dealerName >> firstRank >> secondRank;
        int mainSuit = mainText == "O" ? -1 : (int)suitText.find(mainText[0]);
        int dealer = (int)(find(names.begin(), names.end(), dealerName) - names.begin());
        int declareTeam = dealer % 2, defendTeam = declareTeam ^ 1;
        long long teamRank[2] = {getRank(firstRank), getRank(secondRank)};
        initCards(mainSuit, (int)teamRank[declareTeam]);
        int leader = dealer, usedCards = 0, playedPoints = 0, lastWinner = dealer, lastLen = 1;
        long long defendPoints = 0;
        while (usedCards < 25) {
            vector<Play> plays;
            string text;
            for (int pos = 0; pos < 4; pos++) {
                cin >> text;
                plays.push_back(readPlay(text));
            }
            Shape shape = getShape(plays[0]);
            int winner = leader, bestHonor = shape.honor, trickPoints = 0;
            usedCards += plays[0].size;
            for (int pos = 0; pos < 4; pos++) trickPoints += plays[pos].points;
            for (int pos = 1; pos < 4; pos++) {
                int honor = getHonor(plays[pos], plays[0], shape);
                if (honor > bestHonor) {
                    bestHonor = honor;
                    winner = (leader + pos) % 4;
                }
            }
            playedPoints += trickPoints;
            if (winner % 2 == defendTeam) defendPoints += trickPoints;
            lastWinner = winner;
            lastLen = shape.maxLen;
            leader = winner;
        }
        if (lastWinner % 2 == defendTeam) defendPoints += (200LL - playedPoints) * (1LL << lastLen);
        int nextDealer;
        if (defendPoints < 80) {
            if (defendPoints == 0) teamRank[declareTeam] += 3;
            else if (defendPoints < 40) teamRank[declareTeam] += 2;
            else teamRank[declareTeam]++;
            nextDealer = (dealer + 2) % 4;
        } else {
            teamRank[defendTeam] += (defendPoints - 80) / 40;
            nextDealer = (dealer + 1) % 4;
        }
        cout << "Case #" << caseId << ":\n";
        cout << defendPoints << '\n';
        if (teamRank[0] > 14) cout << "Winner: Team 1\n";
        else if (teamRank[1] > 14) cout << "Winner: Team 2\n";
        else cout << rankText[(int)teamRank[0] - 2] << ' ' << rankText[(int)teamRank[1] - 2] << ' ' << names[nextDealer] << '\n';
    }
    return 0;
}
