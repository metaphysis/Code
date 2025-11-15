// Colored Cubes
// UVa ID: 1352
// Verdict: Accepted
// Submission Date: 2025-11-06
// UVa Run Time: 0.850s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <climits>
#include <functional>

using namespace std;

// 预定义的 24 种旋转映射
// 面的物理位置：0:前, 1:右, 2:上, 3:下, 4:左, 5:后
const int ROTATIONS[24][6] = {
    // 以 0 面（前）为基准的 4 种旋转
    {0, 1, 2, 3, 4, 5}, {0, 2, 4, 1, 3, 5}, {0, 4, 3, 2, 1, 5}, {0, 3, 1, 4, 2, 5},
    // 以 1 面（右）为前
    {1, 5, 2, 3, 0, 4}, {1, 2, 0, 5, 3, 4}, {1, 0, 3, 2, 5, 4}, {1, 3, 5, 0, 2, 4},
    // 以 2 面（上）为前  
    {2, 1, 5, 0, 4, 3}, {2, 5, 4, 1, 0, 3}, {2, 4, 0, 5, 1, 3}, {2, 0, 1, 4, 5, 3},
    // 以 3 面（下）为前
    {3, 1, 0, 5, 4, 2}, {3, 0, 4, 1, 5, 2}, {3, 4, 5, 0, 1, 2}, {3, 5, 1, 4, 0, 2},
    // 以 4 面（左）为前
    {4, 0, 2, 3, 5, 1}, {4, 2, 5, 0, 3, 1}, {4, 5, 3, 2, 0, 1}, {4, 3, 0, 5, 2, 1},
    // 以 5 面（后）为前
    {5, 4, 2, 3, 1, 0}, {5, 2, 1, 4, 3, 0}, {5, 1, 3, 2, 4, 0}, {5, 3, 4, 1, 2, 0}
};

// 应用旋转到立方体
void applyRotation(const vector<string>& original, vector<string>& result, int rotationIndex) {
    for (int i = 0; i < 6; i++) {
        result[i] = original[ROTATIONS[rotationIndex][i]];
    }
}

int main() {
    int cubeCount;
    while (cin >> cubeCount && cubeCount != 0) {
        // 读取并重新映射输入数据
        vector<vector<string>> cubes(cubeCount, vector<string>(6));
        for (int i = 0; i < cubeCount; i++) {
            vector<string> inputColors(6);
            for (int j = 0; j < 6; j++) {
                cin >> inputColors[j];
            }
            // 重新映射到内部表示：0:前, 1:右, 2:上, 3:下, 4:左, 5:后
            cubes[i][0] = inputColors[0]; // 前
            cubes[i][1] = inputColors[1]; // 右  
            cubes[i][2] = inputColors[2]; // 上
            cubes[i][3] = inputColors[3]; // 下
            cubes[i][4] = inputColors[4]; // 左
            cubes[i][5] = inputColors[5]; // 后
        }

        // 单个立方体不需要重新涂色
        if (cubeCount == 1) {
            cout << 0 << endl;
            continue;
        }

        int minRepaint = INT_MAX;
        vector<int> rotationIndices(cubeCount, 0);
        rotationIndices[0] = 0; // 固定第一个立方体的旋转

        // 深度优先搜索枚举所有旋转组合
        function<void(int)> depthFirstSearch = [&](int currentCube) {
            if (currentCube == cubeCount) {
                // 计算当前旋转组合下的重新涂色次数
                int totalRepaint = 0;
                for (int face = 0; face < 6; face++) {
                    map<string, int> colorFrequency;
                    int maxFrequency = 0;
                    for (int cubeIdx = 0; cubeIdx < cubeCount; cubeIdx++) {
                        vector<string> rotatedCube(6);
                        applyRotation(cubes[cubeIdx], rotatedCube, rotationIndices[cubeIdx]);
                        string color = rotatedCube[face];
                        colorFrequency[color]++;
                        maxFrequency = max(maxFrequency, colorFrequency[color]);
                    }
                    totalRepaint += cubeCount - maxFrequency;
                }
                minRepaint = min(minRepaint, totalRepaint);
                return;
            }

            // 枚举当前立方体的所有可能旋转
            for (int rotation = 0; rotation < 24; rotation++) {
                rotationIndices[currentCube] = rotation;
                depthFirstSearch(currentCube + 1);
            }
        };

        depthFirstSearch(1); // 从第二个立方体开始枚举
        cout << minRepaint << endl;
    }

    return 0;
}
