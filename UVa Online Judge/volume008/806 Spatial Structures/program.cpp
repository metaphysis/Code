// Spatial Structures
// UVa ID: 806
// Verdict: Accepted
// Submission Date: 2025-10-23
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 64;

int n;
int image[MAXN][MAXN];    // 存储图像，0 表示白，1 表示黑
vector<int> black_list;   // 存储黑节点的路径编号（十进制）

// 检查从 (x, y) 开始，大小为 size 的区域是否全是 color
bool isUniform(int x, int y, int size, int color) {
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            if (image[i][j] != color) {
                return false;
            }
        }
    }
    return true;
}

// 递归构建四叉树，并记录黑块的路径编号
// (x, y) 是当前子块的左上角坐标
// size 是当前子块的边长
// path 是当前路径的十进制值
// depth 是递归深度（用于计算五进制位权）
void buildQuadtree(int x, int y, int size, int path, int depth) {
    // 如果当前块全黑
    if (isUniform(x, y, size, 1)) {
        black_list.push_back(path);
        return;
    }
    // 如果当前块全白，直接返回
    if (isUniform(x, y, size, 0)) {
        return;
    }
    // 非均匀块，继续划分
    int half = size / 2;
    // 顺序：NW(1), NE(2), SW(3), SE(4)
    // 注意：路径值计算是 path + dir * (5^depth)
    // 因为低位对应靠近根的分支，depth 从 0 开始
    buildQuadtree(x, y, half, path + 1 * pow(5, depth), depth + 1); // NW
    buildQuadtree(x, y + half, half, path + 2 * pow(5, depth), depth + 1); // NE
    buildQuadtree(x + half, y, half, path + 3 * pow(5, depth), depth + 1); // SW
    buildQuadtree(x + half, y + half, half, path + 4 * pow(5, depth), depth + 1); // SE
}

// 根据路径编号填充图像中的对应块为黑色
// (x, y) 是当前子块的左上角坐标
// size 是当前子块的边长
// path 是路径编号（十进制）
void fillImage(int x, int y, int size, int path) {
    // 如果路径编号为 0，表示整个块都是黑色
    if (path == 0) {
        for (int i = x; i < x + size; i++) {
            for (int j = y; j < y + size; j++) {
                image[i][j] = 1;
            }
        }
        return;
    }
    // 根据五进制数字逐步缩小范围
    while (path > 0) {
        int dir = path % 5;  // 取最低位，即靠近根的分支
        path /= 5;
        int half = size / 2;
        switch (dir) {
            case 1: // NW
                size = half;
                break;
            case 2: // NE
                y += half;
                size = half;
                break;
            case 3: // SW
                x += half;
                size = half;
                break;
            case 4: // SE
                x += half;
                y += half;
                size = half;
                break;
        }
    }
    // 填充最终确定的子块
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            image[i][j] = 1;
        }
    }
}

int main() {
    int caseNum = 0;
    while (cin >> n && n != 0) {
        if (caseNum) cout << '\n';
        caseNum++;
        black_list.clear();
        memset(image, 0, sizeof(image));

        if (n > 0) {
            // 读入 n x n 的 0/1 矩阵
            for (int i = 0; i < n; i++) {
                string line;
                cin >> line;
                for (int j = 0; j < n; j++) {
                    image[i][j] = line[j] - '0';
                }
            }
            // 构建四叉树，得到黑节点路径列表
            buildQuadtree(0, 0, n, 0, 0);
            // 排序路径编号（十进制）
            sort(black_list.begin(), black_list.end());

            // 输出结果
            cout << "Image " << caseNum << "\n";
            for (size_t i = 0; i < black_list.size(); i++) {
                // 每 12 个换一行
                if (i > 0 && i % 12 == 0) cout << "\n";
                if (i % 12 != 0) cout << " ";
                cout << black_list[i];
            }
            if (!black_list.empty()) cout << "\n";
            cout << "Total number of black nodes = " << black_list.size() << "\n";
        } else {
            // n < 0，读入路径编号
            n = -n;  // 取绝对值
            int path;
            while (cin >> path && path != -1) {
                if (path == 0) {
                    // 全黑图像
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            image[i][j] = 1;
                        }
                    }
                } else {
                    fillImage(0, 0, n, path);
                }
            }
            // 输出字符图像
            cout << "Image " << caseNum << "\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << (image[i][j] ? '*' : '.');
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
