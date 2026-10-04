#include <bits/stdc++.h>
using namespace std;

constexpr int SECONDS_PER_DAY = 24 * 60 * 60;
constexpr double PI = acos(-1.0);
constexpr double EPS = 1e-12;

int daysInMonth(int month) {
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month < 1 || month > 12) return 0;
    return days[month - 1];
}

bool parseDate(const string& text, int& day, int& month) {
    char extra;
    stringstream ss(text);
    if (!(ss >> day)) return false;
    if (!(ss >> extra) || extra != '/') return false;
    if (!(ss >> month)) return false;
    if (ss >> extra) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month)) return false;
    return true;
}

bool parseTime(const string& text, int& hour, int& minute, int& second) {
    char firstSeparator, secondSeparator, extra;
    stringstream ss(text);
    if (!(ss >> hour >> firstSeparator >> minute >> secondSeparator >> second)) return false;
    if (firstSeparator != ':' || secondSeparator != ':') return false;
    if (ss >> extra) return false;
    if (hour < 0 || hour >= 24) return false;
    if (minute < 0 || minute >= 60) return false;
    if (second < 0 || second >= 60) return false;
    return true;
}

int timeToSeconds(int hour, int minute, int second) {
    return hour * 3600 + minute * 60 + second;
}

int dayOfYear(int day, int month) {
    int result = day;
    for (int currentMonth = 1; currentMonth < month; ++currentMonth) result += daysInMonth(currentMonth);
    return result;
}

void printAngle(double angle, char positiveDirection, char negativeDirection) {
    char direction = angle >= 0.0 ? positiveDirection : negativeDirection;
    int totalSeconds = static_cast<int>(round(fabs(angle) * 3600.0));
    int degree = totalSeconds / 3600;
    int minute = (totalSeconds % 3600) / 60;
    int second = totalSeconds % 60;
    cout << setfill('0') << setw(3) << degree << ':' << setw(2) << minute << ':' << setw(2) << second << ' ' << direction;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string dateText, sunriseText, sunsetText;
    while (cin >> dateText >> sunriseText >> sunsetText) {
        int day, month;
        int sunriseHour, sunriseMinute, sunriseSecond;
        int sunsetHour, sunsetMinute, sunsetSecond;
        bool validDate = parseDate(dateText, day, month);
        bool validSunrise = parseTime(sunriseText, sunriseHour, sunriseMinute, sunriseSecond);
        bool validSunset = parseTime(sunsetText, sunsetHour, sunsetMinute, sunsetSecond);
        int sunriseTime = timeToSeconds(sunriseHour, sunriseMinute, sunriseSecond);
        int sunsetTime = timeToSeconds(sunsetHour, sunsetMinute, sunsetSecond);
        /*
         * 如果日落时间小于日出时间，表示日落发生在第二天。
         * 例如：
         *
         *   日出 13:00
         *   日落 01:00
         *
         * 实际昼长为 12 小时，而不是负数。
         */
        if (sunsetTime < sunriseTime) sunsetTime += SECONDS_PER_DAY;
        double middleSeconds = (sunriseTime + sunsetTime) / 2.0;
        double daylightHours = (sunsetTime - sunriseTime) / 3600.0;
        /*
         * 6 月 21 日 12:00 GMT 作为太阳赤纬计算的参考时刻。
         * middleSeconds 可以大于 24 小时，这正是跨午夜数据所需要的。
         */
        int summerSolsticeDay = dayOfYear(21, 6);
        int currentDay = dayOfYear(day, month);
        double dayDifference = static_cast<double>(currentDay - summerSolsticeDay) + (middleSeconds - 12.0 * 3600.0) / static_cast<double>(SECONDS_PER_DAY);
        /*
         * 太阳赤纬：
         *
         * delta = 23.45 * cos(2 * PI * D / 365)
         */
        double declination = 23.45 * cos(2.0 * PI * dayDifference / 365.0);
        double declinationRadians = declination * PI / 180.0;
        /*
         * 太阳时角：
         *
         * H = 15 * 昼长 / 2
         */
        double hourAngle = 15.0 * daylightHours / 2.0;
        double hourAngleRadians = hourAngle * PI / 180.0;
        double tangentDeclination = tan(declinationRadians);
        /*
         * 春分、秋分附近太阳赤纬为 0，
         * 仅凭昼长无法唯一确定纬度。
         */
        if (fabs(tangentDeclination) < EPS) {
            cout << "Lost My Way\n";
            continue;
        }
        /*
         * 日出、日落时太阳高度角为 0：
         *
         * tan(latitude) = -cos(hourAngle) / tan(declination)
         */
        double tangentLatitude = -cos(hourAngleRadians) / tangentDeclination;
        double latitudeRadians = atan(tangentLatitude);
        double latitude = latitudeRadians * 180.0 / PI;
        /*
         * 当地太阳正午为日出、日落的中点。
         *
         * longitude = (12:00 - 当地太阳正午) * 15
         */
        double middleTimeInHours = middleSeconds / 3600.0;
        double longitude = (12.0 - middleTimeInHours) * 15.0;
        /*
         * 将经度规范化到 [-180, 180]。
         */
        while (longitude < -180.0) longitude += 360.0;
        while (longitude > 180.0) longitude -= 360.0;
        printAngle(latitude, 'N', 'S');
        cout << ' ';
        printAngle(longitude, 'E', 'W');
        cout << '\n';
    }
    return 0;
}
