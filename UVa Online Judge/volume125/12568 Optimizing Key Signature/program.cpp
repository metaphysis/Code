#include <bits/stdc++.h>
using namespace std;

array<int, 7> makeKey(int type, int cnt) {
    array<int, 7> key{};
    string pos = "CDEFGAB", sharp = "FCGDAEB", flat = "BEADGCF";
    for (int i = 0; i < cnt; ++i) {
        if (type == 1) key[pos.find(sharp[i])] = 1;
        else if (type == -1) key[pos.find(flat[i])] = -1;
    }
    return key;
}

int countAcc(const vector<vector<pair<int, int>>> &meas, int type, int cnt) {
    array<int, 7> key = makeKey(type, cnt), cur;
    int ans = 0;
    for (const auto &mea : meas) {
        cur = key;
        for (const auto &note : mea) {
            int id = note.first, val = note.second;
            if (cur[id] != val) {
                ++ans;
                cur[id] = val;
            }
        }
    }
    return ans;
}

string getKeyStr(int type, int cnt) {
    if (cnt == 0) return "0";
    return to_string(cnt) + (type == 1 ? "#" : "b");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt, caseId = 0;
    cin >> testCnt;
    while (testCnt--) {
        string initSig, token, pos = "CDEFGAB";
        cin >> initSig;
        int initCnt = 0, initType = 0;
        if (initSig != "0") {
            initCnt = initSig[0] - '0';
            initType = initSig.back() == '#' ? 1 : -1;
        }
        array<int, 7> initKey = makeKey(initType, initCnt), cur = initKey;
        vector<vector<pair<int, int>>> meas;
        vector<pair<int, int>> mea;
        while (cin >> token) {
            if (token == "|") {
                meas.push_back(mea);
                mea.clear();
                cur = initKey;
            } else if (token == "||") {
                meas.push_back(mea);
                break;
            } else {
                char acc = token.size() == 2 ? token[0] : 0, note = token.back();
                int id = pos.find(note);
                if (acc == '#') cur[id] = 1;
                else if (acc == 'b') cur[id] = -1;
                else if (acc == 'n') cur[id] = 0;
                mea.push_back({id, cur[id]});
            }
        }
        int minAcc = INT_MAX, minCnt = INT_MAX;
        vector<string> ans;
        for (int cnt = 0; cnt <= 7; ++cnt) {
            for (int type = -1; type <= 1; ++type) {
                if (cnt == 0 && type != 0) continue;
                if (cnt > 0 && type == 0) continue;
                int acc = countAcc(meas, type, cnt);
                if (acc < minAcc || (acc == minAcc && cnt < minCnt)) {
                    minAcc = acc;
                    minCnt = cnt;
                    ans.clear();
                    ans.push_back(getKeyStr(type, cnt));
                } else if (acc == minAcc && cnt == minCnt) {
                    ans.push_back(getKeyStr(type, cnt));
                }
            }
        }
        sort(ans.begin(), ans.end());
        cout << "Case " << ++caseId << ": " << minAcc << '\n';
        for (int i = 0; i < (int)ans.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << ans[i];
        }
        cout << "\n\n";
    }
    return 0;
}
