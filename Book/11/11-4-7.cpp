#include <iostream>
#include <limits>

using namespace std;

int maximum_sum_n3(int data[], int n)
{
    int max_sum = numeric_limits<int>::min();

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
        {
            int sum = 0;
            for (int k = i; k <= j; k++)
                sum += data[k];
            max_sum = max(max_sum, sum);
        }

    return max_sum;
}

int maximum_sum_n_logn(int data[], int left, int right)
{
    // 递归出口。
    if (left > right)
        return 0;
        
    if (left == right)
        return data[left];
    
    // 分治。
    int middle = (left + right) / 2;
    
    // 求最大连续子序列和的左半部分。
    int left_max = numeric_limits<int>::min(), left_sum = 0;
    for (int i = middle; i >= left; i--)
    {
        left_sum += data[i];
        left_max = max(left_max, left_sum);   
    }

    // 求最大连续子序列和的左半部分。
    int right_max = numeric_limits<int>::min(), right_sum = 0;
    for (int i = middle + 1; i <= right; i++)
    {
        right_sum += data[i];
        right_max = max(right_max, right_sum);   
    }
    
    // 递归求解。
    return max(left_max + right_max, max(maximum_sum_n_logn(data, left, middle), 
        maximum_sum_n_logn(data, middle + 1, right)));
}

int maximum_sum_n(int data[], int n)
{
    int max_sum = data[0], current_sum = data[0];
    
    for (int i = 1; i < n; i++)
    {
        if (current_sum <= 0) current_sum = data[i];
        else current_sum += data[i];
        max_sum = max(max_sum, current_sum);
    }
    
    return max_sum;
}

int maximum_sum(int data[], int n)
{
    int max_sum = data[0], current_sum = data[0];
    
    for (int i = 1; i < n; i++)
    {
        current_sum = max(data[i], current_sum + data[i]);
        max_sum = max(max_sum, current_sum);
    }
    
    return max_sum;
}

long long maximum_product(int data[], int n)
{
    long long maximum = data[0];
    long long max_current = data[0], min_current = data[0];

    for (int i = 1; i < n; i++)
    {
        long long element = data[i];
        long long next_max = max_current * data[i];
        long long next_min = min_current * data[i];

        max_current = max(element, max(next_max, next_min));
        min_current = min(element, min(next_max, next_min));

        maximum = max(maximum, max_current);
    }
    
    return maximum;
}

int main(int argc, char *argv[])
{
    int data[] = { -13, -17, 45, -20, 33, -33, 90, 30, 41, 7 };

    cout << maximum_sum_n3(data, 10) << endl;
    cout << maximum_sum_n_logn(data, 0, 9) << endl;
    cout << maximum_sum_n(data, 10) << endl;
    cout << maximum_sum(data, 10) << endl;
    cout << maximum_product(data, 10) << endl;
    
    return 0;
}
