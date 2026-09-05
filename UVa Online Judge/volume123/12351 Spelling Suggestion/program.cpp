#include <bits/stdc++.h>
using namespace std;

const int inf = 1000000000;
const string dictChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'";

struct Edge {
    char ch;
    int next, node;
};

struct TrieNode {
    int head, wordId;
    TrieNode() : head(-1), wordId(-1) {}
};

vector<TrieNode> trie;
vector<Edge> edges;
vector<string> dictWords;
bool nearSub[128][128];

int getCharId(char ch) {
    return static_cast<int>(ch);
}

int findChild(int nodeId, char ch) {
    int edgeId = trie[nodeId].head;
    while (edgeId != -1) {
        if (edges[edgeId].ch == ch)
            return edges[edgeId].node;
        edgeId = edges[edgeId].next;
    }
    return -1;
}

int addChild(int nodeId, char ch) {
    int childId = findChild(nodeId, ch);
    if (childId != -1)
        return childId;
    childId = static_cast<int>(trie.size());
    trie.push_back(TrieNode());
    edges.push_back({ch, trie[nodeId].head, childId});
    trie[nodeId].head = static_cast<int>(edges.size()) - 1;
    return childId;
}

void insertWord(const string &word, int wordId) {
    int nodeId = 0;
    for (char ch : word)
        nodeId = addChild(nodeId, ch);
    trie[nodeId].wordId = wordId;
}

int getReplaceCost(char from, char to) {
    if (from == to)
        return 0;
    if (static_cast<unsigned char>(from) < 128 && static_cast<unsigned char>(to) < 128 && nearSub[getCharId(from)][getCharId(to)])
        return 1;
    return 2;
}

void searchTrie(int nodeId, const string &query, const vector<int> &row, const vector<int> &parentRow, char prevChar, int depth, int &best, vector<int> &answers) {
    int wordId = trie[nodeId].wordId;
    if (wordId != -1) {
        int distance = row[query.size()];
        if (distance < best) {
            best = distance;
            answers.clear();
            answers.push_back(wordId);
        } else if (distance == best) {
            answers.push_back(wordId);
        }
    }
    int edgeId = trie[nodeId].head;
    while (edgeId != -1) {
        char currentChar = edges[edgeId].ch;
        int childId = edges[edgeId].node;
        vector<int> nextRow(query.size() + 1, 0);
        nextRow[0] = row[0] + 2;
        for (int i = 1; i <= static_cast<int>(query.size()); ++i) {
            int value = min(nextRow[i - 1] + 2, row[i] + 2);
            value = min(value, row[i - 1] + getReplaceCost(query[i - 1], currentChar));
            if (depth >= 1 && i >= 2 && query[i - 1] == prevChar && query[i - 2] == currentChar)
                value = min(value, parentRow[i - 2] + 2);
            nextRow[i] = value;
        }
        int minValue = *min_element(nextRow.begin(), nextRow.end());
        if (minValue <= best)
            searchTrie(childId, query, nextRow, row, currentChar, depth + 1, best, answers);
        edgeId = edges[edgeId].next;
    }
}

int getDistance(const string &first, const string &second) {
    int n = static_cast<int>(first.size()), m = static_cast<int>(second.size());
    vector<int> prev(m + 1), current(m + 1);
    for (int j = 0; j <= m; ++j)
        prev[j] = j * 2;
    for (int i = 1; i <= n; ++i) {
        current[0] = i * 2;
        for (int j = 1; j <= m; ++j) {
            int value = min(current[j - 1] + 2, prev[j] + 2);
            value = min(value, prev[j - 1] + getReplaceCost(first[i - 1], second[j - 1]));
            if (i >= 2 && j >= 2 && first[i - 1] == second[j - 2] && first[i - 2] == second[j - 1])
                value = min(value, prev[j - 2] + 2);
            current[j] = value;
        }
        prev.swap(current);
    }
    return prev[m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<string>> parts(3);
    string line;
    int partId = 0;
    while (getline(cin, line)) {
        if (line.empty()) {
            if (partId < 2)
                ++partId;
            else
                break;
        } else {
            parts[partId].push_back(line);
        }
    }
    for (const string &rule : parts[0]) {
        stringstream input(rule);
        char from;
        string targets;
        input >> from >> targets;
        for (char to : targets) {
            nearSub[getCharId(from)][getCharId(to)] = true;
            nearSub[getCharId(to)][getCharId(from)] = true;
        }
    }
    trie.push_back(TrieNode());
    for (const string &word : parts[1]) {
        dictWords.push_back(word);
        insertWord(word, static_cast<int>(dictWords.size()) - 1);
    }
    for (const string &query : parts[2]) {
        int best = inf;
        vector<int> answers;
        if (!dictWords.empty())
            best = getDistance(query, dictWords[0]);
        int exactNode = 0;
        bool exactFound = true;
        for (char ch : query) {
            exactNode = findChild(exactNode, ch);
            if (exactNode == -1) {
                exactFound = false;
                break;
            }
        }
        if (exactFound && trie[exactNode].wordId != -1) {
            best = 0;
            answers.clear();
            answers.push_back(trie[exactNode].wordId);
        } else if (!dictWords.empty()) {
            vector<int> rootRow(query.size() + 1, 0);
            vector<int> emptyRow;
            for (int i = 0; i <= static_cast<int>(query.size()); ++i)
                rootRow[i] = i * 2;
            searchTrie(0, query, rootRow, emptyRow, 0, 0, best, answers);
        }
        sort(answers.begin(), answers.end(), [&](int left, int right) {
            return dictWords[left] < dictWords[right];
        });
        answers.erase(unique(answers.begin(), answers.end()), answers.end());
        cout << query << ":" << best << ":";
        for (int i = 0; i < static_cast<int>(answers.size()); ++i) {
            if (i > 0)
                cout << " ";
            cout << dictWords[answers[i]];
        }
        cout << "\n";
    }
    return 0;
}
