#include <bits/stdc++.h>
using namespace std;

string aWord, bWord, cWord;
char op;
int digitMap[26], usedMask;
bool nonZero[26];

bool hasId(const vector<int> &ids, int id) {
    for (int value : ids) if (value == id) return true;
    return false;
}

void addId(vector<int> &ids, int id) {
    if (digitMap[id] == -1 && !hasId(ids, id)) ids.push_back(id);
}

bool dfsAddAssign(int col, int carry, int index, vector<int> &ids);

bool dfsAdd(int col, int carry) {
    int totalCols = max((int)aWord.size(), max((int)bWord.size(), (int)cWord.size()));
    if (col == totalCols) return carry == 0;
    vector<int> ids;
    if (col < (int)aWord.size()) addId(ids, aWord[aWord.size() - 1 - col] - 'a');
    if (col < (int)bWord.size()) addId(ids, bWord[bWord.size() - 1 - col] - 'a');
    return dfsAddAssign(col, carry, 0, ids);
}

bool dfsAddAssign(int col, int carry, int index, vector<int> &ids) {
    if (index < (int)ids.size()) {
        int id = ids[index];
        for (int digit = 0; digit <= 9; digit++) {
            if ((usedMask & (1 << digit)) || (digit == 0 && nonZero[id])) continue;
            digitMap[id] = digit;
            usedMask |= 1 << digit;
            if (dfsAddAssign(col, carry, index + 1, ids)) return true;
            digitMap[id] = -1;
            usedMask ^= 1 << digit;
        }
        return false;
    }
    int aDigit = 0, bDigit = 0;
    if (col < (int)aWord.size()) aDigit = digitMap[aWord[aWord.size() - 1 - col] - 'a'];
    if (col < (int)bWord.size()) bDigit = digitMap[bWord[bWord.size() - 1 - col] - 'a'];
    int sum = aDigit + bDigit + carry, resultDigit = sum % 10, nextCarry = sum / 10;
    if (col >= (int)cWord.size()) {
        if (resultDigit != 0) return false;
        return dfsAdd(col + 1, nextCarry);
    }
    int resultId = cWord[cWord.size() - 1 - col] - 'a';
    if (digitMap[resultId] != -1) {
        if (digitMap[resultId] != resultDigit) return false;
        return dfsAdd(col + 1, nextCarry);
    }
    if ((usedMask & (1 << resultDigit)) || (resultDigit == 0 && nonZero[resultId])) return false;
    digitMap[resultId] = resultDigit;
    usedMask |= 1 << resultDigit;
    if (dfsAdd(col + 1, nextCarry)) return true;
    digitMap[resultId] = -1;
    usedMask ^= 1 << resultDigit;
    return false;
}

bool dfsMulAssign(int col, long long carry, int index, vector<int> &ids);

bool dfsMul(int col, long long carry) {
    int totalCols = max((int)aWord.size() + (int)bWord.size() - 1, (int)cWord.size());
    if (col == totalCols) return carry == 0;
    vector<int> ids;
    for (int i = 0; i < (int)aWord.size(); i++) {
        int j = col - i;
        if (j < 0 || j >= (int)bWord.size()) continue;
        addId(ids, aWord[aWord.size() - 1 - i] - 'a');
        addId(ids, bWord[bWord.size() - 1 - j] - 'a');
    }
    return dfsMulAssign(col, carry, 0, ids);
}

bool dfsMulAssign(int col, long long carry, int index, vector<int> &ids) {
    if (index < (int)ids.size()) {
        int id = ids[index];
        for (int digit = 0; digit <= 9; digit++) {
            if ((usedMask & (1 << digit)) || (digit == 0 && nonZero[id])) continue;
            digitMap[id] = digit;
            usedMask |= 1 << digit;
            if (dfsMulAssign(col, carry, index + 1, ids)) return true;
            digitMap[id] = -1;
            usedMask ^= 1 << digit;
        }
        return false;
    }
    long long sum = carry;
    for (int i = 0; i < (int)aWord.size(); i++) {
        int j = col - i;
        if (j < 0 || j >= (int)bWord.size()) continue;
        int aId = aWord[aWord.size() - 1 - i] - 'a';
        int bId = bWord[bWord.size() - 1 - j] - 'a';
        sum += 1LL * digitMap[aId] * digitMap[bId];
    }
    int resultDigit = sum % 10;
    long long nextCarry = sum / 10;
    if (col >= (int)cWord.size()) {
        if (resultDigit != 0) return false;
        return dfsMul(col + 1, nextCarry);
    }
    int resultId = cWord[cWord.size() - 1 - col] - 'a';
    if (digitMap[resultId] != -1) {
        if (digitMap[resultId] != resultDigit) return false;
        return dfsMul(col + 1, nextCarry);
    }
    if ((usedMask & (1 << resultDigit)) || (resultDigit == 0 && nonZero[resultId])) return false;
    digitMap[resultId] = resultDigit;
    usedMask |= 1 << resultDigit;
    if (dfsMul(col + 1, nextCarry)) return true;
    digitMap[resultId] = -1;
    usedMask ^= 1 << resultDigit;
    return false;
}

long long getValue(const string &word) {
    long long value = 0;
    for (char ch : word) value = value * 10 + digitMap[ch - 'a'];
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    char equalSign;
    while (cin >> aWord >> op >> bWord >> equalSign >> cWord) {
        fill(digitMap, digitMap + 26, -1);
        fill(nonZero, nonZero + 26, false);
        usedMask = 0;
        if (aWord.size() > 1) nonZero[aWord[0] - 'a'] = true;
        if (bWord.size() > 1) nonZero[bWord[0] - 'a'] = true;
        if (cWord.size() > 1) nonZero[cWord[0] - 'a'] = true;
        if (op == '+') dfsAdd(0, 0);
        else dfsMul(0, 0);
        cout << getValue(aWord) << ' ' << op << ' ' << getValue(bWord) << " = " << getValue(cWord) << '\n';
    }
    return 0;
}
