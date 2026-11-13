[UVa 212 Use of Hospital Facilities](https://blog.csdn.net/metaphysis/article/details/161045992)

## 题目分析

本题要求模拟医院一天内手术室和恢复室的使用情况。医院有多个手术室和恢复床位，患者按照固定顺序进行手术。患者进入手术室时，会选择编号最小的空闲手术室；手术后，患者被送往编号最小的空闲恢复床位。手术室和恢复床位的准备时间以及转运时间都是固定的。

输入数据包括医院配置参数（手术室数量、恢复床位数、起始时间、转运时间、准备时间、患者数量）以及每位患者的姓名、手术时间和恢复时间。输出需要包含两个表格：第一个表格记录每位患者使用的手术室和恢复床位及其时间，第二个表格统计各手术室和恢复床位的利用率。

## 解题思路

本题的核心是**事件驱动模拟**。模拟过程分为两个阶段：

1. **手术室阶段**：使用优先队列管理手术室，队列中的手术室按照可用时间排序，同时考虑编号顺序。初始时所有手术室在起始时间可用。依次为每个患者分配手术室，记录手术开始和结束时间，然后更新手术室的可用时间（需加上准备时间）。

2. **恢复室阶段**：患者按离开手术室的时间排序，同时考虑同时间离开时按手术室编号排序。为每个患者分配编号最小的可用恢复床位，记录进入和离开恢复室的时间，更新床位的可用时间（需加上准备时间）。

关键点在于处理同一时间多个事件的顺序：当多个手术室同时可用时，优先分配给患者列表中靠前的患者；当多个患者同时离开手术室时，优先分配编号较小的手术室的患者。

## 代码实现

```cpp
// Use of Hospital Facilities
// UVa ID: 212
// Verdict: Accepted
// Submission Date: 2016-04-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 患者结构体，存储患者的所有信息
struct patient {
    string lastname;          // 患者姓氏
    int index;                // 患者编号（输入顺序）
    int mintues_surgery, mintues_recovery;  // 手术时间、恢复时间
    int enter_room, leave_room, enter_bed, leave_bed;  // 各时间点（分钟）
    int room_number, bed_number;  // 使用的手术室和床位编号

    // 按患者编号排序
    bool operator<(patient x) const {
        return index < x.index;
    }
};

// 手术室结构体
struct room {
    int index;                // 手术室编号
    int mintues_used;         // 累计使用时间
    int time_expried;         // 手术室下次可用的时间
    patient someone;          // 当前正在使用的患者
    int available;            // 是否空闲（1空闲，0占用）

    // 优先队列排序规则：按可用时间早的优先，同时考虑编号
    bool operator<(room x) const {
        if (available != x.available)
            return x.available < available;

        if (available == 0)
            return x.index < index;

        if (time_expried != x.time_expried)
            return x.time_expried < time_expried;
        else
            return x.index < index;
    }
};

// 按手术室编号排序的比较函数
bool cmp_room(room x, room y) {
    return x.index < y.index;
}

// 恢复床位结构体
struct bed {
    int index;                // 床位编号
    int mintues_used;         // 累计使用时间
    int time_expried;         // 床位下次可用的时间
    patient someone;          // 当前正在使用的患者
    int available;            // 是否空闲
};

// 全局变量定义
int operating_rooms, recovery_rooms, starting_mintues,
    mintues_operating_to_recovery, mintues_preparing_operating,
    mintues_preparing_recovery, patients_counter, mintues_required_surgery,
    mintues_required_recovery;

vector<patient> patients;          // 患者列表
priority_queue<room> rooms;        // 手术室优先队列

// 将分钟数转换为时间字符串（如 420 -> "7:00"）
string toTime(int time) {
    string text;
    text += to_string(time / 60);
    text += ":";
    time %= 60;
    text += (time >= 10 ? "" : "0") + to_string(time % 60);
    return text;
}

// 按离开手术室时间排序，时间相同按手术室编号
bool cmp(patient x, patient y) {
    if (x.leave_room == y.leave_room)
        return x.room_number < y.room_number;
    else
        return x.leave_room < y.leave_room;
}

// 主要模拟函数
void arrange() {
    vector<patient> next;          // 等待进入恢复室的患者
    // 第一阶段：手术室模拟
    while (patients.size()) {
        room room = rooms.top();
        rooms.pop();

        if (room.available)        // 手术室空闲，分配新患者
        {
            patient another = patients.front();
            patients.erase(patients.begin());

            another.enter_room = room.time_expried;
            another.room_number = room.index;

            room.someone = another;
            room.time_expried += another.mintues_surgery;
            room.available = 0;
            rooms.push(room);
        }
        else                       // 手术室有患者，记录完成时间
        {
            patient someone = room.someone;
            someone.leave_room = room.time_expried;
            next.push_back(someone);

            room.mintues_used += someone.mintues_surgery;
            room.time_expried = room.time_expried + mintues_preparing_operating;
            room.available = 1;
            rooms.push(room);
        }
    }

    // 收集所有完成手术的患者
    vector<room> usedRooms;
    while (rooms.size()) {
        room room = rooms.top();
        rooms.pop();

        if (!room.available)       // 还有患者在手术室中
        {
            patient someone = room.someone;
            someone.leave_room = room.time_expried;
            room.mintues_used += someone.mintues_surgery;
            next.push_back(someone);
        }

        usedRooms.push_back(room);
    }

    // 按离开手术室时间排序，准备分配恢复床位
    sort(next.begin(), next.end(), cmp);

    // 第二阶段：恢复室模拟
    vector<bed> usedBeds;
    for (int i = 1; i <= recovery_rooms; i++) {
        bed bed;
        bed.index = i;
        bed.time_expried = starting_mintues;
        bed.available = 1;
        bed.mintues_used = 0;
        usedBeds.push_back(bed);
    }

    vector<patient> last;          // 完成所有流程的患者
    for (int i = 0; i < next.size(); i++) {
        patient another = next[i];
        // 查找编号最小的可用床位
        for (int j = 0; j < usedBeds.size(); j++)
            if (usedBeds[j].available ||
                (usedBeds[j].available == 0
                    && another.leave_room >= usedBeds[j].time_expried)) {
                if (usedBeds[j].available == 0)
                    last.push_back(usedBeds[j].someone);

                usedBeds[j].available = 0;
                // 进入恢复室时间：手术结束时间+转运时间 与 床位可用时间的最大值
                another.enter_bed =
                    max(another.leave_room + mintues_operating_to_recovery,
                    usedBeds[j].time_expried);
                another.leave_bed =
                    another.enter_bed + another.mintues_recovery;
                another.bed_number = j + 1;
                usedBeds[j].someone = another;
                usedBeds[j].time_expried =
                    another.leave_bed + mintues_preparing_recovery;
                usedBeds[j].mintues_used += another.mintues_recovery;
                break;
            }
    }

    // 收集所有完成恢复的患者
    for (int i = 0; i < usedBeds.size(); i++)
        if (usedBeds[i].available == 0)
            last.push_back(usedBeds[i].someone);

    // 按患者编号排序，恢复原始顺序
    sort(last.begin(), last.end());

    int space = to_string(patients_counter).length();

    // 输出第一个表格：患者使用记录
    cout << " Patient          Operating Room          Recovery Room\n";
    cout << " #  Name     Room#  Begin   End      Bed#  Begin    End\n";
    cout << " ------------------------------------------------------\n";

    for (int i = 0; i < last.size(); i++) {
        cout << setw(2) << right << last[i].index;
        cout << "  ";
        cout << setw(10) << left << last[i].lastname;
        cout << setw(2) << right << last[i].room_number;
        cout << setw(8) << right << toTime(last[i].enter_room);
        cout << setw(8) << right << toTime(last[i].leave_room);
        cout << setw(7) << right << last[i].bed_number;
        cout << setw(8) << right << toTime(last[i].enter_bed);
        cout << setw(8) << right << toTime(last[i].leave_bed);
        cout << "\n";
    }

    // 计算最后一位患者离开恢复室的时间
    int last_leave_bed = 0;
    for (int i = 0; i < last.size(); i++)
        if (last_leave_bed < last[i].leave_bed)
            last_leave_bed = last[i].leave_bed;

    sort(usedRooms.begin(), usedRooms.end(), cmp_room);

    // 输出第二个表格：设施利用率统计
    cout << "\nFacility Utilization\n";
    cout << "Type  # Minutes  % Used\n";
    cout << "-------------------------\n";

    for (int i = 0; i < usedRooms.size(); i++) {
        cout << "Room";
        cout << setw(3) << right << usedRooms[i].index;
        cout << setw(8) << right << usedRooms[i].mintues_used;
        double percent =
            (double)(usedRooms[i].mintues_used) / (last_leave_bed -
            starting_mintues) * 100.0;
        cout << setw(8) << right << fixed << setprecision(2) << percent;
        cout << "\n";
    }

    for (int i = 0; i < usedBeds.size(); i++) {
        cout << "Bed";
        cout << setw(4) << right << usedBeds[i].index;
        cout << setw(8) << right << usedBeds[i].mintues_used;
        double percent =
            (double)(usedBeds[i].mintues_used) / (last_leave_bed -
            starting_mintues) * 100.0;
        cout << setw(8) << right << fixed << setprecision(2) << percent;
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);

    // 处理多组输入数据
    while (cin >> operating_rooms >> recovery_rooms
        >> starting_mintues >> mintues_operating_to_recovery
        >> mintues_preparing_operating >> mintues_preparing_recovery
        >> patients_counter) {
        // 将起始时间转换为分钟
        starting_mintues *= 60;

        // 初始化所有手术室
        for (int i = 1; i <= operating_rooms; i++) {
            room room;
            room.index = i;
            room.time_expried = starting_mintues;
            room.available = 1;
            room.mintues_used = 0;
            rooms.push(room);
        }

        cin.ignore();

        // 读取患者数据
        string lastname;
        for (int i = 1; i <= patients_counter; i++) {
            getline(cin, lastname);

            cin >> mintues_required_surgery >> mintues_required_recovery;
            cin.ignore();

            patient aPatient;
            aPatient.lastname = lastname;
            aPatient.index = i;
            aPatient.mintues_surgery = mintues_required_surgery;
            aPatient.mintues_recovery = mintues_required_recovery;
            patients.push_back(aPatient);
        }

        arrange();
    }

    return 0;
}
```
