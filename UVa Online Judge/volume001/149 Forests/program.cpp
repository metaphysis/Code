// Forests
// UVa ID: 149
// Verdict: Accepted
// Submission Date: 2016-02-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265358;

struct point
{
    double x, y;
};

double diameter, x, y;
point base[4] = { {100, 100}, {0, 100}, {0, 0}, {100, 0} };
int steps[4][2] = { {100, 100}, {-100, 100}, {-100, -100}, {100, -100} };
int subSteps[8][2] =
    { {-100, 0}, {0, -100}, {100, 0}, {0, -100}, {100, 0}, {0, 100}, {-100, 0},
    {0, 100} };
double maxCos = cos(0.01 / 180 * PI);

bool isObscured(point near, point far)
{
    double a = pow(x - near.x, 2) + pow(y - near.y, 2);
    double b = pow(x - far.x, 2) + pow(y - far.y, 2);
    double c = pow(near.x - far.x, 2) + pow(near.y - far.y, 2);

    double A = asin(diameter / 2 / sqrt(a));
    double B = asin(diameter / 2 / sqrt(b));
    double cosC = (a + b - c) / (2 * sqrt(a) * sqrt(b));

    // 因为余弦的值域为[-1, 1]，故绝对值大于 1 的值取反余弦会得到一个非数值（NAN），
    // 而且题目中提到当角度大于 0.01 度时人眼才能区分，因此需要设定一个阈值。
    // 此处是关键，否则很可能 Wrong Answer。
    if (cosC >= maxCos)
        return true;

    double C = acos(cosC);
    return ((C - A - B) * 180 / PI) <= 0.01f;
}

bool isVisible(point tree, int depth, int quadrant)
{
    for (int subDepth = 0; subDepth < depth; subDepth++)
    {
        point corner =
            { base[quadrant].x + subDepth * steps[quadrant][0],
                base[quadrant].y + subDepth * steps[quadrant][1] };
        if (isObscured(corner, tree))
            return false;

        for (int j = 2 * quadrant; j < 2 * (quadrant + 1); j++)
            for (int k = 0; k < subDepth; k++)
            {
                point vertex =
                    { corner.x + subSteps[j][0] * (k + 1),
                        corner.y + subSteps[j][1] * (k + 1) };
                if (isObscured(vertex, tree))
                    return false;
            }
    }

    return true;
}

int visibleTrees()
{
    int count = 0;
    for (int depth = 0; depth <= 10; depth++)
        for (int i = 0; i < 4; i++)
        {
            point corner =
                { base[i].x + depth * steps[i][0],
                    base[i].y + depth * steps[i][1] };
            if (isVisible(corner, depth, i))
                count++;

            for (int j = 2 * i; j < 2 * (i + 1); j++)
                for (int k = 0; k < depth; k++)
                {
                    point tree =
                        { corner.x + subSteps[j][0] * (k + 1),
                            corner.y + subSteps[j][1] * (k + 1) };
                    if (isVisible(tree, depth, i))
                        count++;
                }
        }

    return count;
}

int main(int argc, char *argv[])
{
    while (cin >> diameter >> x >> y)
    {
        diameter = (int)(diameter * 100);
        x = (int)(x * 100);
        y = (int)(y * 100);

        if (diameter == 0 && x == 0 && y == 0)
            break;

        cout << visibleTrees() << endl;
    }

    return 0;
}
