#include <bits/stdc++.h>
using namespace std;

const int maxN = 205;
const int maxT = 505;
const int maxP = 805;
const int maxE = 205;
const int mod = 13;
const int inf = 1000000000;

int n, alice, rabbit, tripCount, edgeCount;
int edgeId[maxN][maxN], edgeTime[maxE];
int tripDuration[maxT], tripSize[maxT], tripPath[maxT][maxP];
int matrixData[maxT][maxE + 1], pivotRow[maxE];
int road[maxN][maxN], distanceData[maxN];
bool visited[maxN];

int modPow(int base, int exponent) {
    int result = 1;
    while (exponent > 0) {
        if (exponent & 1) result = result * base % mod;
        base = base * base % mod;
        exponent >>= 1;
    }
    return result;
}

void readTrips() {
    int i, j, previous, current;
    edgeCount = 0;
    memset(edgeId, -1, sizeof(edgeId));
    for (i = 0; i < tripCount; i++) {
        cin >> tripDuration[i] >> tripSize[i];
        for (j = 0; j < tripSize[i]; j++)
            cin >> tripPath[i][j];
        for (j = 1; j < tripSize[i]; j++) {
            previous = tripPath[i][j - 1];
            current = tripPath[i][j];
            if (previous == current) continue;
            if (edgeId[previous][current] == -1) {
                edgeId[previous][current] = edgeCount;
                edgeId[current][previous] = edgeCount;
                edgeCount++;
            }
        }
    }
}

void buildEquations() {
    int i, j, previous, current, id;
    memset(matrixData, 0, sizeof(matrixData));
    for (i = 0; i < maxE; i++)
        pivotRow[i] = -1;
    for (i = 0; i < tripCount; i++) {
        for (j = 1; j < tripSize[i]; j++) {
            previous = tripPath[i][j - 1];
            current = tripPath[i][j];
            if (previous == current) continue;
            id = edgeId[previous][current];
            matrixData[i][id] = (matrixData[i][id] + 1) % mod;
        }
        matrixData[i][edgeCount] = tripDuration[i] % mod;
    }
}

void gaussianElimination() {
    int i, j, k, row, pivot, inverse, factor, value;
    row = 0;
    for (j = 0; j < edgeCount; j++) {
        pivot = -1;
        for (i = row; i < tripCount; i++)
            if (matrixData[i][j] != 0) {
                pivot = i;
                break;
            }
        if (pivot == -1) continue;
        swap(matrixData[pivot], matrixData[row]);
        inverse = modPow(matrixData[row][j], mod - 2);
        for (k = j; k <= edgeCount; k++)
            matrixData[row][k] = matrixData[row][k] * inverse % mod;
        for (i = 0; i < tripCount; i++) {
            if (i == row) continue;
            factor = matrixData[i][j];
            if (factor == 0) continue;
            for (k = j; k <= edgeCount; k++) {
                value = matrixData[i][k] - factor * matrixData[row][k] % mod;
                if (value < 0) value += mod;
                matrixData[i][k] = value;
            }
        }
        pivotRow[j] = row;
        row++;
    }
    for (j = 0; j < edgeCount; j++)
        edgeTime[j] = 1;
    for (j = 0; j < edgeCount; j++) {
        if (pivotRow[j] == -1) continue;
        i = pivotRow[j];
        edgeTime[j] = matrixData[i][edgeCount];
        for (k = 0; k < edgeCount; k++) {
            if (k == j || pivotRow[k] != -1) continue;
            edgeTime[j] -= matrixData[i][k] * edgeTime[k] % mod;
            edgeTime[j] %= mod;
        }
        if (edgeTime[j] < 0) edgeTime[j] += mod;
        if (edgeTime[j] == 0) edgeTime[j] = 13;
    }
}

void buildGraph() {
    int i, j, id;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            road[i][j] = inf;
    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++) {
            id = edgeId[i][j];
            if (id == -1) continue;
            road[i][j] = edgeTime[id];
            road[j][i] = edgeTime[id];
        }
}

int dijkstra() {
    int i, j, current;
    for (i = 1; i <= n; i++) {
        distanceData[i] = inf;
        visited[i] = false;
    }
    distanceData[alice] = 0;
    for (i = 1; i <= n; i++) {
        current = -1;
        for (j = 1; j <= n; j++)
            if (!visited[j] && (current == -1 || distanceData[j] < distanceData[current]))
                current = j;
        if (current == -1 || distanceData[current] == inf) break;
        visited[current] = true;
        for (j = 1; j <= n; j++)
            if (road[current][j] != inf && distanceData[j] > distanceData[current] + road[current][j])
                distanceData[j] = distanceData[current] + road[current][j];
    }
    return distanceData[rabbit];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> alice >> rabbit >> tripCount) {
        readTrips();
        buildEquations();
        gaussianElimination();
        buildGraph();
        cout << dijkstra() << '\n';
    }
    return 0;
}
