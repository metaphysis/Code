#include <iostream>
#include <limits>

using namespace std;

int maximumSumN3(int data[], int n)
{
    int maximum = numeric_limits<int>::min();

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            int sum = 0;
            for (int k = i; k <= j; k++)
                sum += data[k];
            maximum = max(maximum, sum);
        }

    return maximum;
}

int maximumSumNLogN(int data[], int left, int right)
{
    // 递归出口。
    if (left > right)
        return 0;
        
    if (left == right)
        return data[left];
    
    // 分治。
    int middle = (left + right) / 2;
    
    // 求最大连续子序列和的左半部分。
    int leftMaximum = numeric_limits<int>::min(), leftSum = 0;
    for (int i = middle; i >= left; i--)
    {
        leftSum += data[i];
        leftMaximum = max(leftMaximum, leftSum);   
    }
    // 求最大连续子序列和的左半部分。
    int rightMaximum = numeric_limits<int>::min(), rightSum = 0;
    for (int i = middle + 1; i <= right; i++)
    {
        rightSum += data[i];
        rightMaximum = max(rightMaximum, rightSum);   
    }
    
    // 递归求解。
    return max(leftMaximum + rightMaximum, max(maximumSumNLogN(data, left, middle), 
        maximumSumNLogN(data, middle + 1, right)));
}

int maximumSumN(int data[], int n)
{
    int maximum = data[0], maximumCurrent = data[0];
    
    for (int i = 1; i < n; i++)
    {
        if (maximumCurrent <= 0)
            maximumCurrent = data[i];
        else
            maximumCurrent += data[i];
        maximum = max(maximum, maximumCurrent);
    }
    
    return maximum;
}

int main(int argc, char *argv[])
{
    int data[] = { 13, -17, 45, 89, -77, 33, 90, -31, 103, 28 };

    cout << maximumSumN3(data, 10) << endl;
    cout << maximumSumNLogN(data, 0, 9) << endl;
    cout << maximumSumN(data, 10) << endl;
    
    return 0;
}
