#include <bits/stdc++.h>
using namespace std;

struct Key {
    bool isInt;
    int num;
    string str;
    bool operator == (const Key &other) const {
        if (isInt != other.isInt) return false;
        if (isInt) return num == other.num;
        return str == other.str;
    }
};

struct KeyHash {
    size_t operator () (const Key &key) const {
        if (key.isInt) return hash<int>()(key.num) * 2 + 1;
        return hash<string>()(key.str) * 2;
    }
};

struct Value {
    int type;
    int num;
    string str;
    int dictId;
    Value() : type(0), num(0), dictId(-1) {}
};

vector<unordered_map<Key, Value, KeyHash> > dicts;
Value vars[26];
bool assigned[26];
vector<int> visitState;
string text;
int pos;

void skipSpace() {
    while (pos < (int)text.size() && isspace(text[pos])) pos++;
}

Key parseKey() {
    skipSpace();
    Key key;
    if (text[pos] == '\'') {
        pos++;
        key.isInt = false;
        while (text[pos] != '\'') key.str += text[pos++];
        pos++;
    } else {
        int sign = 1, num = 0;
        if (text[pos] == '-') {
            sign = -1;
            pos++;
        }
        while (pos < (int)text.size() && isdigit(text[pos])) num = num * 10 + text[pos++] - '0';
        key.isInt = true;
        key.num = sign * num;
    }
    skipSpace();
    return key;
}

int newDict() {
    dicts.push_back(unordered_map<Key, Value, KeyHash>());
    return (int)dicts.size() - 1;
}

Value parseValue() {
    skipSpace();
    Value value;
    if (text[pos] == '{') {
        pos++;
        int id = newDict();
        skipSpace();
        if (text[pos] == '}') {
            pos++;
        } else {
            while (true) {
                Key key = parseKey();
                skipSpace();
                pos++;
                Value item = parseValue();
                dicts[id][key] = item;
                skipSpace();
                if (text[pos] == '}') {
                    pos++;
                    break;
                }
                pos++;
            }
        }
        value.type = 2;
        value.dictId = id;
    } else if (text[pos] == '\'') {
        pos++;
        value.type = 1;
        while (text[pos] != '\'') value.str += text[pos++];
        pos++;
    } else {
        int sign = 1, num = 0;
        if (text[pos] == '-') {
            sign = -1;
            pos++;
        }
        while (pos < (int)text.size() && isdigit(text[pos])) num = num * 10 + text[pos++] - '0';
        value.type = 0;
        value.num = sign * num;
    }
    return value;
}

void parseSlot(int &varId, Key keys[], int &keyCount) {
    skipSpace();
    varId = text[pos++] - 'a';
    keyCount = 0;
    skipSpace();
    while (pos < (int)text.size() && text[pos] == '[') {
        pos++;
        keys[keyCount++] = parseKey();
        skipSpace();
        pos++;
        skipSpace();
    }
}

Value getSlot(int varId, Key keys[], int keyCount) {
    Value value = vars[varId];
    for (int i = 0; i < keyCount; i++) value = dicts[value.dictId][keys[i]];
    return value;
}

bool hasCycle(int id) {
    if (visitState[id] == 1) return true;
    if (visitState[id] == 2) return false;
    visitState[id] = 1;
    for (auto &item : dicts[id])
        if (item.second.type == 2 && hasCycle(item.second.dictId)) return true;
    visitState[id] = 2;
    return false;
}

void executeLine(string line) {
    text = line;
    pos = 0;
    skipSpace();
    if (text.compare(pos, 7, "length(") == 0 || text.compare(pos, 5, "test(") == 0) {
        bool isLength = text.compare(pos, 7, "length(") == 0;
        pos += isLength ? 7 : 5;
        Key keys[105];
        int varId, keyCount;
        parseSlot(varId, keys, keyCount);
        Value value = getSlot(varId, keys, keyCount);
        if (isLength) cout << dicts[value.dictId].size() << '\n';
        else {
            visitState.assign(dicts.size(), 0);
            cout << (hasCycle(value.dictId) ? 1 : 0) << '\n';
        }
        return;
    }
    int equalPos = text.find('=');
    text = text.substr(0, equalPos);
    pos = 0;
    Key leftKeys[105];
    int leftVar, leftCount;
    parseSlot(leftVar, leftKeys, leftCount);
    text = line.substr(equalPos + 1);
    pos = 0;
    skipSpace();
    Value rightValue;
    if (text[pos] == '{' || text[pos] == '\'' || text[pos] == '-' || isdigit(text[pos])) rightValue = parseValue();
    else {
        Key rightKeys[105];
        int rightVar, rightCount;
        parseSlot(rightVar, rightKeys, rightCount);
        rightValue = getSlot(rightVar, rightKeys, rightCount);
    }
    if (leftCount == 0) vars[leftVar] = rightValue;
    else {
        Value current = vars[leftVar];
        for (int i = 0; i + 1 < leftCount; i++) current = dicts[current.dictId][leftKeys[i]];
        dicts[current.dictId][leftKeys[leftCount - 1]] = rightValue;
    }
    assigned[leftVar] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) executeLine(line);
    return 0;
}
