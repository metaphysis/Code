// Lattice Animals
// UVa ID: 1602
// Verdict: Accepted
// Submission Date: 2025-11-10
// UVa Run Time: 0.230s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

const int MAX_N = 10;
const int GRID_SIZE = 20; // 足够大的网格

struct Polyomino {
    char cells[GRID_SIZE][GRID_SIZE];
    int minX, maxX, minY, maxY;
    int size;
    
    Polyomino() {
        memset(cells, 0, sizeof(cells));
        minX = minY = GRID_SIZE;
        maxX = maxY = -1;
        size = 0;
    }
    
    void addCell(int x, int y) {
        cells[x + GRID_SIZE/2][y + GRID_SIZE/2] = 1;
        minX = min(minX, x);
        maxX = max(maxX, x);
        minY = min(minY, y);
        maxY = max(maxY, y);
        size++;
    }
    
    // 获取规范化表示
    Polyomino getCanonical() const {
        vector<Polyomino> variants;
        Polyomino current = *this;
        
        for (int flip = 0; flip < 2; flip++) {
            for (int rot = 0; rot < 4; rot++) {
                variants.push_back(current.normalize());
                current = current.rotate90();
            }
            current = this->flip();
        }
        
        // 返回最小的
        Polyomino best = variants[0];
        for (const auto& v : variants) {
            if (v < best) best = v;
        }
        return best;
    }
    
    Polyomino normalize() const {
        Polyomino result;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (cells[i][j]) {
                    result.addCell(i - GRID_SIZE/2 - minX, j - GRID_SIZE/2 - minY);
                }
            }
        }
        return result;
    }
    
    Polyomino rotate90() const {
        Polyomino result;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (cells[i][j]) {
                    int x = i - GRID_SIZE/2;
                    int y = j - GRID_SIZE/2;
                    result.addCell(y, -x);
                }
            }
        }
        return result;
    }
    
    Polyomino flip() const {
        Polyomino result;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (cells[i][j]) {
                    int x = i - GRID_SIZE/2;
                    int y = j - GRID_SIZE/2;
                    result.addCell(x, -y);
                }
            }
        }
        return result;
    }
    
    bool operator<(const Polyomino& other) const {
        if (size != other.size) return size < other.size;
        
        // 比较网格表示
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (cells[i][j] != other.cells[i][j]) {
                    return cells[i][j] < other.cells[i][j];
                }
            }
        }
        return false;
    }
    
    bool fitsInRectangle(int w, int h) const {
        int width = maxX - minX + 1;
        int height = maxY - minY + 1;
        return (width <= w && height <= h) || (width <= h && height <= w);
    }
    
    void getNeighbors(vector<pair<int, int>>& neighbors) const {
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        
        set<pair<int, int>> neighborSet;
        
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (cells[i][j]) {
                    int x = i - GRID_SIZE/2;
                    int y = j - GRID_SIZE/2;
                    
                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        int gridX = nx + GRID_SIZE/2;
                        int gridY = ny + GRID_SIZE/2;
                        
                        if (gridX >= 0 && gridX < GRID_SIZE && 
                            gridY >= 0 && gridY < GRID_SIZE && 
                            !cells[gridX][gridY]) {
                            neighborSet.insert({nx, ny});
                        }
                    }
                }
            }
        }
        
        neighbors.assign(neighborSet.begin(), neighborSet.end());
    }
    
    Polyomino addCellToCopy(int x, int y) const {
        Polyomino result = *this;
        result.addCell(x, y);
        return result;
    }
};

vector<set<Polyomino>> precomputeAllPolyominoes() {
    vector<set<Polyomino>> allPolyominoes(MAX_N + 1);
    
    // 基础情况
    Polyomino mono;
    mono.addCell(0, 0);
    allPolyominoes[1].insert(mono.getCanonical());
    
    for (int n = 2; n <= MAX_N; n++) {
        set<Polyomino> newSet;
        
        for (const auto& poly : allPolyominoes[n - 1]) {
            vector<pair<int, int>> neighbors;
            poly.getNeighbors(neighbors);
            
            for (const auto& neighbor : neighbors) {
                Polyomino newPoly = poly.addCellToCopy(neighbor.first, neighbor.second);
                newSet.insert(newPoly.getCanonical());
            }
        }
        
        allPolyominoes[n] = newSet;
    }
    
    return allPolyominoes;
}

int main() {
    auto allPolyominoes = precomputeAllPolyominoes();
    
    // 预计算所有答案
    int answer[MAX_N + 1][MAX_N + 1][MAX_N + 1] = {0};
    
    for (int n = 1; n <= MAX_N; n++) {
        for (int w = 1; w <= MAX_N; w++) {
            for (int h = 1; h <= MAX_N; h++) {
                int count = 0;
                for (const auto& poly : allPolyominoes[n]) {
                    if (poly.fitsInRectangle(w, h)) {
                        count++;
                    }
                }
                answer[n][w][h] = count;
            }
        }
    }
    
    int n, w, h;
    while (cin >> n >> w >> h) {
        cout << answer[n][w][h] << endl;
    }
    
    return 0;
}
