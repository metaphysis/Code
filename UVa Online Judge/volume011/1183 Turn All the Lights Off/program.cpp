#include <bits/stdc++.h>
using namespace std;

const int maxCells = 1600;
const int maxColumns = maxCells + 1;

bool canTurnOff(int size, const vector<pair<int, int>>& onLights) {
    int cells = size * size, rank = 0;
    vector<bitset<maxColumns>> matrix(cells);
    for (int pos = 0; pos < cells; pos++) {
        int row = pos / size, column = pos % size;
        matrix[pos].set(pos);
        matrix[pos].set(((row - 1 + size) % size) * size + column);
        matrix[pos].set(((row + 1) % size) * size + column);
        matrix[pos].set(row * size + (column - 1 + size) % size);
        matrix[pos].set(row * size + (column + 1) % size);
    }
    for (const auto& light : onLights) matrix[light.first * size + light.second].set(cells);
    for (int column = 0; column < cells && rank < cells; column++) {
        int pivot = rank;
        while (pivot < cells && !matrix[pivot][column]) pivot++;
        if (pivot == cells) continue;
        swap(matrix[rank], matrix[pivot]);
        for (int row = rank + 1; row < cells; row++) if (matrix[row][column]) matrix[row] ^= matrix[rank];
        rank++;
    }
    for (int row = rank; row < cells; row++) if (matrix[row][cells]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int size, onCount;
    while (cin >> size) {
        cin >> onCount;
        vector<pair<int, int>> onLights(onCount);
        for (int i = 0; i < onCount; i++) cin >> onLights[i].first >> onLights[i].second;
        cout << (canTurnOff(size, onLights) ? "Yes" : "No") << '\n';
    }
    return 0;
}
