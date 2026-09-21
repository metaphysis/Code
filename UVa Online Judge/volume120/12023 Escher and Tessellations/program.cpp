#include <bits/stdc++.h>
using namespace std;

vector<unsigned long long> candidateMasks;
vector<vector<unsigned long long>> coverList;
unordered_set<unsigned long long> failedStates;
unsigned long long fullMask;
int boardH, boardW;

bool search(unsigned long long usedMask) {
    if (usedMask == fullMask) return true;
    if (failedStates.count(usedMask)) return false;
    unsigned long long remainMask = fullMask ^ usedMask;
    int firstCell = __builtin_ctzll(remainMask);
    for (unsigned long long mask : coverList[firstCell]) {
        if ((mask & usedMask) != 0) continue;
        if (search(usedMask | mask)) return true;
    }
    failedStates.insert(usedMask);
    return false;
}

bool canTile(const vector<string>& figure, int height, int width) {
    int figureH = figure.size(), figureW = figure[0].size(), figureArea = 0;
    vector<pair<int, int>> cells;
    for (int i = 0; i < figureH; i++) {
        for (int j = 0; j < figureW; j++) {
            if (figure[i][j] == '#') {
                cells.push_back({i, j});
                figureArea++;
            }
        }
    }
    if ((height * width) % figureArea != 0) return false;
    boardH = height;
    boardW = width;
    int cellCount = boardH * boardW;
    fullMask = cellCount == 64 ? ~0ULL : (1ULL << cellCount) - 1;
    candidateMasks.clear();
    coverList.assign(cellCount, vector<unsigned long long>());
    failedStates.clear();
    unordered_set<unsigned long long> seenMasks;
    for (int shiftH = 0; shiftH < boardH; shiftH++) {
        for (int shiftW = 0; shiftW < boardW; shiftW++) {
            unsigned long long mask = 0;
            bool valid = true;
            for (pair<int, int> cell : cells) {
                int newH = (cell.first + shiftH) % boardH, newW = (cell.second + shiftW) % boardW;
                int index = newH * boardW + newW;
                unsigned long long bit = 1ULL << index;
                if ((mask & bit) != 0) {
                    valid = false;
                    break;
                }
                mask |= bit;
            }
            if (!valid) continue;
            if (!seenMasks.insert(mask).second) continue;
            candidateMasks.push_back(mask);
            for (int i = 0; i < cellCount; i++)
                if ((mask & (1ULL << i)) != 0) coverList[i].push_back(mask);
        }
    }
    return search(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int figureH, figureW;
        cin >> figureH >> figureW;
        vector<string> figure(figureH);
        for (string& row : figure) cin >> row;
        int height, width;
        cin >> height >> width;
        cout << (canTile(figure, height, width) ? "YES" : "NO") << '\n';
    }
    return 0;
}
