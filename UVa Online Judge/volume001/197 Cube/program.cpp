// Cube
// UVa ID: 197
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.490s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <memory.h>

using namespace std;

// 三维坐标结构体
struct Point3D {
    int x;
    int y;
    int z;
};

// 类型定义
typedef vector<Point3D> CoordList;          // 坐标列表
typedef unsigned long FormMask;                  // 形状掩码
typedef vector<FormMask> MaskList;          // 掩码列表
typedef vector<MaskList> AllPieceMasks;     // 所有拼图形状掩码
typedef vector<int> Matrix;                 // 3x3矩阵
typedef vector<Matrix> RotationMatrices;    // 旋转矩阵集合

// 全局变量
AllPieceMasks allPieceMasks;                     // 所有拼图的形状掩码
AllPieceMasks solutions;                         // 存储所有解
RotationMatrices rotationMatrices;               // 旋转矩阵

// 绕X轴旋转矩阵 (0°, 90°, 180°, 270°)
int rotateMatX[][9] = {
    {1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, -1, 0, 1, 0},
    {1, 0, 0, 0, -1, 0, 0, 0, -1},
    {1, 0, 0, 0, 0, 1, 0, -1, 0}
};

// 绕Y轴旋转矩阵
int rotateMatY[][9] = {
    {1, 0, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 1, 0, 1, 0, -1, 0, 0},
    {-1, 0, 0, 0, 1, 0, 0, 0, -1},
    {0, 0, -1, 0, 1, 0, 1, 0, 0}
};

// 绕Z轴旋转矩阵
int rotateMatZ[][9] = {
    {1, 0, 0, 0, 1, 0, 0, 0, 1},
    {0, -1, 0, 1, 0, 0, 0, 0, 1},
    {-1, 0, 0, 0, -1, 0, 0, 0, 1},
    {0, 1, 0, -1, 0, 0, 0, 0, 1}
};

// 七个拼图的初始坐标定义 (每个拼图由3-4个小方块组成)
Point3D pieceDefinitions[][4] = {
    {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 2, 0}}, // 拼图a (L形)
    {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {1, 1, 1}}, // 拼图f (角落形)
    {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 1, 0}}, // 拼图g (Z形)
    {{0, 0, 0}, {0, 0, 1}, {1, 0, 1}, {0, 1, 1}}, // 拼图e (反L形)
    {{0, 1, 0}, {1, 0, 0}, {1, 1, 0}, {1, 2, 0}}, // 拼图c (T形)
    {{0, 0, 0}, {0, 0, 1}, {1, 0, 1}, {1, 0, 2}}, // 拼图d (长条形)
    {{0, 0, 0}, {1, 0, 0}, {0, 0, 1}}             // 拼图b (小L形)
};

// 拼图名称映射 (索引对应pieceDefinitions中的顺序)
char pieceNames[] = {'a', 'f', 'g', 'e', 'c', 'd', 'b'};

// 坐标到输出字符串位置的映射表 (27个位置)
char positionMap[] = {24, 25, 26, 21, 22, 23, 18, 19, 20, 15, 16, 17, 12, 13, 14, 9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2};

// 坐标比较运算符 (用于排序)
bool operator < (const Point3D &p1, const Point3D &p2) {
    return (p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y) ||
        (p1.x == p2.x && p1.y == p2.y && p1.z < p2.z));
}

bool operator == (const Point3D &p1, const Point3D &p2) {
    return (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z);
}

// 矩阵乘法: M1 * M2 = Result
void MatrixMultiply(int *matrix1, int *matrix2, int rows1, int cols2, int n, int *resultMatrix) {
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            resultMatrix[i * cols2 + j] = 0;
            for (int k = 0; k < n; ++k) {
                resultMatrix[i * cols2 + j] += matrix1[i * rows1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
}

// 坐标取反 (用于平移)
Point3D Inverse(Point3D &coord) {
    coord.x = -coord.x;
    coord.y = -coord.y;
    coord.z = -coord.z;
    return coord;
}

// 计算坐标列表的边界 (最小和最大坐标)
void GetBounds(const CoordList &coords, Point3D &minCoord, Point3D &maxCoord) {
    minCoord = maxCoord = coords[0];
    for (size_t i = 1; i < coords.size(); ++i) {
        if (coords[i].x < minCoord.x) minCoord.x = coords[i].x;
        if (coords[i].x > maxCoord.x) maxCoord.x = coords[i].x;
        if (coords[i].y < minCoord.y) minCoord.y = coords[i].y;
        if (coords[i].y > maxCoord.y) maxCoord.y = coords[i].y;
        if (coords[i].z < minCoord.z) minCoord.z = coords[i].z;
        if (coords[i].z > maxCoord.z) maxCoord.z = coords[i].z;
    }
}

// 计算拼图在三个方向上的尺寸
void GetPieceSize(const CoordList &coords, Point3D &size) {
    Point3D minCoord, maxCoord;
    GetBounds(coords, minCoord, maxCoord);
    size.x = maxCoord.x - minCoord.x;
    size.y = maxCoord.y - minCoord.y;
    size.z = maxCoord.z - minCoord.z;
}

// 平移坐标列表
void TranslateCoords(CoordList &coords, const Point3D &offset) {
    for (size_t i = 0; i < coords.size(); ++i) {
        coords[i].x += offset.x;
        coords[i].y += offset.y;
        coords[i].z += offset.z;
    }
}

// 将坐标列表转换为位掩码 (每个坐标对应立方体中的一个位置)
FormMask CoordsToMask(CoordList &coords) {
    FormMask mask = 0;
    for (CoordList::iterator it = coords.begin(); it != coords.end(); ++it) {
        // 将3D坐标转换为1D索引: x + y*3 + z*9
        mask |= (1 << (it->x + it->y * 3 + it->z * 9));
    }
    return mask;
}

// 生成一个拼图的所有可能形状掩码 (包括旋转和平移)
void GenerateAllForms(const Point3D *pieceCoords, int numPoints, MaskList &forms) {
    CoordList originalCoords(pieceCoords, pieceCoords + numPoints);
    CoordList rotatedCoords(numPoints);
    Point3D minCoord, size;
    
    // 排序原始坐标
    sort(originalCoords.begin(), originalCoords.end());

    // 存储所有旋转后的坐标列表
    vector<CoordList> allRotations;

    // 对每个旋转矩阵应用旋转
    for (RotationMatrices::iterator it = rotationMatrices.begin(); it != rotationMatrices.end(); ++it) {
        for (int j = 0; j < numPoints; ++j) {
            MatrixMultiply(it->data(), (int*)&originalCoords[j], 3, 1, 3, (int*)&rotatedCoords[j]);
        }
        // 规格化旋转后的坐标 (平移到原点)
        GetBounds(rotatedCoords, minCoord, size);
        TranslateCoords(rotatedCoords, Inverse(minCoord));
        sort(rotatedCoords.begin(), rotatedCoords.end());
        allRotations.push_back(rotatedCoords);
    }

    // 去除重复的旋转
    sort(allRotations.begin(), allRotations.end());
    allRotations.erase(unique(allRotations.begin(), allRotations.end()), allRotations.end());

    size_t rotationCount = allRotations.size();

    // 为每个旋转生成所有可能的平移
    for (size_t i = 0; i != rotationCount; ++i) {
        GetPieceSize(allRotations[i], size);
        // 在三个维度上进行平移
        for (minCoord.x = 0; minCoord.x < 3 - size.x; ++minCoord.x) {
            for (minCoord.y = 0; minCoord.y < 3 - size.y; ++minCoord.y) {
                for (minCoord.z = 0; minCoord.z < 3 - size.z; ++minCoord.z) {
                    if (minCoord.x != 0 || minCoord.y != 0 || minCoord.z != 0) {
                        allRotations.push_back(allRotations[i]);
                        TranslateCoords(allRotations.back(), minCoord);
                    }
                }
            }
        }
    }

    // 将所有坐标列表转换为掩码
    for (vector<CoordList>::iterator it = allRotations.begin(); it != allRotations.end(); ++it) {
        forms.push_back(CoordsToMask(*it));
    }
}

// 递归填充立方体: 尝试所有拼图形状的组合
void FillCubeRecursive(AllPieceMasks::const_iterator currentPiece, FormMask cubeState, MaskList &currentPath) {
    // 检查是否填满整个立方体 (27位全为1)
    if (cubeState == 0x07ffffff) {
        solutions.push_back(currentPath);
        return;
    }

    const FormMask *pieceForms = currentPiece->data();
    size_t formCount = currentPiece->size();

    // 尝试当前拼图的所有可能形状
    for (size_t i = 0; i < formCount; ++i) {
        // 检查当前形状是否与已填充部分冲突
        if ((cubeState & pieceForms[i]) == 0) {
            FormMask newState = cubeState | pieceForms[i];
            currentPath.push_back(pieceForms[i]);
            FillCubeRecursive(currentPiece + 1, newState, currentPath);
            currentPath.pop_back();
        }
    }
}

int main(int argc, char* argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    // 生成所有旋转矩阵 (24种旋转)
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                int temp[9];
                rotationMatrices.push_back(vector<int>(9));
                MatrixMultiply(rotateMatY[j], rotateMatZ[k], 3, 3, 3, temp);
                MatrixMultiply(rotateMatX[i], temp, 3, 3, 3, rotationMatrices.back().data());
            }
        }
    }
    // 去除重复的旋转矩阵
    sort(rotationMatrices.begin(), rotationMatrices.end());
    rotationMatrices.erase(unique(rotationMatrices.begin(), rotationMatrices.end()), rotationMatrices.end());

    // 为所有7个拼图生成所有可能的形状掩码
    allPieceMasks.resize(7);
    for (int i = 0; i < 7; ++i) {
        // 第7个拼图只有3个点，其他有4个点
        GenerateAllForms(pieceDefinitions[i], 4 - (i / 6), allPieceMasks[i]);
    }

    // 处理输入数据
    for (string inputLine; getline(cin, inputLine) && !inputLine.empty(); ) {
        CoordList inputPieceA;
        solutions.clear();

        // 解析输入中拼图a的位置
        for (string::iterator it = inputLine.begin(); it != inputLine.end(); ++it) {
            if (*it == 'a') {
                int position = it - inputLine.begin();
                // 将字符串位置转换为3D坐标
                Point3D point = {position % 3, 2 - (position % 9) / 3, 2 - position / 9};
                inputPieceA.push_back(point);
            }
        }

        // 规格化输入坐标 (平移到原点)
        Point3D minCoord, maxCoord;
        GetBounds(inputPieceA, minCoord, maxCoord);
        TranslateCoords(inputPieceA, Inverse(minCoord));
        sort(inputPieceA.begin(), inputPieceA.end());
        FormMask inputMask = CoordsToMask(inputPieceA);

        // 在拼图a的所有形状中找到匹配输入的形状
        int formIndex = find(allPieceMasks[0].begin(), allPieceMasks[0].end(), inputMask) - allPieceMasks[0].begin();

        // 使用找到的形状开始搜索
        FormMask fixedFormA = allPieceMasks[0][formIndex];
        MaskList path(1, fixedFormA);
        FillCubeRecursive(allPieceMasks.begin() + 1, fixedFormA, path);

        // 为拼图a的其他相关形状也进行搜索
        for (int i = formIndex * 5 + 24; i < (formIndex + 1) * 5 + 24; ++i) {
            fixedFormA = allPieceMasks[0][i];
            path = MaskList(1, fixedFormA);
            FillCubeRecursive(allPieceMasks.begin() + 1, fixedFormA, path);
        }

        // 将解决方案转换为输出字符串
        vector<string> outputStrings;
        for (AllPieceMasks::iterator solIt = solutions.begin(); solIt != solutions.end(); ++solIt) {
            string outputStr;
            outputStr.resize(27);
            for (size_t pieceIndex = 0; pieceIndex < solIt->size(); ++pieceIndex) {
                FormMask pieceMask = solIt->at(pieceIndex);
                for (size_t pos = 0; pos < 27; ++pos) {
                    if (pieceMask & (1 << positionMap[pos])) {
                        // 使用positionMap将内部坐标映射到输出顺序
                        outputStr[pos] = pieceNames[pieceIndex];
                    }
                }
            }
            outputStrings.push_back(outputStr);
        }

        // 排序并输出所有解
        sort(outputStrings.begin(), outputStrings.end());
        for (vector<string>::iterator outIt = outputStrings.begin(); outIt != outputStrings.end(); ++outIt) {
            cout << *outIt << '\n';
        }
        cout << '\n';
    }

    return 0;
}
