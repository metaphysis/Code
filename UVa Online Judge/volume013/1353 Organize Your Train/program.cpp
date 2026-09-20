#include <bits/stdc++.h>
using namespace std;

struct Link {
    int fromLine, fromSide, toLine, toSide;
};

string encodeState(const vector<string> &lines) {
    string state;
    for (const string &line : lines) {
        state += line;
        state += '{';
    }
    return state;
}

vector<string> decodeState(const string &state, int lineCount) {
    vector<string> lines(lineCount);
    int lineIndex = 0;
    for (char car : state) {
        if (car == '{') {
            lineIndex++;
        } else {
            lines[lineIndex] += car;
        }
    }
    return lines;
}

unordered_map<string, int> getDistances(const string &startState, int lineCount, const vector<Link> &links) {
    unordered_map<string, int> distances;
    queue<string> stateQueue;
    distances[startState] = 0;
    stateQueue.push(startState);
    while (!stateQueue.empty()) {
        string currentState = stateQueue.front();
        stateQueue.pop();
        int currentDistance = distances[currentState];
        if (currentDistance == 3) continue;
        vector<string> lines = decodeState(currentState, lineCount);
        for (const Link &link : links) {
            string source = lines[link.fromLine], destination = lines[link.toLine];
            int sourceLength = source.size();
            for (int moveLength = 1; moveLength <= sourceLength; moveLength++) {
                string movedPart, remainingPart;
                if (link.fromSide == 0) {
                    movedPart = source.substr(0, moveLength);
                    remainingPart = source.substr(moveLength);
                } else {
                    movedPart = source.substr(sourceLength - moveLength);
                    remainingPart = source.substr(0, sourceLength - moveLength);
                }
                if (link.fromSide == link.toSide) reverse(movedPart.begin(), movedPart.end());
                lines[link.fromLine] = remainingPart;
                if (link.toSide == 0) lines[link.toLine] = movedPart + destination;
                else lines[link.toLine] = destination + movedPart;
                string nextState = encodeState(lines);
                if (!distances.count(nextState)) {
                    distances[nextState] = currentDistance + 1;
                    stateQueue.push(nextState);
                }
                lines[link.fromLine] = source;
                lines[link.toLine] = destination;
            }
        }
    }
    return distances;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int lineCount, linkCount;
    while (cin >> lineCount >> linkCount && (lineCount != 0 || linkCount != 0)) {
        vector<Link> links;
        bool connected[4][2][4][2] = {};
        for (int i = 0; i < linkCount; i++) {
            int firstLine, secondLine, firstSide, secondSide;
            char firstEnd, secondEnd;
            cin >> firstLine >> firstEnd >> secondLine >> secondEnd;
            firstSide = firstEnd == 'W' ? 0 : 1;
            secondSide = secondEnd == 'W' ? 0 : 1;
            if (!connected[firstLine][firstSide][secondLine][secondSide]) {
                links.push_back({firstLine, firstSide, secondLine, secondSide});
                connected[firstLine][firstSide][secondLine][secondSide] = true;
            }
            if (!connected[secondLine][secondSide][firstLine][firstSide]) {
                links.push_back({secondLine, secondSide, firstLine, firstSide});
                connected[secondLine][secondSide][firstLine][firstSide] = true;
            }
        }
        vector<string> startLines(lineCount), targetLines(lineCount);
        for (string &line : startLines) {
            cin >> line;
            if (line == "-") line.clear();
        }
        for (string &line : targetLines) {
            cin >> line;
            if (line == "-") line.clear();
        }
        string startState = encodeState(startLines), targetState = encodeState(targetLines);
        unordered_map<string, int> startDistances = getDistances(startState, lineCount, links);
        unordered_map<string, int> targetDistances = getDistances(targetState, lineCount, links);
        int answer = 7;
        for (const auto &item : startDistances) {
            auto targetIterator = targetDistances.find(item.first);
            if (targetIterator != targetDistances.end()) answer = min(answer, item.second + targetIterator->second);
        }
        cout << answer << '\n';
    }
    return 0;
}
