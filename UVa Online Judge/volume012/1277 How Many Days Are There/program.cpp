#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

static const int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int64 floorDiv(int64 a, int64 b) {
    int64 q = a / b;
    int64 r = a % b;
    if (r < 0) --q;
    return q;
}

int64 ceilDiv(int64 a, int64 b) {
    int64 q = a / b;
    int64 r = a % b;
    if (r > 0) ++q;
    return q;
}

bool isLeapYear(int64 year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    return year % 4 == 0;
}

int64 countLeapYears(int64 left, int64 right) {
    if (left > right) return 0;
    auto countDivisibleBy = [](int64 x, int64 divisor) -> int64 {
        return floorDiv(x, divisor);
    };
    return (countDivisibleBy(right, 4) - countDivisibleBy(left - 1, 4))
         - (countDivisibleBy(right, 100) - countDivisibleBy(left - 1, 100))
         + (countDivisibleBy(right, 400) - countDivisibleBy(left - 1, 400));
}

int64 daysBeforeYear(int64 year) {
    if (year >= 1) {
        return 365LL * (year - 1) + countLeapYears(1, year - 1);
    }
    return -(365LL * (1 - year) + countLeapYears(year, 0));
}

int64 dateNumber(int64 year, int month, int day) {
    int64 result = daysBeforeYear(year);
    for (int m = 1; m < month; ++m) {
        result += monthDays[m];
        if (m == 2 && isLeapYear(year)) ++result;
    }
    result += day - 1;
    return result;
}

int weekdayFromDateNumber(int64 number) {
    int64 value = number % 7;
    if (value < 0) value += 7;
    return static_cast<int>((value + 1) % 7);
}

int daysInMonth(int64 year, int month) {
    if (month == 2 && isLeapYear(year)) return 29;
    return monthDays[month];
}

int64 countPart(int64 yearLeft, int64 yearRight, int64 dateLeft, int64 dateRight, int targetWeek, int targetDay) {
    if (yearLeft > yearRight || targetDay <= 0) return 0;
    int64 answer = 0;
    for (int64 year = yearLeft; year <= yearRight; ++year) {
        for (int month = 1; month <= 12; ++month) {
            if (targetDay > daysInMonth(year, month)) continue;
            int64 currentDate = dateNumber(year, month, targetDay);
            if (currentDate < dateLeft || currentDate > dateRight) continue;
            if (weekdayFromDateNumber(currentDate) == targetWeek) ++answer;
        }
    }
    return answer;
}

int64 countOneCycle(int targetWeek, int targetDay) {
    int64 cycleLeft = dateNumber(0, 1, 1);
    int64 cycleRight = dateNumber(399, 12, 31);
    return countPart(0, 399, cycleLeft, cycleRight, targetWeek, targetDay);
}

int64 solve(int targetWeek, int targetDay, int64 year1, int month1, int day1, int64 year2, int month2, int day2) {
    int64 dateLeft = dateNumber(year1, month1, day1);
    int64 dateRight = dateNumber(year2, month2, day2);
    if (dateLeft > dateRight || targetDay <= 0) return 0;
    int64 firstBlock = ceilDiv(year1, 400) * 400;
    int64 lastBlock = floorDiv(year2 - 399, 400) * 400;
    if (firstBlock > lastBlock) {
        return countPart(year1, year2, dateLeft, dateRight, targetWeek, targetDay);
    }
    int64 answer = 0;
    answer += countPart(year1, min(year2, firstBlock - 1), dateLeft, dateRight, targetWeek, targetDay);
    int64 cycleCount = (lastBlock - firstBlock) / 400 + 1;
    answer += cycleCount * countOneCycle(targetWeek, targetDay);
    answer += countPart(max(year1, lastBlock + 400), year2, dateLeft, dateRight, targetWeek, targetDay);
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int targetWeek, targetDay;
    while (cin >> targetWeek >> targetDay) {
        if (targetWeek == 0 && targetDay == 0) break;
        int64 year1, year2, month1, day1, month2, day2;
        cin >> year1 >> month1 >> day1 >> year2 >> month2 >> day2;
        cout << solve(targetWeek, targetDay, year1, month1, day1, year2, month2, day2) << '\n';
    }
    return 0;
}
