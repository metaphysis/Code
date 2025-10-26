// Revolutionary Calendar
// UVa ID: 887
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 月份名称
const vector<string> monthNames = {
    "Alligator", "Bog", "Crayfish", "Damp", "Eel", "Fen", "Gumbo",
    "Hurricane", "Inundation", "Jaguar", "Kudzu", "Lake", "Marsh",
    "Newt", "Overflow"
};

const int commonMonthsCount = 13;
const int daysPerCommonMonth = 28;
const int totalCommonDays = commonMonthsCount * daysPerCommonMonth; // 364
const int daysPerNewt = 1;
const int daysPerLeapYear = totalCommonDays + daysPerNewt + 1; // 366
const int daysPerNormalYear = totalCommonDays + daysPerNewt; // 365

const int cycleYears = 2820;
const int cycleLeaps = 683;

// 预计算：普通日期到天数的映射表
vector<vector<int>> commonDateToIndex;
// 预计算：闰年周期内的天数
vector<long long> cycleDays;
// 预计算：每个年份是否是闰年
vector<bool> isLeapCache;
// 预计算：月份名称前缀映射表
map<string, int> monthPrefixMap;

struct Date {
    int day;
    int monthIndex; // 0-12: common, 13: Newt, 14: Overflow
    int year;

    bool isCommonMonth() const { return monthIndex >= 0 && monthIndex < commonMonthsCount; }
    bool isNewt() const { return monthIndex == commonMonthsCount; }
    bool isOverflow() const { return monthIndex == commonMonthsCount + 1; }
};

// 转换为小写
string toLower(const string& str) {
    string result;
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

// 初始化预计算数据
void initPrecomputation() {
    // 预计算普通日期映射表
    commonDateToIndex.resize(commonMonthsCount, vector<int>(daysPerCommonMonth, -1));
    for (int n = 0; n < totalCommonDays; ++n) {
        int day = n % daysPerCommonMonth;
        int monthIndex = n % commonMonthsCount;
        commonDateToIndex[monthIndex][day] = n;
    }
    
    // 预计算闰年信息
    isLeapCache.resize(cycleYears);
    vector<int> leapIndices(cycleYears, -1);
    int leapCount = 0;
    for (int year = 0; year < cycleYears; ++year) {
        isLeapCache[year] = ((683 * year) % 2820) < 683;
        if (isLeapCache[year]) {
            leapIndices[year] = leapCount;
            leapCount++;
        }
    }
    
    // 预计算2820年周期的总天数
    cycleDays.resize(cycleYears + 1);
    cycleDays[0] = 0;
    for (int year = 0; year < cycleYears; ++year) {
        cycleDays[year + 1] = cycleDays[year] + (isLeapCache[year] ? daysPerLeapYear : daysPerNormalYear);
    }
    
    // 预计算月份名称前缀映射表
    for (int i = 0; i < (int)monthNames.size(); ++i) {
        string lowerMonth = toLower(monthNames[i]);
        // 为每个月份名称生成所有唯一前缀
        for (int len = 1; len <= (int)lowerMonth.length(); ++len) {
            string prefix = lowerMonth.substr(0, len);
            // 如果此前缀已经存在，说明有冲突，标记为-1
            if (monthPrefixMap.find(prefix) != monthPrefixMap.end()) {
                if (monthPrefixMap[prefix] != -1) {
                    // 之前映射到某个有效月份，现在发现冲突，标记为无效
                    monthPrefixMap[prefix] = -1;
                }
            } else {
                // 首次出现，记录映射
                monthPrefixMap[prefix] = i;
            }
        }
    }
}

// 闰年判断（使用缓存）
bool isLeapYear(int year) {
    return isLeapCache[year % cycleYears];
}

// 该年是第几个闰年（从0开始，使用缓存）
int getLeapIndex(int year) {
    int y = year % cycleYears;
    int count = 0;
    for (int i = 0; i <= y; ++i) {
        if (isLeapCache[i]) count++;
    }
    return count - 1;
}

// 月份名称转索引（使用预计算的前缀表）
int monthNameToIndex(const string& name) {
    string lowerName = toLower(name);
    auto it = monthPrefixMap.find(lowerName);
    if (it != monthPrefixMap.end() && it->second != -1) {
        return it->second;
    }
    return -1; // 不唯一或没找到
}

// 解析日期
Date parseDate(const string& dateStr) {
    for (char c : dateStr) {
        if (c == '-') {
            size_t firstDash = dateStr.find('-');
            size_t secondDash = dateStr.find('-', firstDash + 1);
            if (secondDash == string::npos) return {-1, -1, -1};

            int day = stoi(dateStr.substr(0, firstDash));
            string monthStr = dateStr.substr(firstDash + 1, secondDash - firstDash - 1);
            int year = stoi(dateStr.substr(secondDash + 1));

            int monthIndex = monthNameToIndex(monthStr);
            return {day, monthIndex, year};
        }
    }
    return {-1, -1, -1};
}

// 检查普通日期的合法性
bool isValidCommonDate(int day, int monthIndex) {
    if (monthIndex < 0 || monthIndex >= commonMonthsCount) return false;
    if (day < 0 || day >= daysPerCommonMonth) return false;
    return commonDateToIndex[monthIndex][day] != -1;
}

// 检查日期合法性
bool isValidDate(const Date& date) {
    if (date.year < 0 || date.year > 1999999) return false;
    if (date.monthIndex < 0) return false;

    if (date.isCommonMonth()) {
        return isValidCommonDate(date.day, date.monthIndex);
    } else if (date.isNewt()) {
        return date.day == 0;
    } else if (date.isOverflow()) {
        if (date.day < 0 || date.day >= cycleLeaps) return false;
        if (!isLeapYear(date.year)) return false;
        return date.day == getLeapIndex(date.year);
    }
    return false;
}

// 快速计算从 0-Alligator-0 到该日期的总天数
long long dateToDays(const Date& date) {
    long long totalDays = 0;
    
    // 使用周期优化计算整年天数
    int fullCycles = date.year / cycleYears;
    int remainingYears = date.year % cycleYears;
    
    totalDays = fullCycles * cycleDays[cycleYears];
    totalDays += cycleDays[remainingYears];
    
    // 计算当年内的天数
    if (date.isCommonMonth()) {
        totalDays += commonDateToIndex[date.monthIndex][date.day];
    } else if (date.isNewt()) {
        totalDays += totalCommonDays;
    } else if (date.isOverflow()) {
        totalDays += totalCommonDays + daysPerNewt;
    }
    
    return totalDays;
}

int main() {
    // 初始化预计算数据
    initPrecomputation();
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        stringstream stringStream(line);
        string firstDateStr, secondDateStr;
        stringStream >> firstDateStr >> secondDateStr;
        
        if (firstDateStr.empty() || secondDateStr.empty()) {
            cout << "eh?" << endl;
            continue;
        }

        Date firstDate = parseDate(firstDateStr);
        Date secondDate = parseDate(secondDateStr);

        if (!isValidDate(firstDate) || !isValidDate(secondDate)) {
            cout << "eh?" << endl;
            continue;
        }

        long long firstDateDays = dateToDays(firstDate);
        long long secondDateDays = dateToDays(secondDate);
        long long difference = secondDateDays - firstDateDays;
        
        if (difference < 0) {
            difference = -difference;
        }

        cout << difference << endl;
    }
    return 0;
}
