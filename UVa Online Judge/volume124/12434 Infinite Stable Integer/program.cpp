#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-12L;
const long double inf = 1e100L;

struct LinearProgram {
    int constraintCount, variableCount;
    vector<int> basic, nonBasic;
    vector<vector<long double>> table;
    LinearProgram(const vector<vector<long double>>& mat, const vector<long double>& rhs, const vector<long double>& objective) {
        constraintCount = rhs.size();
        variableCount = objective.size();
        basic.resize(constraintCount);
        nonBasic.resize(variableCount + 1);
        table.assign(constraintCount + 2, vector<long double>(variableCount + 2));
        for (int i = 0; i < constraintCount; i++) {
            for (int j = 0; j < variableCount; j++) table[i][j] = mat[i][j];
            basic[i] = variableCount + i;
            table[i][variableCount] = -1;
            table[i][variableCount + 1] = rhs[i];
        }
        for (int j = 0; j < variableCount; j++) {
            nonBasic[j] = j;
            table[constraintCount][j] = -objective[j];
        }
        nonBasic[variableCount] = -1;
        table[constraintCount + 1][variableCount] = 1;
    }

    void pivot(int row, int column) {
        long double inverse = 1.0L / table[row][column];
        for (int i = 0; i < constraintCount + 2; i++) {
            if (i == row) continue;
            for (int j = 0; j < variableCount + 2; j++) {
                if (j == column) continue;
                table[i][j] -= table[row][j] * table[i][column] * inverse;
            }
        }
        for (int j = 0; j < variableCount + 2; j++)
            if (j != column) table[row][j] *= inverse;
        for (int i = 0; i < constraintCount + 2; i++)
            if (i != row) table[i][column] *= -inverse;
        table[row][column] = inverse;
        swap(basic[row], nonBasic[column]);
    }

    bool runSimplex(int phase) {
        int objectiveRow = phase == 1 ? constraintCount + 1 : constraintCount;
        while (true) {
            int column = -1;
            for (int j = 0; j <= variableCount; j++) {
                if (phase == 2 && nonBasic[j] == -1) continue;
                if (column == -1 || table[objectiveRow][j] < table[objectiveRow][column] - eps || (abs(table[objectiveRow][j] - table[objectiveRow][column]) <= eps && nonBasic[j] < nonBasic[column])) column = j;
            }
            if (table[objectiveRow][column] >= -eps) return true;
            int row = -1;
            for (int i = 0; i < constraintCount; i++) {
                if (table[i][column] <= eps) continue;
                if (row == -1) {
                    row = i;
                } else {
                    long double currentRatio = table[i][variableCount + 1] / table[i][column];
                    long double bestRatio = table[row][variableCount + 1] / table[row][column];
                    if (currentRatio < bestRatio - eps || (abs(currentRatio - bestRatio) <= eps && basic[i] < basic[row])) row = i;
                }
            }
            if (row == -1) return false;
            pivot(row, column);
        }
    }

    int solve(long double& answer) {
        int row = 0;
        for (int i = 1; i < constraintCount; i++)
            if (table[i][variableCount + 1] < table[row][variableCount + 1]) row = i;
        if (table[row][variableCount + 1] < -eps) {
            pivot(row, variableCount);
            if (!runSimplex(1) || table[constraintCount + 1][variableCount + 1] < -eps) return -1;
            if (abs(table[constraintCount + 1][variableCount + 1]) > eps) return -1;
            for (int i = 0; i < constraintCount; i++) {
                if (basic[i] != -1) continue;
                int column = -1;
                for (int j = 0; j <= variableCount; j++)
                    if (column == -1 || table[i][j] < table[i][column] - eps || (abs(table[i][j] - table[i][column]) <= eps && nonBasic[j] < nonBasic[column])) column = j;
                if (abs(table[i][column]) > eps) pivot(i, column);
            }
        }
        if (!runSimplex(2)) return 1;
        answer = table[constraintCount][variableCount + 1];
        return 0;
    }
};

struct Edge {
    int from, to, digit;
};

int modValue, leftValue, rightValue, timerValue, componentCount;
vector<vector<pair<int, int>>> graph;
vector<int> discoverTime, lowLink, componentId, stackNodes;
vector<bool> inStack, allowedState;

void tarjan(int node) {
    discoverTime[node] = lowLink[node] = ++timerValue;
    stackNodes.push_back(node);
    inStack[node] = true;
    for (auto transition : graph[node]) {
        int nextNode = transition.first;
        if (!discoverTime[nextNode]) {
            tarjan(nextNode);
            lowLink[node] = min(lowLink[node], lowLink[nextNode]);
        } else if (inStack[nextNode]) {
            lowLink[node] = min(lowLink[node], discoverTime[nextNode]);
        }
    }
    if (lowLink[node] == discoverTime[node]) {
        while (true) {
            int currentNode = stackNodes.back();
            stackNodes.pop_back();
            inStack[currentNode] = false;
            componentId[currentNode] = componentCount;
            if (currentNode == node) break;
        }
        componentCount++;
    }
}

long double solveComponent(const vector<int>& nodes, const vector<int>& lowBound, const vector<int>& highBound) {
    vector<int> localId(modValue, -1);
    for (int i = 0; i < (int)nodes.size(); i++) localId[nodes[i]] = i;
    vector<Edge> edges;
    for (int node : nodes) {
        for (auto transition : graph[node]) {
            int nextNode = transition.first, digit = transition.second;
            if (localId[nextNode] != -1) edges.push_back({node, nextNode, digit});
        }
    }
    int edgeCount = edges.size(), nodeCount = nodes.size();
    if (edgeCount == 0) return -inf;
    vector<vector<long double>> matrix;
    vector<long double> rhs;
    auto addConstraint = [&](const vector<long double>& row, long double value) {
        matrix.push_back(row);
        rhs.push_back(value);
    };
    for (int i = 0; i + 1 < nodeCount; i++) {
        vector<long double> row(edgeCount);
        int node = nodes[i];
        for (int j = 0; j < edgeCount; j++) {
            if (edges[j].from == node) row[j] += 1;
            if (edges[j].to == node) row[j] -= 1;
        }
        addConstraint(row, 0);
        for (int j = 0; j < edgeCount; j++) row[j] = -row[j];
        addConstraint(row, 0);
    }
    vector<long double> totalRow(edgeCount, 1);
    addConstraint(totalRow, 1);
    for (int j = 0; j < edgeCount; j++) totalRow[j] = -1;
    addConstraint(totalRow, -1);
    for (int digit = 0; digit <= 9; digit++) {
        vector<long double> row(edgeCount);
        for (int j = 0; j < edgeCount; j++)
            if (edges[j].digit == digit) row[j] = 1;
        addConstraint(row, (long double)highBound[digit] / 100.0L);
        for (int j = 0; j < edgeCount; j++) row[j] = -row[j];
        addConstraint(row, -(long double)lowBound[digit] / 100.0L);
    }
    vector<long double> objective(edgeCount);
    for (int i = 0; i < edgeCount; i++) objective[i] = edges[i].digit;
    LinearProgram linearProgram(matrix, rhs, objective);
    long double answer = 0;
    if (linearProgram.solve(answer) != 0) return -inf;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 0;
    while (cin >> modValue >> leftValue >> rightValue) {
        vector<int> lowBound(10), highBound(10);
        for (int i = 0; i < 10; i++) cin >> lowBound[i];
        for (int i = 0; i < 10; i++) cin >> highBound[i];
        graph.assign(modValue, vector<pair<int, int>>());
        allowedState.assign(modValue, false);
        for (int state = leftValue; state <= rightValue; state++) allowedState[state] = true;
        for (int state = leftValue; state <= rightValue; state++) {
            for (int digit = 0; digit <= 9; digit++) {
                int nextState = (state * 10 + digit) % modValue;
                if (allowedState[nextState]) graph[state].push_back({nextState, digit});
            }
        }
        vector<bool> reachable(modValue, false);
        queue<int> stateQueue;
        for (int digit = 0; digit <= 9; digit++) {
            int state = digit % modValue;
            if (allowedState[state] && !reachable[state]) {
                reachable[state] = true;
                stateQueue.push(state);
            }
        }
        while (!stateQueue.empty()) {
            int state = stateQueue.front();
            stateQueue.pop();
            for (auto transition : graph[state]) {
                int nextState = transition.first;
                if (!reachable[nextState]) {
                    reachable[nextState] = true;
                    stateQueue.push(nextState);
                }
            }
        }
        discoverTime.assign(modValue, 0);
        lowLink.assign(modValue, 0);
        componentId.assign(modValue, -1);
        inStack.assign(modValue, false);
        stackNodes.clear();
        timerValue = componentCount = 0;
        for (int state = leftValue; state <= rightValue; state++)
            if (!discoverTime[state]) tarjan(state);
        vector<vector<int>> components(componentCount);
        for (int state = leftValue; state <= rightValue; state++) components[componentId[state]].push_back(state);
        long double bestAnswer = -inf;
        for (const vector<int>& nodes : components) {
            bool canReach = false;
            for (int node : nodes)
                if (reachable[node]) canReach = true;
            if (!canReach) continue;
            long double currentAnswer = solveComponent(nodes, lowBound, highBound);
            bestAnswer = max(bestAnswer, currentAnswer);
        }
        cout << "Case " << ++caseNumber << ": ";
        if (bestAnswer < -inf / 2) {
            cout << "NO SOLUTION\n";
        } else {
            bestAnswer = max(0.0L, min(9.0L, bestAnswer));
            cout << fixed << setprecision(8) << bestAnswer << '\n';
        }
    }
    return 0;
}
