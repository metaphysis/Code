// Tempus Fugit
// UVa ID: 480
// Verdict: Accepted
// Submission Date: 2026-06-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int WORK_START = 9 * 60;
const int WORK_END = 17 * 60;
const int LUNCH_START = 12 * 60 + 30;
const int LUNCH_END = 13 * 60 + 30;
const int BLOCK = 10;
const int MAX_DAILY = 240;
const int DAYS = 5;
const int BLOCKS_PER_DAY = (WORK_END - WORK_START) / BLOCK;

int dayIndex(const string& d) {
    if (d == "MON") return 0;
    if (d == "TUE") return 1;
    if (d == "WED") return 2;
    if (d == "THU") return 3;
    return 4;
}

string dayName(int i) {
    static const string names[DAYS] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY"};
    return names[i];
}

string formatTime(int minutes) {
    int h = minutes / 60, m = minutes % 60;
    if (h >= 13) h -= 12;
    string hh = to_string(h);
    string mm = (m < 10 ? "0" : "") + to_string(m);
    return hh + ":" + mm;
}

int floor10(int t) { return (t / BLOCK) * BLOCK; }
int ceil10(int t) { return ((t + BLOCK - 1) / BLOCK) * BLOCK; }

struct Appointment { string name; int startMin, endMin; };

bool occupied[DAYS][BLOCKS_PER_DAY];
int dailyTotal[DAYS];
vector<Appointment> schedule[DAYS];
vector<string> failed;

bool isFree(int day, int block) { return !occupied[day][block]; }

bool canPlace(int day, int startMin, int endMin, int dur) {
    if (startMin < WORK_START || endMin > WORK_END || startMin >= endMin) return false;
    if (startMin < LUNCH_START && endMin > LUNCH_START) return false;
    if (startMin >= LUNCH_START && startMin < LUNCH_END) return false;
    int startBlock = (startMin - WORK_START) / BLOCK;
    int endBlock = (endMin - WORK_START) / BLOCK;
    for (int b = startBlock; b < endBlock; ++b)
        if (!isFree(day, b)) return false;
    if (dailyTotal[day] + dur > MAX_DAILY) return false;
    return true;
}

void placeAppointment(int day, const string& name, int startMin, int endMin) {
    int dur = endMin - startMin;
    int startBlock = (startMin - WORK_START) / BLOCK;
    int endBlock = (endMin - WORK_START) / BLOCK;
    for (int b = startBlock; b < endBlock; ++b) occupied[day][b] = true;
    dailyTotal[day] += dur;
    schedule[day].push_back({name, startMin, endMin});
    if (endMin != LUNCH_START && endMin != WORK_END) {
        int breakBlock = (endMin - WORK_START) / BLOCK;
        occupied[day][breakBlock] = true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int d = 0; d < DAYS; ++d) {
        for (int b = 0; b < BLOCKS_PER_DAY; ++b) occupied[d][b] = false;
        int lunchStartBlock = (LUNCH_START - WORK_START) / BLOCK;
        int lunchEndBlock = (LUNCH_END - WORK_START) / BLOCK;
        for (int b = lunchStartBlock; b < lunchEndBlock; ++b) occupied[d][b] = true;
        dailyTotal[d] = 0;
    }

    string name, day;
    int sh, sm, dh, dm;
    vector<tuple<string, int, int, int>> requests;
    while (cin >> name >> day >> sh >> sm >> dh >> dm) {
        if (sh < 9) sh += 12;                     // 将下午时间转换为24小时制
        int startOrig = sh * 60 + sm;
        int dur = dh * 60 + dm;
        int dayIdx = dayIndex(day);
        requests.emplace_back(name, startOrig, dur, dayIdx);
    }

    for (auto& req : requests) {
        string reqName = get<0>(req);
        int startOrig = get<1>(req);
        int dur = get<2>(req);
        int reqDay = get<3>(req);

        int startAdj = floor10(startOrig);
        int endAdj = ceil10(startOrig + dur);
        int adjDur = endAdj - startAdj;

        bool scheduled = false;
        for (int d = reqDay; d < DAYS; ++d) {
            if (!canPlace(d, startAdj, endAdj, adjDur)) continue;
            bool needBreak = (endAdj != LUNCH_START && endAdj != WORK_END);
            if (needBreak) {
                int breakBlock = (endAdj - WORK_START) / BLOCK;
                if (breakBlock < 0 || breakBlock >= BLOCKS_PER_DAY) continue;
                if (!isFree(d, breakBlock)) continue;
            }
            placeAppointment(d, reqName, startAdj, endAdj);
            scheduled = true;
            break;
        }
        if (!scheduled) failed.push_back(reqName);
    }

    cout << "APPOINTMENT SCHEDULE FOR THE WEEK\n";
    for (int d = 0; d < DAYS; ++d) {
        cout << dayName(d) << "\n";
        if (schedule[d].empty()) {
            cout << "No Appointments Scheduled\n";
        } else {
            sort(schedule[d].begin(), schedule[d].end(),
                 [](const Appointment& a, const Appointment& b) { return a.startMin < b.startMin; });
            for (const auto& app : schedule[d])
                cout << app.name << " " << formatTime(app.startMin) << " to " << formatTime(app.endMin) << "\n";
        }
    }
    cout << "APPOINTMENTS COULD NOT BE SCHEDULED FOR:\n";
    for (const string& s : failed) cout << s << "\n";
    return 0;
}
