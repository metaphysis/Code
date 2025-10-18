// Euro 2004
// UVa ID: 917
// Verdict: Accepted
// Submission Date: 2025-10-18
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 常量定义：最大队伍数量和最大比赛数量
const int MAX_TEAMS = 10010, MAX_GAMES = 10010;

// 队伍数据结构：存储队伍的积分、进球数、失球数和胜场数
struct Team {
    int pts = 0, gs = 0, gc = 0, win = 0;  // 积分、进球数、失球数、胜场数
    // 计算净胜球
    int gd() const { return gs - gc; }
};

// 比赛数据结构：存储两支队伍的ID和各自的进球数
struct Game {
    int t1, t2, g1, g2;  // 队伍1ID, 队伍2ID, 队伍1进球, 队伍2进球
};

// 全局变量声明
Game games[MAX_GAMES];           // 存储所有比赛的数组
int gameCnt, teamCnt;            // 比赛数量和队伍数量计数器
Team global[MAX_TEAMS];          // 存储所有队伍全局数据的数组
map<string, int> nameToId;       // 队名到ID的映射
string idToName[MAX_TEAMS];      // ID到队名的反向映射

// 队伍比较函数：用于排序，按积分、净胜球、胜场数、进球数、字母顺序的优先级比较
bool teamCompare(const Team& a, const Team& b) {
    if (a.pts != b.pts) return a.pts > b.pts;              // 积分高的排前面
    if (a.gd() != b.gd()) return a.gd() > b.gd();          // 净胜球多的排前面
    if (a.win != b.win) return a.win > b.win;              // 胜场数多的排前面
    if (a.gs != b.gs) return a.gs > b.gs;                  // 进球数多的排前面
    return false;                                          // 其他情况保持原顺序
}

// 判断两个队伍在所有排名参数上是否完全相等
bool teamsEqual(const Team& a, const Team& b) {
    return a.pts == b.pts && a.gd() == b.gd() && a.win == b.win && a.gs == b.gs;
}

// 计算子联赛数据：只考虑指定队伍之间的比赛
void calcLeague(const vector<int>& teams, Team res[]) {
    // 初始化结果数组
    for (int i = 0; i < teamCnt; i++) res[i] = Team();
    
    // 标记哪些队伍在当前子联赛中
    bool inLeague[MAX_TEAMS] = {false};
    for (int t : teams) inLeague[t] = true;
    
    // 遍历所有比赛，只处理子联赛内队伍之间的比赛
    for (int i = 0; i < gameCnt; i++) {
        const Game& g = games[i];
        if (inLeague[g.t1] && inLeague[g.t2]) {
            Team& t1 = res[g.t1], & t2 = res[g.t2];
            // 更新进球和失球数据
            t1.gs += g.g1;  t1.gc += g.g2;
            t2.gs += g.g2;  t2.gc += g.g1;
            // 根据比赛结果更新积分和胜场数
            if (g.g1 > g.g2) { t1.pts += 3; t1.win++; }        // 队伍1获胜
            else if (g.g1 < g.g2) { t2.pts += 3; t2.win++; }   // 队伍2获胜
            else { t1.pts++; t2.pts++; }                       // 平局
        }
    }
}

// 递归排名函数：对给定队伍组进行排名，处理并列情况
vector<vector<int>> rankTeams(const vector<int>& teams) {
    // 基本情况：如果只有一支队伍，直接返回
    if (teams.size() == 1) return {teams};
    
    // 计算当前组的子联赛数据
    Team sub[MAX_TEAMS];
    calcLeague(teams, sub);
    
    // 将队伍数据与ID配对并排序
    vector<pair<Team, int>> vec;
    for (int t : teams) vec.push_back({sub[t], t});
    sort(vec.begin(), vec.end(), [](const pair<Team, int>& a, const pair<Team, int>& b) { return teamCompare(a.first, b.first); });
    
    // 按积分分组
    vector<vector<int>> res;
    for (size_t i = 0; i < vec.size(); ) {
        vector<int> group = {vec[i].second};
        int curPts = vec[i].first.pts;
        // 将积分相同的队伍分到同一组
        while (++i < vec.size() && vec[i].first.pts == curPts) group.push_back(vec[i].second);
        
        if (group.size() == 1)
            res.push_back(group);  // 单支队伍直接加入结果
        else {
            // 对积分相同的队伍组进行进一步处理
            Team finalSub[MAX_TEAMS];
            calcLeague(group, finalSub);
            
            // 检查在子联赛中这些队伍的积分是否仍然相同
            bool samePts = true;
            int firstPts = finalSub[group[0]].pts;
            for (size_t j = 1; j < group.size() && samePts; j++)
                if (finalSub[group[j]].pts != firstPts) samePts = false;
            
            if (!samePts) {
                // 积分不再相同，递归处理这个组
                auto subGroups = rankTeams(group);
                res.insert(res.end(), subGroups.begin(), subGroups.end());
            } else {
                // 积分仍然相同，使用其他排名标准
                vector<pair<Team, int>> finalVec;
                for (int t : group) finalVec.push_back({finalSub[t], t});
                sort(finalVec.begin(), finalVec.end(), [](const pair<Team, int>& a, const pair<Team, int>& b) { return teamCompare(a.first, b.first); });
                
                // 按排名参数分组，处理完全并列的情况
                for (size_t k = 0; k < finalVec.size(); ) {
                    vector<int> equalTeams = {finalVec[k].second};
                    size_t m = k + 1;
                    // 找到所有参数完全相同的队伍
                    while (m < finalVec.size() && teamsEqual(finalVec[k].first, finalVec[m].first)) {
                        equalTeams.push_back(finalVec[m].second); m++;
                    }
                    // 完全并列的队伍按字母顺序排序
                    sort(equalTeams.begin(), equalTeams.end(), [](int a, int b) { return idToName[a] < idToName[b]; });
                    res.push_back(equalTeams);
                    k = m;
                }
            }
        }
    }
    
    return res;
}

// 获取队伍ID：将队名映射为整数ID，如果不存在则创建新ID
int getId(const string& name) {
    if (nameToId.find(name) == nameToId.end()) {
        int id = teamCnt++;
        nameToId[name] = id;
        idToName[id] = name;
        return id;
    }
    return nameToId[name];
}

int main() {
    // I/O优化
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int T;  // 测试用例数量
    cin >> T;
    
    // 处理每个测试用例
    for (int tc = 0; tc < T; tc++) {
        if (tc > 0) cout << '\n';  // 测试用例之间输出空行
        
        // 初始化全局变量
        gameCnt = 0, teamCnt = 0;
        nameToId.clear();
        
        int G;  // 比赛数量
        cin >> G;
        
        // 初始化全局队伍数据
        for (int i = 0; i < MAX_TEAMS; i++) global[i] = Team();
        
        // 读取并处理所有比赛数据
        for (int i = 0; i < G; i++) {
            string t1, t2;
            int g1, g2;
            cin >> t1 >> t2 >> g1 >> g2;
            
            // 获取队伍ID
            int id1 = getId(t1), id2 = getId(t2);
            
            // 存储比赛信息
            games[gameCnt++] = {id1, id2, g1, g2};
            
            // 更新全局队伍数据
            Team& tm1 = global[id1], & tm2 = global[id2];
            tm1.gs += g1;  tm1.gc += g2;  // 更新队伍1的进球失球
            tm2.gs += g2;  tm2.gc += g1;  // 更新队伍2的进球失球
            // 根据比赛结果更新积分和胜场
            if (g1 > g2) { tm1.pts += 3; tm1.win++; }        // 队伍1获胜
            else if (g1 < g2) { tm2.pts += 3; tm2.win++; }   // 队伍2获胜
            else { tm1.pts++; tm2.pts++; }                     // 平局
        }
        
        // 收集所有队伍的ID
        vector<int> allTeams;
        for (int i = 0; i < teamCnt; i++) allTeams.push_back(i);
        
        // 按全局数据对队伍进行初步排序
        sort(allTeams.begin(), allTeams.end(), [](int a, int b) {
            return teamCompare(global[a], global[b]);
        });
        
        // 构建最终排名分组
        vector<vector<int>> finalGroups;
        for (size_t i = 0; i < allTeams.size(); ) {
            vector<int> group = {allTeams[i]};
            int curPts = global[allTeams[i]].pts;
            // 按积分分组
            while (++i < allTeams.size() && global[allTeams[i]].pts == curPts) group.push_back(allTeams[i]);
            
            if (group.size() == 1) finalGroups.push_back(group);  // 单支队伍直接加入
            else {
                // 多支队伍积分相同，进入子联赛排名
                auto subGroups = rankTeams(group);
                finalGroups.insert(finalGroups.end(), subGroups.begin(), subGroups.end());
            }
        }
        
        // 输出最终排名结果
        int place = 1;
        for (const auto& group : finalGroups) {
            for (int t : group) cout << place << ' ' << idToName[t] << '\n';
            place += group.size();  // 更新名次
        }
    }
    
    return 0;
}
