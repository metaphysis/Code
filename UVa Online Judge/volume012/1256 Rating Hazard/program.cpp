// Rating Hazard
// UVa ID: 1256
// Verdict: Accepted
// Submission Date: 2025-10-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const LL INF = 1e9 + 7;

/**
 * 计算 x/y 的四舍五入值
 * @param numerator 分子
 * @param denominator 分母
 * @return 四舍五入后的整数值
 */
inline LL calculateRounding(LL numerator, LL denominator)
{
    if (denominator == 0) return -INF;
    LL quotient = numerator / denominator;
    // 检查是否需要四舍五入：余数的两倍 >= 分母
    if (numerator % denominator * 2 >= denominator) quotient++;
    return quotient;
}

/**
 * 比较两个分数 a/b 和 c/d 的大小
 * @return a*d - c*b，正数表示 a/b > c/d，负数表示 a/b < c/d
 */
inline LL compareFractions(LL a, LL b, LL c, LL d)
{
    return a * d - c * b;
}

/**
 * 在Stern-Brocot树的分支上进行二分搜索
 * @param isLeftBranch true表示搜索左分支（小于目标值的方向），false表示搜索右分支（大于目标值的方向）
 */
void searchBranch(LL currentNum, LL currentDen, 
                 LL stepNum, LL stepDen, 
                 LL maxSteps, LL scaleFactor, LL targetValue, LL& bestDen,
                 bool isLeftBranch)
{
    LL left = 1, right = maxSteps;
    LL foundSteps = 0;
    
    // 二分搜索找到最大的步数
    while (left <= right)
    {
        LL mid = (left + right) >> 1;
        LL newNum = currentNum + stepNum * mid;
        LL newDen = currentDen + stepDen * mid;
        
        LL roundedValue = calculateRounding(newNum * scaleFactor, newDen);
        
        if (isLeftBranch) {
            // 左分支：寻找四舍五入值 < 目标值的最大步数
            if (roundedValue < targetValue) {
                foundSteps = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            // 右分支：寻找四舍五入值 > 目标值的最大步数
            if (roundedValue > targetValue) {
                foundSteps = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    // 检查下一步是否满足条件
    foundSteps++;
    LL finalNum = currentNum + stepNum * foundSteps;
    LL finalDen = currentDen + stepDen * foundSteps;
    
    if (calculateRounding(finalNum * scaleFactor, finalDen) == targetValue)
        if (finalDen < bestDen) bestDen = finalDen;
}

int main()
{
    // 加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string inputStr;
    int caseNumber = 1;
    
    while (cin >> inputStr)
    {
        // 终止条件：输入负数
        if (inputStr[0] == '-') break;
        
        // 解析输入的小数字符串
        int strLen = inputStr.length();
        LL scaleFactor = 1;  // 缩放因子，10的小数位数次方
        LL integerValue = 0; // 去掉小数点后的整数值
        bool foundDot = false;
        
        for (int i = 0; i < strLen; i++)
        {
            if (inputStr[i] == '.') {
                foundDot = true;
                continue;
            }
            integerValue = integerValue * 10 + (inputStr[i] - '0');
            if (foundDot) scaleFactor *= 10;
        }

        // Stern-Brocot树初始化
        // 左边界：0/1
        LL leftNum = 0, leftDen = 1;
        // 右边界：1/0（表示无穷大）
        LL rightNum = 1, rightDen = 0;
        LL bestDenominator = INF;  // 最优解（最小分母）
        
        // 步长向量，用于在树上快速移动
        LL stepLeftNum = 0, stepLeftDen = 0;
        LL stepRightNum = 0, stepRightDen = 0;
        
        // 迭代搜索，防止无限循环
        const LL maxIterations = 1000000;
        
        for (LL iteration = 0; iteration < maxIterations; iteration++)
        {
            // 计算当前中间节点（左边界和右边界的中间值）
            LL midNum = leftNum + rightNum;
            LL midDen = leftDen + rightDen;
            
            // 提前终止：分母过大
            if (midDen > 1000000) break;
            
            // 检查当前中间节点是否满足四舍五入条件
            LL roundedValue = calculateRounding(midNum * scaleFactor, midDen);
            if (roundedValue == integerValue)
            {
                if (midDen < bestDenominator) bestDenominator = midDen;
                break;
            }
            
            // 决定下一步搜索的方向
            LL newLeftNum = leftNum, newLeftDen = leftDen;
            LL newRightNum = rightNum, newRightDen = rightDen;
            
            if (compareFractions(midNum, midDen, integerValue, scaleFactor) <= 0) 
            {
                // 中间值小于等于目标值，向右子树移动
                newLeftNum = midNum; 
                newLeftDen = midDen;
            }
            else 
            {
                // 中间值大于目标值，向左子树移动
                newRightNum = midNum; 
                newRightDen = midDen;
            }
            
            LL stepCount = 1;
            
            // 检查步长是否与上一次相同，如果是则可以进行二分加速
            if (newLeftNum - leftNum == stepLeftNum && 
                newRightNum - rightNum == stepRightNum && 
                newLeftDen - leftDen == stepLeftDen && 
                newRightDen - rightDen == stepRightDen)
            {
                // 二分搜索确定最大步数
                LL leftBound = 1, rightBound = INF;
                LL bestStepCount = 1;
                
                while (leftBound <= rightBound)
                {
                    LL midStep = (leftBound + rightBound) >> 1;
                    LL testLeftNum = leftNum + stepLeftNum * midStep;
                    LL testRightNum = rightNum + stepRightNum * midStep;
                    LL testLeftDen = leftDen + stepLeftDen * midStep;
                    LL testRightDen = rightDen + stepRightDen * midStep;
                    
                    // 边界检查
                    if (testLeftNum < 0 || testRightNum < 0 || 
                        testLeftDen < 0 || testRightDen < 0) {
                        rightBound = midStep - 1;
                        continue;
                    }
                    
                    // 比较分数大小
                    LL cmpLeft = compareFractions(testLeftNum, testLeftDen, integerValue, scaleFactor);
                    LL cmpRight = compareFractions(testRightNum, testRightDen, integerValue, scaleFactor);
                    
                    // 检查是否仍在目标区间内
                    if (cmpLeft < 0 && cmpRight > 0) {
                        bestStepCount = midStep;
                        leftBound = midStep + 1;
                    } else {
                        rightBound = midStep - 1;
                    }
                }
                
                // 在两个分支上搜索解
                searchBranch(leftNum, leftDen, stepLeftNum, stepLeftDen, 
                           bestStepCount, scaleFactor, integerValue, bestDenominator, true);
                searchBranch(rightNum, rightDen, stepRightNum, stepRightDen, 
                           bestStepCount, scaleFactor, integerValue, bestDenominator, false);
                
                // 提前终止：如果找到解
                if (bestDenominator != INF) break;
                
                stepCount = bestStepCount;
            }
            else
            {
                // 更新步长向量
                stepLeftNum = newLeftNum - leftNum;
                stepRightNum = newRightNum - rightNum;
                stepLeftDen = newLeftDen - leftDen;
                stepRightDen = newRightDen - rightDen;
            }
            
            // 沿步长向量移动
            leftNum += stepLeftNum * stepCount;
            rightNum += stepRightNum * stepCount;
            leftDen += stepLeftDen * stepCount;
            rightDen += stepRightDen * stepCount;
            
            // 提前终止：如果找到解
            if (bestDenominator != INF) break;
        }
        
        printf("Case %d: %lld\n", caseNumber++, bestDenominator);
    }
    
    return 0;
}

