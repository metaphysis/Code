#include <bits/stdc++.h>
using namespace std;

struct BigInteger {
    static const long long base = 1000000000LL;
    vector<long long> digits;

    BigInteger(long long value = 0) {
        if (value == 0) {
            digits.push_back(0);
        } else {
            while (value > 0) {
                digits.push_back(value % base);
                value /= base;
            }
        }
    }
};

struct Choice {
    array<int, 26> required;
    int multiplicity;
};

vector<vector<Choice> > tasks;
vector<unordered_map<string, BigInteger> > memo;
array<int, 26> available;

bool readNonEmptyLine(string &line) {
    while (getline(cin, line)) {
        bool nonEmpty = false;
        for (char ch : line) {
            if (ch != ' ' && ch != '\t' && ch != '\r') {
                nonEmpty = true;
                break;
            }
        }
        if (nonEmpty) return true;
    }
    return false;
}

vector<string> splitWords(const string &line, bool allowUnderscore) {
    vector<string> words;
    string word;
    for (char ch : line) {
        bool isLowercase = ch >= 'a' && ch <= 'z';
        bool isUppercase = ch >= 'A' && ch <= 'Z';
        if (isLowercase || isUppercase || (allowUnderscore && ch == '_')) {
            if (isUppercase) ch = char(ch - 'A' + 'a');
            word += ch;
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

void addMultiple(BigInteger &left, const BigInteger &right, int multiplier) {
    long long carry = 0;
    int size = max(left.digits.size(), right.digits.size());
    for (int i = 0; i < size || carry > 0; ++i) {
        if (i == (int)left.digits.size()) left.digits.push_back(0);
        long long value = left.digits[i] + carry;
        if (i < (int)right.digits.size()) value += right.digits[i] * multiplier;
        left.digits[i] = value % BigInteger::base;
        carry = value / BigInteger::base;
    }
}

string toString(const BigInteger &value) {
    string result = to_string(value.digits.back());
    for (int i = (int)value.digits.size() - 2; i >= 0; --i) {
        string part = to_string(value.digits[i]);
        result += string(9 - part.size(), '0') + part;
    }
    return result;
}

string makeStateKey() {
    string key;
    for (int i = 0; i < 26; ++i) key += to_string(available[i]) + '#';
    return key;
}

BigInteger solve(int position) {
    if (position == (int)tasks.size()) return BigInteger(1);
    string state = makeStateKey();
    unordered_map<string, BigInteger>::iterator found = memo[position].find(state);
    if (found != memo[position].end()) return found->second;
    BigInteger result(0);
    for (const Choice &choice : tasks[position]) {
        bool possible = true;
        for (int i = 0; i < 26; ++i) {
            if (choice.required[i] > available[i]) {
                possible = false;
                break;
            }
        }
        if (!possible) continue;
        for (int i = 0; i < 26; ++i) available[i] -= choice.required[i];
        BigInteger subResult = solve(position + 1);
        addMultiple(result, subResult, choice.multiplicity);
        for (int i = 0; i < 26; ++i) available[i] += choice.required[i];
    }
    memo[position][state] = result;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (readNonEmptyLine(line)) {
        int trayLineCount, groundLetterCount, dictionaryLineCount;
        trayLineCount = stoi(line);
        vector<string> trayWords;
        for (int i = 0; i < trayLineCount; ++i) {
            getline(cin, line);
            vector<string> words = splitWords(line, true);
            trayWords.insert(trayWords.end(), words.begin(), words.end());
        }
        readNonEmptyLine(line);
        groundLetterCount = stoi(line);
        available.fill(0);
        for (int i = 0; i < groundLetterCount; ++i) {
            readNonEmptyLine(line);
            stringstream input(line);
            char letter;
            int count;
            input >> letter >> count;
            if (letter >= 'A' && letter <= 'Z') letter = char(letter - 'A' + 'a');
            available[letter - 'a'] = count;
        }
        readNonEmptyLine(line);
        dictionaryLineCount = stoi(line);
        set<string> dictionarySet;
        for (int i = 0; i < dictionaryLineCount; ++i) {
            getline(cin, line);
            vector<string> words = splitWords(line, false);
            for (const string &word : words) dictionarySet.insert(word);
        }
        vector<string> dictionary(dictionarySet.begin(), dictionarySet.end());
        tasks.clear();
        bool valid = true;
        for (const string &pattern : trayWords) {
            if (pattern.find('_') == string::npos) continue;
            map<array<int, 26>, int> choices;
            for (const string &word : dictionary) {
                if (word.size() != pattern.size()) continue;
                bool matched = true;
                array<int, 26> required;
                required.fill(0);
                for (int i = 0; i < (int)pattern.size(); ++i) {
                    if (pattern[i] == '_') {
                        ++required[word[i] - 'a'];
                    } else if (pattern[i] != word[i]) {
                        matched = false;
                        break;
                    }
                }
                if (matched) ++choices[required];
            }
            if (choices.empty()) {
                valid = false;
                break;
            }
            vector<Choice> task;
            for (map<array<int, 26>, int>::const_iterator it = choices.begin(); it != choices.end(); ++it) {
                Choice choice;
                choice.required = it->first;
                choice.multiplicity = it->second;
                task.push_back(choice);
            }
            tasks.push_back(task);
        }
        if (!valid) {
            cout << "0\n";
            continue;
        }
        memo.assign(tasks.size(), unordered_map<string, BigInteger>());
        BigInteger answer = solve(0);
        cout << toString(answer) << '\n';
    }
    return 0;
}
