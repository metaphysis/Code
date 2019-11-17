// PostScript Emulation
// UVa ID: 329
// Verdict: Accepted
// Submission Date: 2019-11-03
// UVa Run Time: 0.140s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

double im[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};

void multiply(double rm[3][3])
{
    double tmp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            tmp[i][j] = 0;
            for (int k = 0; k < 3; k++)
                tmp[i][j] += im[i][k] * rm[k][j];
        }
    memcpy(im, tmp, sizeof(tmp));
}

pair<double, double> restore(double x, double y)
{
    double nx = im[0][0] * x + im[0][1] * y + im[0][2];
    double ny = im[1][0] * x + im[1][1] * y + im[1][2];
    return make_pair(nx, ny);
}

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, parameter;
    double cx = 0, cy = 0;

    while (getline(cin, line), line != "*") {
        vector<string> cmd;
        istringstream iss(line);
        while (iss >> parameter) cmd.push_back(parameter);

        if (cmd.back() == "translate") {
            double tx = stod(cmd[0]);
            double ty = stod(cmd[1]);
            double rm[3][3] = {
                {1, 0, tx},
                {0, 1, ty},
                {0, 0, 1}
            };
            multiply(rm);
            cx -= tx, cy -= ty;
        } else if (cmd.back() == "rotate") {
            double alpha = stod(cmd.front()) * PI / 180.0;
            double rm[3][3] = {
                {cos(alpha), -sin(alpha), 0},
                {sin(alpha), cos(alpha), 0},
                {0, 0, 1}
            };
            multiply(rm);
            double nextx = cx * cos(alpha) + cy * sin(alpha);
            double nexty = -cx * sin(alpha) + cy * cos(alpha) ;
            cx = nextx, cy = nexty;
        } else if (cmd.back() == "scale") {
            double sx = stod(cmd[0]);
            double sy = stod(cmd[1]);
            double rm[3][3] = {
                {sx, 0, 0},
                {0, sy, 0},
                {0, 0, 1}
            };
            multiply(rm);
            cx /= sx, cy /= sy;
        } else if (cmd.back() == "moveto" || cmd.back() == "lineto") {
            cx = stod(cmd[0]);
            cy = stod(cmd[1]);
            pair<double, double> r = restore(cx, cy);
            cout << fixed << setprecision(6) << r.first << ' ';
            cout << fixed << setprecision(6) << r.second << ' ';
            cout << cmd.back() << '\n';
        } else if (cmd.back() == "rmoveto" || cmd.back() == "rlineto") {
            pair<double, double> r1 = restore(cx, cy);
            cx += stod(cmd[0]);
            cy += stod(cmd[1]);
            pair<double, double> r2 = restore(cx, cy);
            cout << fixed << setprecision(6) << (r2.first - r1.first) << ' ';
            cout << fixed << setprecision(6) << (r2.second - r1.second) << ' ';
            cout << cmd.back() << '\n';
        }
    }
    return 0;
}
