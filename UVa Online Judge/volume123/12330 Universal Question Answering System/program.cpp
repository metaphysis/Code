#include <bits/stdc++.h>
using namespace std;

map<string, int> idMap;
vector<vector<int>> adj;

int getId(const string &word, char type) {
    string key = string(1, type) + word;
    if (idMap.count(key)) return idMap[key];
    int id = adj.size();
    idMap[key] = id;
    adj.push_back(vector<int>());
    return id;
}

vector<string> splitSentence(string line) {
    vector<string> words;
    string word;
    while (!line.empty() && isspace(static_cast<unsigned char>(line.back()))) line.pop_back();
    if (!line.empty()) line.pop_back();
    stringstream ss(line);
    while (ss >> word) words.push_back(word);
    return words;
}

bool canReach(int src, int dst) {
    if (src == dst) return true;
    vector<int> vis(adj.size(), 0);
    queue<int> q;
    vis[src] = 1;
    q.push(src);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int next : adj[cur]) {
            if (vis[next]) continue;
            if (next == dst) return true;
            vis[next] = 1;
            q.push(next);
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    string line;
    getline(cin, line);
    for (int caseNum = 1; caseNum <= testCount; caseNum++) {
        idMap.clear();
        adj.clear();
        string ans;
        while (getline(cin, line)) {
            while (!line.empty() && isspace(static_cast<unsigned char>(line.back()))) line.pop_back();
            if (line.empty()) continue;
            char endChar = line.back();
            if (endChar == '!') break;
            vector<string> words = splitSentence(line);
            int src, dst;
            if (endChar == '.') {
                if (words.size() == 3) {
                    src = getId(words[0], 'N');
                    if (words[1] == "are") dst = getId(words[2], 'N');
                    else dst = getId(words[2], 'V');
                } else {
                    src = getId(words[3], 'V');
                    if (words[4] == "are") dst = getId(words[5], 'N');
                    else dst = getId(words[5], 'V');
                }
                adj[src].push_back(dst);
            } else if (endChar == '?') {
                if (words.size() == 3) {
                    src = getId(words[1], 'N');
                    if (words[0] == "are") dst = getId(words[2], 'N');
                    else dst = getId(words[2], 'V');
                } else {
                    src = getId(words[4], 'V');
                    if (words[0] == "are") dst = getId(words[5], 'N');
                    else dst = getId(words[5], 'V');
                }
                ans += canReach(src, dst) ? 'Y' : 'M';
            }
        }
        cout << "Case #" << caseNum << ":\n";
        cout << ans << '\n';
    }
    return 0;
}
