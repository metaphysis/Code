#include <bits/stdc++.h>
using namespace std;

bool readLab(vector<vector<pair<int, int>>> &rev, int &startRoom) {
    int doorCount, roomCount = 1, src, dst;
    char label;
    if (!(cin >> doorCount)) return false;
    vector<array<int, 3>> doors(doorCount);
    startRoom = rev.size();
    for (int i = 0; i < doorCount; ++i) {
        cin >> src >> label >> dst;
        roomCount = max(roomCount, max(src, dst));
        doors[i] = {{src - 1, dst - 1, label - 'A'}};
    }
    rev.resize(startRoom + roomCount);
    for (const auto &door : doors) rev[startRoom + door[1]].push_back({startRoom + door[0], door[2]});
    return true;
}

bool isEquivalent(const vector<vector<pair<int, int>>> &rev, int firstStart, int secondStart) {
    int roomCount = rev.size();
    vector<vector<int>> blocks(1);
    vector<int> blockId(roomCount, 0);
    queue<int> pending;
    for (int i = 0; i < roomCount; ++i) blocks[0].push_back(i);
    pending.push(0);
    while (!pending.empty()) {
        int curId = pending.front();
        pending.pop();
        vector<vector<bool>> marked(4, vector<bool>(roomCount, false));
        for (int room : blocks[curId]) {
            for (const auto &edge : rev[room]) marked[edge.second][edge.first] = true;
        }
        for (int label = 0; label < 4; ++label) {
            int blockCount = blocks.size();
            for (int i = 0; i < blockCount; ++i) {
                vector<int> yesRooms, noRooms;
                for (int room : blocks[i]) {
                    if (marked[label][room]) yesRooms.push_back(room);
                    else noRooms.push_back(room);
                }
                if (yesRooms.empty() || noRooms.empty()) continue;
                int newId = blocks.size();
                blocks[i].swap(yesRooms);
                blocks.push_back(move(noRooms));
                for (int room : blocks[newId]) blockId[room] = newId;
                pending.push(i);
                pending.push(newId);
            }
        }
    }
    return blockId[firstStart] == blockId[secondStart];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        vector<vector<pair<int, int>>> rev;
        int firstStart, secondStart;
        if (!readLab(rev, firstStart)) break;
        if (!readLab(rev, secondStart)) break;
        cout << (isEquivalent(rev, firstStart, secondStart) ? "yes" : "no") << '\n';
    }
    return 0;
}
