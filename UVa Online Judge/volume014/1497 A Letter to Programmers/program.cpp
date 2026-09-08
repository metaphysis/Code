#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    double a[4][4];
};

Matrix getUnit() {
    Matrix res;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res.a[i][j] = i == j ? 1.0 : 0.0;
    return res;
}

Matrix multiply(const Matrix &x, const Matrix &y) {
    Matrix res;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res.a[i][j] = 0.0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                res.a[i][j] += x.a[i][k] * y.a[k][j];
    return res;
}

Matrix matrixPower(Matrix base, long long exp) {
    Matrix res = getUnit();
    while (exp > 0) {
        if (exp & 1) res = multiply(base, res);
        base = multiply(base, base);
        exp >>= 1;
    }
    return res;
}

Matrix parseBlock(const vector<string> &code, int &pos) {
    Matrix res = getUnit();
    while (pos < (int)code.size()) {
        stringstream ss(code[pos]);
        string cmd;
        ss >> cmd;
        if (cmd == "end") {
            pos++;
            return res;
        }
        if (cmd == "repeat") {
            long long count;
            ss >> count;
            pos++;
            Matrix inner = parseBlock(code, pos);
            res = multiply(matrixPower(inner, count), res);
        } else {
            Matrix cur = getUnit();
            if (cmd == "translate") {
                double x, y, z;
                ss >> x >> y >> z;
                cur.a[0][3] = x;
                cur.a[1][3] = y;
                cur.a[2][3] = z;
            } else if (cmd == "scale") {
                double x, y, z;
                ss >> x >> y >> z;
                cur.a[0][0] = x;
                cur.a[1][1] = y;
                cur.a[2][2] = z;
            } else if (cmd == "rotate") {
                double x, y, z, degree;
                ss >> x >> y >> z >> degree;
                double len = sqrt(x * x + y * y + z * z);
                double ux = x / len, uy = y / len, uz = z / len;
                double pi = acos(-1.0), angle = degree * pi / 180.0;
                double c = cos(angle), s = sin(angle), t = 1.0 - c;
                cur.a[0][0] = t * ux * ux + c;
                cur.a[0][1] = t * ux * uy - s * uz;
                cur.a[0][2] = t * ux * uz + s * uy;
                cur.a[1][0] = t * ux * uy + s * uz;
                cur.a[1][1] = t * uy * uy + c;
                cur.a[1][2] = t * uy * uz - s * ux;
                cur.a[2][0] = t * ux * uz - s * uy;
                cur.a[2][1] = t * uy * uz + s * ux;
                cur.a[2][2] = t * uz * uz + c;
            }
            res = multiply(cur, res);
            pos++;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        vector<string> code;
        string line;
        int depth = 0;
        while (getline(cin, line)) {
            code.push_back(line);
            string cmd;
            stringstream ss(line);
            ss >> cmd;
            if (cmd == "repeat")
                depth++;
            else if (cmd == "end") {
                if (depth == 0)
                    break;
                depth--;
            }
        }
        int pos = 0;
        Matrix total = parseBlock(code, pos);
        cout << fixed << setprecision(2);
        for (int i = 0; i < n; i++) {
            double x, y, z;
            cin >> x >> y >> z;
            double nx = total.a[0][0] * x + total.a[0][1] * y + total.a[0][2] * z + total.a[0][3];
            double ny = total.a[1][0] * x + total.a[1][1] * y + total.a[1][2] * z + total.a[1][3];
            double nz = total.a[2][0] * x + total.a[2][1] * y + total.a[2][2] * z + total.a[2][3];
            if (fabs(nx) < 0.0005) nx = 0.0;
            if (fabs(ny) < 0.0005) ny = 0.0;
            if (fabs(nz) < 0.0005) nz = 0.0;
            cout << nx << ' ' << ny << ' ' << nz << '\n';
        }
        cout << '\n';
    }
    return 0;
}
