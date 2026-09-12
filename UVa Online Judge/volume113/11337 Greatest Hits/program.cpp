#include <bits/stdc++.h>
using namespace std;

struct Cd {
    string name;
    vector<int> songs;
    int cost;
};

vector<Cd> cds;
vector<int> usedSong;
int budget, cdCount, bestMask, bestCost, bestSongs;

bool isMoney(const string &text) {
    return !text.empty() && text[0] == '$';
}

int parseMoney(const string &text) {
    return stoi(text.substr(1));
}

bool better(int mask, int cost, int songCount) {
    int i;
    if (songCount != bestSongs)
        return songCount > bestSongs;
    if (cost != bestCost)
        return cost < bestCost;
    for (i = 0; i < cdCount; i++)
        if (((mask >> i) & 1) != ((bestMask >> i) & 1))
            return (mask >> i) & 1;
    return false;
}

void dfs(int idx, int cost, int mask, int songCount) {
    int nextSongs, song;
    if (idx == cdCount) {
        if (better(mask, cost, songCount)) {
            bestMask = mask;
            bestCost = cost;
            bestSongs = songCount;
        }
        return;
    }
    dfs(idx + 1, cost, mask, songCount);
    if (cost + cds[idx].cost <= budget) {
        nextSongs = songCount;
        for (auto song : cds[idx].songs) {
            if (usedSong[song] == 0)
                nextSongs++;
            usedSong[song]++;
        }
        dfs(idx + 1, cost + cds[idx].cost, mask | (1 << idx), nextSongs);
        for (auto song : cds[idx].songs)
            usedSong[song]--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCount, pos, i, songIdValue;
    string line;
    vector<string> lines;
    unordered_map<string, int> songId;
    getline(cin, line);
    caseCount = stoi(line);
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (!line.empty())
            lines.push_back(line);
    }
    pos = 0;
    for (i = 1; i <= caseCount; i++) {
        cds.clear();
        songId.clear();
        budget = parseMoney(lines[pos++]);
        while (pos < (int)lines.size() && !isMoney(lines[pos])) {
            Cd cd;
            cd.name = lines[pos++];
            while (pos < (int)lines.size() && !isMoney(lines[pos])) {
                auto it = songId.find(lines[pos]);
                if (it == songId.end()) {
                    songIdValue = songId.size();
                    songId[lines[pos]] = songIdValue;
                } else {
                    songIdValue = it->second;
                }
                cd.songs.push_back(songIdValue);
                pos++;
            }
            cd.cost = parseMoney(lines[pos++]);
            cds.push_back(cd);
        }
        cdCount = cds.size();
        usedSong.assign(songId.size(), 0);
        bestMask = 0;
        bestCost = 0;
        bestSongs = 0;
        dfs(0, 0, 0, 0);
        cout << "Scenario #" << i << ": " << bestSongs << '\n';
        for (int j = 0; j < cdCount; j++)
            if ((bestMask >> j) & 1)
                cout << cds[j].name << '\n';
        cout << '\n';
    }
    return 0;
}
