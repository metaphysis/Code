// Ars Longa
// UVa ID: 1050
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163183149

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int gaussRank(vector<vector<double>> a) {
    int m = (int)a.size(), n = (int)a[0].size();
    int rank = 0;
    for (int col = 0; col < n && rank < m; ++col) {
        int pivot = -1;
        for (int i = rank; i < m; ++i)
            if (fabs(a[i][col]) > EPS) { pivot = i; break; }
        if (pivot == -1) continue;
        swap(a[rank], a[pivot]);
        double div = a[rank][col];
        for (int j = col; j < n; ++j) a[rank][j] /= div;
        for (int i = 0; i < m; ++i)
            if (i != rank && fabs(a[i][col]) > EPS) {
                double factor = a[i][col];
                for (int j = col; j < n; ++j) a[i][j] -= factor * a[rank][j];
            }
        ++rank;
    }
    return rank;
}

int main() {
    int J, R;
    int sculptureCnt = 0;
    while (cin >> J >> R && (J != 0 || R != 0)) {
        ++sculptureCnt;
        vector<array<double, 3>> points(J);
        for (int i = 0; i < J; ++i) cin >> points[i][0] >> points[i][1] >> points[i][2];
        vector<pair<int, int>> rods(R);
        for (int i = 0; i < R; ++i) { cin >> rods[i].first >> rods[i].second; --rods[i].first; --rods[i].second; }
        vector<int> freeIndex(J, -1);
        vector<int> freeNodes;
        for (int i = 0; i < J; ++i)
            if (points[i][2] > EPS) {
                freeIndex[i] = (int)freeNodes.size();
                freeNodes.push_back(i);
            }
        int Nf = (int)freeNodes.size();
        int eqRows = 3 * Nf;
        vector<vector<double>> A(eqRows, vector<double>(R, 0.0));
        vector<double> b(eqRows, 0.0);
        for (int i = 0; i < Nf; ++i) b[3 * i + 2] = 1.0;
        for (int k = 0; k < R; ++k) {
            int u = rods[k].first, v = rods[k].second;
            double dx = points[v][0] - points[u][0];
            double dy = points[v][1] - points[u][1];
            double dz = points[v][2] - points[u][2];
            double len = sqrt(dx*dx + dy*dy + dz*dz);
            if (len < EPS) continue;
            double eX = dx / len, eY = dy / len, eZ = dz / len;
            if (freeIndex[u] != -1) {
                int idx = freeIndex[u];
                A[3*idx + 0][k] = eX;
                A[3*idx + 1][k] = eY;
                A[3*idx + 2][k] = eZ;
            }
            if (freeIndex[v] != -1) {
                int idx = freeIndex[v];
                A[3*idx + 0][k] = -eX;
                A[3*idx + 1][k] = -eY;
                A[3*idx + 2][k] = -eZ;
            }
        }
        vector<vector<double>> aug(eqRows, vector<double>(R + 1, 0.0));
        for (int i = 0; i < eqRows; ++i) {
            for (int j = 0; j < R; ++j) aug[i][j] = A[i][j];
            aug[i][R] = b[i];
        }
        int rankA = 0, rankAug = 0;
        if (eqRows > 0) {
            if (R > 0) {
                vector<vector<double>> A_copy = A;
                rankA = gaussRank(A_copy);
            } else rankA = 0;
            rankAug = gaussRank(aug);
        } else {
            rankA = 0;
            rankAug = 0;
        }
        bool isStatic = (rankA == rankAug);
        if (!isStatic) {
            cout << "Sculpture " << sculptureCnt << ": NON-STATIC\n";
            continue;
        }
        int colNum = 3 * Nf;
        vector<vector<double>> B(R, vector<double>(colNum, 0.0));
        for (int k = 0; k < R; ++k) {
            int u = rods[k].first, v = rods[k].second;
            double dx = points[v][0] - points[u][0];
            double dy = points[v][1] - points[u][1];
            double dz = points[v][2] - points[u][2];
            double len = sqrt(dx*dx + dy*dy + dz*dz);
            if (len < EPS) continue;
            double eX = dx / len, eY = dy / len, eZ = dz / len;
            if (freeIndex[u] != -1) {
                int idx = freeIndex[u];
                B[k][3*idx + 0] = eX;
                B[k][3*idx + 1] = eY;
                B[k][3*idx + 2] = eZ;
            }
            if (freeIndex[v] != -1) {
                int idx = freeIndex[v];
                B[k][3*idx + 0] -= eX;
                B[k][3*idx + 1] -= eY;
                B[k][3*idx + 2] -= eZ;
            }
        }
        int rankB = 0;
        if (colNum > 0) {
            if (R > 0) rankB = gaussRank(B);
            else rankB = 0;
        } else {
            rankB = 0;
        }
        bool isStable = (rankB == colNum);
        cout << "Sculpture " << sculptureCnt << ": " << (isStable ? "STABLE" : "UNSTABLE") << "\n";
    }
    return 0;
}
