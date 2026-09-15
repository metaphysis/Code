#include <bits/stdc++.h>
using namespace std;

class Parser {
private:
    string expr;
    int pos;
    double x;
    double parseExpr() {
        double value = parseTerm();
        while (pos < (int)expr.size()) {
            if (expr[pos] == '+') {
                ++pos;
                value += parseTerm();
            } else if (expr[pos] == '-') {
                ++pos;
                value -= parseTerm();
            } else
                break;
        }
        return value;
    }
    double parseTerm() {
        double value = parseFactor();
        while (pos < (int)expr.size()) {
            if (expr[pos] == '*') {
                ++pos;
                value *= parseFactor();
            } else if (expr[pos] == '/') {
                ++pos;
                value /= parseFactor();
            } else
                break;
        }
        return value;
    }
    double parseFactor() {
        if (expr[pos] == '+') {
            ++pos;
            return parseFactor();
        }
        if (expr[pos] == '-') {
            ++pos;
            return -parseFactor();
        }
        if (expr[pos] == '(') {
            ++pos;
            double value = parseExpr();
            ++pos;
            return value;
        }
        if (expr[pos] == 'x') {
            ++pos;
            return x;
        }
        int start = pos;
        while (pos < (int)expr.size() && (isdigit(expr[pos]) || expr[pos] == '.'))
            ++pos;
        return stod(expr.substr(start, pos - start));
    }
public:
    Parser(const string &value) : expr(value), pos(0), x(0.0) {}
    double getValue(double value) {
        x = value;
        pos = 0;
        return parseExpr();
    }
};

struct Cup {
    double h, b, glassMass, glassMoment;
    Parser *radius;
    Parser *thickness;
};

double simpson(const function<double(double)> &func, double left, double right, double fLeft, double fMid, double fRight) {
    return (right - left) * (fLeft + 4.0 * fMid + fRight) / 6.0;
}

double adaptiveSimpson(const function<double(double)> &func, double left, double right, double fLeft, double fMid, double fRight, double whole, double eps, int depth) {
    double mid = (left + right) / 2.0;
    double leftMid = (left + mid) / 2.0, rightMid = (mid + right) / 2.0;
    double fLeftMid = func(leftMid), fRightMid = func(rightMid);
    double leftPart = simpson(func, left, mid, fLeft, fLeftMid, fMid);
    double rightPart = simpson(func, mid, right, fMid, fRightMid, fRight);
    if (depth <= 0 || fabs(leftPart + rightPart - whole) <= 15.0 * eps)
        return leftPart + rightPart + (leftPart + rightPart - whole) / 15.0;
    return adaptiveSimpson(func, left, mid, fLeft, fLeftMid, fMid, leftPart, eps / 2.0, depth - 1) + adaptiveSimpson(func, mid, right, fMid, fRightMid, fRight, rightPart, eps / 2.0, depth - 1);
}

double integrate(const function<double(double)> &func, double left, double right) {
    if (fabs(left - right) < 1e-12)
        return 0.0;
    double mid = (left + right) / 2.0;
    double fLeft = func(left), fMid = func(mid), fRight = func(right);
    double whole = simpson(func, left, right, fLeft, fMid, fRight);
    return adaptiveSimpson(func, left, right, fLeft, fMid, fRight, whole, 1e-10, 30);
}

double centerOfMass(const Cup &cup, double waterLevel) {
    auto waterArea = [&](double x) {
        double outerRadius = cup.radius->getValue(x), thickness = cup.thickness->getValue(x);
        double innerRadius = outerRadius - thickness;
        return innerRadius * innerRadius;
    };
    double waterMass = integrate(waterArea, cup.b, waterLevel);
    double waterMoment = integrate([&](double x) { return x * waterArea(x); }, cup.b, waterLevel);
    return (cup.glassMoment + waterMoment) / (cup.glassMass + waterMass);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double h, b;
    while (cin >> h >> b && (h != 0.0 || b != 0.0)) {
        string radiusExpr, thicknessExpr;
        cin >> radiusExpr >> thicknessExpr;
        Parser radiusParser(radiusExpr), thicknessParser(thicknessExpr);
        Cup cup;
        cup.h = h;
        cup.b = b;
        cup.radius = &radiusParser;
        cup.thickness = &thicknessParser;
        auto glassArea = [&](double x) {
            double outerRadius = radiusParser.getValue(x);
            if (x <= b)
                return outerRadius * outerRadius;
            double thickness = thicknessParser.getValue(x), innerRadius = outerRadius - thickness;
            return outerRadius * outerRadius - innerRadius * innerRadius;
        };
        auto glassMomentFunc = [&](double x) {
            return x * glassArea(x);
        };
        cup.glassMass = 2.5 * (integrate(glassArea, 0.0, b) + integrate(glassArea, b, h));
        cup.glassMoment = 2.5 * (integrate(glassMomentFunc, 0.0, b) + integrate(glassMomentFunc, b, h));
        double left = b, right = h;
        for (int i = 0; i < 100; ++i) {
            double mid1 = (2.0 * left + right) / 3.0, mid2 = (left + 2.0 * right) / 3.0;
            if (centerOfMass(cup, mid1) < centerOfMass(cup, mid2))
                right = mid2;
            else
                left = mid1;
        }
        double waterLevel = (left + right) / 2.0;
        double waterVolume = integrate([&](double x) {
            double outerRadius = radiusParser.getValue(x), thickness = thicknessParser.getValue(x);
            double innerRadius = outerRadius - thickness;
            return innerRadius * innerRadius;
        }, b, waterLevel) * acos(-1.0);
        cout << fixed << setprecision(3);
        cout << "Pour " << waterVolume / 1000.0 << " litres / " << waterLevel - b << " cm of water.\n";
    }
    return 0;
}
