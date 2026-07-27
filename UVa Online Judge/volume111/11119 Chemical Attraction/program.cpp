// Chemical Attraction
// UVa ID: 11119
// Verdict: Accepted
// Submission Date: 2026-07-27
// UVa Run Time: 0.020s
// https://blog.csdn.net/metaphysis/article/details/163247969

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int scenario = 0;
    int Nc;
    while (cin >> Nc && Nc != 0) {
        ++scenario;
        vector<string> cationSymbols(Nc);
        for (int i = 0; i < Nc; ++i) cin >> cationSymbols[i];
        int Na;
        cin >> Na;
        vector<string> anionSymbols(Na);
        for (int i = 0; i < Na; ++i) cin >> anionSymbols[i];
        vector<vector<int>> cationPref(Nc, vector<int>(Na));
        for (int i = 0; i < Nc; ++i)
            for (int j = 0; j < Na; ++j)
                cin >> cationPref[i][j];
        vector<vector<int>> anionPref(Na, vector<int>(Nc));
        for (int i = 0; i < Na; ++i)
            for (int j = 0; j < Nc; ++j)
                cin >> anionPref[i][j];
        unordered_map<string, int> cationMap, anionMap;
        for (int i = 0; i < Nc; ++i) cationMap[cationSymbols[i]] = i;
        for (int i = 0; i < Na; ++i) anionMap[anionSymbols[i]] = i;
        int mixture = 0;
        int M;
        while (cin >> M && M != 0) {
            ++mixture;
            vector<int> cations(M), anions(M);
            for (int i = 0; i < M; ++i) {
                string comp;
                cin >> comp;
                string cSym = comp.substr(0, 2);
                string aSym = comp.substr(2, 2);
                cations[i] = cationMap[cSym];
                anions[i] = anionMap[aSym];
            }
            // 构建每个阳离子个体的偏好列表（按吸引力降序）
            vector<vector<int>> prefC(M);
            for (int i = 0; i < M; ++i) {
                vector<int> list(M);
                iota(list.begin(), list.end(), 0);
                sort(list.begin(), list.end(), [&](int a1, int a2) {
                    return cationPref[cations[i]][anions[a1]] >
                           cationPref[cations[i]][anions[a2]];
                });
                prefC[i] = move(list);
            }
            // 构建每个阴离子个体的偏好列表（按吸引力降序）
            vector<vector<int>> prefA(M);
            for (int j = 0; j < M; ++j) {
                vector<int> list(M);
                iota(list.begin(), list.end(), 0);
                sort(list.begin(), list.end(), [&](int c1, int c2) {
                    return anionPref[anions[j]][cations[c1]] >
                           anionPref[anions[j]][cations[c2]];
                });
                prefA[j] = move(list);
            }
            // Gale-Shapley 算法（阳离子主动求婚）
            vector<int> matchA(M, -1), matchC(M, -1), nextProposal(M, 0);
            queue<int> freeC;
            for (int i = 0; i < M; ++i) freeC.push(i);
            while (!freeC.empty()) {
                int c = freeC.front(); freeC.pop();
                if (nextProposal[c] >= M) continue;
                int a = prefC[c][nextProposal[c]++];

                if (matchA[a] == -1) {
                    matchA[a] = c;
                    matchC[c] = a;
                } else {
                    int curC = matchA[a];
                    int curType = cations[curC], newType = cations[c], aType = anions[a];
                    if (anionPref[aType][newType] > anionPref[aType][curType]) {
                        matchA[a] = c;
                        matchC[c] = a;
                        matchC[curC] = -1;
                        freeC.push(curC);
                    } else {
                        freeC.push(c);
                    }
                }
            }
            // 输出结果
            cout << "Scenario " << scenario << ", Mixture " << mixture << ":";
            for (int i = 0; i < M; ++i)
                cout << " " << cationSymbols[cations[i]] << anionSymbols[anions[matchC[i]]];
            cout << "\n\n";
        }
    }
    return 0;
}
