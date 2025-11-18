// Volleyball
// UVa ID: 10933
// Verdict: Accepted
// Submission Date: 2025-11-15
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Team {
    string name;
    int wins;
    int setsWon;
    int setsLost;
    int points;
    // 默认构造函数
    Team() : wins(0), setsWon(0), setsLost(0), points(0) {}
    // 带参数的构造函数
    Team(const string& n) : name(n), wins(0), setsWon(0), setsLost(0), points(0) {}
};

void processMatch(const string& teamA, const string& teamB, const vector<pair<int, int>>& sets, map<string, Team>& teams) {
    int winA = 0, winB = 0;
    int pointsA = 0, pointsB = 0;
    
    for (auto& s : sets) {
        pointsA += s.first;
        pointsB += s.second;
        if (s.first >= 25 && s.first - s.second >= 2) {
            winA++;
        } else if (s.second >= 25 && s.second - s.first >= 2) {
            winB++;
        }
    }
    
    teams[teamA].setsWon += winA;
    teams[teamA].setsLost += winB;
    teams[teamA].points += pointsA;
    
    teams[teamB].setsWon += winB;
    teams[teamB].setsLost += winA;
    teams[teamB].points += pointsB;
    
    if (winA > winB) {
        teams[teamA].wins++;
    } else {
        teams[teamB].wins++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T && T != 0) {
        
        cin.ignore();
        map<string, Team> teamsMap;
        vector<string> teamNames;
        
        for (int i = 0; i < T; i++) {
            string name;
            getline(cin, name);
            teamsMap[name] = Team(name);
            teamNames.push_back(name);
        }
        
        int M;
        cin >> M;
        cin.ignore();
        
        for (int i = 0; i < M; i++) {
            string line;
            getline(cin, line);
            size_t dashPos = line.find('-');
            size_t colonPos = line.find(':', dashPos);
            string teamA = line.substr(0, dashPos);
            string teamB = line.substr(dashPos + 1, colonPos - dashPos - 1);
            
            string setsStr = line.substr(colonPos + 1);
            vector<pair<int, int>> sets;
            istringstream iss(setsStr);
            string setResult;
            while (iss >> setResult) {
                size_t pos = setResult.find('-');
                int a = stoi(setResult.substr(0, pos));
                int b = stoi(setResult.substr(pos + 1));
                sets.push_back({a, b});
            }
            
            processMatch(teamA, teamB, sets, teamsMap);
        }
        
        vector<Team> teams;
        for (auto& name : teamNames) {
            teams.push_back(teamsMap[name]);
        }
        
        sort(teams.begin(), teams.end(), [](const Team& a, const Team& b) {
            if (a.wins != b.wins) return a.wins > b.wins;
            int diffA = a.setsWon - a.setsLost;
            int diffB = b.setsWon - b.setsLost;
            if (diffA != diffB) return diffA > diffB;
            if (a.points != b.points) return a.points > b.points;
            return a.name < b.name;
        });
        
        for (auto& t : teams) {
            int diff = t.setsWon - t.setsLost;
            cout << t.name << right << setw(25 - t.name.length()) << t.wins;
            cout << right << setw(5) << diff;
            cout << right << setw(10) << t.points << "\n";
        }
        cout << '\n';
    }
    
    return 0;
}
