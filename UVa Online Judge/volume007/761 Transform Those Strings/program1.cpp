// Transform Those Strings
// UVa ID: 761
// Verdict: Wrong Answer
// Submission Date: 2026-10-21
// UVa Run Time: 0.510s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

// 正确的实现，但是由于标准程序存在问题，在线测试数据也时有问题的，因此这个版本的代码无法通过。

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int rule;
};

struct Parent {
    int previousPosition;
    int type;

    Parent() : previousPosition(-1), type(-1) {}
    Parent(int positionValue, int typeValue) : previousPosition(positionValue), type(typeValue) {}
};

enum OperationType {
    DELETE_OPERATION = 0,
    SINGLE_OPERATION = 1,
    EXPAND_OPERATION = 2
};

vector<Edge> characterGraph[26];
bool canReach[26][26];
int firstHop[26][26];
int firstRule[26][26];

unsigned long long getLowMask(int bitCount) {
    if (bitCount <= 0) {
        return 0ULL;
    }
    if (bitCount >= 64) {
        return ~0ULL;
    }
    return (1ULL << bitCount) - 1ULL;
}

bool getBit(const vector<unsigned long long>& bits, int position, int bitCount) {
    if (position < 0 || position >= bitCount) {
        return false;
    }
    return (bits[position >> 6] & (1ULL << (position & 63))) != 0;
}

void setRange(vector<unsigned long long>& bits, int left, int right, int bitCount) {
    if (left > right || right < 0 || left >= bitCount) {
        return;
    }
    left = max(left, 0);
    right = min(right, bitCount - 1);
    int firstWord = left >> 6;
    int lastWord = right >> 6;
    int firstOffset = left & 63;
    int lastOffset = right & 63;
    if (firstWord == lastWord) {
        bits[firstWord] |= getLowMask(lastOffset - firstOffset + 1) << firstOffset;
        return;
    }
    bits[firstWord] |= ~0ULL << firstOffset;
    for (int word = firstWord + 1; word < lastWord; ++word) {
        bits[word] = ~0ULL;
    }
    bits[lastWord] |= getLowMask(lastOffset + 1);
}

int findAnyBit(const vector<unsigned long long>& bits, int left, int right, int bitCount) {
    if (left > right || right < 0 || left >= bitCount) {
        return -1;
    }
    left = max(left, 0);
    right = min(right, bitCount - 1);
    int firstWord = left >> 6;
    int lastWord = right >> 6;
    for (int word = firstWord; word <= lastWord; ++word) {
        unsigned long long value = bits[word];
        if (word == firstWord) {
            value &= ~0ULL << (left & 63);
        }
        if (word == lastWord) {
            value &= getLowMask((right & 63) + 1);
        }
        if (value != 0ULL) {
            return word * 64 + __builtin_ctzll(value);
        }
    }
    return -1;
}

void addCharacterRule(char from, char to, int rule) {
    characterGraph[from - 'a'].push_back({to - 'a', rule});
}

void buildCharacterReachability() {
    for (int i = 0; i < 26; ++i) {
        characterGraph[i].clear();
    }
    addCharacterRule('t', 'i', 1);
    for (char c = 'a'; c <= 'z'; ++c) {
        addCharacterRule(c, 'm', 2);
    }
    addCharacterRule('s', 'i', 3);
    addCharacterRule('t', 'r', 6);
    for (char c = 'a'; c <= 'g'; ++c) {
        addCharacterRule(c, 'h', 7);
    }
    addCharacterRule('o', 'a', 8);
    addCharacterRule('t', 's', 9);
    for (char c = 't'; c <= 'z'; ++c) {
        addCharacterRule(c, 'u', 10);
    }
    memset(canReach, 0, sizeof(canReach));
    memset(firstHop, -1, sizeof(firstHop));
    memset(firstRule, -1, sizeof(firstRule));
    for (int source = 0; source < 26; ++source) {
        queue<int> pending;
        canReach[source][source] = true;
        firstHop[source][source] = source;
        pending.push(source);
        while (!pending.empty()) {
            int vertex = pending.front();
            pending.pop();
            for (const Edge& edge : characterGraph[vertex]) {
                if (canReach[source][edge.to]) {
                    continue;
                }
                canReach[source][edge.to] = true;
                if (vertex == source) {
                    firstHop[source][edge.to] = edge.to;
                    firstRule[source][edge.to] = edge.rule;
                } else {
                    firstHop[source][edge.to] = firstHop[source][vertex];
                    firstRule[source][edge.to] = firstRule[source][vertex];
                }
                pending.push(edge.to);
            }
        }
    }
}

vector<pair<int, int>> getCharacterPath(int from, int to) {
    vector<pair<int, int>> path;
    int current = from;
    while (current != to) {
        int next = firstHop[current][to];
        int rule = firstRule[current][to];
        if (next == -1 || rule == -1) {
            return vector<pair<int, int>>();
        }
        path.push_back({next, rule});
        current = next;
    }
    return path;
}

void printStep(int rule, const string& before, const string& after) {
    cout << rule << ": " << before << " -> " << after << '\n';
}

void applyCharacterPath(string& current, int position, char target) {
    int from = current[position] - 'a';
    int to = target - 'a';
    vector<pair<int, int>> path = getCharacterPath(from, to);
    for (const pair<int, int>& step : path) {
        string before = current;
        current[position] = static_cast<char>('a' + step.first);
        printStep(step.second, before, current);
    }
}

bool solveCase(const string& source, const string& target) {
    if (source == target) {
        printStep(5, source, target);
        return true;
    }
    int sourceLength = static_cast<int>(source.size());
    int targetLength = static_cast<int>(target.size());
    int stateCount = targetLength + 1;
    int wordCount = (stateCount + 63) / 64;
    bool expandable[26] = {};
    bool canExpand[26] = {};
    for (int c = 0; c < 26; ++c) {
        expandable[c] = canReach[0][c];
        canExpand[c] = canReach[c][0];
    }
    vector<pair<int, int>> expandableRuns;
    for (int left = 0; left < targetLength;) {
        if (!expandable[target[left] - 'a']) {
            ++left;
            continue;
        }
        int right = left;
        while (right + 1 < targetLength && expandable[target[right + 1] - 'a']) {
            ++right;
        }
        expandableRuns.push_back({left, right});
        left = right + 1;
    }
    vector<vector<unsigned long long>> allowedBits(26, vector<unsigned long long>(wordCount, 0ULL));
    for (int c = 0; c < 26; ++c) {
        for (int position = 0; position < targetLength; ++position) {
            if (canReach[c][target[position] - 'a']) {
                allowedBits[c][position >> 6] |= 1ULL << (position & 63);
            }
        }
    }
    vector<vector<unsigned long long>> states(sourceLength + 1, vector<unsigned long long>(wordCount, 0ULL));
    states[0][0] = 1ULL;
    for (int i = 0; i < sourceLength; ++i) {
        const vector<unsigned long long>& current = states[i];
        vector<unsigned long long>& next = states[i + 1];
        next = current;
        int sourceChar = source[i] - 'a';
        for (int word = 0; word < wordCount; ++word) {
            unsigned long long currentAllowed = current[word] & allowedBits[sourceChar][word];
            unsigned long long shifted = currentAllowed << 1;
            if (word > 0) {
                unsigned long long previousAllowed = current[word - 1] & allowedBits[sourceChar][word - 1];
                if ((previousAllowed & (1ULL << 63)) != 0ULL) {
                    shifted |= 1ULL;
                }
            }
            next[word] |= shifted;
        }
        if (canExpand[sourceChar]) {
            for (const pair<int, int>& run : expandableRuns) {
                int first = findAnyBit(current, run.first, run.second, stateCount);
                if (first == -1) {
                    continue;
                }
                setRange(next, first + 1, run.second + 1, stateCount);
            }
        }
        int validBitsInLastWord = stateCount & 63;
        if (validBitsInLastWord != 0) {
            next[wordCount - 1] &= getLowMask(validBitsInLastWord);
        }
    }
    if (!getBit(states[sourceLength], targetLength, stateCount)) {
        cout << "no\n";
        return false;
    }
    vector<string> assigned(sourceLength);
    int i = sourceLength;
    int j = targetLength;
    while (i > 0) {
        const vector<unsigned long long>& previous = states[i - 1];
        int sourceChar = source[i - 1] - 'a';
        if (getBit(previous, j, stateCount)) {
            assigned[i - 1] = "";
            --i;
            continue;
        }
        if (j > 0 && canReach[sourceChar][target[j - 1] - 'a'] && getBit(previous, j - 1, stateCount)) {
            assigned[i - 1] = target.substr(j - 1, 1);
            --i;
            --j;
            continue;
        }
        bool recovered = false;
        if (canExpand[sourceChar] && j > 0 && expandable[target[j - 1] - 'a']) {
            for (const pair<int, int>& run : expandableRuns) {
                if (j - 1 < run.first || j - 1 > run.second) {
                    continue;
                }
                int previousPosition = findAnyBit(previous, run.first, min(run.second, j - 1), stateCount);
                if (previousPosition == -1) {
                    continue;
                }
                assigned[i - 1] = target.substr(previousPosition, j - previousPosition);
                j = previousPosition;
                --i;
                recovered = true;
                break;
            }
        }
        if (!recovered) {
            cout << "no\n";
            return false;
        }
    }
    if (j != 0) {
        cout << "no\n";
        return false;
    }
    string current = source;
    int position = 0;
    for (int index = 0; index < sourceLength; ++index) {
        const string& piece = assigned[index];
        if (piece.empty()) {
            string before = current;
            current.erase(current.begin() + position);
            printStep(5, before, current);
            continue;
        }
        if (piece.size() == 1) {
            applyCharacterPath(current, position, piece[0]);
            ++position;
            continue;
        }
        applyCharacterPath(current, position, 'a');
        for (size_t count = 1; count < piece.size(); ++count) {
            string before = current;
            current.replace(position, 1, "aa");
            printStep(4, before, current);
        }
        for (size_t offset = 0; offset < piece.size(); ++offset) {
            applyCharacterPath(current, position + static_cast<int>(offset), piece[offset]);
        }
        position += static_cast<int>(piece.size());
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildCharacterReachability();
    string source;
    string target;
    bool firstCase = true;
    while (cin >> source >> target) {
        if (!firstCase) {
            cout << '\n';
        }
        firstCase = false;
        solveCase(source, target);
    }
    return 0;
}
