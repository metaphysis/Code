// Puncher
// UVa ID: 770
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

pair<int, int> getNextPoint(int height, int width, int rotation, int reflection, int row, int column) {
    int nextRow;
    int nextColumn;
    int targetWidth = width;
    if (rotation == 0) {
        nextRow = row;
        nextColumn = column;
    } else if (rotation == 1) {
        nextRow = column;
        nextColumn = height - 1 - row;
        targetWidth = height;
    } else if (rotation == 2) {
        nextRow = height - 1 - row;
        nextColumn = width - 1 - column;
    } else {
        nextRow = width - 1 - column;
        nextColumn = row;
        targetWidth = height;
    }
    if (reflection) nextColumn = targetWidth - 1 - nextColumn;
    return {nextRow, nextColumn};
}

long long countFixedPatterns(int height, int width, int rotation, int reflection) {
    long long result = 0;
    for (int removeMask = 0; removeMask < 16; removeMask++) {
        vector<bool> allowed(height * width, true);
        for (int row = 0; row < height; row++)
            for (int column = 0; column < width; column++) {
                if ((removeMask & 1) && row == 0) allowed[row * width + column] = false;
                if ((removeMask & 2) && row == height - 1) allowed[row * width + column] = false;
                if ((removeMask & 4) && column == 0) allowed[row * width + column] = false;
                if ((removeMask & 8) && column == width - 1) allowed[row * width + column] = false;
            }
        vector<bool> visited(height * width, false);
        int orbitCount = 0;
        bool valid;
        for (int row = 0; row < height; row++)
            for (int column = 0; column < width; column++) {
                int startIndex = row * width + column;
                if (visited[startIndex]) continue;
                valid = true;
                int currentRow = row;
                int currentColumn = column;
                do {
                    int currentIndex = currentRow * width + currentColumn;
                    visited[currentIndex] = true;
                    if (!allowed[currentIndex]) valid = false;
                    pair<int, int> nextPoint = getNextPoint(height, width, rotation, reflection, currentRow, currentColumn);
                    currentRow = nextPoint.first;
                    currentColumn = nextPoint.second;
                } while (currentRow != row || currentColumn != column);
                if (valid) orbitCount++;
            }
        long long fixedCount = 1LL << orbitCount;
        if (__builtin_popcount(removeMask) % 2 == 0) result += fixedCount;
        else result -= fixedCount;
    }
    return result;
}

long long countDifferentPunchers(int maxHeight, int maxWidth) {
    long long answer = 0;
    for (int height = 1; height <= maxHeight; height++)
        for (int width = 1; width <= maxWidth; width++) {
            if (height > width && width <= maxHeight && height <= maxWidth) continue;
            vector<pair<int, int>> transformations;
            if (height == width) {
                for (int rotation = 0; rotation < 4; rotation++)
                    for (int reflection = 0; reflection < 2; reflection++)
                        transformations.push_back({rotation, reflection});
            } else {
                transformations.push_back({0, 0});
                transformations.push_back({0, 1});
                transformations.push_back({2, 0});
                transformations.push_back({2, 1});
            }
            long long fixedSum = 0;
            for (pair<int, int> transformation : transformations)
                fixedSum += countFixedPatterns(height, width, transformation.first, transformation.second);
            answer += fixedSum / transformations.size();
        }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int maxHeight;
    int maxWidth;
    while (cin >> maxHeight >> maxWidth)
        cout << countDifferentPunchers(maxHeight, maxWidth) << '\n';
    return 0;
}
