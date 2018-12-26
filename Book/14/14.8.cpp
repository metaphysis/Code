// The Closest Pair Problem （最近点对问题）
// PC/UVa IDs: 111402/10245, Popularity: A, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2017-02-25
// UVa Run Time: 0.120s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 点的最大数量。
const int MAXV = 10010;

// “无限大” 距离值，需要根据具体应用设置。
const double MAX_DIST = 1E20;

struct point
{
    double x, y;
};

double getDistance(const point& a, const point& b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
    
// 记录点的坐标数据。
point dots[MAXV];

// 分治法求最近点对距离。
double closestDistance(int *P, int Pn, int *X, int Xn, int *Y, int Yn)
{
    // 递归调用的出口，当拆分后点数小于等于3个时，使用穷举法计算最近距离。注意初始距
    // 离应设为“无限大”，“无限大”的具体值应该根据具体应用设置。
    if (Pn <= 3)
    {
        double dist = MAX_DIST;
        for (int i = 0; i < Pn - 1; i++)
            for (int j = i + 1; j < Pn; j++)
                dist = min(dist, getDistance(dots[P[i]], dots[P[j]]));
        return dist;
    }

    // 分解：把点集P划分为两个集合Pl和Pr。并得到相应的Xl，Xr，Yl，Yr。
    int Pl[Pn], Pln, Pr[Pn], Prn;
    int Xl[Pn], Xln, Xr[Pn], Xrn;
    int Yl[Pn], Yln, Yr[Pn], Yrn;

    // 标记某点是否在划分的集合Pl中。初始时，所有点不在集合Pl中。
    unordered_set<int> inPl;

    // 将数组P划分为两个数量接近的集合Pl和Pr。Pl中的所有点在线l上或在l的左侧，Pr中
    // 的所有点在线l上或在l的右侧。数组X被划分为两个数组Xl和Xr，分别包含Pl和Pr中的
    // 点，并按x坐标单调递增的顺序排序。类似的，数组Y被划分为两个数组Yl和Yr，分别包
    // 含Pl和Pr中的点，并按y坐标单调递增的顺序进行排序。对于Xl，Xr，Yl，Yr，由于参
    // 数X和Y均已排序，只需从中拆分出相应的点即可，并不需要再次排序，拆分后的数组仍
    // 保持排序的性质不变，这是获得O（nlog2n）运行时间的关键，否则若再次排序，运行
    // 时间将为O（n（log2n）^2）。
    int middle = Pn / 2;
    Pln = Xln = middle;
    for (int i = 0; i < Pln; i++)
    {
        Pl[i] = Xl[i] = X[i];
        inPl.insert(X[i]);
    }

    Prn = Xrn = (Pn - middle);
    for (int i = 0; i < Prn; i++)
        Pr[i] = Xr[i] = X[i + middle];

    // 根据某点所属集合，划分Yl和Yr。
    Yln = Yrn = 0;
    for (int i = 0; i < Yn; i++)
    {
        if (inPl.find(Y[i]) != inPl.end())
            Yl[Yln++] = Y[i];
        else
            Yr[Yrn++] = Y[i];
    }

    // 解决：把P划分为Pl和Pr后，再进行两次递归调用，一次找出Pl中的最近点对，另一次
    // 找出Pr中的最近点对。
    double distanceL = closestDistance(Pl, Pln, Xl, Xln, Yl, Yln);
    double distanceR = closestDistance(Pr, Prn, Xr, Xrn, Yr, Yrn);

    // 合并：最近点对要么是某次递归调用找出的距离为minDist的点对，要么是Pl中的一个
    // 点与Pr中的一个点组成的点对，算法确定是否存在其距离小于minDist的一个点对。
    double minDist = min(distanceL, distanceR);

    // 建立一个数组Y'，它是把数组Y中所有不在宽度为2*minDist的垂直带形区域内去掉后
    // 所得的数组。数组Y'与Y一样，是按y坐标顺序排序的。
    int tmpY[Pn], tmpYn = 0;
    for (int i = 0; i < Yn; i++)
        if (fabs(dots[Y[i]].x - dots[X[middle]].x) <= minDist)
            tmpY[tmpYn++] = Y[i];

    // 对数组Y'中的每个点p，算法试图找出Y'中距离p在minDist单位以内的点。仅需要考虑
    // 在Y'中紧随p后的7个点。算法计算出从p到这7个点的距离，并记录下Y'的所有点对中，
    // 最近点对的距离tmpDist。
    double tmpDist = MAX_DIST;
    for (int i = 0; i < tmpYn; i++)
    {
        int top = ((i + 7) < tmpYn ? (i + 7) : (tmpYn - 1));
        for (int j = i + 1; j <= top; j++)
            tmpDist = min(tmpDist, getDistance(dots[tmpY[i]], dots[tmpY[j]]));
    }

    // 如果tmpDist小于minDist，则垂直带形区域内，的确包含比根据递归调用所找出的
    // 最近距离更近的点对，于是返回该点对及其距离tmpDist。否则，就返回递归调用中
    // 发现的最近点对及其距离minDist。
    return min(minDist, tmpDist);
}

bool cmpX(int a, int b)
{
    return dots[a].x < dots[b].x;
}

bool cmpY(int a, int b)
{
    return dots[a].y < dots[b].y;
}

double getClosestDistance(int number)
{
    // 准备初始条件，注意，数组中保存的只是各个点的序号而已，并不是点的坐标，这样
    // 可以减少一些数据复制的时间，同时不影响算法的实现。
    int P[number], Pn, X[number], Xn, Y[number], Yn;

    // 初始化。
    Pn = Xn = Yn = number;
    for (int i = 0; i < number; i++)
        P[i] = X[i] = Y[i] = i;

    // 预排序，按 x 坐标和 y 坐标分别排序。
    sort(X, X + Xn, cmpX);
    sort(Y, Y + Yn, cmpY);

    // 调用分治算法。
    return closestDistance(P, Pn, X, Xn, Y, Yn);
}

int main(int ac, char *av[])
{
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
    
    cout.precision(4);
    cout.setf(ios::fixed | ios::showpoint);

    int number;
    while (cin >> number, number)
    {
        for (int i = 0; i < number; i++)
            cin >> dots[i].x >> dots[i].y;

        double minDist = sqrt(getClosestDistance(number));

        if (minDist > 10000.0)
            cout << "INFINITY" << '\n';
        else
            cout << minDist << '\n';
    }

    return 0;
}
