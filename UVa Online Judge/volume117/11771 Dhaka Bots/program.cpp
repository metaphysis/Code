#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const ld pi = acosl(-1.0L), tau = 2 * pi, epsTime = 1e-9L;

struct Axis {
    ld a, u, c, s;
};

struct Bound {
    ld a, b, c;
    bool isLower;
};

struct Solver {
    ld halfSize, omega, period;
    vector<Axis> axes;
    vector<Bound> bounds;
    vector<ld> cuts;
    ld getValue(const Bound &bound, ld phase) {
        return bound.a * cosl(phase) + bound.b * sinl(phase) + bound.c - phase / omega;
    }

    ld normalize(ld phase) {
        phase = fmodl(phase, tau);
        if (phase < 0) phase += tau;
        return phase;
    }

    void addRoots(ld a, ld b, ld c) {
        ld radius = hypotl(a, b);
        if (radius == 0 || fabsl(c) > radius) return;
        ld value = max(-1.0L, min(1.0L, -c / radius));
        ld base = atan2l(b, a), angle = acosl(value);
        cuts.push_back(normalize(base - angle));
        cuts.push_back(normalize(base + angle));
    }

    bool clipLinear(ld a, ld u, ld &left, ld &right) {
        if (u == 0) return fabsl(a) < halfSize;
        ld first = (-halfSize - a) / u, last = (halfSize - a) / u;
        if (first > last) swap(first, last);
        left = max(left, first);
        right = min(right, last);
        return left < right;
    }

    bool validStatic(ld phase) {
        ld cosValue = cosl(phase), sinValue = sinl(phase);
        for (const Axis &axis : axes) {
            if (axis.u == 0 && fabsl(axis.a - axis.c * cosValue - axis.s * sinValue) >= halfSize) return false;
        }
        return true;
    }

    bool clipBound(const Bound &bound, ld target, ld &left, ld &right) {
        ld sign = bound.isLower ? 1 : -1;
        ld leftValue = sign * (getValue(bound, left) - target);
        ld rightValue = sign * (getValue(bound, right) - target);
        if (leftValue >= 0 && rightValue >= 0) return false;
        if (leftValue < 0 && rightValue < 0) return true;
        ld low = left, high = right;
        for (int step = 0; step < 65; ++step) {
            ld middle = (low + high) / 2;
            if (middle == low || middle == high) break;
            ld middleValue = sign * (getValue(bound, middle) - target);
            if ((middleValue < 0) == (leftValue < 0)) low = middle;
            else high = middle;
        }
        ld root = (low + high) / 2;
        if (leftValue < 0) right = root;
        else left = root;
        return left < right;
    }

    bool validCollision(ld phase, ld cycleTime) {
        ld time = cycleTime + phase / omega;
        ld cosValue = cosl(phase), sinValue = sinl(phase);
        for (const Axis &axis : axes) {
            ld distance = axis.a + axis.u * time - axis.c * cosValue - axis.s * sinValue;
            if (fabsl(distance) >= halfSize) return false;
        }
        return true;
    }

    ld solve(ld sizeA, ld xA, ld yA, ld vx, ld vy, ld sizeB, ld xB, ld yB, ld cx, ld cy, ld speed) {
        halfSize = (sizeA + sizeB) / 2;
        ld dx = xB - cx, dy = yB - cy, radius = hypotl(dx, dy);
        if (radius == 0 || speed == 0) {
            ld left = 0, right = 1e100L;
            if (!clipLinear(xA - xB, vx, left, right)) return -1;
            if (!clipLinear(yA - yB, vy, left, right)) return -1;
            return right - left > epsTime ? left : -1;
        }
        omega = speed / radius;
        period = tau / omega;
        axes = {{xA - cx, vx, dx, -dy}, {yA - cy, vy, dy, dx}};
        bounds.clear();
        cuts = {0, tau};
        for (const Axis &axis : axes) {
            if (axis.u == 0) {
                addRoots(axis.c, axis.s, -halfSize - axis.a);
                addRoots(axis.c, axis.s, halfSize - axis.a);
            } else {
                ld first = (-halfSize - axis.a) / axis.u;
                ld last = (halfSize - axis.a) / axis.u;
                if (first > last) swap(first, last);
                bounds.push_back({axis.c / axis.u, axis.s / axis.u, first, true});
                bounds.push_back({axis.c / axis.u, axis.s / axis.u, last, false});
            }
        }
        for (const Bound &bound : bounds) addRoots(bound.b, -bound.a, -1 / omega);
        for (int i = 0; i < (int)bounds.size(); ++i) {
            for (int j = i + 1; j < (int)bounds.size(); ++j) {
                addRoots(bounds[i].a - bounds[j].a, bounds[i].b - bounds[j].b, bounds[i].c - bounds[j].c);
            }
        }
        sort(cuts.begin(), cuts.end());
        cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());
        ld answer = -1;
        for (int i = 0; i + 1 < (int)cuts.size(); ++i) {
            ld left = cuts[i], right = cuts[i + 1], middle = (left + right) / 2;
            if (right <= left || !validStatic(middle)) continue;
            if (bounds.empty()) return left / omega;
            int lowerId = -1, upperId = -1;
            ld lowerValue = -1e100L, upperValue = 1e100L;
            for (int j = 0; j < (int)bounds.size(); ++j) {
                ld value = getValue(bounds[j], middle);
                if (bounds[j].isLower) {
                    if (value > lowerValue) {
                        lowerValue = value;
                        lowerId = j;
                    }
                } else if (value < upperValue) {
                    upperValue = value;
                    upperId = j;
                }
            }
            if (lowerValue >= upperValue) continue;
            ld minLower = min(getValue(bounds[lowerId], left), getValue(bounds[lowerId], right));
            ld maxUpper = max(getValue(bounds[upperId], left), getValue(bounds[upperId], right));
            if (maxUpper <= 0 || minLower >= maxUpper) continue;
            long long firstCycle = max(0LL, (long long)floorl(minLower / period));
            for (int offset = 0; offset < 3; ++offset) {
                long long cycle = firstCycle + offset;
                ld cycleTime = cycle * period;
                if (cycleTime > maxUpper) break;
                if (answer >= 0 && cycleTime + left / omega >= answer) break;
                ld phaseLeft = left, phaseRight = right;
                bool valid = true;
                for (const Bound &bound : bounds) {
                    if (!clipBound(bound, cycleTime, phaseLeft, phaseRight)) {
                        valid = false;
                        break;
                    }
                }
                if (!valid || (phaseRight - phaseLeft) / omega <= epsTime) continue;
                if (!validCollision((phaseLeft + phaseRight) / 2, cycleTime)) continue;
                ld time = cycleTime + phaseLeft / omega;
                if (answer < 0 || time < answer) answer = time;
                break;
            }
        }
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(6);
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        ld sizeA, xA, yA, vx, vy, sizeB, xB, yB, cx, cy, speed;
        cin >> sizeA >> xA >> yA >> vx >> vy;
        cin >> sizeB >> xB >> yB >> cx >> cy >> speed;
        Solver solver;
        ld answer = solver.solve(sizeA, xA, yA, vx, vy, sizeB, xB, yB, cx, cy, speed);
        cout << "Case " << caseId << ": ";
        if (answer < 0) cout << "never\n";
        else cout << answer << '\n';
    }
    return 0;
}
