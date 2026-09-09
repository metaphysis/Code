#include <bits/stdc++.h>
using namespace std;

string alphabet, answer[105];
int codeValue[105], answerCount;

void addNumber(int length) {
    int index;
    string number;
    number.clear();
    for (index = 0; index < length; ++index)
        number += alphabet[codeValue[index]];
    answer[answerCount++] = number;
}

void generate() {
    int k, alphabetSize;
    answerCount = 0;
    alphabetSize = alphabet.size();
    if (alphabetSize < 4) return;
    memset(codeValue, 0, sizeof(codeValue));
    codeValue[0] = 1, codeValue[1] = 2, codeValue[2] = 1;
    addNumber(4);
    memset(codeValue, 0, sizeof(codeValue));
    codeValue[0] = 2, codeValue[2] = 2;
    addNumber(4);
    if (alphabetSize >= 5) {
        memset(codeValue, 0, sizeof(codeValue));
        codeValue[0] = 2, codeValue[1] = 1, codeValue[2] = 2;
        addNumber(5);
    }
    if (alphabetSize >= 7) {
        memset(codeValue, 0, sizeof(codeValue));
        codeValue[0] = 3, codeValue[1] = 2, codeValue[2] = 1, codeValue[3] = 1;
        addNumber(7);
    }
    for (k = 4; k + 4 <= alphabetSize; ++k) {
        memset(codeValue, 0, sizeof(codeValue));
        codeValue[0] = k, codeValue[1] = 2, codeValue[2] = 1, codeValue[k] = 1;
        addNumber(k + 4);
    }
}

int main() {
    int T;
    cin >> T;
    cin.ignore(64, '\n');
    for (int cs = 0; cs < T; ++cs) {
        getline(cin, alphabet);
        generate();
        if (cs) cout << '\n';
        for (int i = 0; i < answerCount; ++i) cout << answer[i] << '\n';
    }
    return 0;
}
