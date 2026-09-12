#include <bits/stdc++.h>
using namespace std;

struct Record {
    string phone, name;
    vector<string> sortKey;
};

void appendBelow1000(int value, vector<string>& key) {
    static const string ones[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    static const string tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    if (value >= 100) {
        key.push_back(ones[value / 100]);
        key.push_back("hundred");
        value %= 100;
    }
    if (value >= 20) {
        key.push_back(tens[value / 10]);
        value %= 10;
    }
    if (value > 0) key.push_back(ones[value]);
}

void appendNumber(long long value, vector<string>& key) {
    if (value == 0) {
        key.push_back("zero");
        return;
    }
    if (value >= 1000000) {
        appendBelow1000(static_cast<int>(value / 1000000), key);
        key.push_back("million");
        value %= 1000000;
    }
    if (value >= 1000) {
        appendBelow1000(static_cast<int>(value / 1000), key);
        key.push_back("thousand");
        value %= 1000;
    }
    if (value > 0) appendBelow1000(static_cast<int>(value), key);
}

bool isDigitWord(const string& word) {
    if (word.empty()) return false;
    for (char ch : word)
        if (ch < '0' || ch > '9') return false;
    return true;
}

bool isUpperWord(const string& word) {
    if (word.empty()) return false;
    for (char ch : word)
        if (ch < 'A' || ch > 'Z') return false;
    return true;
}

void appendWord(const string& word, vector<string>& key) {
    if (isDigitWord(word)) {
        appendNumber(stoll(word), key);
        return;
    }
    if (isUpperWord(word)) {
        for (char ch : word)
            key.push_back(string(1, static_cast<char>(tolower(static_cast<unsigned char>(ch)))));
        return;
    }
    string lowerWord = word;
    for (char& ch : lowerWord)
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    key.push_back(lowerWord);
}

vector<string> makeSortKey(const string& name) {
    vector<string> key;
    string word;
    for (char ch : name) {
        if (isalnum(static_cast<unsigned char>(ch))) {
            word += ch;
        } else {
            if (!word.empty()) {
                appendWord(word, key);
                word.clear();
            }
        }
    }
    if (!word.empty()) appendWord(word, key);
    return key;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Record> records;
    string line;
    while (getline(cin, line)) {
        if (line.size() < 7) continue;
        Record record;
        record.phone = line.substr(0, 7);
        record.name = line.substr(7);
        record.sortKey = makeSortKey(record.name);
        records.push_back(record);
    }
    stable_sort(records.begin(), records.end(), [](const Record& first, const Record& second) {
        return first.sortKey < second.sortKey;
    });
    for (const Record& record : records) {
        string formatPhone = record.phone.substr(0, 3) + " " + record.phone.substr(3);
        cout << left << setw(52) << record.name << "   " << formatPhone << '\n';
    }
    return 0;
}
