#include <bits/stdc++.h>
using namespace std;

struct Batch {
    int clothCount;
    bool active;
};

int getIndex(int index, int n) {
    return (index % n + n) % n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int caseCount;
    cin >> caseCount;
    for (int caseId = 0; caseId < caseCount; caseId++) {
        int n, lineCount;
        cin >> n >> lineCount;
        vector<bool> hasCloth(n, false), isSeparator(n, false);
        vector<Batch> batches(n);
        for (int i = 0; i < n; i++) {
            batches[i].clothCount = 0;
            batches[i].active = false;
        }
        int curPos = 0;
        for (int lineId = 0; lineId < lineCount; lineId++) {
            char command;
            int value;
            cin >> command >> value;
            if (command == 'D') {
                int clothCount = value, zoneSize = clothCount + 2;
                int ticket = -1;
                for (int start = curPos; start < curPos + n; start++) {
                    bool canUse = true;
                    for (int offset = 0; offset < zoneSize; offset++)
                        if (hasCloth[getIndex(start + offset, n)]) {
                            canUse = false;
                            break;
                        }
                    if (canUse) {
                        ticket = getIndex(start, n);
                        break;
                    }
                }
                if (ticket == -1) {
                    cout << "No space left, please come back later.\n";
                    continue;
                }
                for (int offset = 0; offset < zoneSize; offset++) {
                    int index = getIndex(ticket + offset, n);
                    hasCloth[index] = false;
                    isSeparator[index] = false;
                }
                isSeparator[ticket] = true;
                isSeparator[getIndex(ticket + clothCount + 1, n)] = true;
                for (int offset = 1; offset <= clothCount; offset++)
                    hasCloth[getIndex(ticket + offset, n)] = true;
                batches[ticket].clothCount = clothCount;
                batches[ticket].active = true;
                curPos = getIndex(ticket + clothCount + 1, n);
                cout << "The launderer gives ticket " << ticket << ".\n";
            } else {
                int ticket = value, clothCount = batches[ticket].clothCount;
                vector<bool> newlyFree(n, false);
                curPos = ticket;
                for (int offset = 1; offset <= clothCount; offset++) {
                    int index = getIndex(ticket + offset, n);
                    if (hasCloth[index]) {
                        hasCloth[index] = false;
                        newlyFree[index] = true;
                    }
                }
                int rightSeparator = getIndex(ticket + clothCount + 1, n);
                if (isSeparator[ticket] && !hasCloth[getIndex(ticket - 1, n)] && !hasCloth[getIndex(ticket + 1, n)]) {
                    isSeparator[ticket] = false;
                    newlyFree[ticket] = true;
                }
                if (isSeparator[rightSeparator] && !hasCloth[getIndex(rightSeparator - 1, n)] && !hasCloth[getIndex(rightSeparator + 1, n)]) {
                    isSeparator[rightSeparator] = false;
                    newlyFree[rightSeparator] = true;
                }
                batches[ticket].active = false;
                cout << "The launderer gives back batch " << ticket << ".\n";
                for (int offset = 0; offset <= clothCount + 1; offset++) {
                    int index = getIndex(ticket + offset, n);
                    if (newlyFree[index])
                        cout << index << " is freed.\n";
                }
            }
        }
        if (caseId + 1 < caseCount)
            cout << '\n';
    }
    return 0;
}
