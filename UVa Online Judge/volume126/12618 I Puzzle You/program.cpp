#include <bits/stdc++.h>
using namespace std;

int rotateInfo[9][12] = {
    {1, 4, 7, 13, 25, 37, 46, 49, 52, 45, 33, 21},
    {3, 6, 9, 15, 27, 39, 48, 51, 54, 43, 31, 19},
    {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
    {34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45},
    {1, 2, 3, 18, 30, 42, 54, 53, 52, 34, 22, 10},
    {7, 8, 9, 16, 28, 40, 48, 47, 46, 36, 24, 12},
    {2, 5, 8, 14, 26, 38, 47, 50, 53, 44, 32, 20},
    {4, 5, 6, 17, 29, 41, 51, 50, 49, 35, 23, 11},
    {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33}
};
int rotateFace[6][9] = {
    {10, 11, 12, 22, 23, 24, 34, 35, 36},
    {18, 17, 16, 30, 29, 28, 42, 41, 40},
    {1, 4, 7, 2, 5, 8, 3, 6, 9},
    {52, 49, 46, 53, 50, 47, 54, 51, 48},
    {21, 20, 19, 33, 32, 31, 45, 44, 43},
    {13, 14, 15, 25, 26, 27, 37, 38, 39}
};
int rotateOrder1[9] = {2, 5, 8, 1, 4, 7, 0, 3, 6};
int rotateOrder2[9] = {6, 3, 0, 7, 4, 1, 8, 5, 2};
int face[6][9] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9},
    {10, 11, 12, 22, 23, 24, 34, 35, 36},
    {13, 14, 15, 25, 26, 27, 37, 38, 39},
    {16, 17, 18, 28, 29, 30, 40, 41, 42},
    {19, 20, 21, 31, 32, 33, 43, 44, 45},
    {46, 47, 48, 49, 50, 51, 52, 53, 54}
};

map<string, int> rightStep, leftStep;

void adjustInfo() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 12; j++)
            rotateInfo[i][j]--;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 9; j++)
            face[i][j]--;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 9; j++)
            rotateFace[i][j]--;
}

int isCompleted(const string &state) {
    for (int i = 0; i < 6; i++) {
        for (int j = 1; j < 9; j++)
            if (state[face[i][j]] != state[face[i][0]])
                return 0;
    }
    return 1;
}

string reduceCube(string state) {
    int colorId[256] = {}, nextId = 0;
    for (int i = 0; i < (int)state.size(); i++) {
        unsigned char color = state[i];
        if (colorId[color] == 0)
            colorId[color] = ++nextId;
        state[i] = char('A' + colorId[color] - 1);
    }
    return state;
}

string rotateCube(string state, int kind, int direction) {
    if (direction == 0) {
        char first[3] = {state[rotateInfo[kind][0]], state[rotateInfo[kind][1]], state[rotateInfo[kind][2]]};
        for (int i = 0; i < 3; i++) {
            int a = i * 3, b = i * 3 + 1, c = i * 3 + 2;
            state[rotateInfo[kind][a]] = state[rotateInfo[kind][a + 3]];
            state[rotateInfo[kind][b]] = state[rotateInfo[kind][b + 3]];
            state[rotateInfo[kind][c]] = state[rotateInfo[kind][c + 3]];
        }
        state[rotateInfo[kind][9]] = first[0];
        state[rotateInfo[kind][10]] = first[1];
        state[rotateInfo[kind][11]] = first[2];
        if (kind < 6) {
            char temp[9];
            for (int i = 0; i < 9; i++)
                temp[i] = state[rotateFace[kind][i]];
            for (int i = 0; i < 9; i++)
                state[rotateFace[kind][i]] = temp[rotateOrder1[i]];
        }
    } else {
        char last[3] = {state[rotateInfo[kind][9]], state[rotateInfo[kind][10]], state[rotateInfo[kind][11]]};
        for (int i = 3; i > 0; i--) {
            int a = i * 3, b = i * 3 + 1, c = i * 3 + 2;
            state[rotateInfo[kind][a]] = state[rotateInfo[kind][a - 3]];
            state[rotateInfo[kind][b]] = state[rotateInfo[kind][b - 3]];
            state[rotateInfo[kind][c]] = state[rotateInfo[kind][c - 3]];
        }
        state[rotateInfo[kind][0]] = last[0];
        state[rotateInfo[kind][1]] = last[1];
        state[rotateInfo[kind][2]] = last[2];
        if (kind < 6) {
            char temp[9];
            for (int i = 0; i < 9; i++)
                temp[i] = state[rotateFace[kind][i]];
            for (int i = 0; i < 9; i++)
                state[rotateFace[kind][i]] = temp[rotateOrder2[i]];
        }
    }
    return state;
}

int getHeuristic(const string &state) {
    int result = 0;
    for (int i = 0; i < 6; i++) {
        bool used[256] = {};
        int count = 0;
        for (int j = 0; j < 9; j++) {
            unsigned char color = state[face[i][j]];
            if (!used[color]) {
                used[color] = true;
                count++;
            }
        }
        result = max(result, count - 1);
    }
    return result;
}

void buildRightTable(const string &start) {
    queue<string> states;
    string current, next;
    rightStep.clear();
    string initial = reduceCube(start);
    states.push(initial);
    rightStep[initial] = 0;
    while (!states.empty()) {
        current = states.front();
        states.pop();
        int step = rightStep[current];
        if (step >= 4)
            continue;
        for (int i = 0; i < 9; i++) {
            next = reduceCube(rotateCube(current, i, 0));
            if (rightStep.find(next) == rightStep.end()) {
                rightStep[next] = step + 1;
                states.push(next);
            }
            next = reduceCube(rotateCube(current, i, 1));
            if (rightStep.find(next) == rightStep.end()) {
                rightStep[next] = step + 1;
                states.push(next);
            }
        }
    }
}

int solve(const string &start) {
    if (isCompleted(start))
        return 0;
    queue<string> states;
    string current, next;
    leftStep.clear();
    string initial = reduceCube(start);
    states.push(initial);
    leftStep[initial] = 0;
    int answer = 0x3f3f3f3f;
    while (!states.empty()) {
        current = states.front();
        states.pop();
        int step = leftStep[current];
        if (rightStep.find(current) != rightStep.end())
            answer = min(answer, step + rightStep[current]);
        if (step >= 3 || step + getHeuristic(current) >= min(7, answer))
            continue;
        for (int i = 0; i < 9; i++) {
            next = reduceCube(rotateCube(current, i, 0));
            if (leftStep.find(next) == leftStep.end()) {
                leftStep[next] = step + 1;
                states.push(next);
            }
            next = reduceCube(rotateCube(current, i, 1));
            if (leftStep.find(next) == leftStep.end()) {
                leftStep[next] = step + 1;
                states.push(next);
            }
        }
    }
    return answer <= 7 ? answer : -1;
}

int main() {
    adjustInfo();
    buildRightTable("WWWWWWWWWRRRBBBOOOGGGRRRBBBOOOGGGRRRBBBOOOGGGYYYYYYYYY");
    int testCases, caseId = 0;
    string state;
    cin >> testCases;
    while (testCases--) {
        cin >> state;
        int answer = solve(state);
        cout << "Case " << ++caseId << ": ";
        if (answer == -1)
            cout << "Impossible\n";
        else
            cout << answer << '\n';
    }
    return 0;
}
