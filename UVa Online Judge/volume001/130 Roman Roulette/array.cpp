#include <iostream>
#include <vector>

using namespace std;

const int MAX_NUMBER = 100;

int n, k;
int circle[MAX_NUMBER + 1];

// 模拟计数的过程。
int findCW(int start, int count)
{
    for (int i = start; i < n; i++)
        if (circle[i] > 0 && ((--count) == 0))
            return i;

    while (true)
    {
        for (int i = 0; i < n; i++)
            if (circle[i] > 0 && ((--count) == 0))
                return i;
    }
}

// 找到幸存者的编号。
int findSurvivor()
{
    for (int i = 0; i < n; i++)
        if (circle[i] > 0)
            return circle[i];
}

int main(int argc, char* argv[])
{
    int counter;
    while (cin >> n >> k, n || k)
    {
        counter = n;
        for (int i = 1; i <= n; i++)
            circle[i - 1] = i;

        int killed = 0, burier;
        while (counter > 1)
        {
            killed = findCW(killed, k);
            circle[killed] = 0;
            
            burier = findCW(killed, k);
            circle[killed] = circle[burier];
            circle[burier] = 0;
            
            // 根据题意，往顺时针方向移动一个位置开始下一轮计数。
            killed = (killed + 1) % n;
            counter--;
        }
        
        // 根据环形对称，假设幸存者的编号为 s，那么从编号为 1 的人往逆时针
        // 方向数 s 个人，然后从此位置开始计数，则幸存者为原编号为 1 的人。
        cout << (n - findSurvivor() + 1) % n + 1 << endl;
    }
    
    return 0;
}
