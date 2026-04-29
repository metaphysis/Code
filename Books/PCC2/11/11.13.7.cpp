#include <bits/stdc++.h>

using namespace std;

int maximumSum1(int data[], int n)
{
    int maxSum = numeric_limits<int>::min();

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
        {
            int sum = 0;
            for (int k = i; k <= j; k++)
                sum += data[k];
            maxSum = max(maxSum, sum);
        }

    return maxSum;
}

int maximumSum2(int data[], int left, int right)
{
    // 递归出口。
    if (left > right)
        return 0;
        
    if (left == right)
        return data[left];
    
    // 分治。
    int middle = (left + right) / 2;
    
    // 求最大连续子序列和的左半部分。
    int leftMax = numeric_limits<int>::min(), leftSum = 0;
    for (int i = middle; i >= left; i--)
    {
        leftSum += data[i];
        leftMax = max(leftMax, leftSum);   
    }

    // 求最大连续子序列和的左半部分。
    int rightMax = numeric_limits<int>::min(), rightSum = 0;
    for (int i = middle + 1; i <= right; i++)
    {
        rightSum += data[i];
        rightMax = max(rightMax, rightSum);   
    }
    
    // 递归求解。
    return max(leftMax + rightMax, max(maximumSum2(data, left, middle), 
        maximumSum2(data, middle + 1, right)));
}

int maximumSum3(int data[], int n)
{
    int maxSum = data[0], currentSum = data[0];
    
    for (int i = 1; i < n; i++)
    {
        if (currentSum <= 0) currentSum = data[i];
        else currentSum += data[i];
        maxSum = max(maxSum, currentSum);
    }
    
    return maxSum;
}

int maximumSum4(int data[], int n)
{
    int maxSum = data[0], currentSum = data[0];
    
    for (int i = 1; i < n; i++)
    {
        currentSum = max(data[i], currentSum + data[i]);
        maxSum = max(maxSum, currentSum);
    }
    
    return maxSum;
}

long long maximumProduct(int data[], int n)
{
    long long maximum = data[0];
    long long maxCurrent = data[0], minCurrent = data[0];

    for (int i = 1; i < n; i++)
    {
        long long element = data[i];
        long long next_max = maxCurrent * data[i];
        long long next_min = minCurrent * data[i];

        maxCurrent = max(element, max(next_max, next_min));
        minCurrent = min(element, min(next_max, next_min));

        maximum = max(maximum, maxCurrent);
    }
    
    return maximum;
}

int main(int argc, char *argv[])
{
    int data[] = { -13, -17, 45, -20, 33, -33, 90, 30, 41, 7 };

    cout << maximumSum1(data, 10) << endl;
    cout << maximumSum2(data, 0, 9) << endl;
    cout << maximumSum3(data, 10) << endl;
    cout << maximumSum4(data, 10) << endl;
    cout << maximumProduct(data, 10) << endl;
    
    return 0;
}
