// Matching Meetings
// UVa ID: 419
// Verdict: Accepted
// Submission Date: 2025-12-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 星期字符映射
map<char, int> dayIndex = {{'M', 0}, {'T', 1}, {'W', 2}, {'R', 3}, {'F', 4}, {'A', 5}, {'S', 6}};
string dayStr = "MTWRF";

struct Date {
    // 星期几从 0 开始计数，0 对应星期一，6 对应星期日
    // 月份从 0 开始计数，0 对应 1 月，11 对应 12 月份
    // 天数从 1 开始计数
    int dayIdx;
    int month;
    int day;
    bool operator<(const Date& other) const {
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    bool operator==(const Date& other) const {
        return month == other.month && day == other.day;
    }
};

// 时间转换为分钟数
int timeToMinutes(int hour, int minute) {
    return hour * 60 + minute;
}

// 日期增加天数
Date addDays(const Date& date, int days) {
    Date result = date;
    result.day += days;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (result.day > daysInMonth[result.month]) {
        result.day -= daysInMonth[result.month];
        result.month++;
        // 调整月份
        result.month %= 12;
    }
    result.dayIdx = (result.dayIdx + days) % 7;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 读取当前日期
    char dayChar;
    int curMonth, curDay;
    cin >> dayChar >> curMonth >> curDay;
    Date currentDate = {dayIndex[dayChar], curMonth - 1, curDay};
    int n, t;
    cin >> n >> t;
    // 一天从9:00到17:00共8小时，每15分钟一个时段，共32个时段
    const int SLOTS_PER_DAY = 32;
    const int START_HOUR = 9;
    // 存储所有可能的日期（从当前日期开始一年内）
    vector<Date> allDates;
    Date curDate = currentDate;
    for (int i = 0; i < 365; i++) {
        // 忽略休息日
        if (curDate.dayIdx < 5) allDates.push_back(curDate);
        curDate = addDays(curDate, 1);
    }
    // 为每个日期创建一个bitset，初始全0（表示都空闲）
    map<pair<int, int>, bitset<SLOTS_PER_DAY>> dateBusy;
    // 忽略换行符
    cin.ignore(128, '\n');
    // 读取每个人的日程
    string name;
    while (getline(cin, name)) {
        if (name == "done") break;
        // 读取这个人的预约
        string line;
        while (getline(cin, line)) {
            if (line == "done") break;
            istringstream iss(line);
            char dayChar;
            int month, day;
            string startStr, endStr;
            iss >> dayChar >> month >> day >> startStr >> endStr;
            // 解析时间
            int startHour = stoi(startStr.substr(0, 2));
            int startMin = stoi(startStr.substr(2, 2));
            int endHour = stoi(endStr.substr(0, 2));
            int endMin = stoi(endStr.substr(2, 2));
            // 转换为时段索引
            int startSlot = (startHour - START_HOUR) * 4 + startMin / 15;
            int endSlot = (endHour - START_HOUR) * 4 + endMin / 15;
            // 确保在有效范围内
            startSlot = max(0, startSlot);
            endSlot = min(SLOTS_PER_DAY, endSlot);
            // 标记忙碌时段
            auto dateKey = make_pair(month - 1, day);
            for (int slot = startSlot; slot < endSlot; slot++) dateBusy[dateKey].set(slot);
        }
    }
    // 寻找可用的会议时间
    vector<pair<Date, pair<int, int>>> meetings; // 日期，小时，分钟
    // 需要占用的时段数
    int requiredSlots = t / 15;
    // 检查每个日期
    for (const Date& date : allDates) {
        auto dateKey = make_pair(date.month, date.day);
        bitset<SLOTS_PER_DAY> busy = dateBusy[dateKey];
        // 寻找连续requiredSlots个空闲时段
        for (int startSlot = 0; startSlot <= SLOTS_PER_DAY - requiredSlots; startSlot++) {
            bool available = true;
            for (int i = 0; i < requiredSlots; i++) {
                if (busy[startSlot + i]) {
                    available = false;
                    break;
                }
            }
            if (available) {
                // 找到可用时段，计算开始时间
                int totalMinutes = startSlot * 15;
                int hour = START_HOUR + totalMinutes / 60;
                int minute = totalMinutes % 60;
                meetings.push_back({date, {hour, minute}});
                // 标记这些时段为已占用（给后续会议）
                for (int i = 0; i < requiredSlots; i++) busy.set(startSlot + i);
                // 如果已经找到足够多的会议，可以提前停止
                if (meetings.size() >= n) break;
            }
        }
        if (meetings.size() >= n) break;
    }
    // 输出结果
    int outputCount = min(n, (int)meetings.size());
    for (int i = 0; i < outputCount; i++) {
        const Date& date = meetings[i].first;
        int hour = meetings[i].second.first;
        int minute = meetings[i].second.second;
        printf("%c %d %d %02d%02d\n", dayStr[date.dayIdx], date.month + 1, date.day, hour, minute);
    }
    if (outputCount < n) cout << "No more times available\n";
    return 0;
}
