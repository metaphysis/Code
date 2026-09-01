#include <bits/stdc++.h>
using namespace std;

void solveLine(const string& line) {
    stringstream input(line);
    vector<string> tokens;
    string token;
    while (input >> token)
        tokens.push_back(token);
    vector<int> carIndex(tokens.size(), -1), finalPos;
    int carCount = 0;
    for (int i = 0; i < (int)tokens.size(); i++) {
        if (tokens[i] == "#")
            continue;
        carIndex[i] = carCount++;
        finalPos.push_back(i);
    }
    for (int i = 0; i < (int)tokens.size(); i++) {
        if (tokens[i] != "-" && tokens[i] != "#") {
            int distance = stoi(tokens[i]), current = carIndex[i];
            int target = current - distance;
            tokens[i] = to_string(finalPos[current] - finalPos[target]);
        }
    }
    for (int i = 0; i < (int)tokens.size(); i++) {
        if (i > 0)
            cout << ' ';
        cout << tokens[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        stringstream input(line);
        string first;
        input >> first;
        if (first == "0")
            break;
        if (!first.empty())
            solveLine(line);
    }
    return 0;
}
