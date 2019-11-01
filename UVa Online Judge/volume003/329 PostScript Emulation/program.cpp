// PostScript Emulation
// UVa ID: 329
// Verdict: Accepted
// Submission Date: 2019-11-01
// UVa Run Time: 0.150s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

double im[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};

double getValueOfMatrix(double a[3][3])
{
    double v = 0;
    v += a[0][0] * a[1][1] * a[2][2];
    v += a[0][1] * a[1][2] * a[2][0];
    v += a[0][2] * a[1][0] * a[2][1];
    v -= a[0][2] * a[1][1] * a[2][0];
    v -= a[0][1] * a[1][0] * a[2][2];
    v -= a[0][0] * a[1][2] * a[2][1];
    return v;
}

void updateInverseMatrix(double a[3][3])
{
    double A = getValueOfMatrix(a);
    double b[4];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            double sign = 1;
            if ((i + j) % 2) sign = -1;
            int idx = 0;
            for (int ii = 0; ii < 3; ii++)
                for (int jj = 0; jj < 3; jj++)
                {
                    if (ii == i || jj == j) continue;
                    b[idx++] = a[ii][jj];
                }
            im[i][j] = sign * (b[0] * b[3] - b[1] * b[2]) / A;
        }
    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++)
            swap(im[i][j], im[j][i]);
}

void multiply(double a[3][3], double b[3][3])
{
    double c[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < 3; k++)
                c[i][j] += b[i][k] * a[k][j];
        }
    memcpy(a, c, sizeof(c));
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
    double a[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}    
    };

    while (getline(cin, line), line != "*")
    {
        vector<string> parameters;
        istringstream iss(line);
        while (iss >> parameter) parameters.push_back(parameter);

        if (parameters.back() == "rotate")
        {
            double alpha = stod(parameters.front()) * PI / 180.0;
            double b[3][3] = {
                {cos(alpha), -sin(alpha), 0},
                {sin(alpha), cos(alpha), 0},
                {0, 0, 1}
            };
            multiply(b, im);
            //updateInverseMatrix(a);
            double nextx = cx * cos(alpha) + cy * sin(alpha);
            double nexty = -cx * sin(alpha) + cy * cos(alpha) ;
            cx = nextx, cy = nexty;
        }
        else if (parameters.back() == "translate")
        {
            double tx = stod(parameters[0]);
            double ty = stod(parameters[1]);
            double b[3][3] = {
                {1, 0, tx},
                {0, 1, ty},
                {0, 0, 1}
            };
            multiply(b, im);
            //updateInverseMatrix(a);
            cx -= tx, cy -= ty;
        }
        else if (parameters.back() == "scale")
        {
            double sx = stod(parameters[0]);
            double sy = stod(parameters[1]);
            double b[3][3] = {
                {sx, 0, 0},
                {0, sy, 0},
                {0, 0, 1}
            };
            multiply(b, im);
            //updateInverseMatrix(a);
            cx /= sx, cy /= sy;
        }
        else if (parameters.back() == "moveto" || parameters.back() == "lineto")
        {
            cx = stod(parameters[0]);
            cy = stod(parameters[1]);
            pair<double, double> r = restore(cx, cy);
            cout << fixed << setprecision(6) << r.first << ' ';
            cout << fixed << setprecision(6) << r.second << ' ';
            cout << parameters.back() << '\n';
            
        }
        else if (parameters.back() == "rmoveto" || parameters.back() == "rlineto")
        {
            pair<double, double> r1 = restore(cx, cy);
            cx += stod(parameters[0]);
            cy += stod(parameters[1]);
            pair<double, double> r2 = restore(cx, cy);
            cout << fixed << setprecision(6) << (r2.first - r1.first) << ' ';
            cout << fixed << setprecision(6) << (r2.second - r1.second) << ' ';
            cout << parameters.back() << '\n';
        }
    }

    return 0;
}
