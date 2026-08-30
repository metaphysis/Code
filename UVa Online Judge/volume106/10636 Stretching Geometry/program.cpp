#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const ll MAX_N = 15000;
const ld PI = acosl(-1.0L);
ll prevCoprime[MAX_N + 1];
ll nextCoprime[MAX_N + 2];

ll gcd(ll a, ll b) {
    while (b != 0) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

ll extGcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll nextX, nextY;
    ll result = extGcd(b, a % b, nextX, nextY);
    x = nextY;
    y = nextX - (a / b) * nextY;
    return result;
}

ll floorDiv(ll a, ll b) {
    ll result = a / b;
    if (a < 0 && a % b != 0) result--;
    return result;
}

ll ceilDiv(ll a, ll b) {
    return -floorDiv(-a, b);
}

void buildCoprimeTables() {
    prevCoprime[0] = -1;
    for (ll i = 1; i <= MAX_N; i++) {
        if (gcd(i, MAX_N) == 1) prevCoprime[i] = i;
        else prevCoprime[i] = prevCoprime[i - 1];
    }
    nextCoprime[MAX_N + 1] = -1;
    for (ll i = MAX_N; i >= 1; i--) {
        if (gcd(i, MAX_N) == 1) nextCoprime[i] = i;
        else nextCoprime[i] = nextCoprime[i + 1];
    }
}

bool isBetterFraction(ll p1, ll q1, ll p2, ll q2) {
    if (p2 == -1) return true;
    return (__int128)q1 * p2 < (__int128)q2 * p1;
}

void updatePoint(ll p, ll q, ll &bestP, ll &bestQ) {
    if (p < 1 || q < 1 || p > MAX_N || q > MAX_N) return;
    if (gcd(p, q) != 1) return;
    if (isBetterFraction(p, q, bestP, bestQ)) {
        bestP = p;
        bestQ = q;
    }
}

void getNextPoint(ll indexX, ll indexY, ll &bestP, ll &bestQ) {
    bestP = -1;
    bestQ = -1;
    ll u, v;
    extGcd(indexX, indexY, u, v);
    ll baseP = -v;
    ll baseQ = u;
    ll lowK = max(ceilDiv(-baseP, indexX), ceilDiv(-baseQ, indexY));
    ll highK = min(floorDiv(MAX_N - baseP, indexX), floorDiv(MAX_N - baseQ, indexY));
    if (lowK <= highK) {
        ll p = baseP + indexX * highK;
        ll q = baseQ + indexY * highK;
        updatePoint(p, q, bestP, bestQ);
        return;
    }
    ll maxP = (indexX * MAX_N - 1) / indexY;
    maxP = min(maxP, MAX_N);
    if (maxP >= 1) {
        ll p = prevCoprime[maxP];
        if (p >= 1) updatePoint(p, MAX_N, bestP, bestQ);
    }
    ll minQ = (indexY * MAX_N) / indexX + 1;
    if (minQ <= MAX_N) {
        ll q = nextCoprime[minQ];
        if (q >= 1 && q <= MAX_N) updatePoint(MAX_N, q, bestP, bestQ);
    }
}

bool isValidOriginalPoint(ll x1, ll y1, ll d, ll indexX, ll indexY) {
    if (indexX < 1 || indexX > MAX_N) return false;
    if (indexY < 1 || indexY > MAX_N) return false;
    if (__gcd(indexX, indexY) != 1) return false;
    if (x1 % (d * indexX) != 0) return false;
    if (y1 % (d * indexY) != 0) return false;
    return true;
}

ll multiplyDivide(ll value, ll multiplier, ll divisor) {
    return (ll)((__int128)value * multiplier / divisor);
}

ld getAngleInDegree(ll x1, ll y1, ll x2, ll y2) {
    __int128 cross = (__int128)x1 * y2 - (__int128)y1 * x2;
    __int128 dot = (__int128)x1 * x2 + (__int128)y1 * y2;
    if (cross <= 0) return -1.0L;
    ld preciseCross = (ld)cross;
    ld preciseDot = (ld)dot;
    return atan2l(preciseCross, preciseDot) * 180.0L / PI;
}

void checkCandidate(ll x1, ll y1, ll d, ll indexX, ll indexY, ld phi, ll &answerX, ll &answerY, ld &bestDifference, bool &found) {
    if (!isValidOriginalPoint(x1, y1, d, indexX, indexY)) return;
    ll pointP, pointQ;
    getNextPoint(indexX, indexY, pointP, pointQ);
    if (pointP == -1 || pointQ == -1) return;
    ll x2 = multiplyDivide(x1, pointP, indexX);
    ll y2 = multiplyDivide(y1, pointQ, indexY);
    ld actualPhi = getAngleInDegree(x1, y1, x2, y2);
    if (actualPhi < 0.0L) return;
    ld difference = fabsl(actualPhi - phi);
    if (!found || difference < bestDifference) {
        found = true;
        bestDifference = difference;
        answerX = x2;
        answerY = y2;
    }
}

bool findAnswer(ll x1, ll y1, ll d, ll ab, ld phi, ll &answerX, ll &answerY) {
    __int128 numerator = (__int128)x1 * y1;
    __int128 denominator = (__int128)ab * d * d;
    if (numerator % denominator != 0) return false;
    ll product = (ll)(numerator / denominator);
    ld bestDifference = numeric_limits<ld>::infinity();
    bool found = false;
    for (ll i = 1; i * i <= product; i++) {
        if (product % i != 0) continue;
        ll j = product / i;
        checkCandidate(x1, y1, d, i, j, phi, answerX, answerY, bestDifference, found);
        if (i != j) checkCandidate(x1, y1, d, j, i, phi, answerX, answerY, bestDifference, found);
    }
    return found;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildCoprimeTables();
    ll x1, y1, d, ab;
    ld phi;
    while (cin >> x1 >> y1 >> d >> ab >> phi) {
        if (x1 == -1) break;
        if (y1 == 0) {
            ll x2 = x1 * MAX_N;
            ll y2 = ab * d * d / x1;
            cout << x2 << ' ' << y2 << '\n';
            continue;
        }
        if (x1 == 0) {
            ll x2 = ab * d * d / y1;
            cout << x2 << " 0\n";
            continue;
        }
        ll x2 = 0;
        ll y2 = 0;
        if (findAnswer(x1, y1, d, ab, phi, x2, y2)) cout << x2 << ' ' << y2 << '\n';
    }
    return 0;
}
