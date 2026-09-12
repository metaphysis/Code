// Fuzzy Google Suggest
// UVa ID: 1462
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.450s

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    int child[26], count, label;
    TrieNode() {
        fill(child, child + 26, -1);
        count = 0;
        label = 0;
    }
};

vector<TrieNode> trie;
int queryId;
string queryWord;

void insertWord(const string &word) {
    int node = 0;
    for (char ch : word) {
        int index = ch - 'a';
        if (trie[node].child[index] == -1) {
            trie[node].child[index] = trie.size();
            trie.emplace_back();
        }
        node = trie[node].child[index];
        trie[node].count++;
    }
}

void fuzzyDfs(int node, int index, int rest) {
    if (rest < 0) return;
    if (trie[node].label == queryId + 1) return;
    if (index == (int)queryWord.size()) {
        trie[node].label = queryId + 1;
        return;
    }
    if (trie[node].label < queryId) trie[node].label = queryId;
    for (int next = 0; next < 26; next++) {
        int child = trie[node].child[next];
        if (child == -1) continue;
        if (next == queryWord[index] - 'a') fuzzyDfs(child, index + 1, rest);
        else fuzzyDfs(child, index + 1, rest - 1);
        fuzzyDfs(child, index, rest - 1);
    }
    fuzzyDfs(node, index + 1, rest - 1);
}

int countDfs(int node) {
    if (trie[node].label == queryId + 1) return trie[node].count;
    if (trie[node].label < queryId) return 0;
    int result = 0;
    for (int next = 0; next < 26; next++) {
        int child = trie[node].child[next];
        if (child != -1) result += countDfs(child);
    }
    return result;
}

int fuzzyFind(const string &word, int limit) {
    queryWord = word;
    queryId += 2;
    fuzzyDfs(0, 0, limit);
    return countDfs(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    while (cin >> n && n) {
        trie.clear();
        trie.reserve(n * 10 + 1);
        trie.emplace_back();
        queryId = 0;
        for (int i = 0; i < n; i++) {
            string word;
            cin >> word;
            insertWord(word);
        }
        cin >> q;
        for (int i = 0; i < q; i++) {
            string word;
            int limit;
            cin >> word >> limit;
            cout << fuzzyFind(word, limit) << '\n';
        }
    }
    return 0;
}
