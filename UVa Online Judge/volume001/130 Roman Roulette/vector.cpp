#include <iostream>
#include <vector>
using namespace std;

int n, k, m;
vector < int > circle;

// 模拟计数的过程。
int findCW(int start, int count)
{
    for (int i = start; i < circle.size(); i++)
        if (circle[i] > 0 && ((--count) == 0))
            return i;

    while (true)
    {
        for (int i = 0; i < circle.size(); i++)
            if (circle[i] > 0 && ((--count) == 0))
                return i;
    }
}

// 找到幸存者的编号。
int findSurvivor()
{
    for (int i = 0; i < circle.size(); i++)
        if (circle[i] > 0)
            return circle[i];
}

int main(int argc, char *argv[])
{
    int n, k;
    while (cin >> n >> k, n || k)
    {
        circle.clear();
        for (int i = 1; i <= n; i++)
            circle.push_back(i);

        int killed = 0, burier;
        while (n > 1)
        {
            killed = findCW(killed, k);
            circle[killed] = 0;
            
            burier = findCW(killed, k);
            circle[killed] = circle[burier];
            circle[burier] = 0;
            
            // 根据题意，往顺时针方向移动一个位置开始下一轮计数。
            killed = (killed + 1) % circle.size();
            n--;
        }
        
        // 根据环形对称，假设幸存者的编号为s，那么从编号为1的人往逆时针方向数s
        // 个人，然后从此位置开始计数，则幸存者为原编号为1的人。
        cout << (circle.size() - findSurvivor() + 1) % circle.size() + 1 << endl;
    }
    
    return 0;
}
