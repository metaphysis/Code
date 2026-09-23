#include <bits/stdc++.h>
using namespace std;

struct Mirror {
    int pos[3], type, nextId[6];
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    const int turnDir[6][6] = {
        {3, 2, 1, 0, 4, 5},
        {2, 3, 0, 1, 4, 5},
        {0, 1, 5, 4, 3, 2},
        {0, 1, 4, 5, 2, 3},
        {5, 4, 2, 3, 1, 0},
        {4, 5, 2, 3, 0, 1}
    };
    const int faceId[6] = {3, 2, 5, 4, 1, 0};
    for (int caseId = 0; caseId < testCount; ++caseId) {
        int s, n;
        cin >> s >> n;
        vector<Mirror> mirrors(n);
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            cin >> mirrors[i].pos[0] >> mirrors[i].pos[1]
                >> mirrors[i].pos[2] >> mirrors[i].type;
            fill(mirrors[i].nextId, mirrors[i].nextId + 6, -1);
            order[i] = i;
        }
        for (int axis = 0; axis < 3; ++axis) {
            int firstAxis = (axis + 1) % 3, secondAxis = (axis + 2) % 3;
            sort(order.begin(), order.end(), [&](int a, int b) {
                if (mirrors[a].pos[firstAxis] != mirrors[b].pos[firstAxis]) return mirrors[a].pos[firstAxis] < mirrors[b].pos[firstAxis];
                if (mirrors[a].pos[secondAxis] != mirrors[b].pos[secondAxis]) return mirrors[a].pos[secondAxis] < mirrors[b].pos[secondAxis];
                return mirrors[a].pos[axis] < mirrors[b].pos[axis];
            });
            for (int i = 1; i < n; ++i) {
                int prevId = order[i - 1], curId = order[i];
                if (mirrors[prevId].pos[firstAxis] == mirrors[curId].pos[firstAxis] &&
                    mirrors[prevId].pos[secondAxis] == mirrors[curId].pos[secondAxis]) {
                    mirrors[prevId].nextId[axis * 2 + 1] = curId;
                    mirrors[curId].nextId[axis * 2] = prevId;
                }
            }
        }
        long long rayCount[6] = {}, turnCount[6] = {};
        rayCount[4] = 1LL * (s + 1) * (s + 1);
        for (int i = 0; i < n; ++i) {
            if (mirrors[i].nextId[2] != -1) continue;
            --rayCount[4];
            int curId = i, dir = 3;
            long long turns = 0;
            while (curId != -1) {
                int newDir = turnDir[mirrors[curId].type][dir];
                if (newDir != dir) ++turns;
                dir = newDir;
                curId = mirrors[curId].nextId[dir];
            }
            ++rayCount[faceId[dir]];
            turnCount[faceId[dir]] += turns;
        }
        if (caseId > 0) cout << '\n';
        for (int i = 0; i < 6; ++i) {
            cout << rayCount[i] << '\n';
            cout << turnCount[i] << '\n';
        }
    }
    return 0;
}
