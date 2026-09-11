#include <bits/stdc++.h>
using namespace std;

const int maxCard = 21;
const int maxClue = 150;

struct Clue {
    int player;
    int card[3];
};

int testCount, clauseCount;
int myCard[maxCard], knownOwner[maxCard], banCard[maxCard][5];
int ownerCard[maxCard], cardDomain[maxCard], playerCount[5];
Clue clues[maxClue];
bool possibleCard[3][maxCard];

bool canAssign() {
    for (int i = 0; i < clauseCount; i++) {
        bool satisfied = false, possible = false;
        for (int j = 0; j < 3; j++) {
            int card = clues[i].card[j];
            if (ownerCard[card] == clues[i].player)
                satisfied = true;
            else if (ownerCard[card] == -1 && (cardDomain[card] & (1 << clues[i].player)))
                possible = true;
        }
        if (!satisfied && !possible)
            return false;
    }
    int selectCard = -1, minChoice = 10;
    for (int i = 0; i < maxCard; i++) {
        if (ownerCard[i] == -1) {
            int choice = __builtin_popcount(cardDomain[i]);
            if (choice < minChoice) {
                minChoice = choice;
                selectCard = i;
            }
        }
    }
    if (selectCard == -1)
        return playerCount[2] == 5 && playerCount[3] == 4 && playerCount[4] == 4;
    for (int player = 2; player <= 4; player++) {
        if (cardDomain[selectCard] & (1 << player)) {
            ownerCard[selectCard] = player;
            playerCount[player]++;
            if (playerCount[player] <= (player == 2 ? 5 : 4) && canAssign())
                return true;
            playerCount[player]--;
            ownerCard[selectCard] = -1;
        }
    }
    return false;
}

bool checkCandidate(int person, int weapon, int room) {
    for (int i = 0; i < maxCard; i++) {
        ownerCard[i] = -1;
        cardDomain[i] = 0;
        playerCount[i < 5 ? i : 0] = 0;
    }
    for (int i = 0; i < maxCard; i++)
        ownerCard[i] = -1;
    for (int i = 0; i < maxCard; i++) {
        if (myCard[i])
            ownerCard[i] = 1;
    }
    ownerCard[person] = 0;
    ownerCard[weapon] = 0;
    ownerCard[room] = 0;
    for (int i = 0; i < maxCard; i++) {
        if (knownOwner[i] != -1) {
            if (ownerCard[i] != -1 && ownerCard[i] != knownOwner[i])
                return false;
            ownerCard[i] = knownOwner[i];
        }
    }
    for (int i = 0; i < maxCard; i++) {
        if (ownerCard[i] != -1) {
            if (ownerCard[i] >= 1 && banCard[i][ownerCard[i]])
                return false;
            if (ownerCard[i] >= 1)
                playerCount[ownerCard[i]]++;
        } else {
            for (int player = 2; player <= 4; player++)
                if (!banCard[i][player])
                    cardDomain[i] |= 1 << player;
            if (cardDomain[i] == 0)
                return false;
        }
    }
    if (playerCount[1] != 5 || playerCount[2] > 5 || playerCount[3] > 4 || playerCount[4] > 4)
        return false;
    return canAssign();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> testCount) {
        memset(myCard, 0, sizeof(myCard));
        memset(knownOwner, -1, sizeof(knownOwner));
        memset(banCard, 0, sizeof(banCard));
        memset(possibleCard, 0, sizeof(possibleCard));
        clauseCount = 0;
        for (int i = 0; i < 5; i++) {
            char card;
            cin >> card;
            myCard[card - 'A'] = 1;
        }
        string line;
        getline(cin, line);
        for (int turn = 0; turn < testCount; turn++) {
            do {
                getline(cin, line);
            } while (line.empty());
            stringstream input(line);
            char suggestion[3], response[3];
            int responseCount = 0;
            input >> suggestion[0] >> suggestion[1] >> suggestion[2];
            while (responseCount < 3 && input >> response[responseCount])
                responseCount++;
            int suggester = turn % 4 + 1;
            int responder = suggester % 4 + 1;
            for (int i = 0; i < responseCount; i++) {
                int card[3];
                for (int j = 0; j < 3; j++)
                    card[j] = suggestion[j] - 'A';
                if (response[i] == '-') {
                    for (int j = 0; j < 3; j++)
                        banCard[card[j]][responder] = 1;
                } else if (response[i] == '*') {
                    clues[clauseCount].player = responder;
                    for (int j = 0; j < 3; j++)
                        clues[clauseCount].card[j] = card[j];
                    clauseCount++;
                } else {
                    int evidence = response[i] - 'A';
                    if (knownOwner[evidence] != -1 && knownOwner[evidence] != responder)
                        knownOwner[evidence] = -2;
                    else
                        knownOwner[evidence] = responder;
                }
                responder = responder % 4 + 1;
            }
        }
        for (int person = 0; person < 6; person++) {
            for (int weapon = 6; weapon < 12; weapon++) {
                for (int room = 12; room < 21; room++) {
                    if (checkCandidate(person, weapon, room)) {
                        possibleCard[0][person] = true;
                        possibleCard[1][weapon] = true;
                        possibleCard[2][room] = true;
                    }
                }
            }
        }
        for (int type = 0; type < 3; type++) {
            int begin = type == 0 ? 0 : (type == 1 ? 6 : 12);
            int end = type == 0 ? 6 : (type == 1 ? 12 : 21);
            int answer = -1, count = 0;
            for (int card = begin; card < end; card++) {
                if (possibleCard[type][card]) {
                    answer = card;
                    count++;
                }
            }
            if (count == 1)
                cout << char('A' + answer);
            else
                cout << '?';
        }
        cout << '\n';
    }
    return 0;
}
