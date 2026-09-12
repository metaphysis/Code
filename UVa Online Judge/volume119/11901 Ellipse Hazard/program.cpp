#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1.0);
const double eps = 1e-10;
int xOne, yOne, a, b, xTwo, yTwo, c, d, pOne, pTwo;

double evaluate(const double coe[], int degree, double x) {
    double ret = coe[degree];
    for (int i = degree - 1; i >= 0; i--)
        ret = ret * x + coe[i];
    return ret;
}

void addRoot(double roots[], int &rootCnt, double value) {
    for (int i = 0; i < rootCnt; i++)
        if (fabs(roots[i] - value) < 1e-7 * (1.0 + fabs(value)))
            return;
    roots[rootCnt++] = value;
}

void getRealRoots(const double inputCoe[], int inputDegree, double roots[], int &rootCnt) {
    double coe[5], der[4], critical[4], points[6];
    int degree = inputDegree, criticalCnt = 0, pointCnt = 0;
    double scale = 0;
    for (int i = 0; i <= inputDegree; i++)
        scale = max(scale, fabs(inputCoe[i]));
    if (scale < eps)
        return;
    for (int i = 0; i <= inputDegree; i++)
        coe[i] = inputCoe[i] / scale;
    while (degree > 0 && fabs(coe[degree]) < eps)
        degree--;
    if (degree == 0)
        return;
    if (degree == 1) {
        addRoot(roots, rootCnt, -coe[0] / coe[1]);
        return;
    }
    for (int i = 1; i <= degree; i++)
        der[i - 1] = i * coe[i];
    getRealRoots(der, degree - 1, critical, criticalCnt);
    double bound = 1;
    for (int i = 0; i < degree; i++)
        bound = max(bound, 1.0 + fabs(coe[i] / coe[degree]));
    sort(critical, critical + criticalCnt);
    points[pointCnt++] = -bound;
    for (int i = 0; i < criticalCnt; i++)
        if (critical[i] > -bound && critical[i] < bound)
            points[pointCnt++] = critical[i];
    points[pointCnt++] = bound;
    for (int i = 0; i < pointCnt; i++) {
        double value = evaluate(coe, degree, points[i]);
        if (fabs(value) < 1e-8)
            addRoot(roots, rootCnt, points[i]);
    }
    for (int i = 0; i + 1 < pointCnt; i++) {
        double left = points[i], right = points[i + 1];
        double leftValue = evaluate(coe, degree, left);
        double rightValue = evaluate(coe, degree, right);
        if (leftValue * rightValue >= 0)
            continue;
        for (int loop = 0; loop < 100; loop++) {
            double middle = (left + right) / 2;
            double middleValue = evaluate(coe, degree, middle);
            if (leftValue * middleValue <= 0) {
                right = middle;
                rightValue = middleValue;
            } else {
                left = middle;
                leftValue = middleValue;
            }
        }
        addRoot(roots, rootCnt, (left + right) / 2);
    }
}

void addAnswer(double answers[], int &answerCnt, double value) {
    for (int i = 0; i < answerCnt; i++)
        if (fabs(answers[i] - value) < 1e-6)
            return;
    answers[answerCnt++] = value;
}

int getAnswers(double answers[]) {
    double radOne = pOne * pi / 180.0, radTwo = pTwo * pi / 180.0;
    double ux = a * cos(radOne), uy = a * sin(radOne);
    double vx = -b * sin(radOne), vy = b * cos(radOne);
    double dx = xOne - xTwo, dy = yOne - yTwo;
    double cs = cos(radTwo), sn = sin(radTwo);
    double xZero = dx * cs + dy * sn, yZero = -dx * sn + dy * cs;
    double xU = ux * cs + uy * sn, yU = -ux * sn + uy * cs;
    double xV = vx * cs + vy * sn, yV = -vx * sn + vy * cs;
    double aa = xU * xU / (c * c) + yU * yU / (d * d);
    double bb = xV * xV / (c * c) + yV * yV / (d * d);
    double cc = 2 * (xU * xV / (c * c) + yU * yV / (d * d));
    double dd = 2 * (xZero * xU / (c * c) + yZero * yU / (d * d));
    double ee = 2 * (xZero * xV / (c * c) + yZero * yV / (d * d));
    double ff = xZero * xZero / (c * c) + yZero * yZero / (d * d) - 1;
    double coe[5], roots[4];
    int rootCnt = 0, answerCnt = 0;
    coe[0] = aa + dd + ff;
    coe[1] = 2 * cc + 2 * ee;
    coe[2] = -2 * aa + 4 * bb + 2 * ff;
    coe[3] = -2 * cc + 2 * ee;
    coe[4] = aa - dd + ff;
    getRealRoots(coe, 4, roots, rootCnt);
    for (int i = 0; i < rootCnt; i++) {
        double z = roots[i], t = 2 * atan(z);
        if (t < 0)
            t += 2 * pi;
        double ct = cos(t), st = sin(t);
        double px = xOne + ux * ct + vx * st;
        double py = yOne + uy * ct + vy * st;
        double value = (px - xTwo) * cs + (py - yTwo) * sn;
        double valueTwo = -(px - xTwo) * sn + (py - yTwo) * cs;
        double check = value * value / (c * c) + valueTwo * valueTwo / (d * d) - 1;
        if (fabs(check) < 1e-6)
            addAnswer(answers, answerCnt, px + py);
    }
    double qPi = aa - dd + ff;
    double maxCoe = 0;
    for (int i = 0; i < 5; i++)
        maxCoe = max(maxCoe, fabs(coe[i]));
    if (fabs(qPi) < 1e-8 * max(1.0, maxCoe)) {
        double px = xOne - ux, py = yOne - uy;
        addAnswer(answers, answerCnt, px + py);
    }
    sort(answers, answers + answerCnt);
    return answerCnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 0;
    double answers[4];
    while (cin >> xOne >> yOne >> a >> b >> pOne >> xTwo >> yTwo >> c >> d >> pTwo) {
        if (a < 0 || b < 0 || c < 0 || d < 0)
            break;
        int answerCnt = getAnswers(answers);
        cout << "Case " << ++caseId << ":\n";
        if (answerCnt == 0)
            cout << "Do_not_intersect.\n";
        else
            for (int i = 0; i < answerCnt; i++)
                cout << fixed << setprecision(10) << answers[i] << '\n';
    }
    return 0;
}
