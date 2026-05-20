#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<double> ratio = {
        // 1个等边三角形：三角形的边为斜边，正方形的边为直角边，两条边夹角为15度，根据三角函数可以计算
        1.0 / cos(15.0 / 180.0 * M_PI),
        // 2个等边三角形：高的两倍与正方形的对角线长度相等
        sqrt(6) / 3,
        // 3个等边三角形:令三角形的高为h，正方形的边长为S，根据几何关系可以得到：sqrt(2) * S - h = sqrt(2) * h
        2.0 * sqrt(2) / (sqrt(6) + sqrt(3)),
        // 4个等边三角形：令三角形的边长为a，正方形的边长为S，可以得到：(S - a) / (a / 2) = 2 / sqrt(3)
        sqrt(3) / (1 + sqrt(3)),
        // 5个等边三角形：
        //0.5 * (18 + 12 * sqrt(3) - sqrt(pow(18 + 12 * sqrt(3), 2) - 4 * (11 + 6 * sqrt(3)) * (8 + 4 * sqrt(3)))) / (11 + 6 * sqrt(3)),
        //(2 + sqrt(3)) / (5 + sqrt(3)),
        0.55457915731485700607,
        // 6个等边三角形：令三角形的边长为a，正方形的边长为S，根据面积关系，可以得到：3 * sqrt(3) * a - (1 + sqrt(3)) * S = 0
        (1.0 + sqrt(3)) / (3 * sqrt(3)),
        // 7个等边三角形：令三角形的边长为a，正方形的边长为S，根据边长关系，可以得到：a = (3 + sqrt(3)) / (3 + 4 * sqrt(3)) * S
        (3 + sqrt(3)) / (3 + 4 * sqrt(3))
    };

    double S;
    while (cin >> S) {
        cout << fixed << setprecision(10);
        for (int i = 0; i < 7; i++) cout << ratio[i] * S << " \n"[i == 6];
    }
    return 0;
}
