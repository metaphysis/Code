#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct Light {
    double x, red, green;
};

struct State {
    double time;
    int lightId;
};

bool isGreen(const Light &light, double time) {
    double period = light.red + light.green, phase = fmod(time, period);
    if (phase + eps >= light.red) return true;
    if (phase <= eps && time + eps >= period) return true;
    return false;
}

double getTravelTime(double speed, double dist) {
    return 2.0 * dist / (sqrt(speed * speed + dist) + speed);
}

bool canPass(const vector<Light> &lights, int fromId, int toId, double startTime, double waitTime, double speed) {
    double startX = fromId < 0 ? 0.0 : lights[fromId].x;
    for (int i = fromId + 1; i < toId; ++i) {
        double dist = lights[i].x - startX, passTime = startTime + waitTime + getTravelTime(speed, dist);
        if (!isGreen(lights[i], passTime)) return false;
    }
    return true;
}

double getUpperBound(const vector<Light> &lights, double dest) {
    double time = 0.0, lastX = 0.0;
    for (const Light &light : lights) {
        time += 2.0 * sqrt(light.x - lastX);
        double period = light.red + light.green, phase = fmod(time, period);
        if (phase < light.red) time += light.red - phase;
        lastX = light.x;
    }
    return time + 2.0 * sqrt(dest - lastX);
}

double solve(const vector<Light> &lights, double dest) {
    int lightCount = static_cast<int>(lights.size());
    double upperBound = getUpperBound(lights, dest), answer = upperBound;
    vector<State> states;
    states.push_back({0.0, -1});
    for (int i = 0; i < lightCount; ++i) {
        double period = lights[i].red + lights[i].green;
        for (int k = 0; ; ++k) {
            double greenTime = k * period + lights[i].red, redTime = (k + 1) * period;
            if (greenTime > upperBound + eps) break;
            states.push_back({greenTime, i});
            if (redTime <= upperBound + eps) states.push_back({redTime, i});
        }
    }
    sort(states.begin(), states.end(), [](const State &a, const State &b) {
        if (a.time != b.time) return a.time < b.time;
        return a.lightId < b.lightId;
    });
    int stateCount = static_cast<int>(states.size());
    vector<double> dp(stateCount, -1.0);
    dp[0] = 0.0;
    for (int i = 0; i < stateCount; ++i) {
        if (states[i].time >= answer) break;
        if (dp[i] < 0.0) continue;
        int fromId = states[i].lightId;
        double startX = fromId < 0 ? 0.0 : lights[fromId].x;
        double startTime = states[i].time, speed = dp[i];
        double finishTime = startTime + getTravelTime(speed, dest - startX);
        if (finishTime < answer && canPass(lights, fromId, lightCount, startTime, 0.0, speed)) answer = finishTime;
        for (int j = i + 1; j < stateCount; ++j) {
            if (states[j].time >= answer) break;
            int toId = states[j].lightId;
            if (toId <= fromId) continue;
            double duration = states[j].time - startTime, dist = lights[toId].x - startX;
            if (duration <= 0.0) continue;
            if (dist > speed * duration + 0.25 * duration * duration + eps) continue;
            double waitTime = 0.0, startSpeed = 0.0, endSpeed = 0.0;
            if (dist >= 0.25 * duration * duration) {
                startSpeed = dist / duration - 0.25 * duration;
                endSpeed = startSpeed + 0.5 * duration;
            } else {
                waitTime = duration - 2.0 * sqrt(dist);
                endSpeed = sqrt(dist);
            }
            if (endSpeed <= dp[j]) continue;
            if (canPass(lights, fromId, toId, startTime, waitTime, startSpeed)) dp[j] = endSpeed;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double dest;
    int lightCount;
    cout << fixed << setprecision(3);
    while (cin >> dest >> lightCount) {
        vector<Light> lights(lightCount);
        for (Light &light : lights) cin >> light.x >> light.red >> light.green;
        cout << solve(lights, dest) << '\n';
    }
    return 0;
}
