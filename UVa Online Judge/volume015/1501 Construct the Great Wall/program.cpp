#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
int dp[10][1 << 8][1 << 8];

struct DisjointSet {
    int parent[20];
    void init(int n) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int findParent(int x) {
        return parent[x] == x ? x : parent[x] = findParent(parent[x]);
    }
    bool join(int x, int y) {
        x = findParent(x);
        y = findParent(y);
        if (x == y)
            return false;
        parent[x] = y;
        return true;
    }
};

vector<int> getPlace(int mustIn, int mustOut, int width) {
    vector<int> result;
    for (int mask = (1 << width) - 1; mask >= 0; mask--) {
        if ((mask & mustIn) != mustIn || (mask & mustOut) != 0)
            continue;
        result.push_back(mask);
    }
    return result;
}

bool checkIntersect(int upper, int lower, int width) {
    for (int col = 1; col < width; col++) {
        int topLeft = (upper >> (col - 1)) & 1, topRight = (upper >> col) & 1;
        int bottomLeft = (lower >> (col - 1)) & 1, bottomRight = (lower >> col) & 1;
        if (topLeft + topRight + bottomLeft + bottomRight != 2)
            continue;
        if (topLeft == bottomRight || topRight == bottomLeft)
            return true;
    }
    return false;
}

int solveCase(const vector<string> &grid) {
    int height = static_cast<int>(grid.size()), width = static_cast<int>(grid[0].size());
    int lastCityRow = 0, rowMustIn[10] = {}, rowMustOut[10] = {};
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (grid[row][col] == 'o') {
                lastCityRow = row;
                rowMustIn[row] |= 1 << col;
            }
            if (grid[row][col] == 'x')
                rowMustOut[row] |= 1 << col;
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = 0;
    for (int row = 0; row < height; row++) {
        vector<int> places = getPlace(rowMustIn[row], rowMustOut[row], width);
        for (int upper = 0; upper < (1 << width); upper++) {
            for (int component = 0; component < (1 << (2 * 4)); component++) {
                if (dp[row][upper][component] >= inf)
                    continue;
                int upperKind[4] = {}, upperLabel[8] = {}, previous = 0, upperCount = 0;
                for (int part = 0; part < 4; part++) {
                    upperKind[part] = (component >> (2 * part)) & 3;
                    while (previous < width && ((upper >> previous) & 1) == 0)
                        previous++;
                    if (previous < width)
                        upperCount++;
                    while (previous < width && ((upper >> previous) & 1) == 1)
                        upperLabel[previous] = upperKind[part], previous++;
                }
                for (int lower : places) {
                    if (checkIntersect(upper, lower, width))
                        continue;
                    DisjointSet dsu;
                    int lowerComponent[8], mappedComponent[12], upperUse[4] = {};
                    bool invalid = false;
                    dsu.init(4 + width);
                    for (int i = 0; i < 12; i++)
                        mappedComponent[i] = -1;
                    previous = -2;
                    for (int col = 0; col < width; col++) {
                        if ((lower >> col) & 1) {
                            if (previous == col - 1)
                                dsu.join(4 + previous, 4 + col);
                            previous = col;
                        }
                    }
                    for (int col = 0; col < width; col++) {
                        if (((lower >> col) & 1) && ((upper >> col) & 1)) {
                            int kind = upperLabel[col];
                            upperUse[kind]++;
                            dsu.join(kind, 4 + col);
                        }
                    }
                    for (int col = 0; col < width; col++) {
                        if ((upper >> col) & 1) {
                            int kind = upperLabel[col];
                            if (upperUse[kind] == 0)
                                invalid = true;
                        }
                    }
                    if (invalid)
                        continue;
                    int componentCount = 0, lowerCount = 0, lowerState = 0;
                    previous = -2;
                    for (int col = 0; col < width; col++) {
                        if ((lower >> col) & 1) {
                            if (previous != col - 1) {
                                int root = dsu.findParent(col + 4);
                                if (mappedComponent[root] == -1)
                                    mappedComponent[root] = componentCount++;
                                lowerState |= mappedComponent[root] << (2 * lowerCount);
                                lowerComponent[lowerCount++] = mappedComponent[root];
                            }
                            previous = col;
                        }
                    }
                    for (int col = 0; col < width;) {
                        while (col < width && ((lower >> col) & 1) == 0)
                            col++;
                        if (col >= width)
                            break;
                        int kindCount[4] = {};
                        while (col < width && ((lower >> col) & 1) == 1) {
                            if ((upper >> col) & 1) {
                                int kind = upperLabel[col];
                                kindCount[kind]++;
                                if (kindCount[kind] > 1)
                                    invalid = true;
                                while (col < width && ((lower >> col) & 1) && ((upper >> col) & 1))
                                    col++;
                            } else
                                col++;
                        }
                    }
                    if (invalid)
                        continue;
                    int added = 0;
                    for (int col = 0; col < width; col++) {
                        if (((lower >> col) & 1) == 0)
                            continue;
                        int cost = 4;
                        if (col > 0 && ((lower >> (col - 1)) & 1))
                            cost -= 2;
                        if ((upper >> col) & 1)
                            cost -= 2;
                        added += cost;
                    }
                    dp[row + 1][lower][lowerState] = min(dp[row + 1][lower][lowerState], dp[row][upper][component] + added);
                }
            }
        }
    }
    int answer = inf;
    for (int row = lastCityRow + 1; row <= height; row++)
        for (int mask = 0; mask < (1 << width); mask++)
            answer = min(answer, dp[row][mask][0]);
    return answer == inf ? -1 : answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int height, width;
        cin >> height >> width;
        vector<string> grid(height);
        for (string &row : grid)
            cin >> row;
        cout << "Case #" << testCase << ": " << solveCase(grid) << '\n';
    }
    return 0;
}
