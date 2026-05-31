// Intelligent Cats
// UVa ID: 10456
// Verdict: Accepted
// Submission Date: 2026-05-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int x[31], y[31], fixedX, fixedY, n, tempX[31], tempY[31], len, totalArea;

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int main() {
    while (scanf("%d", &n) == 1) {
        // 读入多边形顶点
        for (int i = 0; i < n; i++) {
            scanf("%d %d", x + i, y + i);
        }
        x[n] = x[0];  // 方便循环处理
        y[n] = y[0];
        
        // 计算多边形面积的两倍
        totalArea = 0;
        for (int i = 0; i < n; i++) {
            totalArea += x[i] * y[i + 1] - x[i + 1] * y[i];
        }
        
        int k;
        scanf("%d", &k);
        while (k--) {
            scanf("%d %d", &fixedX, &fixedY);
            int p = 0;
            len = 0;
            
            // 找到固定点所在的边
            for (int i = n - 1; i >= 0; i--) {
                if ((x[i + 1] - x[i]) * (fixedY - y[i]) == (fixedX - x[i]) * (y[i + 1] - y[i])) {
                    p = i;
                }
            }
            
            // 构建顶点序列
            tempX[len] = fixedX;
            tempY[len++] = fixedY;
            tempX[len] = x[p + 1];
            tempY[len++] = y[p + 1];
            
            // 遍历后续顶点，寻找分割点所在的边
            for (int i = (p + 2) % n; i != p; i = (i + 1) % n) {
                tempX[len] = x[i];
                tempY[len++] = y[i];
                tempX[len] = fixedX;
                tempY[len] = fixedY;
                
                // 计算当前多边形面积的两倍
                int temp = 0;
                for (int j = 0; j < len; j++) {
                    temp += tempX[j] * tempY[j + 1] - tempX[j + 1] * tempY[j];
                }
                if (2 * temp < totalArea) {
                    continue;  // 面积未达到一半，继续
                }
                
                // 找到分割边，计算分割点坐标
                int lastX = x[(i + n - 1) % n], lastY = y[(i + n - 1) % n];
                int dx = x[i] - lastX, dy = y[i] - lastY;
                int sum1 = 0, sum2 = 0;
                
                for (int j = 0; j < len; j++) {
                    if (j < len - 2) {
                        sum1 += tempX[j] * tempY[j + 1] - tempX[j + 1] * tempY[j];
                    } else if (j == len - 2) {
                        sum2 += lastX * dy - lastY * dx;
                    } else {
                        sum1 += lastX * tempY[0] - lastY * tempX[0];
                        sum2 += dx * tempY[0] - dy * tempX[0];
                    }
                }
                
                sum1 = (totalArea - 2 * sum1);
                int numeratorX = lastX * 2 * sum2 + dx * sum1;
                int denominatorX = 2 * sum2;
                int d = gcd(numeratorX, denominatorX);
                numeratorX /= d;
                denominatorX /= d;
                if (denominatorX < 0) {
                    numeratorX *= -1;
                    denominatorX *= -1;
                }
                printf("(%d/%d),", numeratorX, denominatorX);
                
                int numeratorY = lastY * 2 * sum2 + dy * sum1;
                int denominatorY = 2 * sum2;
                int dd = gcd(numeratorY, denominatorY);
                numeratorY /= dd;
                denominatorY /= dd;
                if (denominatorY < 0) {
                    numeratorY *= -1;
                    denominatorY *= -1;
                }
                printf("(%d/%d)\n", numeratorY, denominatorY);
                break;
            }
        }
    }
    return 0;
}
