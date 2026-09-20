#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        vector<string> names(n);
        unordered_map<string, int> flavorId;
        for (int i = 0; i < n; i++) {
            cin >> names[i];
            flavorId[names[i]] = i;
        }
        vector<vector<int>> traditionalIn(n);
        vector<int> traditionalCount(m, 0), glazedChoice(m, -1);
        for (int i = 0; i < m; i++) {
            int a;
            cin >> a;
            for (int j = 0; j < a; j++) {
                int type;
                string flavor;
                cin >> type >> flavor;
                int id = flavorId[flavor];
                if (type == 1) glazedChoice[i] = id;
                if (type == 2) {
                    traditionalCount[i]++;
                    traditionalIn[id].push_back(i);
                }
            }
        }
        queue<int> pending;
        for (int i = 0; i < m; i++) if (traditionalCount[i] == 0) pending.push(i);
        vector<bool> isGlazed(n, false);
        bool possible = true;
        while (!pending.empty() && possible) {
            int client = pending.front();
            pending.pop();
            int flavor = glazedChoice[client];
            if (flavor == -1) {
                possible = false;
                continue;
            }
            if (isGlazed[flavor]) continue;
            isGlazed[flavor] = true;
            for (int affectedClient : traditionalIn[flavor]) {
                traditionalCount[affectedClient]--;
                if (traditionalCount[affectedClient] == 0) pending.push(affectedClient);
            }
        }
        if (!possible) {
            cout << "Impossible\n";
            continue;
        }
        vector<string> answer;
        for (int i = 0; i < n; i++) if (isGlazed[i]) answer.push_back(names[i]);
        sort(answer.begin(), answer.end());
        cout << answer.size() << '\n';
        for (const string &flavor : answer) cout << flavor << '\n';
    }
    return 0;
}
