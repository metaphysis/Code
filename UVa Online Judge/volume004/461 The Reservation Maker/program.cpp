// The Reservation Maker
// UVa ID: 461
// Verdict: Accepted
// Submission Date: 2026-10-23
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

using Time = long long;

constexpr int MAX_PARTY_SIZE = 22;
constexpr int MAX_JOINED_TABLES = 5;
constexpr Time INF = numeric_limits<Time>::max();

struct Table {
    int number;
    int capacity;
};

// blocked[table][size]：
// 对于指定人数，禁止入座时间的区间并集，采用 [left, right)。
// 下标 0 用于兼容 size <= 0；合法输入的人数至少为 1。
map<Time, Time> blocked[71][MAX_PARTY_SIZE + 1];

Time getDuration(int size) {
    if (size == 1) return 35;
    if (size == 2) return 47;
    if (size <= 4) return 52;
    if (size <= 10) return 55;
    return static_cast<Time>(size) * 5 + 16;
}

int getSizeIndex(int size) {
    return max(size, 0);
}

void addBlockedInterval(map<Time, Time>& intervals, Time left, Time right) {
    auto it = intervals.lower_bound(left);
    if (it != intervals.begin()) {
        auto previous = prev(it);
        if (previous->second >= left) {
            left = previous->first;
            right = max(right, previous->second);
            it = intervals.erase(previous);
        }
    }
    while (it != intervals.end() && it->first <= right) {
        right = max(right, it->second);
        it = intervals.erase(it);
    }
    intervals.emplace_hint(it, left, right);
}

void addReservation(int table, Time start, Time end) {
    for (int size = 0; size <= MAX_PARTY_SIZE; ++size) {
        Time duration = getDuration(size);
        addBlockedInterval(blocked[table][size], start - duration + 1, end);
    }
}

// 返回不早于 start 的第一个可入座时间。
// 用于单独分配 booth。
Time getNextStart(int table, int sizeIndex, Time start) {
    const auto& intervals = blocked[table][sizeIndex];
    auto it = intervals.upper_bound(start);
    if (it == intervals.begin()) return start;
    --it;
    if (start < it->second) return it->second;
    return start;
}

// 查询 start 时刻是否可以入座，同时返回下一次状态变化的时间。
// 可用 -> 不可用：下一个禁止区间的左端点。
// 不可用 -> 可用：当前禁止区间的右端点。
bool getAvailability(int table, int sizeIndex, Time start, Time& nextChange) {
    const auto& intervals = blocked[table][sizeIndex];
    auto next = intervals.upper_bound(start);
    if (next != intervals.begin()) {
        auto current = prev(next);
        if (start < current->second) {
            nextChange = current->second;
            return false;
        }
    }
    nextChange = (next == intervals.end() ? INF : next->first);
    return true;
}

void addTables(vector<Table>& pool, int first, int last, int capacity) {
    for (int number = first; number <= last; ++number) pool.push_back({number, capacity});
}

// 按编号依次选择当前可用的桌子，最多五张。
// 容量检查位于 if (available[i]) 外部。
bool chooseTables(const vector<Table>& pool, const vector<int>& available, int partySize, vector<int>& chosen) {
    chosen.clear();
    int seats = 0;
    for (int i = 0; i < static_cast<int>(pool.size()); ++i) {
        if (available[i]) {
            if (!chosen.empty()) seats -= 2;
            chosen.push_back(pool[i].number);
            seats += pool[i].capacity;
        }
        if (seats >= partySize) return true;
        if (static_cast<int>(chosen.size()) == MAX_JOINED_TABLES) break;
    }
    chosen.clear();
    return false;
}

bool findTableStart(const vector<Table>& pool, int partySize, Time arrival, Time& resultStart, vector<int>& chosen) {
    int count = static_cast<int>(pool.size());
    int sizeIndex = getSizeIndex(partySize);
    vector<int> available(count);
    Time start = arrival;
    while (true) {
        int freeCount = 0;
        Time nextChange = INF;
        // 必须统计整个区域，而不是只统计选桌循环访问的部分。
        for (int i = 0; i < count; ++i) {
            Time tableNextChange;
            available[i] = getAvailability(pool[i].number, sizeIndex, start, tableNextChange);
            freeCount += available[i];
            nextChange = min(nextChange, tableNextChange);
        }
        if (chooseTables(pool, available, partySize, chosen)) {
            resultStart = start;
            return true;
        }
        // 复现标准程序的提前终止：
        // 所有桌子均可用，但当前仍无法安排，就直接失败。
        if (freeCount == count) {
            chosen.clear();
            return false;
        }
        if (nextChange == INF) {
            chosen.clear();
            return false;
        }
        start = nextChange;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Table> nonsmokingTables;
    vector<Table> smokingTables;
    addTables(nonsmokingTables, 11, 20, 4);
    addTables(nonsmokingTables, 31, 40, 4);
    addTables(nonsmokingTables, 51, 55, 6);
    addTables(nonsmokingTables, 61, 65, 2);
    addTables(smokingTables, 21, 30, 4);
    addTables(smokingTables, 41, 50, 4);
    addTables(smokingTables, 56, 60, 6);
    addTables(smokingTables, 66, 70, 2);
    Time arrival;
    int partySize;
    char section;
    char type;
    while (cin >> arrival >> partySize >> section >> type) {
        int maxPartySize = (type == 'B' ? 6 : MAX_PARTY_SIZE);
        if (partySize > maxPartySize) {
            cout << "Impossible\n";
            continue;
        }
        int sizeIndex = getSizeIndex(partySize);
        Time duration = getDuration(partySize);
        Time bestStart = INF;
        vector<int> bestTables;
        bool found = false;
        if (type == 'B') {
            int first = (section == 'N' ? 1 : 5);
            int last = (section == 'N' ? 4 : 10);
            if (partySize <= 0) {
                // 复现循环底部的容量检查：
                // 第一张 booth 可用时，先选中它，再判断容量；
                // 第一张 booth 不可用时，0 >= partySize 已经成立，
                // 因而不选任何 booth，立即成功。
                found = true;
                bestStart = arrival;
                if (getNextStart(first, sizeIndex, arrival) == arrival) bestTables.push_back(first);
            } else {
                for (int table = first; table <= last; ++table) {
                    Time start = getNextStart(table, sizeIndex, arrival);
                    if (!found || start < bestStart) {
                        found = true;
                        bestStart = start;
                        bestTables.assign(1, table);
                    }
                }
            }
        } else {
            const vector<Table>& pool = (section == 'N' ? nonsmokingTables : smokingTables);
            found = findTableStart(pool, partySize, arrival, bestStart, bestTables);
        }
        // 不用 bestTables.empty() 判断成功与否：
        // 非正人数可能在尚未选择桌子时通过容量检查。
        if (!found) {
            cout << "Impossible\n";
            continue;
        }
        for (int table : bestTables) {
            cout << table << ' ';
            addReservation(table, bestStart, bestStart + duration);
        }
        cout << bestStart - arrival << '\n';
    }
    return 0;
}
