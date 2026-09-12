#include <bits/stdc++.h>
using namespace std;

const int maxSize = 20;
const int maxWordCount = 105;
const int maxSlotCount = 405;

struct Slot {
    int len, pos[maxSize];
};

int lineCount, colCount, wordCount, slotCount, filledCount;
char board[maxSize][maxSize];
string wordList[maxWordCount];
Slot slotList[maxSlotCount];
bool usedWord[maxWordCount], usedSlot[maxSlotCount];

void buildSlots() {
    int r, c, start, len, k;
    for (r = 0; r < lineCount; r++) {
        c = 0;
        while (c < colCount) {
            if (board[r][c] == '1') {
                c++;
                continue;
            }
            start = c;
            while (c < colCount && board[r][c] != '1')
                c++;
            len = c - start;
            if (len >= 2) {
                slotList[slotCount].len = len;
                for (k = 0; k < len; k++)
                    slotList[slotCount].pos[k] = r * colCount + start + k;
                slotCount++;
            }
        }
    }
    for (c = 0; c < colCount; c++) {
        r = 0;
        while (r < lineCount) {
            if (board[r][c] == '1') {
                r++;
                continue;
            }
            start = r;
            while (r < lineCount && board[r][c] != '1')
                r++;
            len = r - start;
            if (len >= 2) {
                slotList[slotCount].len = len;
                for (k = 0; k < len; k++)
                    slotList[slotCount].pos[k] = (start + k) * colCount + c;
                slotCount++;
            }
        }
    }
}

bool canPlace(int slotId, int wordId) {
    int k, pos, r, c;
    if ((int)wordList[wordId].size() != slotList[slotId].len)
        return false;
    for (k = 0; k < slotList[slotId].len; k++) {
        pos = slotList[slotId].pos[k];
        r = pos / colCount;
        c = pos % colCount;
        if (board[r][c] != '\0' && board[r][c] != wordList[wordId][k])
            return false;
    }
    return true;
}

bool search() {
    int slotId, wordId, bestSlot, bestCount, count, k, pos, r, c, changedCount;
    int changedPos[maxSize];
    if (filledCount == slotCount)
        return true;
    bestSlot = -1;
    bestCount = wordCount + 1;
    for (slotId = 0; slotId < slotCount; slotId++) {
        if (usedSlot[slotId])
            continue;
        count = 0;
        for (wordId = 0; wordId < wordCount; wordId++)
            if (!usedWord[wordId] && canPlace(slotId, wordId))
                count++;
        if (count == 0)
            return false;
        if (count < bestCount) {
            bestCount = count;
            bestSlot = slotId;
        }
    }
    usedSlot[bestSlot] = true;
    for (wordId = 0; wordId < wordCount; wordId++) {
        if (usedWord[wordId] || !canPlace(bestSlot, wordId))
            continue;
        changedCount = 0;
        for (k = 0; k < slotList[bestSlot].len; k++) {
            pos = slotList[bestSlot].pos[k];
            r = pos / colCount;
            c = pos % colCount;
            if (board[r][c] == '\0') {
                board[r][c] = wordList[wordId][k];
                changedPos[changedCount++] = pos;
            }
        }
        usedWord[wordId] = true;
        filledCount++;
        if (search())
            return true;
        filledCount--;
        usedWord[wordId] = false;
        for (k = 0; k < changedCount; k++) {
            pos = changedPos[k];
            r = pos / colCount;
            c = pos % colCount;
            board[r][c] = '\0';
        }
    }
    usedSlot[bestSlot] = false;
    return false;
}

int main() {
    int r, c;
    string row;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> lineCount >> colCount;
    for (r = 0; r < lineCount; r++) {
        cin >> row;
        for (c = 0; c < colCount; c++)
            board[r][c] = row[c] == '1' ? '1' : '\0';
    }
    cin >> wordCount;
    for (r = 0; r < wordCount; r++)
        cin >> wordList[r];
    buildSlots();
    search();
    for (r = 0; r < lineCount; r++) {
        for (c = 0; c < colCount; c++)
            cout << (board[r][c] == '\0' ? '1' : board[r][c]);
        cout << '\n';
    }
    return 0;
}
