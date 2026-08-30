#include <bits/stdc++.h>
using namespace std;

struct Kid {
    string name, mainWeapon, secondWeapon;
};

struct Result {
    Kid winner;
    string winnerWeapon;
};

string getWeaponName(const string &weapon) {
    if (weapon == "R") return "R";
    if (weapon == "P") return "P";
    return "S";
}

bool winWeapon(const string &first, const string &second) {
    return (first == "R" && second == "S") || (first == "S" && second == "P") || (first == "P" && second == "R");
}

bool isWinner(const string &first, const string &second) {
    if (first == second) return false;
    return winWeapon(first, second);
}

Result playGame(const Kid &first, const Kid &second) {
    vector<string> firstWeapons, secondWeapons;
    if (first.mainWeapon != second.mainWeapon) {
        firstWeapons.push_back(first.mainWeapon);
        secondWeapons.push_back(second.mainWeapon);
    } else {
        firstWeapons.push_back(first.mainWeapon);
        secondWeapons.push_back(second.mainWeapon);
        firstWeapons.push_back(first.secondWeapon);
        secondWeapons.push_back(second.mainWeapon);
        firstWeapons.push_back(first.mainWeapon);
        secondWeapons.push_back(second.secondWeapon);
        firstWeapons.push_back(first.secondWeapon);
        secondWeapons.push_back(second.secondWeapon);
    }
    string usedFirst = firstWeapons[0], usedSecond = secondWeapons[0];
    bool firstWins = false;
    bool secondWins = false;
    for (int i = 0; i < (int)firstWeapons.size(); i++) {
        usedFirst = firstWeapons[i];
        usedSecond = secondWeapons[i];
        if (isWinner(usedFirst, usedSecond)) {
            firstWins = true;
            break;
        }
        if (isWinner(usedSecond, usedFirst)) {
            secondWins = true;
            break;
        }
    }
    cout << first.name << ", Weapon: " << usedFirst << " VS " << second.name << ", Weapon: " << usedSecond << '\n';
    if (secondWins) {
        cout << "Won: " << second.name << '\n';
        return {second, usedSecond};
    }
    cout << "Won: " << first.name << '\n';
    return {first, usedFirst};
}

class Parser {
private:
    string text;
    int pos;
    vector<string> &logs;
    Kid parseKid() {
        pos++;
        string name, mainWeapon, secondWeapon;
        while (text[pos] != '-') name += text[pos++];
        pos++;
        mainWeapon = text[pos++];
        pos++;
        secondWeapon = text[pos++];
        pos++;
        return {name, mainWeapon, secondWeapon};
    }
    Kid parseCommunity() {
        pos++;
        vector<Kid> kids;
        bool hasChildCommunity = false;
        Kid champion;
        while (text[pos] != ']') {
            if (text[pos] == '(') {
                kids.push_back(parseKid());
            } else if (text[pos] == '[') {
                champion = parseCommunity();
                hasChildCommunity = true;
            } else {
                pos++;
            }
        }
        pos++;
        if (hasChildCommunity) {
            for (int i = 0; i < (int)kids.size(); i++) {
                Result game = playGame(champion, kids[i]);
                champion = game.winner;
            }
        } else {
            champion = kids[0];
            for (int i = 1; i < (int)kids.size(); i++) {
                Result game = playGame(champion, kids[i]);
                champion = game.winner;
            }
        }
        return champion;
    }
public:
    Parser(const string &input, vector<string> &output) : text(input), pos(0), logs(output) {}
    Kid parse() {
        return parseCommunity();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    bool firstCase = true;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (!firstCase) cout << '\n';
        firstCase = false;
        vector<string> logs;
        Parser parser(line, logs);
        Kid champion = parser.parse();
        cout << "Final Winner: (" << champion.name << '-' << champion.mainWeapon << '-' << champion.secondWeapon << ")\n";
    }
    return 0;
}
