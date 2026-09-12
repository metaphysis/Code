#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        int people, tubes, ideas;
        cin >> people >> tubes >> ideas;
        string line;
        getline(cin, line);
        vector<vector<char>> creates(people, vector<char>(ideas)), needMem(people, vector<char>(ideas));
        for (int p = 0; p < people; p++) {
            getline(cin, line);
            stringstream needIn(line);
            int idea;
            while (needIn >> idea) needMem[p][idea] = 1;
            getline(cin, line);
            stringstream createIn(line);
            while (createIn >> idea) creates[p][idea] = 1;
        }
        vector<vector<int>> rev(people);
        vector<pair<int, int>> edges(tubes);
        for (int e = 0; e < tubes; e++) {
            int from, to;
            cin >> from >> to;
            edges[e] = {from, to};
            rev[to].push_back(from);
        }
        for (int idea = 0; idea < ideas; idea++) {
            queue<int> que;
            for (int p = 0; p < people; p++)
                if (needMem[p][idea]) que.push(p);
            while (!que.empty()) {
                int cur = que.front();
                que.pop();
                for (int pre : rev[cur]) {
                    if (!creates[pre][idea] && !needMem[pre][idea]) {
                        needMem[pre][idea] = 1;
                        que.push(pre);
                    }
                }
            }
        }
        for (auto edge : edges) {
            int to = edge.second;
            bool first = true;
            for (int idea = 0; idea < ideas; idea++) {
                if (needMem[to][idea]) {
                    if (!first) cout << ' ';
                    cout << idea;
                    first = false;
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
