#include <bits/stdc++.h>
using namespace std;

struct Sign {
    vector<int> pos;
    int x, y;
};

int rowN, colN, leftCnt;
vector<int> tab;
vector<Sign> signList, ans, path;
vector<vector<int>> cover;

bool canUse(int id) {
    for (int p : signList[id].pos)
        if (tab[p] == 0) return false;
    return true;
}

void useSign(int id, int add) {
    for (int p : signList[id].pos) {
        if (add == -1) {
            if (tab[p] == 1) leftCnt--;
            tab[p]--;
        } else {
            if (tab[p] == 0) leftCnt++;
            tab[p]++;
        }
    }
}

bool dfs() {
    if (leftCnt == 0) {
        if (path.size() >= 2 && path.size() <= 9) {
            ans = path;
            return true;
        }
        return false;
    }
    if (path.size() == 9) return false;
    int bestPos = -1, bestNum = INT_MAX;
    vector<int> bestList;
    for (int p = 0; p < rowN * colN; p++) {
        if (tab[p] == 0) continue;
        vector<int> cur;
        for (int id : cover[p])
            if (canUse(id)) cur.push_back(id);
        if (cur.empty()) return false;
        if ((int)cur.size() < bestNum) {
            bestNum = cur.size();
            bestPos = p;
            bestList = cur;
        }
        if (bestNum == 1) break;
    }
    for (int id : bestList) {
        useSign(id, -1);
        path.push_back(signList[id]);
        if (dfs()) return true;
        path.pop_back();
        useSign(id, 1);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testN;
    cin >> testN;
    while (testN--) {
        cin >> rowN >> colN;
        tab.assign(rowN * colN, 0);
        leftCnt = 0;
        for (int i = 0; i < rowN; i++) {
            for (int j = 0; j < colN; j++) {
                cin >> tab[i * colN + j];
                if (tab[i * colN + j] > 0) leftCnt++;
            }
        }
        signList.clear();
        cover.assign(rowN * colN, {});
        for (int i = 0; i < rowN; i++) {
            for (int j = 0; j < colN; j++) {
                if (tab[i * colN + j] != 1) continue;
                for (int d = 1; d <= 5; d++) {
                    if (i - d < 0 || i + d >= rowN || j - d < 0 || j + d >= colN) continue;
                    Sign now;
                    now.x = i;
                    now.y = j;
                    now.pos.push_back(i * colN + j);
                    for (int k = 1; k <= d; k++) {
                        now.pos.push_back((i - k) * colN + j);
                        now.pos.push_back((i + k) * colN + j);
                        now.pos.push_back(i * colN + j - k);
                        now.pos.push_back(i * colN + j + k);
                    }
                    bool ok = true;
                    for (int p : now.pos)
                        if (tab[p] == 0) ok = false;
                    if (!ok) continue;
                    int id = signList.size();
                    signList.push_back(now);
                    for (int p : now.pos) cover[p].push_back(id);
                }
            }
        }
        ans.clear();
        path.clear();
        dfs();
        int lastX = -1, lastY = -1;
        for (Sign s : ans) {
            if (s.x > lastX || (s.x == lastX && s.y > lastY)) {
                lastX = s.x;
                lastY = s.y;
            }
        }
        cout << ans.size() << '\n';
        cout << lastX + 1 << ' ' << lastY + 1 << '\n';
    }
    return 0;
}
