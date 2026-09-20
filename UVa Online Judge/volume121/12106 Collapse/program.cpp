#include <bits/stdc++.h>
using namespace std;
using Real = long double;

struct Rock {
    int x, r, t;
};

const Real eps = 1e-10L;
int rockCount, shipWidth, shipHeight, caveLen, caveHeight, fallSpeed, timeLimit;
Real maxU;
vector<Rock> rocks;
vector<Real> candidates;

void addCandidate(Real u, Real d, Real e) {
    if (!isfinite(u) || u <= 0 || u > maxU + eps) return;
    u = min(u, maxU);
    if (d + e * u < -eps) return;
    candidates.push_back(u);
}

void addRoots(Real d, Real e, Real r) {
    Real aCoef = e * e - r * r, bCoef = 2 * d * e, cCoef = d * d - r * r, delta, q;
    if (aCoef == 0) {
        if (bCoef != 0) addCandidate(-cCoef / bCoef, d, e);
        return;
    }
    delta = d * d + e * e - r * r;
    if (delta < 0) return;
    q = -d * e - copysignl(r * sqrtl(delta), d * e);
    if (q == 0) {
        addCandidate(-bCoef / (2 * aCoef), d, e);
        return;
    }
    addCandidate(q / aCoef, d, e);
    addCandidate(cCoef / q, d, e);
}

bool canEscape(Real u) {
    Real limit = (Real)fallSpeed * timeLimit - caveLen * u, factor = hypotl(1.0L, u), cur = 0;
    vector<pair<Real, Real>> intervals;
    if (limit < -eps) return false;
    limit = max(limit, 0.0L);
    intervals.reserve(rockCount);
    for (const Rock &rock : rocks) {
        Real low = (Real)fallSpeed * rock.t + caveHeight - shipHeight - rock.x * u - rock.r * factor;
        Real high = (Real)fallSpeed * rock.t + caveHeight - (rock.x - shipWidth) * u + rock.r * factor;
        intervals.emplace_back(low, high);
    }
    sort(intervals.begin(), intervals.end());
    for (const auto &interval : intervals) {
        if (interval.second <= cur + eps) continue;
        if (interval.first >= cur - eps) return true;
        cur = interval.second;
        if (cur > limit + eps) return false;
    }
    return cur <= limit + eps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNum = 0;
    cout << fixed << setprecision(2);
    while (cin >> rockCount && rockCount != 0) {
        cin >> shipWidth >> shipHeight >> caveLen >> caveHeight >> fallSpeed >> timeLimit;
        rocks.resize(rockCount);
        for (Rock &rock : rocks) cin >> rock.x >> rock.r >> rock.t;
        maxU = (Real)fallSpeed * timeLimit / caveLen;
        candidates.clear();
        candidates.push_back(maxU);
        for (int i = 0; i < rockCount; ++i) {
            addRoots((Real)fallSpeed * rocks[i].t + caveHeight - shipHeight, -rocks[i].x, rocks[i].r);
            addRoots((Real)fallSpeed * (timeLimit - rocks[i].t) - caveHeight, -(caveLen - rocks[i].x + shipWidth), rocks[i].r);
            for (int j = 0; j < rockCount; ++j) if (i != j) addRoots((Real)fallSpeed * (rocks[j].t - rocks[i].t) - shipHeight, rocks[i].x - shipWidth - rocks[j].x, rocks[i].r + rocks[j].r);
        }
        sort(candidates.begin(), candidates.end(), greater<Real>());
        Real answer = 0;
        for (Real u : candidates) {
            if (!canEscape(u)) continue;
            answer = fallSpeed / u;
            break;
        }
        cout << "Case " << ++caseNum << ": " << answer << '\n';
    }
    return 0;
}
