#include <bits/stdc++.h>

using namespace std;

pair<int, int> findSingleNumberIII(vector<int> nums)
{
    // 获取所有元素的异或值。
    int xorSum = 0;
    for (auto n : nums) xorSum ^= n;

    // 找到第一个非零的二进制位所对应的二进制数。
    int mask = 1;
    while (!(xorSum & mask)) mask <<= 1;

    // 划分数组同时得到两个不同元素的值。
    int X = 0, Y = 0;
    for (auto n : nums)
        if (n & mask) X ^= n;
        else Y ^= n;
    
    return make_pair(X, Y);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<int> nums;
    int n;
    while (cin >> n) nums.push_back(n);
    pair<int, int> p = findSingleNumberIII(nums);
    cout << p.first << ' ' << p.second << '\n';
    
    return 0;
}
