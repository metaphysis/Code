#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    char label;
};

vector<vector<Edge>> graphData, inGraph;
vector<int> outDegree;
vector<double> visitProb;
int cityCount;

vector<double> solveTarget(int target) {
    vector<vector<int>> stateId(cityCount, vector<int>(cityCount, -1));
    int totalState = 0;
    for (int u = 0; u < cityCount; u++)
        if (u != target)
            for (int v = 0; v < cityCount; v++)
                if (v != target)
                    stateId[u][v] = totalState++;
    vector<vector<double>> matrix(totalState, vector<double>(totalState + 1, 0.0));
    for (int u = 0; u < cityCount; u++) {
        if (u == target)
            continue;
        for (int v = 0; v < cityCount; v++) {
            if (v == target)
                continue;
            int row = stateId[u][v];
            if (u == v)
                matrix[row][totalState] += 1.0;
            if (outDegree[u] > 0)
                for (const Edge &firstEdge : graphData[u])
                    if (firstEdge.to == v)
                        matrix[row][totalState] += visitProb[u];
            for (const Edge &firstEdge : graphData[u]) {
                int x = firstEdge.to;
                if (x == target)
                    continue;
                for (const Edge &lastEdge : inGraph[v]) {
                    int y = lastEdge.to;
                    if (y == target || firstEdge.label != lastEdge.label)
                        continue;
                    int column = stateId[x][y];
                    if (column >= 0)
                        matrix[row][column] -= visitProb[u] * visitProb[y];
                }
            }
        }
    }
    int row = 0;
    const double eps = 1e-12;
    for (int column = 0; column < totalState && row < totalState; column++) {
        int pivot = row;
        for (int i = row + 1; i < totalState; i++)
            if (fabs(matrix[i][column]) > fabs(matrix[pivot][column]))
                pivot = i;
        if (fabs(matrix[pivot][column]) < eps)
            continue;
        swap(matrix[pivot], matrix[row]);
        double divisor = matrix[row][column];
        for (int j = column; j <= totalState; j++)
            matrix[row][j] /= divisor;
        for (int i = 0; i < totalState; i++) {
            if (i == row)
                continue;
            double factor = matrix[i][column];
            if (fabs(factor) < eps)
                continue;
            for (int j = column; j <= totalState; j++)
                matrix[i][j] -= factor * matrix[row][j];
        }
        row++;
    }
    vector<double> result(totalState, 0.0);
    for (int i = 0; i < totalState; i++) {
        int pivotColumn = -1;
        for (int j = 0; j < totalState; j++) {
            if (fabs(matrix[i][j]) > eps) {
                pivotColumn = j;
                break;
            }
        }
        if (pivotColumn >= 0)
            result[pivotColumn] = matrix[i][totalState];
    }
    vector<double> answer(cityCount, 0.0);
    for (int start = 0; start < cityCount; start++) {
        if (start == target || outDegree[start] == 0)
            continue;
        for (const Edge &firstEdge : graphData[start]) {
            if (firstEdge.to == target)
                answer[start] += visitProb[start];
            else {
                int x = firstEdge.to;
                for (const Edge &lastEdge : inGraph[target]) {
                    int y = lastEdge.to;
                    if (y == target || firstEdge.label != lastEdge.label)
                        continue;
                    int state = stateId[x][y];
                    if (state >= 0)
                        answer[start] += visitProb[start] * visitProb[y] * result[state];
                }
            }
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseNumber = 1; caseNumber <= testCount; caseNumber++) {
        int roadCount;
        cin >> cityCount >> roadCount;
        graphData.assign(cityCount, vector<Edge>());
        inGraph.assign(cityCount, vector<Edge>());
        outDegree.assign(cityCount, 0);
        for (int i = 0; i < roadCount; i++) {
            int from, to;
            char label;
            cin >> from >> to >> label;
            graphData[from].push_back({to, label});
            inGraph[to].push_back({from, label});
            outDegree[from]++;
        }
        visitProb.assign(cityCount, 0.0);
        for (int i = 0; i < cityCount; i++)
            if (outDegree[i] > 0)
                visitProb[i] = 1.0 / outDegree[i];
        int queryCount;
        cin >> queryCount;
        vector<pair<int, int>> queries(queryCount);
        vector<vector<double>> cachedAnswer(cityCount);
        vector<bool> calculated(cityCount, false);
        cout << "Case " << caseNumber << ":\n";
        for (int i = 0; i < queryCount; i++) {
            int start, target;
            cin >> start >> target;
            queries[i] = {start, target};
            if (!calculated[target]) {
                cachedAnswer[target] = solveTarget(target);
                calculated[target] = true;
            }
            cout << fixed << setprecision(6) << cachedAnswer[target][start] + 0.0 << '\n';
        }
    }
    return 0;
}
