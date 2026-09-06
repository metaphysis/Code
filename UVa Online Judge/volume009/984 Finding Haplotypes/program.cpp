#include <bits/stdc++.h>
using namespace std;

struct HapPair {
    int first, second;
};

struct TryPair {
    int first, second, addCount;
};

int n, l, bestCount, selectedCount;
vector<string> genotypes;
vector<vector<HapPair>> options;
bitset<1024> selected;

bool isCovered(int index) {
    for (const HapPair& item : options[index])
        if (selected[item.first] && selected[item.second])
            return true;
    return false;
}

void getCandidates(int index, vector<TryPair>& candidates, int& minAdd) {
    set<pair<int, int>> used;
    minAdd = INT_MAX;
    for (const HapPair& item : options[index]) {
        int addCount = 0, first = -1, second = -1;
        if (!selected[item.first]) {
            first = item.first;
            addCount++;
        }
        if (!selected[item.second]) {
            if (second == -1 && item.second != first) {
                second = item.second;
                addCount++;
            }
        }
        if (addCount == 0) continue;
        if (selectedCount + addCount >= bestCount) continue;
        if (first == -1) first = second;
        if (second == -1) second = first;
        if (first > second) swap(first, second);
        if (!used.insert({first, second}).second) continue;
        minAdd = min(minAdd, addCount);
        candidates.push_back({first, second, addCount});
    }
}

void searchAnswer(int doneMask) {
    if (doneMask == (1 << n) - 1) {
        bestCount = min(bestCount, selectedCount);
        return;
    }
    if (selectedCount >= bestCount) return;
    int chooseIndex = -1, minSize = INT_MAX, minNeed = 0;
    vector<TryPair> chooseCandidates;
    for (int i = 0; i < n; i++) {
        if (doneMask & (1 << i)) continue;
        vector<TryPair> currentCandidates;
        int currentMinAdd;
        getCandidates(i, currentCandidates, currentMinAdd);
        if (currentCandidates.empty()) return;
        minNeed = max(minNeed, currentMinAdd);
        if ((int)currentCandidates.size() < minSize) {
            minSize = currentCandidates.size();
            chooseIndex = i;
            chooseCandidates = currentCandidates;
        }
    }
    if (selectedCount + minNeed >= bestCount) return;
    sort(chooseCandidates.begin(), chooseCandidates.end(), [](const TryPair& a, const TryPair& b) {
        return a.addCount < b.addCount;
    });
    for (const TryPair& item : chooseCandidates) {
        bool firstAdded = !selected[item.first];
        bool secondAdded = item.first != item.second && !selected[item.second];
        if (firstAdded) {
            selected[item.first] = true;
            selectedCount++;
        }
        if (secondAdded) {
            selected[item.second] = true;
            selectedCount++;
        }
        int nextDone = doneMask;
        for (int i = 0; i < n; i++)
            if (!(nextDone & (1 << i)) && isCovered(i))
                nextDone |= 1 << i;
        searchAnswer(nextDone);
        if (secondAdded) {
            selected[item.second] = false;
            selectedCount--;
        }
        if (firstAdded) {
            selected[item.first] = false;
            selectedCount--;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> l) {
        if (n == 0 && l == 0) break;
        genotypes.assign(n, "");
        options.assign(n, {});
        for (int i = 0; i < n; i++)
            cin >> genotypes[i];
        for (int i = 0; i < n; i++) {
            int base = 0, twoCount = 0;
            vector<int> positions;
            for (int j = 0; j < l; j++) {
                if (genotypes[i][j] == '1')
                    base |= 1 << j;
                else if (genotypes[i][j] == '2') {
                    positions.push_back(j);
                    twoCount++;
                }
            }
            set<pair<int, int>> used;
            for (int mask = 0; mask < (1 << twoCount); mask++) {
                int first = base, second;
                for (int j = 0; j < twoCount; j++)
                    if (mask & (1 << j))
                        first |= 1 << positions[j];
                second = first;
                for (int position : positions)
                    second ^= 1 << position;
                if (first > second) swap(first, second);
                used.insert({first, second});
            }
            for (const pair<int, int>& item : used)
                options[i].push_back({item.first, item.second});
        }
        bestCount = 2 * n;
        selected.reset();
        selectedCount = 0;
        searchAnswer(0);
        cout << bestCount << '\n';
    }
    return 0;
}
