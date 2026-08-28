#include <bits/stdc++.h>
using namespace std;

const int modVal = 1000003;

struct Node {
    int next[26], fail;
    bool bad;
    Node() {
        fill(next, next + 26, 0);
        fail = 0;
        bad = false;
    }
};

vector<Node> buildAutomaton(const vector<string>& words) {
    vector<Node> trie(1);
    for (const string& word : words) {
        int state = 0;
        for (char ch : word) {
            int index = ch - 'a';
            if (trie[state].next[index] == 0) {
                trie[state].next[index] = trie.size();
                trie.push_back(Node());
            }
            state = trie[state].next[index];
        }
        trie[state].bad = true;
    }
    queue<int> que;
    for (int i = 0; i < 26; i++) {
        int nextState = trie[0].next[i];
        if (nextState != 0) que.push(nextState);
    }
    while (!que.empty()) {
        int state = que.front();
        que.pop();
        trie[state].bad = trie[state].bad || trie[trie[state].fail].bad;
        for (int i = 0; i < 26; i++) {
            int nextState = trie[state].next[i];
            if (nextState != 0) {
                trie[nextState].fail = trie[trie[state].fail].next[i];
                que.push(nextState);
            } else {
                trie[state].next[i] = trie[trie[state].fail].next[i];
            }
        }
    }
    return trie;
}

int getLetterIndex(int ch) {
    if (ch < 26) return ch;
    if (ch < 52) return ch - 26;
    if (ch == 52) return 14;
    if (ch == 53) return 8;
    if (ch == 55) return 4;
    if (ch == 57) return 18;
    if (ch == 59) return 19;
    return -1;
}

int solveCase(int minLen, int maxLen, const vector<string>& words) {
    vector<Node> trie = buildAutomaton(words);
    int stateCount = trie.size();
    vector<array<int, 62>> go(stateCount);
    for (int state = 0; state < stateCount; state++) {
        for (int ch = 0; ch < 62; ch++) {
            int letterIndex = getLetterIndex(ch);
            if (letterIndex == -1) {
                go[state][ch] = 0;
            } else {
                go[state][ch] = trie[state].next[letterIndex];
            }
        }
    }
    vector<int> current(stateCount * 8, 0), next(stateCount * 8, 0);
    current[0] = 1;
    int answer = 0;
    for (int length = 1; length <= maxLen; length++) {
        fill(next.begin(), next.end(), 0);
        for (int state = 0; state < stateCount; state++) {
            for (int mask = 0; mask < 8; mask++) {
                int value = current[state * 8 + mask];
                if (value == 0) continue;
                for (int ch = 0; ch < 62; ch++) {
                    int nextState = go[state][ch];
                    if (trie[nextState].bad) continue;
                    int addMask;
                    if (ch < 26) {
                        addMask = 1;
                    } else if (ch < 52) {
                        addMask = 2;
                    } else {
                        addMask = 4;
                    }
                    int nextMask = mask | addMask;
                    int& target = next[nextState * 8 + nextMask];
                    target += value;
                    if (target >= modVal) target -= modVal;
                }
            }
        }
        current.swap(next);
        if (length < minLen) continue;
        for (int state = 0; state < stateCount; state++) {
            answer += current[state * 8 + 7];
            if (answer >= modVal) answer -= modVal;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int minLen, maxLen;
    while (cin >> minLen >> maxLen) {
        int wordCount;
        cin >> wordCount;
        vector<string> words(wordCount);
        for (string& word : words) cin >> word;
        cout << solveCase(minLen, maxLen, words) << '\n';
    }
    return 0;
}
