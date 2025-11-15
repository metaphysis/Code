// Cutting Diamonds
// UVa ID: 10351
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double PI = acos(-1.0); // 定义圆周率

int main() {
    double boxLength, boxWidth, boxHeight; // 盒子的长、宽、高（全长）
    double diamondX, diamondY, diamondZ;   // 椭球的 x、y、z 轴长度（全长）
    int setNumber = 0; // 测试用例编号
    
    // 循环读取输入直到文件结束
    while (cin >> boxLength >> boxWidth >> boxHeight >> diamondX >> diamondY >> diamondZ) {
        setNumber++; // 更新测试用例编号
        
        // 计算椭球的半轴长度
        double semiAxisX = diamondX / 2.0;
        double semiAxisY = diamondY / 2.0;
        double semiAxisZ = diamondZ / 2.0;
        
        double cutArea = 0.0; // 切割面积
        
        // 检查 x 方向是否需要切割
        if (boxLength < diamondX) {
            cutArea = PI * semiAxisY * semiAxisZ * (1.0 - (boxLength - semiAxisX) * (boxLength - semiAxisX) / (semiAxisX * semiAxisX));
        }
        // 检查 y 方向是否需要切割
        else if (boxWidth < diamondY) {
            cutArea = PI * semiAxisX * semiAxisZ * (1.0 - (boxWidth - semiAxisY) * (boxWidth - semiAxisY) / (semiAxisY * semiAxisY));
        }
        // 检查 z 方向是否需要切割
        else if (boxHeight < diamondZ) {
            cutArea = PI * semiAxisX * semiAxisY * (1.0 - (boxHeight - semiAxisZ) * (boxHeight - semiAxisZ) / (semiAxisZ * semiAxisZ));
        }
        
        // 输出结果
        cout << "Set #" << setNumber << "\n";
        cout << fixed << setprecision(6) << cutArea << "\n";
    }
    
    return 0;
}
