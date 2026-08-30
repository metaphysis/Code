#include <bits/stdc++.h>
using namespace std;

const int rows = 7, cols = 21, pixelCount = 58, segmentCount = 30;
const int digitMask[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
const int baseCol[4] = {0, 5, 12, 17};

struct Pixel {
    int row, col, segment;
    Pixel(int r, int c, int s) : row(r), col(c), segment(s) {}
};

bool isOn(int digit, int segment) {
    if (digit == -1) return false;
    return ((digitMask[digit] >> segment) & 1) != 0;
}

bool expectedState(int start, int frame, int segment) {
    int current = (start + frame) % 1440, hour = current / 60, minute = current % 60;
    int digits[4] = {hour >= 10 ? hour / 10 : -1, hour % 10, minute / 10, minute % 10};
    if (segment < 28) return isOn(digits[segment / 7], segment % 7);
    return true;
}

vector<Pixel> buildPixels() {
    vector<Pixel> pixels;
    pixels.reserve(pixelCount);
    for (int digitIndex = 0; digitIndex < 4; ++digitIndex) {
        int left = baseCol[digitIndex], segmentBase = digitIndex * 7;
        pixels.push_back({0, left + 1, segmentBase + 0});
        pixels.push_back({0, left + 2, segmentBase + 0});
        pixels.push_back({1, left + 3, segmentBase + 1});
        pixels.push_back({2, left + 3, segmentBase + 1});
        pixels.push_back({4, left + 3, segmentBase + 2});
        pixels.push_back({5, left + 3, segmentBase + 2});
        pixels.push_back({6, left + 1, segmentBase + 3});
        pixels.push_back({6, left + 2, segmentBase + 3});
        pixels.push_back({4, left, segmentBase + 4});
        pixels.push_back({5, left, segmentBase + 4});
        pixels.push_back({1, left, segmentBase + 5});
        pixels.push_back({2, left, segmentBase + 5});
        pixels.push_back({3, left + 1, segmentBase + 6});
        pixels.push_back({3, left + 2, segmentBase + 6});
    }
    pixels.push_back({2, 10, 28});
    pixels.push_back({4, 10, 29});
    return pixels;
}

bool readFrame(vector<string> &frame) {
    frame.clear();
    string line;
    while (true) {
        if (!getline(cin, line)) return false;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.find_first_not_of(" \t") != string::npos) break;
    }
    if ((int)line.size() < cols) return false;
    frame.push_back(line.substr(0, cols));
    for (int row = 1; row < rows; ++row) {
        if (!getline(cin, line)) return false;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if ((int)line.size() < cols) return false;
        frame.push_back(line.substr(0, cols));
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const vector<Pixel> pixels = buildPixels();
    int n;
    while (cin >> n) {
        string rest;
        getline(cin, rest);
        vector<vector<string>> image(n, vector<string>(rows));
        bool inputOk = true;
        for (int frame = 0; frame < n; ++frame) {
            vector<string> currentFrame;
            if (!readFrame(currentFrame)) {
                inputOk = false;
                break;
            }
            image[frame] = currentFrame;
        }
        if (!inputOk) break;
        bool possible[pixelCount][3] = {};
        bool hasValidStart = false;
        for (int start = 0; start < 1440; ++start) {
            bool validStart = true, currentPossible[pixelCount][3] = {};
            for (int pixelIndex = 0; pixelIndex < pixelCount; ++pixelIndex) {
                const Pixel &pixel = pixels[pixelIndex];
                bool canBeAlwaysOff = true, canBeAlwaysOn = true, canBeWorking = true;
                for (int frame = 0; frame < n; ++frame) {
                    bool expected = expectedState(start, frame, pixel.segment), actual = image[frame][pixel.row][pixel.col] == 'X';
                    if (actual) canBeAlwaysOff = false;
                    if (!actual) canBeAlwaysOn = false;
                    if (actual != expected) canBeWorking = false;
                }
                if (!canBeAlwaysOff && !canBeAlwaysOn && !canBeWorking) {
                    validStart = false;
                    break;
                }
                currentPossible[pixelIndex][0] = canBeAlwaysOff;
                currentPossible[pixelIndex][1] = canBeAlwaysOn;
                currentPossible[pixelIndex][2] = canBeWorking;
            }
            if (!validStart) continue;
            hasValidStart = true;
            for (int pixelIndex = 0; pixelIndex < pixelCount; ++pixelIndex)
                for (int state = 0; state < 3; ++state)
                    possible[pixelIndex][state] = possible[pixelIndex][state] || currentPossible[pixelIndex][state];
        }
        if (!hasValidStart) {
            cout << "impossible\n";
            continue;
        }
        vector<string> answer(rows, string(cols, '.'));
        const char stateChar[3] = {'0', '1', 'W'};
        for (int pixelIndex = 0; pixelIndex < pixelCount; ++pixelIndex) {
            int stateCount = 0;
            char result = '?';
            for (int state = 0; state < 3; ++state) {
                if (possible[pixelIndex][state]) {
                    ++stateCount;
                    result = stateChar[state];
                }
            }
            if (stateCount != 1) result = '?';
            const Pixel &pixel = pixels[pixelIndex];
            answer[pixel.row][pixel.col] = result;
        }
        for (const string &line : answer) cout << line << '\n';
    }
    return 0;
}
