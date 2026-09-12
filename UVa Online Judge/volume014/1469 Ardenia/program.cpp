// Ardenia 
// UVa ID: 1469
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.100s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y, z;
};

struct Fraction {
    __int128 num, den;
};

__int128 absValue(__int128 value) {
    return value < 0 ? -value : value;
}

__int128 gcdValue(__int128 a, __int128 b) {
    a = absValue(a);
    b = absValue(b);
    while (b != 0) {
        __int128 temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

Fraction makeFraction(__int128 num, __int128 den) {
    if (den < 0) {
        num = -num;
        den = -den;
    }
    __int128 divisor = gcdValue(num, den);
    return {num / divisor, den / divisor};
}

Point subtractPoint(Point a, Point b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Point crossProduct(Point a, Point b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

__int128 dotProduct(Point a, Point b) {
    return (__int128)a.x * b.x + (__int128)a.y * b.y + (__int128)a.z * b.z;
}

__int128 lengthSquare(Point a) {
    return dotProduct(a, a);
}

Fraction pointSegmentDistance(Point point, Point first, Point second) {
    Point direction = subtractPoint(second, first);
    Point offset = subtractPoint(point, first);
    __int128 projection = dotProduct(offset, direction);
    __int128 directionLength = lengthSquare(direction);
    if (projection <= 0) return makeFraction(lengthSquare(offset), 1);
    if (projection >= directionLength) return makeFraction(lengthSquare(subtractPoint(point, second)), 1);
    Point cross = crossProduct(offset, direction);
    return makeFraction(lengthSquare(cross), directionLength);
}

bool lessFraction(Fraction first, Fraction second) {
    return first.num * second.den < second.num * first.den;
}

void updateAnswer(Fraction &answer, Fraction candidate) {
    if (lessFraction(candidate, answer)) answer = candidate;
}

string toString(__int128 value) {
    if (value == 0) return "0";
    bool negative = value < 0;
    if (negative) value = -value;
    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    if (negative) result.push_back('-');
    reverse(result.begin(), result.end());
    return result;
}

Fraction segmentDistance(Point firstA, Point secondA, Point firstB, Point secondB) {
    Fraction answer = pointSegmentDistance(firstA, firstB, secondB);
    updateAnswer(answer, pointSegmentDistance(secondA, firstB, secondB));
    updateAnswer(answer, pointSegmentDistance(firstB, firstA, secondA));
    updateAnswer(answer, pointSegmentDistance(secondB, firstA, secondA));
    Point directionA = subtractPoint(secondA, firstA);
    Point directionB = subtractPoint(secondB, firstB);
    Point offset = subtractPoint(firstA, firstB);
    __int128 aa = dotProduct(directionA, directionA), ab = dotProduct(directionA, directionB), bb = dotProduct(directionB, directionB);
    __int128 aw = dotProduct(offset, directionA), bw = dotProduct(offset, directionB);
    __int128 determinant = aa * bb - ab * ab;
    if (determinant != 0) {
        __int128 parameterA = ab * bw - bb * aw;
        __int128 parameterB = aa * bw - ab * aw;
        if (parameterA >= 0 && parameterA <= determinant && parameterB >= 0 && parameterB <= determinant) {
            Point cross = crossProduct(directionA, directionB);
            __int128 distance = dotProduct(cross, offset);
            updateAnswer(answer, makeFraction(distance * distance, determinant));
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        Point firstA, secondA, firstB, secondB;
        cin >> firstA.x >> firstA.y >> firstA.z >> secondA.x >> secondA.y >> secondA.z;
        cin >> firstB.x >> firstB.y >> firstB.z >> secondB.x >> secondB.y >> secondB.z;
        Fraction answer = segmentDistance(firstA, secondA, firstB, secondB);
        cout << toString(answer.num) << ' ' << toString(answer.den) << '\n';
    }
    return 0;
}
