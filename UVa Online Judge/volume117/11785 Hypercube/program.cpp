#include <bits/stdc++.h>
using namespace std;

bool isPowerOfTwo(int number) {
    return number > 0 && (number & (number - 1)) == 0;
}

bool hasExactlyOneBit(int number) {
    return number > 0 && (number & (number - 1)) == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int vertexCount, edgeCount;
    while (cin >> vertexCount >> edgeCount) {
        if (vertexCount == 0) break;
        bool isHypercube = true;
        int dimension = 0;
        if (!isPowerOfTwo(vertexCount)) isHypercube = false;
        else {
            int temp = vertexCount;
            while (temp > 1) {
                temp >>= 1;
                ++dimension;
            }
        }
        vector<vector<bool>> connected(vertexCount, vector<bool>(vertexCount, false));
        vector<int> degree(vertexCount, 0);
        for (int i = 0; i < edgeCount; ++i) {
            long long firstVertex, secondVertex;
            cin >> firstVertex >> secondVertex;
            if (firstVertex < 0 || firstVertex >= vertexCount || secondVertex < 0 || secondVertex >= vertexCount) {
                isHypercube = false;
                continue;
            }
            int u = static_cast<int>(firstVertex);
            int v = static_cast<int>(secondVertex);
            if (u == v) {
                isHypercube = false;
                continue;
            }
            if (connected[u][v]) {
                isHypercube = false;
                continue;
            }
            if (!hasExactlyOneBit(u ^ v)) isHypercube = false;
            connected[u][v] = true;
            connected[v][u] = true;
            ++degree[u];
            ++degree[v];
        }
        if (edgeCount != vertexCount * dimension / 2) isHypercube = false;
        for (int i = 0; i < vertexCount; ++i)
            if (degree[i] != dimension) isHypercube = false;
        cout << (isHypercube ? "YES" : "NO") << '\n';
    }
    return 0;
}
