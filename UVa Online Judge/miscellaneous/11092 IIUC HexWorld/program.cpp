// IIUC HexWorld
// UVa ID: 11092
// Verdict: Accepted
// Submission Date: 2016-09-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

// 需要计算对应直角坐标的格点数目，从0开始计数。
const int MAX_V = 10000001;

// 表示直角坐标，其中单位距离为2，横坐标的单位为1，纵坐标的单位为sqrt(3)。
struct point
{
    int x, y;
};

// 保存格点直角坐标的数组。
point grid[MAX_V];

// 计算指定数量格点的直角坐标。
void setCoordinate()
{
    // 定义横纵坐标值的偏移量，沿着格点形成的六边形行走，有固定的偏移量。
    int offset[6][2] = {{1, 1}, {-1, 1}, {-2, 0}, {-1, -1}, {1, -1}, {2, 0}};
    
    // 定义每次行走所经过的格点数，注意是从原点开始，第一步是向右行走。
    int steps[6] = {0, 1, 1, 1, 1, 1};

    // 设置最后一次经过的格点的坐标。
    int index = 0;
    point last = (point){0, 0};
    grid[index++] = last;

    // 根据编号规律计算格点的直角坐标。
    while (true)
    {
        last.x += 2, grid[index++] = last;
        if (index >= MAX_V) return;
    
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < steps[i]; j++)
            {
                last.x += offset[i][0], last.y += offset[i][1];
                grid[index++] = last;
                if (index >= MAX_V) return;
            }
            
            // 每完成一圈，各边上的格点数增加1。
            steps[i]++;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    setCoordinate();
    
    int A, B;
    while (cin >> A >> B)
    {
        double aliceToBob = fabs(B - A);
        cout << fixed << setprecision(3) << aliceToBob << ' ';
        double bobToAlice = sqrt(pow(grid[A].x - grid[B].x, 2) + 3 * pow(grid[A].y - grid[B].y, 2)) / 2.0;
        cout << fixed << setprecision(3) << bobToAlice << '\n';
    }
    
	return 0;
}
