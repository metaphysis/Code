// Radar Tracking （雷达追踪）
// PC/UVa IDs: 111406/849, Popularity: C, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2016-04-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// 一道不是非常完善的题目。测试数据和评判程序可能有问题，不过好在测试数据应该比较
// 简单，不然很难 AC。截止 AC 时，只有 22 通过。

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = 3.14159265358979323846;
const int COUNTER_CLOCKWISE = 0, CLOCKWISE_SAME_SAME_CYCLE = 1,
          CLOCKWISE_SAME_NEXT_CYCLE = 2, CLOCKWISE_NEXT_NEXT_CYCLE = 3;

struct point
{
    double angle, distance;
};

bool cmp(point x, point y)
{
    return (x.angle != y.angle) ? x.angle < y.angle : x.distance > y.distance;
}

double toRadian(double degree)
{
    return (degree / 180.0) * PI;
}

double toDegree(double radian)
{
    return (radian / PI) * 180.0;
}

double getValue(double b, double c, double A, double x, double C, int category)
{
    if (category == COUNTER_CLOCKWISE)
        return b * sin(x) - sin(A - x) * c * (2.0 * PI - x) / (2.0 * PI - C);
    else if (category == CLOCKWISE_SAME_SAME_CYCLE)
        return b * sin(x) - sin(A - x) * c * x / C;
    else if (category == CLOCKWISE_SAME_NEXT_CYCLE)
        return b * sin(x) - sin(A - x) * c * (2.0 * PI + x) / C;
    else if (category == CLOCKWISE_NEXT_NEXT_CYCLE)
        return b * sin(x) - sin(A - x) * c * (2.0 * PI + x) / (2.0 * PI + C);
}

double binarySearch(double b, double c, double A, double C, int category)
{
    double x = 0.0;
    while (x < A)
    {
        x += (0.01 * PI / 180.0);
        if (getValue(b, c, A, x, C, category) > 0)
            break;
    }

    // 二分查找。
    double up = x - (0.01 * PI / 180.0), down = x, middle;
    while (fabs(up - down) > 1e-10)
    {
        middle = (up + down) / 2.0;
        if (getValue(b, c, A, middle, C, category) < 0)
            up = middle;
        else
            down = middle;
    }

    return middle;
}

void calculate(point first, point second)
{
    point solutions[3];
    int counter = 0;

    // 当前后两次的角度相同时，说明物体的运动轨迹是过极点的直线，且前两次观察结果方向相同。
    if (first.angle == second.angle)
    {
        // 远离极点方向。
        if (second.distance >= first.distance)
            solutions[counter++] = (point)
        {
            first.angle, second.distance + (second.distance - first.distance)
        };
        // 靠近极点方向，可能会越过极点到相对的另一侧。
        else
        {
            if (second.distance > (first.distance - second.distance))
                solutions[counter++] = (point)
            {
                first.angle, second.distance - (first.distance - second.distance)
            };
            else
                solutions[counter++] = (point)
            {
                ((first.angle >= 180.0) ? (first.angle - 180.0) : (first.angle + 180.0)),
                fabs(second.distance - (first.distance - second.distance))
            };
        }
    }
    // 当前后两次观察到的位置极角相差 180 度时，说明物体的运动轨迹是过极点的直线。
    else if (fabs(first.angle - second.angle) == 180.0)
    {
        // 注意在第二次观察时，时间过去了 1 s，但是再下一次观察时，将是 3s。故移动距
        // 离要增加一倍。
        solutions[counter++] = (point)
        {
            second.angle, 3 * second.distance + 2 * first.distance
        };
        if (fabs(2 * second.distance - first.distance) < 1e-8)
            solutions[counter++] = (point)
        {
            second.angle, first.distance + second.distance
        };
    }
    // 当第一次和第二次的极角不同，且相差不是 180 度时，物体的运动轨迹是一条不过极点的直线。
    else
    {
        // 当第二次观察位置出现在第一次的逆时针方向，则表明雷达是在一个周期的时间内观察
        // 到两个位置。则第三次观察时只有一种可能的位置。
        double C = 0.0, finalAngle, finalDistance, x;
        double angleDiff = fabs(first.angle - second.angle);
        if ((first.angle > second.angle && angleDiff < 180.0) || (first.angle < second.angle && angleDiff > 180.0))
        {
            // 二分数值法求近似解。
            // 先求出前后两次观察位置之间的角度差，设为角 C，对应边为 c。
            if (first.angle < second.angle && angleDiff > 180.0)
                C = toRadian(first.angle + (360.0 - second.angle));
            else
                C = toRadian(first.angle - second.angle);

            // 不失一般性，设第一次观察的位置距离为 a，第二次观察的距离为 b，可
            // 由余弦定理求出边 b 对应的角 B。先求边 c。
            double a = first.distance, b = second.distance;
            double c = sqrt(a * a + b * b - 2.0 * a * b * cos(C));
            double A = acos((b * b + c * c - a * a) / (2.0 * b * c));

            // 找到边界值。
            double x = A;
            while (x > 0.0)
            {
                x -= (0.01 * PI / 180.0);
                if (getValue(b, c, A, x, C, COUNTER_CLOCKWISE) < 0)
                    break;
            }

            // 二分查找。
            double up = x + (0.01 * PI / 180.0), down = x, middle;
            while (fabs(up - down) > 1e-10)
            {
                middle = (up + down) / 2.0;
                if (getValue(b, c, A, middle, C, COUNTER_CLOCKWISE) > 0)
                    up = middle;
                else
                    down = middle;
            }

            // 计算距离。
            x = middle;
            finalAngle = second.angle - toDegree(x);
            if (finalAngle < 0.0)
                finalAngle += 360.0;
            finalDistance = b * sin(A) / sin(A - x);
            solutions[counter++] = (point)
            {
                finalAngle, finalDistance
            };
        }
        else
        {
            // 第二个位置在第一个位置的顺时针方向，有两种可能，一种是在观察到第一个位置后的
            // 同一个扫描周期内观察到第二个位置，另外一种情况是在下一个扫描周期内观察到第二
            // 个位置。则第三次观察可能有三种情况，能 AC 的组合是 1，3 或 2，3。
            if (first.angle > second.angle && angleDiff > 180.0)
                C = toRadian(second.angle + (360.0 - first.angle));
            else
                C = toRadian(second.angle - first.angle);

            double a = first.distance, b = second.distance;
            double c = sqrt(a * a + b * b - 2.0 * a * b * cos(C));
            double A = acos((b * b + c * c - a * a) / (2.0 * b * c));

            double x = binarySearch(b, c, A, C, CLOCKWISE_SAME_SAME_CYCLE);
            double finalAngle = second.angle + toDegree(x);
            if (finalAngle > 360.0)
                finalAngle -= 360.0;
            if (fabs(finalAngle - second.angle) < 0.02)
            {
                x = binarySearch(b, c, A, C, CLOCKWISE_SAME_NEXT_CYCLE);
                finalAngle = second.angle + toDegree(x);
                if (finalAngle > 360.0)
                    finalAngle -= 360.0;
            }
            finalDistance = b * sin(A) / sin(A - x);
            solutions[counter++] = (point)
            {
                finalAngle, finalDistance
            };

            x = binarySearch(b, c, A, C, CLOCKWISE_NEXT_NEXT_CYCLE);
            finalAngle = second.angle + toDegree(x);
            if (finalAngle > 360.0)
                finalAngle -= 360.0;
            finalDistance = b * sin(A) / sin(A - x);
            solutions[counter++] = (point)
            {
                finalAngle, finalDistance
            };
        }
    }

    sort(solutions, solutions + counter, cmp);

    for (int i = 0, printBlank = false; i < counter; i++)
    {
        if (printBlank)
            cout << " ";
        else
            printBlank = true;

        cout << fixed << setprecision(2) << solutions[i].angle << " ";
        cout << fixed << setprecision(2) << solutions[i].distance;
    }
    cout << endl;
}

int main (int argc, char *argv[])
{
    point first, second;
    while (cin >> first.angle >> first.distance,
            cin >> second.angle >> second.distance)
        calculate(first, second);

    return 0;
}
