// The Sultan's Successors
// UVa ID: 167
// Verdict: Accepted
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int number[64], k;
vector<int> column;
vector<vector<int>> positions;

// 判断皇后在对角线上是否会互相攻击。
bool isSolution()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < i; j++)
            if (abs(i - j) == abs(column[i] - column[j]))
                return false;
    return true;
}

// 回溯查找所有可能排列。
void backtrack()
{
    for (int i = 0; i < 8; i++) column.push_back(i);

    do
    {
        if (isSolution())
        {
            vector<int> solution;
            for (int i = 0; i < 8; i++) solution.push_back(i * 8 + column[i]);
            positions.push_back(solution);
        }
        
    } while (next_permutation(column.begin(), column.end()));
}

// 对符合要求的放置方案求数值和。
int findMaxSum()
{
    int maxSum = 0;
    for (int i = 0; i < positions.size(); i++)
    {
        int sum = 0;
        for (int j = 0; j < positions[i].size(); j++)
            sum += number[positions[i][j]];
        maxSum = max(sum, maxSum);
    }
    return maxSum;
}

// 读入数据，查找最大值并输出。
int main(int argc, char* argv[])
{
    backtrack();
    
    cin >> k;
    while (k--)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                cin >> number[i * 8 + j];
        cout << setw(5) << right << findMaxSum() << endl;
    }
    
	return 0;
}
