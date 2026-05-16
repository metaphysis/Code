// Rubik's Cube
// UVa ID: 281
// Verdict: Accepted
// Submission Date: 2026-05-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 输入 9x12（去除空格后）到 54 个贴纸的映射
int netToIdx[9][12] = {
    {-1, -1, -1,  0,  1,  2, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1,  3,  4,  5, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1,  6,  7,  8, -1, -1, -1, -1, -1, -1},
    {18, 19, 20,  9, 10, 11, 27, 28, 29, 36, 37, 38},
    {21, 22, 23, 12, 13, 14, 30, 31, 32, 39, 40, 41},
    {24, 25, 26, 15, 16, 17, 33, 34, 35, 42, 43, 44},
    {-1, -1, -1, 45, 46, 47, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, 48, 49, 50, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, 51, 52, 53, -1, -1, -1, -1, -1, -1}
};

// 24 种面对置换及旋转（6个面：U, F, L, R, B, D 对应索引 0 - 5）
// 个位数表示所对应的原始面，十位数表示该面在变换过程中需要向左旋转的次数
int faces[24][6] = {
    {0, 1, 2, 3, 4, 5}, {10, 2, 4, 1, 3, 35}, {20, 4, 3, 2, 1, 25}, {30, 3, 1, 4, 2, 15},
    {1, 5, 12, 33, 20, 24}, {11, 12, 20, 5, 33, 14}, {21, 20, 33, 12, 5, 4}, {31, 33, 5, 20, 12, 34},
    {2, 35, 14, 31, 30, 23}, {12, 14, 30, 35, 31, 13}, {22, 30, 31, 14, 35, 3}, {32, 31, 35, 30, 14, 33},
    {3, 15, 11, 34, 10, 22}, {13, 11, 10, 15, 34, 12}, {23, 10, 34, 11, 15, 2}, {33, 34, 15, 10, 11, 32},
    {4, 25, 13, 32, 0, 21}, {14, 13, 0, 25, 32, 11}, {24, 0, 32, 13, 25, 1}, {34, 32, 25, 0, 13, 31},
    {5, 24, 22, 23, 21, 0}, {15, 22, 21, 24, 23, 30}, {25, 21, 23, 22, 24, 20}, {35, 23, 24, 21, 22, 10}
};

// 逆时针旋转 90 度
void rotate(char cube[3][3]) {
    char rotated[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            rotated[3 - j - 1][i] = cube[i][j];
    memcpy(cube, rotated, sizeof rotated);
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    while (n--) {
        // 读取输入
        string line;
        vector<string> cube1, cube2;
        for (int i = 0; i < 9; ++i) {
            getline(cin, line);
            string clean;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ' ' || line[i] == '|') continue;
                clean += line[i];
            }
            cube1.push_back(clean.substr(0, 12));
            cube2.push_back(clean.substr(12));
        }
        // 获取各个面
        char color1[6][3][3], color2[6][3][3];
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 12; j++) {
                int id = netToIdx[i][j];
                if (netToIdx[i][j] != -1) {
                    color1[id / 9][(id % 9) / 3][(id % 9) % 3] = cube1[i][j];
                    color2[id / 9][(id % 9) / 3][(id % 9) % 3] = cube2[i][j];
                }
            }
        bool same = false;
        char color3[6][3][3];
        for (int i = 0; i < 24 && !same; i++) {
            // 获取旋转后的各个面
            for (int j = 0; j < 6; j++) {
                int rotates = faces[i][j] / 10, face = faces[i][j] % 10;
                for (int r = 0; r < 3; r++)
                    for (int c = 0; c < 3; c++)
                        color3[j][r][c] = color1[face][r][c];
                for (int k = 0; k < rotates; k++) rotate(color3[j]);
            }
            // 与目标魔方尝试建立映射
            bool matched = true;
            map<char, char> mp;
            for (int j = 0; j < 6 && matched; j++)
                for (int r = 0; r < 3 && matched; r++)
                    for (int c = 0; c < 3; c++) {
                        if (!mp.count(color3[j][r][c])) mp[color3[j][r][c]] = color2[j][r][c];
                        else {
                            if (mp[color3[j][r][c]] != color2[j][r][c]) {
                                matched = false;
                                break;
                            }
                        }
                    }
            if (matched) same = true;
        }
        cout << (same ? "same" : "different") << '\n';
        // 读取空行
        getline(cin, line);
    }
    return 0;
}
