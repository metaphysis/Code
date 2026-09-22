#include <bits/stdc++.h>
using namespace std;

using Time = long long;

struct Cut {
    Time startTime, endTime;
};

struct Block {
    Time startTime, endTime;
    vector<string> lines;
};

Time parseTime(const string &str) {
    Time hour = stoll(str.substr(0, 2)), minute = stoll(str.substr(3, 2)), second = stoll(str.substr(6, 2)), milli = stoll(str.substr(9, 3));
    return ((hour * 60 + minute) * 60 + second) * 1000 + milli;
}

string formatTime(Time value) {
    Time hour = value / 3600000, minute = value / 60000 % 60, second = value / 1000 % 60, milli = value % 1000;
    ostringstream out;
    out << setfill('0') << setw(2) << hour << ':' << setw(2) << minute << ':' << setw(2) << second << ',' << setw(3) << milli;
    return out.str();
}

bool readLine(string &line) {
    if (!getline(cin, line)) return false;
    if (!line.empty() && line.back() == '\r') line.pop_back();
    return true;
}

bool readNonEmpty(string &line) {
    while (readLine(line)) if (!line.empty()) return true;
    return false;
}

void addBlock(vector<Block> &blocks, Time startTime, Time endTime, const vector<string> &lines) {
    if (startTime > endTime) return;
    if (!blocks.empty() && blocks.back().lines == lines && startTime == blocks.back().endTime + 1) blocks.back().endTime = endTime;
    else blocks.push_back({startTime, endTime, lines});
}

void processBlock(const Block &block, const vector<Cut> &cuts, Time shift, vector<Block> &blocks) {
    Time cur = block.startTime, endTime = block.endTime, removed = 0;
    for (const Cut &cut : cuts) {
        if (cut.endTime < cur) {
            removed += cut.endTime - cut.startTime + 1;
            continue;
        }
        if (cut.startTime > endTime) break;
        if (cur < cut.startTime) addBlock(blocks, cur - removed + shift, cut.startTime - 1 - removed + shift, block.lines);
        cur = cut.endTime + 1;
        removed += cut.endTime - cut.startTime + 1;
        if (cur > endTime) break;
    }
    if (cur <= endTime) addBlock(blocks, cur - removed + shift, endTime - removed + shift, block.lines);
}

void splitBlocks(const vector<Block> &blocks, const vector<Time> &bDur, vector<vector<Block>> &result) {
    int bCount = static_cast<int>(bDur.size());
    vector<Time> border(bCount + 1, 0);
    for (int i = 0; i < bCount; ++i) border[i + 1] = border[i] + bDur[i];
    for (const Block &block : blocks) {
        for (int i = 0; i < bCount; ++i) {
            Time startTime = max(block.startTime, border[i]), endTime = min(block.endTime, border[i + 1] - 1);
            if (startTime <= endTime) addBlock(result[i], startTime - border[i], endTime - border[i], block.lines);
        }
    }
}

void printFiles(const vector<vector<Block>> &files) {
    for (const vector<Block> &blocks : files) {
        int index = 1;
        for (const Block &block : blocks) {
            cout << index++ << '\n';
            cout << formatTime(block.startTime) << " --> " << formatTime(block.endTime) << '\n';
            for (const string &line : block.lines) cout << line << '\n';
            cout << '\n';
        }
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line, startStr, endStr, arrow;
    while (readNonEmpty(line)) {
        int bCount = stoi(line), cutCount, sCount;
        vector<Time> bDur(bCount), sDur;
        Time bAd, sAd, offset = 0, shift;
        for (int i = 0; i < bCount; ++i) {
            readNonEmpty(line);
            bDur[i] = parseTime(line);
        }
        readNonEmpty(line);
        bAd = parseTime(line);
        readNonEmpty(line);
        cutCount = stoi(line);
        vector<Cut> cuts(cutCount);
        for (int i = 0; i < cutCount; ++i) {
            readNonEmpty(line);
            istringstream in(line);
            in >> startStr >> endStr;
            cuts[i] = {parseTime(startStr), parseTime(endStr)};
        }
        sort(cuts.begin(), cuts.end(), [](const Cut &left, const Cut &right) {
            return left.startTime < right.startTime;
        });
        readNonEmpty(line);
        sCount = stoi(line);
        sDur.resize(sCount);
        for (int i = 0; i < sCount; ++i) {
            readNonEmpty(line);
            sDur[i] = parseTime(line);
        }
        readNonEmpty(line);
        sAd = parseTime(line);
        shift = bAd - sAd;
        vector<Block> blocks;
        for (int i = 0; i < sCount; ++i) {
            while (readNonEmpty(line)) {
                if (stoi(line) == 0) break;
                readNonEmpty(line);
                istringstream in(line);
                in >> startStr >> arrow >> endStr;
                Block block;
                block.startTime = parseTime(startStr) + offset;
                block.endTime = parseTime(endStr) + offset;
                while (readLine(line) && !line.empty()) block.lines.push_back(line);
                processBlock(block, cuts, shift, blocks);
            }
            offset += sDur[i];
        }
        vector<vector<Block>> result(bCount);
        splitBlocks(blocks, bDur, result);
        printFiles(result);
    }
    return 0;
}
