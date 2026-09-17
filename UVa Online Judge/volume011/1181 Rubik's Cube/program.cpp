#include <bits/stdc++.h>
using namespace std;

struct Vec {
    int x, y, z;
};

Vec rotateVec(Vec value, Vec axis, int direction) {
    Vec crossValue = {axis.y * value.z - axis.z * value.y, axis.z * value.x - axis.x * value.z, axis.x * value.y - axis.y * value.x};
    int dotValue = axis.x * value.x + axis.y * value.y + axis.z * value.z;
    return {axis.x * dotValue + direction * crossValue.x, axis.y * dotValue + direction * crossValue.y, axis.z * dotValue + direction * crossValue.z};
}

int dotVec(Vec first, Vec second) {
    return first.x * second.x + first.y * second.y + first.z * second.z;
}

bool sameVec(Vec first, Vec second) {
    return first.x == second.x && first.y == second.y && first.z == second.z;
}

Vec slotPos[48], slotNorm[48], faceNorm[6];
int movePerm[6][2][48];

void initSlots() {
    Vec rightDir[6] = {{1, 0, 0}, {-1, 0, 0}, {0, -1, 0}, {0, 0, -1}, {1, 0, 0}, {-1, 0, 0}};
    Vec downDir[6] = {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}};
    int colValue[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int rowValue[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    faceNorm[0] = {0, 1, 0};
    faceNorm[1] = {0, -1, 0};
    faceNorm[2] = {1, 0, 0};
    faceNorm[3] = {-1, 0, 0};
    faceNorm[4] = {0, 0, -1};
    faceNorm[5] = {0, 0, 1};
    for (int face = 0; face < 6; face++) {
        for (int index = 0; index < 8; index++) {
            int slot = face * 8 + index, col = colValue[index], row = rowValue[index];
            slotPos[slot] = {faceNorm[face].x + col * rightDir[face].x + row * downDir[face].x, faceNorm[face].y + col * rightDir[face].y + row * downDir[face].y, faceNorm[face].z + col * rightDir[face].z + row * downDir[face].z};
            slotNorm[slot] = faceNorm[face];
        }
    }
}

void initMoves() {
    for (int face = 0; face < 6; face++) {
        for (int sign = 0; sign < 2; sign++) {
            int direction = sign == 0 ? -1 : 1;
            for (int source = 0; source < 48; source++) {
                Vec nextPos = slotPos[source], nextNorm = slotNorm[source];
                movePerm[face][sign][source] = source;
                if (dotVec(slotPos[source], faceNorm[face]) == 1) {
                    nextPos = rotateVec(nextPos, faceNorm[face], direction);
                    nextNorm = rotateVec(nextNorm, faceNorm[face], direction);
                }
                for (int target = 0; target < 48; target++) {
                    if (sameVec(nextPos, slotPos[target]) && sameVec(nextNorm, slotNorm[target])) {
                        movePerm[face][sign][source] = target;
                        break;
                    }
                }
            }
        }
    }
}

void applyMove(int state[], int move) {
    int nextState[48], face = abs(move) - 1, sign = move > 0 ? 1 : 0;
    for (int source = 0; source < 48; source++) nextState[movePerm[face][sign][source]] = state[source];
    for (int index = 0; index < 48; index++) state[index] = nextState[index];
}

void printState(int state[]) {
    for (int face = 0; face < 6; face++) {
        for (int index = 0; index < 8; index++) {
            if (index > 0) cout << ' ';
            cout << setw(2) << right << state[face * 8 + index];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initSlots();
    initMoves();
    int state[48], move;
    bool firstCase = true;
    for (int index = 0; index < 48; index++) state[index] = index + 1;
    while (cin >> move) {
        if (move == 0) {
            if (!firstCase) cout << '\n';
            printState(state);
            firstCase = false;
            for (int index = 0; index < 48; index++) state[index] = index + 1;
        } else applyMove(state, move);
    }
    return 0;
}
