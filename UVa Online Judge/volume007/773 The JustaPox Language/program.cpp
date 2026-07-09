// The JustaPox Language
// UVa ID: 773
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Item {
    enum Type { BASIC, REF } type;
    int value;  // BASIC: 长度; REF: 数组索引
};

struct ArrayInfo {
    string name;
    vector<Item> items;
    int totalLen;
};

vector<ArrayInfo> arrays;
unordered_map<string, int> nameToIdx;
string inputStr;
size_t pos = 0;

void skipSpaces() {
    while (pos < inputStr.size() && isspace(inputStr[pos])) ++pos;
}

string readToken() {
    skipSpaces();
    if (pos >= inputStr.size()) return "";
    char c = inputStr[pos];
    if (isalpha(c) || c == '_') {
        size_t start = pos;
        while (pos < inputStr.size() && (isalnum(inputStr[pos]) || inputStr[pos] == '_')) ++pos;
        return inputStr.substr(start, pos - start);
    } else if (isdigit(c)) {
        size_t start = pos;
        while (pos < inputStr.size() && isdigit(inputStr[pos])) ++pos;
        return inputStr.substr(start, pos - start);
    } else {
        return string(1, inputStr[pos++]);
    }
}

bool checkArray(int idx, const vector<int>& vals, int start) {
    int cur = start;
    vector<tuple<int, int, int>> refs; // (refIdx, startPos, len)
    for (const auto& item : arrays[idx].items) {
        if (item.type == Item::BASIC) {
            cur += item.value;
        } else {
            int refIdx = item.value;
            int len = arrays[refIdx].totalLen;
            if (!checkArray(refIdx, vals, cur)) return false;
            refs.push_back(make_tuple(refIdx, cur, len));
            cur += len;
        }
    }
    for (size_t i = 0; i < refs.size(); ++i)
        for (size_t j = i + 1; j < refs.size(); ++j)
            if (get<0>(refs[i]) == get<0>(refs[j])) {
                int len = get<2>(refs[i]);
                int s1 = get<1>(refs[i]);
                int s2 = get<1>(refs[j]);
                for (int k = 0; k < len; ++k)
                    if (vals[s1 + k] != vals[s2 + k]) return false;
            }
    return true;
}

bool isConsistent(int idx, const vector<int>& vals) {
    if ((int)vals.size() != arrays[idx].totalLen) return false;
    return checkArray(idx, vals, 0);
}

int main() {
    string line;
    while (getline(cin, line)) {
        inputStr += line;
        inputStr += '\n';
    }

    vector<string> inconsistent;

    while (pos < inputStr.size()) {
        skipSpaces();
        if (pos >= inputStr.size()) break;
        int startPos = pos;
        string id = readToken();
        if (id.empty()) break;
        skipSpaces();
        string next = readToken();

        if (next == "is") {
            ArrayInfo info;
            info.name = id;
            while (true) {
                skipSpaces();
                if (pos >= inputStr.size()) break;
                string tok = readToken();
                if (tok == ".") break;
                else if (tok == "[") {
                    skipSpaces();
                    string numStr = readToken();
                    int k = stoi(numStr);
                    skipSpaces();
                    string close = readToken(); // ']'
                    Item it;
                    it.type = Item::BASIC;
                    it.value = k;
                    info.items.push_back(it);
                } else {
                    auto itMap = nameToIdx.find(tok);
                    if (itMap != nameToIdx.end()) {
                        Item it;
                        it.type = Item::REF;
                        it.value = itMap->second;
                        info.items.push_back(it);
                    }
                }
            }
            int total = 0;
            for (const auto& item : info.items)
                if (item.type == Item::BASIC) total += item.value;
                else total += arrays[item.value].totalLen;
            info.totalLen = total;
            int idx = arrays.size();
            arrays.push_back(info);
            nameToIdx[id] = idx;
        } else if (next == "=") {
            vector<int> vals;
            while (true) {
                skipSpaces();
                if (pos >= inputStr.size()) break;
                string tok = readToken();
                if (tok == ".") break;
                else vals.push_back(stoi(tok));
            }
            auto itMap = nameToIdx.find(id);
            if (itMap != nameToIdx.end()) {
                int idx = itMap->second;
                if (!isConsistent(idx, vals)) {
                    string original = inputStr.substr(startPos, pos - startPos);
                    inconsistent.push_back(original);
                }
            }
        } else break;
    }

    for (const string& s : inconsistent)
        cout << s << '\n';

    return 0;
}
