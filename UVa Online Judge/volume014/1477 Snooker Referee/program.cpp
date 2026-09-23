#include <bits/stdc++.h>
using namespace std;

int getBall(const string &s) {
    if (s == "None") return 0;
    if (s == "Red") return 1;
    if (s == "Yellow") return 2;
    if (s == "Green") return 3;
    if (s == "Brown") return 4;
    if (s == "Blue") return 5;
    if (s == "Pink") return 6;
    if (s == "Black") return 7;
    return 8;
}

string getName(int ball) {
    if (ball == 1) return "Red";
    if (ball == 2) return "Yellow";
    if (ball == 3) return "Green";
    if (ball == 4) return "Brown";
    if (ball == 5) return "Blue";
    if (ball == 6) return "Pink";
    if (ball == 7) return "Black";
    return "White";
}

vector<string> splitLine(const string &s) {
    stringstream ss(s);
    vector<string> res;
    string word;
    while (ss >> word) res.push_back(word);
    return res;
}

string getLine() {
    string line;
    while (getline(cin, line) && line.empty());
    return line;
}

void printTurn(const string &name, bool inHand) {
    cout << name << "'s turn";
    if (inHand) cout << ", in-hand";
    cout << '\n';
}

void printRespot(vector<int> balls) {
    if (balls.empty()) return;
    sort(balls.begin(), balls.end());
    cout << "Respot";
    for (int ball : balls) cout << ' ' << getName(ball);
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    string line;
    getline(cin, line);
    for (int tc = 1; tc <= t; tc++) {
        if (tc > 1) cout << '\n';
        line = getLine();
        vector<string> players = splitLine(line);
        int score[2] = {0, 0};
        int red = 15, stage = 0, target = 2, cur = 0;
        bool inHand = true, pending = false, ended = false;
        string nextLine;
        cout << "Frame " << tc << '\n';
        printTurn(players[cur], true);
        while (!ended) {
            if (pending) {
                line = nextLine;
                pending = false;
            } else {
                line = getLine();
            }
            vector<string> parts = splitLine(line);
            int first = getBall(parts[0]), on, redCnt = 0, whiteCnt = 0;
            int oldStage = stage;
            bool onlyBlack = stage == 2 && target == 7;
            vector<int> pots, respot;
            if (stage == 0) {
                on = 1;
            } else if (stage == 1) {
                if (first >= 2 && first <= 7) on = first;
                else on = 2;
            } else {
                on = target;
            }
            for (int i = 1; i < (int)parts.size(); i++) {
                int ball = getBall(parts[i]);
                pots.push_back(ball);
                if (ball == 1) redCnt++;
                if (ball == 8) whiteCnt++;
            }
            bool foul = first != on;
            for (int ball : pots)
                if (ball != on) foul = true;
            if (whiteCnt > 0) foul = true;
            int penalty = max(4, on);
            if (first >= 1 && first <= 7) penalty = max(penalty, first);
            for (int ball : pots)
                if (ball >= 1 && ball <= 7) penalty = max(penalty, ball);
            bool scored = false;
            int gain = 0;
            if (!foul) {
                if (on == 1 && redCnt > 0) {
                    scored = true;
                    gain = redCnt;
                } else if (on >= 2 && on <= 7) {
                    for (int ball : pots)
                        if (ball == on) {
                            scored = true;
                            gain = on;
                        }
                }
            }
            red -= redCnt;
            if (foul) {
                score[cur ^ 1] += penalty;
            } else if (scored) {
                score[cur] += gain;
            }
            for (int ball : pots)
                if (ball >= 2 && ball <= 7 && (foul || oldStage != 2)) respot.push_back(ball);
            inHand = whiteCnt > 0;
            if (oldStage == 0) {
                if (!foul && scored) {
                    stage = 1;
                } else if (red == 0) {
                    stage = 2;
                    target = 2;
                }
            } else if (oldStage == 1) {
                if (red > 0) {
                    stage = 0;
                } else {
                    stage = 2;
                    target = 2;
                }
            } else if (!foul && scored) {
                target++;
            }
            if (foul) cout << "Foul!\n";
            cout << score[0] << " : " << score[1] << '\n';
            if (onlyBlack && (foul || scored)) {
                if (score[0] == score[1]) {
                    cout << "Tie\n";
                    cout << "Respot Black\n";
                    line = getLine();
                    if (line == players[0]) cur = 0;
                    else cur = 1;
                    stage = 2;
                    target = 7;
                    inHand = true;
                    printTurn(players[cur], true);
                } else {
                    int win;
                    if (score[0] > score[1]) win = 0;
                    else win = 1;
                    cout << players[win] << " wins\n";
                    ended = true;
                }
                continue;
            }
            printRespot(respot);
            if (foul) {
                cur ^= 1;
                printTurn(players[cur], inHand);
                line = getLine();
                if (line == "Play again") {
                    cur ^= 1;
                    printTurn(players[cur], inHand);
                } else {
                    pending = true;
                    nextLine = line;
                }
            } else if (!scored) {
                cur ^= 1;
                printTurn(players[cur], inHand);
            }
        }
    }
    return 0;
}
