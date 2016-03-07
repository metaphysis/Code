#include <iostream>
#include <algorithm>

using namespace std;

int n, k;
const int MAXN = 10000;
bool circle[MAXN + 10];

int findLast()
{
    fill(circle, circle + MAXN, true);

    // 从编号为 1 的参与者开始计数。
    int index = 1, nn = n;
    while (nn > 1)
    {
        // 因为是用数组来表示环，首先需要从上一次计数结束的地方开始计数到数组末尾。
        int kk = k;
        for (; index <= n; index++)
            if (circle[index] && (--kk == 0))
                break;

        // 若计数未达到设定的计数值，从数组起始位置继续计数。
        while (kk)
        {
            for (index = 1; index <= n; index++)
                if (circle[index] && (--kk == 0))
                    break;
        }

        // 计数到 k，剩余参与者人数减少 1。
        circle[index] = false;
        nn--;
    }

    // 找到并输出最后剩下的参与者编号。
    for (int i = 1; i <= n; i++)
        if (circle[i])
            return i;
}

int main(int argc, char *argv[])
{
    while (cin >> n >> k, n && k)
        cout << findLast() << endl;

    return 0;
}
