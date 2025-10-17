// Euro 2004
// UVa ID: 917
// Verdict: Accepted
// Submission Date: 2025-10-18
// UVa Run Time: 1.270s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

struct Team {
    string name;
    int points = 0;
    int goals_scored = 0;
    int goals_conceded = 0;
    int wins = 0;

    Team() = default;
    Team(const string& n) : name(n) {}

    int goal_diff() const {
        return goals_scored - goals_conceded;
    }
};

struct Game {
    string team1, team2;
    int goals1, goals2;
};

vector<Game> games;

bool team_compare(const Team& a, const Team& b) {
    if (a.points != b.points) return a.points > b.points;
    if (a.goal_diff() != b.goal_diff()) return a.goal_diff() > b.goal_diff();
    if (a.wins != b.wins) return a.wins > b.wins;
    if (a.goals_scored != b.goals_scored) return a.goals_scored > b.goals_scored;
    return a.name < b.name;
}

bool teams_equal(const Team& a, const Team& b) {
    return a.points == b.points &&
           a.goal_diff() == b.goal_diff() &&
           a.wins == b.wins &&
           a.goals_scored == b.goals_scored;
}

void compute_subleague(const vector<string>& team_names, map<string, Team>& sub_teams) {
    sub_teams.clear();
    for (const auto& name : team_names) {
        sub_teams[name] = Team(name);
    }

    for (const auto& g : games) {
        bool t1_in = find(team_names.begin(), team_names.end(), g.team1) != team_names.end();
        bool t2_in = find(team_names.begin(), team_names.end(), g.team2) != team_names.end();
        if (t1_in && t2_in) {
            Team& t1 = sub_teams[g.team1];
            Team& t2 = sub_teams[g.team2];
            
            t1.goals_scored += g.goals1;
            t1.goals_conceded += g.goals2;
            t2.goals_scored += g.goals2;
            t2.goals_conceded += g.goals1;

            if (g.goals1 > g.goals2) {
                t1.points += 3;
                t1.wins++;
            } else if (g.goals1 < g.goals2) {
                t2.points += 3;
                t2.wins++;
            } else {
                t1.points++;
                t2.points++;
            }
        }
    }
}

vector<vector<string>> rank_teams_grouped(const vector<string>& team_names) {
    if (team_names.size() == 1) {
        return {team_names};
    }

    map<string, Team> sub_teams;
    compute_subleague(team_names, sub_teams);

    vector<Team> sub_vec;
    for (const auto& name : team_names) {
        sub_vec.push_back(sub_teams[name]);
    }
    sort(sub_vec.begin(), sub_vec.end(), team_compare);

    vector<vector<string>> result;
    for (size_t i = 0; i < sub_vec.size(); ) {
        vector<string> group = {sub_vec[i].name};
        int current_points = sub_vec[i].points;
        
        while (++i < sub_vec.size() && sub_vec[i].points == current_points) {
            group.push_back(sub_vec[i].name);
        }

        if (group.size() == 1) {
            result.push_back(group);
        } else {
            map<string, Team> final_sub_teams;
            compute_subleague(group, final_sub_teams);
            
            bool all_same = true;
            int first_pts = final_sub_teams[group[0]].points;
            for (size_t j = 1; j < group.size() && all_same; j++) {
                if (final_sub_teams[group[j]].points != first_pts) {
                    all_same = false;
                }
            }

            if (!all_same) {
                auto sub_groups = rank_teams_grouped(group);
                result.insert(result.end(), sub_groups.begin(), sub_groups.end());
            } else {
                vector<Team> final_group;
                for (const auto& name : group) {
                    final_group.push_back(final_sub_teams[name]);
                }
                sort(final_group.begin(), final_group.end(), team_compare);
                
                for (size_t k = 0; k < final_group.size(); ) {
                    vector<string> equal_teams = {final_group[k].name};
                    size_t m = k + 1;
                    while (m < final_group.size() && teams_equal(final_group[k], final_group[m])) {
                        equal_teams.push_back(final_group[m].name);
                        m++;
                    }
                    sort(equal_teams.begin(), equal_teams.end());
                    result.push_back(equal_teams);
                    k = m;
                }
            }
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 0; tc < T; tc++) {
        if (tc > 0) cout << '\n';

        games.clear();
        map<string, Team> global_teams;
        set<string> all_team_names;

        int G;
        cin >> G;
        for (int i = 0; i < G; i++) {
            string t1, t2;
            int g1, g2;
            cin >> t1 >> t2 >> g1 >> g2;
            games.push_back({t1, t2, g1, g2});

            all_team_names.insert(t1);
            all_team_names.insert(t2);

            Team& team1 = global_teams[t1];
            Team& team2 = global_teams[t2];
            team1.name = t1;
            team2.name = t2;

            team1.goals_scored += g1;
            team1.goals_conceded += g2;
            team2.goals_scored += g2;
            team2.goals_conceded += g1;

            if (g1 > g2) {
                team1.points += 3;
                team1.wins++;
            } else if (g1 < g2) {
                team2.points += 3;
                team2.wins++;
            } else {
                team1.points++;
                team2.points++;
            }
        }

        vector<string> all_teams(all_team_names.begin(), all_team_names.end());
        vector<Team> global_vec;
        for (const auto& name : all_teams) {
            global_vec.push_back(global_teams[name]);
        }
        sort(global_vec.begin(), global_vec.end(), team_compare);

        vector<vector<string>> final_groups;
        for (size_t i = 0; i < global_vec.size(); ) {
            vector<string> group = {global_vec[i].name};
            int current_points = global_vec[i].points;
            
            while (++i < global_vec.size() && global_vec[i].points == current_points) {
                group.push_back(global_vec[i].name);
            }

            if (group.size() == 1) {
                final_groups.push_back(group);
            } else {
                auto sub_groups = rank_teams_grouped(group);
                final_groups.insert(final_groups.end(), sub_groups.begin(), sub_groups.end());
            }
        }

        int place = 1;
        for (const auto& group : final_groups) {
            for (const auto& name : group) {
                cout << place << ' ' << name << '\n';
            }
            place += group.size();
        }
    }

    return 0;
}
