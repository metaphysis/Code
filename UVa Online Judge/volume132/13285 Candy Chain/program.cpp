#include <bits/stdc++.h>
using namespace std;

struct Node {
    int next[26], parent, depth, price, first, last;
    Node() {
        fill(next, next + 26, -1);
        parent = -1;
        depth = 0;
        price = -1;
        first = -1;
        last = -1;
    }
};

void addWord(vector<Node> &nodes, const string &word, int price) {
    int cur = 0;
    for (char ch : word) {
        int letter = ch - 'a';
        if (nodes[cur].next[letter] == -1) {
            int child = nodes.size();
            nodes[cur].next[letter] = child;
            nodes.emplace_back();
            nodes[child].parent = cur;
            nodes[child].depth = nodes[cur].depth + 1;
            nodes[child].first = nodes[cur].depth == 0 ? letter : nodes[cur].first;
            nodes[child].last = letter;
        }
        cur = nodes[cur].next[letter];
    }
    nodes[cur].price = max(nodes[cur].price, price);
}

int solveCase(const string &chain, const vector<pair<string, int>> &offers) {
    int n = chain.size(), square = n * n;
    vector<Node> nodes(1);
    for (const auto &offer : offers) {
        if ((int)offer.first.size() > n) continue;
        addWord(nodes, offer.first, offer.second);
        string reversed = offer.first;
        reverse(reversed.begin(), reversed.end());
        addWord(nodes, reversed, offer.second);
    }
    vector<int> byLast[26];
    for (int u = 1; u < (int)nodes.size(); ++u) byLast[nodes[u].last].push_back(u);
    vector<int> full(square, -1), match(nodes.size() * square, -1);
    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            int r = l + len - 1, pos = l * n + r;
            for (int k = l; k < r; ++k) {
                int left = full[l * n + k], right = full[(k + 1) * n + r];
                if (left >= 0 && right >= 0) full[pos] = max(full[pos], left + right);
            }
            for (int u : byLast[chain[r] - 'a']) {
                if (nodes[u].depth > len || nodes[u].first != chain[l] - 'a') continue;
                int value = -1;
                if (nodes[u].depth == 1) {
                    if (l == r) value = 0;
                } else {
                    int parent = nodes[u].parent, base = parent * square + l * n;
                    for (int k = l + nodes[u].depth - 2; k < r; ++k) {
                        int previous = match[base + k];
                        if (previous < 0) continue;
                        int gap = k + 1 == r ? 0 : full[(k + 1) * n + r - 1];
                        if (gap >= 0) value = max(value, previous + gap);
                    }
                }
                if (value < 0) continue;
                match[u * square + pos] = value;
                if (nodes[u].price >= 0) full[pos] = max(full[pos], value + nodes[u].price);
            }
        }
    }
    vector<int> best(n + 1, 0);
    for (int r = 0; r < n; ++r) {
        best[r + 1] = best[r];
        for (int l = 0; l <= r; ++l) {
            int value = full[l * n + r];
            if (value >= 0) best[r + 1] = max(best[r + 1], best[l] + value);
        }
    }
    return best[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string chain;
    int childCount;
    while (cin >> chain >> childCount) {
        vector<pair<string, int>> offers(childCount);
        for (auto &offer : offers) cin >> offer.first >> offer.second;
        cout << solveCase(chain, offers) << '\n';
    }
    return 0;
}
