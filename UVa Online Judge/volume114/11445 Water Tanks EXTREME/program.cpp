#include <bits/stdc++.h>
using namespace std;

const double waterFactor = 0.097;

int n;
vector<double> tankHeight, pipeHeight, waterHeight;

double getPressure(double level, double baseVolume, double airMass, bool isOpen) {
    if (isOpen) return 1.0;
    double airVolume = baseVolume - level;
    if (airVolume <= 0.0) return numeric_limits<double>::infinity();
    return airMass / airVolume;
}

double getNeed(double level, double baseVolume, double airMass, double otherMax, bool isOpen) {
    double pressure = getPressure(level, baseVolume, airMass, isOpen);
    return pressure + waterFactor * max(level, otherMax);
}

// 返回最终注水位置的 p + waterFactor * h。
// 当本次调用是左子区间时，注水位置始终是该区间最右侧水箱，
// 返回值可直接作为右子区间的供水条件。
double solve(int left, int right, int cur, double initialPressure, double supplyHead) {
    bool isOpen = (left == 1);
    double initialAirVolume = 0.0;
    for (int i = left; i <= right; ++i) initialAirVolume += tankHeight[i] - waterHeight[i];
    // 区间已经全部充满水，没有需要继续压缩的空气。
    // 这种情况下，水可以传递传入的供水压力。
    if (initialAirVolume <= 0.0) return supplyHead;
    double airMass = initialPressure * initialAirVolume;
    while (true) {
        double airVolume = 0.0, otherMax = 0.0;
        for (int i = left; i <= right; ++i) {
            airVolume += tankHeight[i] - waterHeight[i];
            if (i != cur) otherMax = max(otherMax, waterHeight[i]);
        }
        // 当前水箱水位为 x 时，区间空气体积为 baseVolume - x。
        double baseVolume = airVolume + waterHeight[cur];
        double target = tankHeight[cur];
        if (cur > left) target = min(target, pipeHeight[cur - 1]);
        if (cur < right) target = min(target, pipeHeight[cur]);
        if (getNeed(target, baseVolume, airMass, otherMax, isOpen) > supplyHead) {
            double low = waterHeight[cur], high = target;
            for (int step = 0; step < 100; ++step) {
                double mid = (low + high) / 2.0;
                if (getNeed(mid, baseVolume, airMass, otherMax, isOpen) <= supplyHead) low = mid;
                else high = mid;
            }
            waterHeight[cur] = (low + high) / 2.0;
            double finalPressure = getPressure(waterHeight[cur], baseVolume, airMass, isOpen);
            // 关键：返回当前水面实际能向后方提供的压力条件。
            return finalPressure + waterFactor * waterHeight[cur];
        }
        waterHeight[cur] = target;
        // 单个水箱能够达到顶部，说明已经充满。
        if (left == right) return supplyHead;
        // 等高事件仍然优先向右注水。
        if (cur < right && target == pipeHeight[cur]) {
            ++cur;
            continue;
        }
        if (cur > left && target == pipeHeight[cur - 1]) {
            double nextPressure = getPressure(target, baseVolume, airMass, isOpen);
            // 先求出左侧最终状态，以及它能向右侧提供的压力。
            double rightSupplyHead = solve(left, cur - 1, cur - 1, nextPressure, supplyHead);
            // 右侧使用左侧实际提供的压力，不能继续沿用 supplyHead。
            return solve(cur, right, cur, nextPressure, rightSupplyHead);
        }
        return supplyHead;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 1;
    while (cin >> n && n != 0) {
        tankHeight.assign(n + 2, 0.0);
        pipeHeight.assign(n + 2, 0.0);
        waterHeight.assign(n + 2, 0.0);
        for (int i = 1; i <= n; ++i) cin >> tankHeight[i];
        for (int i = 1; i < n; ++i) cin >> pipeHeight[i];
        double initialSupplyHead = 1.0 + waterFactor * tankHeight[1];
        solve(1, n, 1, 1.0, initialSupplyHead);
        double answer = 0.0;
        for (int i = 1; i <= n; ++i) answer += waterHeight[i];
        cout << "Case " << caseId++ << ": " << fixed << setprecision(3) << answer << "\n\n";
    }
    return 0;
}
