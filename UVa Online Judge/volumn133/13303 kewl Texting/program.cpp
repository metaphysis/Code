#include <bits/stdc++.h>
using namespace std;

bool lessWord(int a, int b, const vector<string> &word) {
    if (a != b && (a == 0 || b == 0)) return a == 0;
    if (a != b && (a == 1 || b == 1)) return a == 1;
    return word[a] < word[b];
}

bool better(int a, int b, int ca, int cb, const vector<int> &freq, const vector<string> &word) {
    if (b == -1) return true;
    if (ca != cb) return ca > cb;
    if (freq[a] != freq[b]) return freq[a] > freq[b];
    return lessWord(a, b, word);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        string line;
        getline(cin, line);
        map<string, int> id;
        vector<string> word = {"{start}", "{end}"};
        vector<int> freq(2, 0);
        unordered_map<long long, int> edge;
        auto getId = [&](const string &s) {
            if (id.count(s)) return id[s];
            int x = word.size();
            id[s] = x;
            word.push_back(s);
            freq.push_back(0);
            return x;
        };
        for (int i = 0; i < n; i++) {
            getline(cin, line);
            stringstream ss(line);
            string s;
            vector<int> seq;
            seq.push_back(0);
            freq[0]++;
            freq[1]++;
            while (ss >> s) {
                int x = getId(s);
                seq.push_back(x);
                freq[x]++;
            }
            seq.push_back(1);
            int m = seq.size();
            for (int j = 0; j + 1 < m; j++) {
                long long key = ((long long)seq[j] << 32) | (unsigned int)seq[j + 1];
                edge[key]++;
            }
        }
        int m = word.size();
        vector<int> best(m, -1), bestCnt(m, 0);
        for (const auto &it : edge) {
            int a = (int)(it.first >> 32), b = (int)(it.first & 0xffffffff);
            if (better(b, best[a], it.second, bestCnt[a], freq, word)) {
                best[a] = b;
                bestCnt[a] = it.second;
            }
        }
        vector<string> ans;
        vector<char> vis(m, 0);
        int cur = 0;
        bool inf = false;
        while (true) {
            if (vis[cur]) {
                inf = true;
                break;
            }
            vis[cur] = 1;
            int nxt = best[cur];
            if (nxt == -1 || nxt == 1) break;
            ans.push_back(word[nxt]);
            cur = nxt;
        }
        if (inf) {
            cout << "INFINITE\n";
        } else {
            for (int i = 0; i < (int)ans.size(); i++) {
                if (i) cout << ' ';
                cout << ans[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
