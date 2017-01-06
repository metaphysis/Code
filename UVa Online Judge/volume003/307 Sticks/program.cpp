// Sticks
// UVa ID: 307
// Verdict: Accepted
// Submission Date: 2017-01-06
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int stick[105], remain[105], used[105], goal, total, n;

// 使用回溯对预设的木棒原始长度进行拼接验证。
// idx表示搜索可用木棒的起始序号，done表示当前木棒拼接是否完成，sum表示当前木棒已经
// 拼接的长度，count表示已经得到的原始长度的木棒数量。
bool dfs(int idx, int done, int sum, int count)
{
    // 检查是否已经将所有木棒拼接完毕。
    if (sum == goal)
    {
        if (count + 1 == total) return true;
        if (dfs(0, 1, 0, count + 1)) return true;
        return false;
    }

    if (done == 1)
    {
        // 当前木棒已经拼接完毕，选取下一段尚未拼接的木棒继续拼接。
        for (int i = 0; i < n; i++)
        {
            if (used[i]) continue;
            used[i] = 1;
            if (dfs(i + 1, 0, stick[i], count)) return true;
            used[i] = 0;
            break;
        }
    }
    else
    {
        // 拼接当前木棒。
        for (int i = idx; i < n; i++)
            // 剪枝：已拼接的长度加上当前木棒长度不能大于目标值；加上剩余木棒长度
            // 不能小于目标值，否则即使用上剩余的所有木棒也无法完成拼接。
            if (!used[i] && sum + stick[i] <= goal && sum + remain[i] >= goal)
            {
                // 剪枝：当前木棒和上一木棒长度相同且上一木棒未使用，那么使用当前
                // 木棒肯定也不可能完成拼接。
                if (i && stick[i] == stick[i - 1] && !used[i - 1]) continue;
                
                // 尝试使用当前木棒。
                used[i] = 1;
                if (dfs(i + 1, 0, sum + stick[i], count)) return true;
                used[i] = 0;
                if (sum + stick[i] == goal) return false;
            }
    }

    return false;
}

int main(int argc, char *argv[])
{
    while (cin >> n, n)
    {
        // 读入数据，统计所有木棒的长度和。
        int length = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> stick[i];
            length += stick[i];
        }

        // 将切割后的木棒长度按照从大到小的顺序进行排列。
        sort(stick, stick + n, greater < int >());

        // 计算第i根木棒开始后续木棒的长度和，为剪枝做准备。
        remain[n] = 0;
        for (int i = n - 1; i >= 0; i--) remain[i] = remain[i + 1] + stick[i];

        // 从小到大遍历可能的木棒初始长度，回溯进行拼接验证。
        for (goal = stick[0]; goal <= length; goal++)
        {
            // 确定木棒的初始长度和木棒的原始数量。
            if (length % goal) continue;
            total = length / goal;

            // 进行拼接验证，成功则输出。
            memset(used, 0, sizeof(used));
            if (dfs(0, 1, 0, 0))
            {
                cout << goal << '\n';
                break;
            }
        }
    }

    return 0;
}
