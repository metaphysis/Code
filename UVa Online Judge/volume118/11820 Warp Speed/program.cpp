#include <bits/stdc++.h>
using namespace std;

struct BigNum {
    static const int base = 1000000000;
    vector<int> num;
    BigNum(int value = 0) {
        if (value > 0) num.push_back(value);
    }
    void add(const BigNum &other) {
        int carry = 0, size = max(num.size(), other.num.size());
        if ((int)num.size() < size) num.resize(size, 0);
        for (int i = 0; i < size || carry; i++) {
            if (i == (int)num.size()) num.push_back(0);
            long long value = num[i] + carry + (i < (int)other.num.size() ? other.num[i] : 0);
            num[i] = value % base;
            carry = value / base;
        }
    }
    string toString() const {
        if (num.empty()) return "0";
        string result = to_string(num.back());
        for (int i = (int)num.size() - 2; i >= 0; i--) {
            string part = to_string(num[i]);
            result += string(9 - part.size(), '0') + part;
        }
        return result;
    }
};

struct Node {
    int child[52];
    bool end;
    Node() {
        fill(child, child + 52, -1);
        end = false;
    }
};

vector<Node> trie;
vector<int> minHop;

int charId(char ch) {
    if (ch >= 'a' && ch <= 'z') return ch - 'a';
    return ch - 'A' + 26;
}

void addRule(const string &rule) {
    int cur = 0;
    for (char ch : rule) {
        int id = charId(ch);
        if (trie[cur].child[id] == -1) {
            trie[cur].child[id] = trie.size();
            trie.push_back(Node());
        }
        cur = trie[cur].child[id];
    }
    trie[cur].end = true;
}

void printDfs(const string &path, int pos, vector<string> &parts) {
    int n = path.size();
    if (pos == n) {
        for (int i = 0; i < (int)parts.size(); i++) {
            if (i > 0) cout << ' ';
            cout << parts[i];
        }
        cout << '\n';
        return;
    }
    if (minHop[pos] == minHop[pos + 1] + 1) {
        parts.push_back(path.substr(pos, 1));
        printDfs(path, pos + 1, parts);
        parts.pop_back();
    }
    int cur = 0;
    for (int i = pos; i < n; i++) {
        int id = charId(path[i]);
        if (trie[cur].child[id] == -1) break;
        cur = trie[cur].child[id];
        if (trie[cur].end && minHop[pos] == minHop[i + 1] + 1) {
            parts.push_back(path.substr(pos, i - pos + 1));
            printDfs(path, i + 1, parts);
            parts.pop_back();
        }
    }
}

void solvePath(const string &path) {
    int n = path.size();
    vector<BigNum> ways(n + 1);
    minHop.assign(n + 1, 0);
    ways[n] = BigNum(1);
    for (int i = n - 1; i >= 0; i--) {
        minHop[i] = minHop[i + 1] + 1;
        ways[i] = ways[i + 1];
        int cur = 0;
        for (int j = i; j < n; j++) {
            int id = charId(path[j]);
            if (trie[cur].child[id] == -1) break;
            cur = trie[cur].child[id];
            if (trie[cur].end) {
                int candidate = minHop[j + 1] + 1;
                if (candidate < minHop[i]) {
                    minHop[i] = candidate;
                    ways[i] = ways[j + 1];
                } else if (candidate == minHop[i]) {
                    ways[i].add(ways[j + 1]);
                }
            }
        }
    }
    cout << ways[0].toString() << ' ' << minHop[0] << '\n';
    vector<string> parts;
    printDfs(path, 0, parts);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    trie.push_back(Node());
    string line;
    bool readPath = false;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) {
            if (!readPath) readPath = true;
            else break;
        } else if (!readPath) {
            addRule(line);
        } else {
            solvePath(line);
        }
    }
    return 0;
}
