#include <bits/stdc++.h>
using namespace std;

struct Pole {
    int pos, oldFlag, newFlag;
};

int getMinWidth(const vector<Pole>& poles, int startId, int nationCnt, bool reversed) {
    vector<int> diff(nationCnt + 1, 0);
    int rightId = startId, badCnt = 0, minWidth = INT_MAX;
    for (int i = 0; i <= startId; i++) {
        int flag = reversed ? poles[i].newFlag : poles[i].oldFlag;
        if (flag != 0) diff[flag]--;
    }
    for (int leftId = 0; leftId <= startId; leftId++) {
        if (leftId > 0) {
            int flag = reversed ? poles[leftId - 1].oldFlag : poles[leftId - 1].newFlag;
            diff[flag]++;
            if (diff[flag] == 1) badCnt++;
        }
        while (badCnt > 0) {
            rightId++;
            int flag = reversed ? poles[rightId].newFlag : poles[rightId].oldFlag;
            if (diff[flag] == 1) badCnt--;
            diff[flag]--;
        }
        minWidth = min(minWidth, poles[rightId].pos - poles[leftId].pos);
    }
    return minWidth;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    while (testCnt--) {
        int poleCnt, startPos, nationCnt, startId = -1;
        cin >> poleCnt >> startPos >> nationCnt;
        vector<Pole> poles;
        poles.reserve(poleCnt + 1);
        for (int i = 0; i < poleCnt; i++) {
            int pos, oldFlag, newFlag;
            cin >> pos >> oldFlag >> newFlag;
            if (startId == -1 && pos > startPos) {
                startId = poles.size();
                poles.push_back({startPos, 0, 0});
            }
            poles.push_back({pos, oldFlag, newFlag});
        }
        if (startId == -1) {
            startId = poles.size();
            poles.push_back({startPos, 0, 0});
        }
        int minWidth = min(getMinWidth(poles, startId, nationCnt, false), getMinWidth(poles, startId, nationCnt, true));
        long long answer = 2LL * (poles.back().pos - poles.front().pos + minWidth);
        cout << answer << '\n';
    }
    return 0;
}
