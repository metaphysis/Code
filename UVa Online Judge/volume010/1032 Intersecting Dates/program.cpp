// Intersecting Dates
// UVa ID: 1032
// Verdict: Accepted
// Submission Date: 2026-06-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 判断是否为闰年
bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 每月的天数（非闰年）
int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// 将日期 YYYYMMDD 转换为从 1/1/1700 开始经过的天数
int dateToDays(int date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;
    
    int total = 0;
    // 累加年份
    for (int y = 1700; y < year; ++y) {
        total += isLeap(y) ? 366 : 365;
    }
    // 累加月份
    for (int m = 1; m < month; ++m) {
        if (m == 2) total += isLeap(year) ? 29 : 28;
        else total += daysInMonth[m];
    }
    // 累加天数（从1号开始，所以减1使1号对应0）
    total += day - 1;
    return total;
}

// 将天数转换回 YYYYMMDD 格式
int daysToDate(int days) {
    int year = 1700;
    // 减去每年的天数
    while (true) {
        int daysInYear = isLeap(year) ? 366 : 365;
        if (days < daysInYear) break;
        days -= daysInYear;
        ++year;
    }
    int month = 1;
    while (true) {
        int daysInMon = (month == 2) ? (isLeap(year) ? 29 : 28) : daysInMonth[month];
        if (days < daysInMon) break;
        days -= daysInMon;
        ++month;
    }
    int day = days + 1;  // 因为之前减了1，现在加回来
    return year * 10000 + month * 100 + day;
}

// 格式化日期为 月/日/年
string formatDate(int date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;
    return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
}

// 合并区间（区间用天数表示）
vector<pair<int, int>> mergeIntervals(vector<pair<int, int>>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());
    vector<pair<int, int>> merged;
    merged.push_back(intervals[0]);
    for (size_t i = 1; i < intervals.size(); ++i) {
        int curL = intervals[i].first, curR = intervals[i].second;
        int lastL = merged.back().first, lastR = merged.back().second;
        // 相邻或重叠则合并（相邻条件：curL <= lastR + 1）
        if (curL <= lastR + 1) merged.back().second = max(lastR, curR);
        else merged.push_back({curL, curR});
    }
    return merged;
}

int main() {
    int NX, NR;
    int caseNo = 0;
    while (cin >> NX >> NR) {
        if (NX == 0 && NR == 0) break;
        
        vector<pair<int, int>> existing, required;
        // 读取已有区间并转换为天数
        for (int i = 0; i < NX; ++i) {
            int startDate, endDate;
            cin >> startDate >> endDate;
            int startDay = dateToDays(startDate);
            int endDay = dateToDays(endDate);
            existing.push_back({startDay, endDay});
        }
        // 读取所需区间并转换为天数
        for (int i = 0; i < NR; ++i) {
            int startDate, endDate;
            cin >> startDate >> endDate;
            int startDay = dateToDays(startDate);
            int endDay = dateToDays(endDate);
            required.push_back({startDay, endDay});
        }
        
        // 合并已有区间（天数版本）
        vector<pair<int, int>> mergedExisting = mergeIntervals(existing);
        // 合并所需区间（天数版本）
        vector<pair<int, int>> mergedRequired = mergeIntervals(required);
        
        // 计算差集：所需区间减去已有区间
        vector<pair<int, int>> resultDays;
        for (auto req : mergedRequired) {
            int reqL = req.first, reqR = req.second;
            int curL = reqL;
            for (auto ex : mergedExisting) {
                int exL = ex.first, exR = ex.second;
                if (exR < curL) continue;
                if (exL > reqR) break;
                // 已有区间覆盖了当前待处理区间的一部分
                if (exL <= curL && exR >= curL) {
                    curL = exR + 1;
                } else if (exL > curL && exL <= reqR) {
                    // 未被覆盖的部分：curL 到 exL-1
                    if (curL <= exL - 1) {
                        resultDays.push_back({curL, exL - 1});
                    }
                    curL = max(curL, exR + 1);
                }
                if (curL > reqR) break;
            }
            // 剩余未被覆盖的部分
            if (curL <= reqR) {
                resultDays.push_back({curL, reqR});
            }
        }
        
        // 将天数结果转换回日期格式
        vector<pair<int, int>> resultDates;
        for (auto p : resultDays) {
            int startDate = daysToDate(p.first);
            int endDate = daysToDate(p.second);
            resultDates.push_back({startDate, endDate});
        }
        
        // 输出
        if (caseNo) cout << '\n';
        cout << "Case " << ++caseNo << ":\n";
        if (resultDates.empty()) cout << "    No additional quotes are required.\n";
        else {
            for (size_t i = 0; i < resultDates.size(); ++i) {
                int l = resultDates[i].first, r = resultDates[i].second;
                cout << "    ";
                if (l == r) cout << formatDate(l);
                else cout << formatDate(l) << " to " << formatDate(r);
                cout << '\n';
            }
        }
    }
    return 0;
}
