#include <bits/stdc++.h>
using namespace std;

const string keyText = "the quick brown fox jumps over the lazy dog";

bool buildKey(const string &cipherText, int encToPlain[26], int plainToEnc[26]) {
    int index, cipherIndex, plainIndex;
    char cipherChar, plainChar;
    if (cipherText.size() != keyText.size()) return false;
    fill(encToPlain, encToPlain + 26, -1);
    fill(plainToEnc, plainToEnc + 26, -1);
    for (index = 0; index < (int)keyText.size(); index++) {
        cipherChar = cipherText[index];
        plainChar = keyText[index];
        if (cipherChar == ' ' || plainChar == ' ') {
            if (cipherChar != plainChar) return false;
            continue;
        }
        cipherIndex = cipherChar - 'a';
        plainIndex = plainChar - 'a';
        if (encToPlain[cipherIndex] != -1 && encToPlain[cipherIndex] != plainIndex) return false;
        if (plainToEnc[plainIndex] != -1 && plainToEnc[plainIndex] != cipherIndex) return false;
        encToPlain[cipherIndex] = plainIndex;
        plainToEnc[plainIndex] = cipherIndex;
    }
    return true;
}

string decodeLine(const string &cipherText, const int encToPlain[26]) {
    string plainText;
    char currentChar;
    for (char currentChar : cipherText)
        plainText += currentChar == ' ' ? ' ' : char('a' + encToPlain[currentChar - 'a']);
    return plainText;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCount, caseIndex;
    string line;
    cin >> caseCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (caseIndex = 0; caseIndex < caseCount; caseIndex++) {
        vector<string> lines;
        while (getline(cin, line) && line.empty()) {
        }
        if (!line.empty()) {
            lines.push_back(line);
            while (getline(cin, line) && !line.empty())
                lines.push_back(line);
        }
        if (caseIndex > 0) cout << '\n';
        int encToPlain[26], plainToEnc[26];
        bool hasKey = false;
        for (const string &currentLine : lines) {
            if (!hasKey && buildKey(currentLine, encToPlain, plainToEnc))
                hasKey = true;
        }
        if (!hasKey) {
            cout << "No solution.\n";
            continue;
        }
        for (const string &currentLine : lines)
            cout << decodeLine(currentLine, encToPlain) << '\n';
    }
    return 0;
}
