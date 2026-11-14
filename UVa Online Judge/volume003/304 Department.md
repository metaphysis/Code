[UVa 304 Department](https://blog.csdn.net/metaphysis/article/details/161445536)

## 题目描述

安保部门的新总部大楼有多层楼层，每层楼的房间编号为 $xxyy$，其中 $yy$ 是房间号，$xx$ 是楼层号（$0 < xx, yy < 10$）。大楼配备了“循环式”电梯（$\texttt{pater-noster elevator}$），由多个轿厢组成，持续循环运行。

特工们需要访问总部，每次访问他们希望按房间号递增的顺序参观多个房间，并在每个房间停留一段时间。出于安全原因，**同一时间同一房间内只能有一名特工**，电梯也是同理。访问计划确保可以在一天内完成。每个特工每天最多访问总部一次。

每个特工从 $1$ 楼进入大楼，通过接待处，然后按照列表开始参观房间。特工按照房间号递增的顺序参观。特工之间有一个线性层级结构，每个特工分配了一个单字母个人代码。**资历高的特工代码字典序更小**。没有两个特工有相同的代码。

当多名特工想要进入同一个房间或同一部电梯时，他们必须排队。在队列中，他们按照代码顺序站立——**资历越高（代码越小）的越靠前**。电梯每隔 $5$ 秒（$\texttt{seconds}$）让队列最前面的特工进入。

特工在参观完最后一个房间后，如果需要，使用电梯前往 $1$ 楼，然后离开大楼。

### 时间设定

- **进入大楼**：通过接待处并到达电梯或 $1$ 楼的房间，需要 $30$ 秒
- **离开大楼**：走出电梯或 $1$ 楼的房间并通过接待处，需要 $30$ 秒
- **同层移动**：电梯到房间、房间到电梯、房间到房间，需要 $10$ 秒
- **电梯楼层移动**：上下一个楼层需要 $30$ 秒

### 输入格式

输入文件包含 $n \geq 0$ 个不同特工的访问记录。每个访问记录的第一行包含：
- 特工的代码 $C$（一个大写字母）
- 进入总部的时间，格式为 $HH:MM:SS$

接下来的若干行（至少一行）包含：
- 房间号（$xxyy$ 格式）
- 计划停留时间（秒）

房间列表按房间号递增顺序给出，以一行 `0` 结束。所有访问记录以一行 `.` 结束。

### 输出格式

输出包含每个特工访问的详细记录，按照特工代码递增的顺序输出。

每个特工的输出块：
- 第一行：特工代码
- 接下来若干行：每行包含**开始时间**、**结束时间**和**活动描述**
- 时间数据之间用一个空格分隔，描述与时间之间用一个空格分隔

**活动描述**可以是以下之一：
- `Entry`
- `Exit`
- `Waiting in elevator queue`
- `Waiting in front of room RoomNumber`
- `Transfer from room RoomNumber to room RoomNumber`
- `Transfer from elevator to room RoomNumber`
- `Transfer from RoomNumber to elevator`
- `Stay in room RoomNumber`
- `Stay in elevator`

每个输出块结束后打印一个空行。

### 样例输入

```
A 10:00:00
0101 100
0110 50
0202 90
0205 50
0
B 10:01:00
0105 100
0201 5
0205 200
0
.
```

### 样例输出（见原题，此处略）

---

## 题目分析

### 问题的本质

这是一个**离散事件模拟**问题。多个特工按照预先规划的行程在大楼内移动，由于房间和电梯的容量限制（每次只能容纳一人），特工可能需要在房间门口或电梯前排队等待。

核心挑战：
1. 每个特工的行程是预定的（房间列表按递增顺序）
2. 资源竞争：房间和电梯都是互斥资源
3. 排队规则：按特工代码的字典序（资历高低）
4. 电梯的特殊规则：每 $5$ 秒允许一名特工进入
5. 需要模拟所有特工的所有活动，并记录完整的时间线

### 关键观察

**观察 1**：特工按房间号递增顺序参观，意味着行程中房间的顺序是确定的。但不同特工的行程可能相交，产生资源竞争。

**观察 2**：由于资源互斥，特工的实际活动时间可能会比计划时间延迟。延迟可能来自：
- 在房间门口等待前一个特工离开
- 在电梯前等待电梯可用（每 $5$ 秒一人）

**观察 3**：特工之间的优先级由代码决定（$\texttt{A} < \texttt{B} < \dots < \texttt{Z}$），这决定了排队顺序。

**观察 4**：电梯是特殊的共享资源——它在每个楼层都可能被不同特工使用，且使用规则是每 $5$ 秒允许一人进入。

---

## 解题思路

### 步骤一：数据建模

定义三个核心数据结构：

1. **`schedule`**：特工的预定行程
   - `floor`：楼层号
   - `room`：房间号
   - `duration`：停留时间
   - `room_label`：房间标签（四位字符串）

2. **`event`**：特工的具体活动事件
   - `details`：活动描述字符串
   - `room_label`：关联的房间号（用于排队标识）
   - `is_elevator_event`：是否为电梯相关事件
   - `start_time`：事件开始时间（秒）
   - `duration`：事件持续时间
   - `waiting_time`：开始等待的时间（仅在等待事件中有意义）
   - `waiting_duration`：等待的持续时间

3. **`agent`**：特工信息
   - `enter_time`：进入大楼的时间
   - `schedules`：预定行程列表
   - `events`：实际活动事件列表
   - `event_indexer`：事件索引映射（房间标签 → 事件在 `events` 中的位置）

### 步骤二：生成初始事件序列（无竞争）

对于每个特工，首先生成一个**理想化的事件序列**，假设没有竞争、没有等待。这个序列包括：

1. `Entry`（$30$ 秒）
2. 对于每个房间：
   - 如果需要跨楼层：`Stay in elevator`（$30 \times$ 楼层差）→ `Transfer from elevator to room`（$10$ 秒）
   - 如果需要同层移动：`Transfer from room to room`（$10$ 秒）
   - `Stay in room`（停留时间）
3. 离开大楼：
   - 如果需要下楼：`Transfer from room to elevator`（$10$ 秒）→ `Stay in elevator`（$30 \times$ 楼层差）
   - `Exit`（$30$ 秒）

在这个阶段，每个特工的事件开始时间是基于进入时间累加计算的。

同时，为每个房间和每个楼层的电梯建立索引映射：
- `event_indexer[room_label]`：指向特工在该房间的 `Stay in room` 事件
- `event_indexer["elevator" + floor]`：指向特工在该楼层使用电梯的事件

### 步骤三：处理资源竞争

这是模拟的核心部分。对于每个资源（房间或电梯），需要：

1. 找出所有需要该资源的事件
2. 按事件开始时间排序（开始早的先访问）
3. 按排队规则处理（相同开始时间时，代码小的优先）
4. 更新后续事件的开始时间（延迟传播）

**房间竞争处理**：

对于每个房间，收集所有要访问该房间的特工事件。由于房间一次只能一人，需要按顺序处理。如果多个特工同时到达，按代码排序排队。

**电梯竞争处理**：

电梯的规则比房间复杂：
- 电梯每 $5$ 秒允许一名特工进入
- 电梯在不同楼层是独立的资源（即 $1$ 楼的电梯队列和 $2$ 楼的电梯队列互不影响）
- 需要按楼层分别处理

关键代码逻辑（`visiting` 函数）：

```cpp
void visiting(string label) {
    bool is_room_event = (label.find("elevator") == label.npos);
    
    while (true) {
        // 找到第一个可以访问该资源的特工
        int first_visitor = -1, minimum_start_time = INF;
        for (int k = 'A'; k <= 'Z'; k++) {
            if (agents[k].event_indexer.count(label) && !visited[k]) {
                int start_time = agents[k].events[index].start_time;
                
                // 电梯特殊规则：每5秒才能进入一人
                if (!is_room_event) {
                    if (start_time % 5 > 0)
                        start_time += (5 - (start_time % 5));
                }
                
                if (start_time < minimum_start_time) {
                    minimum_start_time = start_time;
                    first_visitor = k;
                }
            }
        }
        
        if (first_visitor == -1) break;
        
        // 构建等待队列（按代码顺序）
        priority_queue<char, vector<char>, greater<char>> waiting_queue;
        waiting_queue.push(first_visitor);
        
        int last_start_time = minimum_start_time;
        
        // 处理队列中的每个特工
        while (!waiting_queue.empty()) {
            int current = waiting_queue.top();
            waiting_queue.pop();
            
            // 计算等待时间并更新事件
            int delay = last_start_time - agents[current].events[index].start_time;
            if (delay > 0) {
                // 记录等待事件
            }
            
            // 更新该特工后续所有事件的开始时间
            for (int k = index; k < agents[current].events.size(); k++)
                agents[current].events[k].start_time += delay;
            
            // 当前事件持续时间
            int duration = is_room_event ? 
                agents[current].events[index].duration : 5;
            
            // 找出下一个可以加入队列的特工
            for (int k = 'A'; k <= 'Z'; k++) {
                if (agents[k].event_indexer.count(label) && !visited[k]) {
                    if (agents[k].events[agents[k].event_indexer[label]].start_time 
                        <= last_start_time + duration) {
                        waiting_queue.push(k);
                        visited[k] = true;
                    }
                }
            }
            last_start_time += duration;
        }
    }
}
```

### 步骤四：时间格式化输出

实现两个辅助函数：
- `getTime(string text)`：将 $HH:MM:SS$ 格式转换为秒数
- `toTime(int seconds)`：将秒数转换为 $HH:MM:SS$ 格式（两位填充）

### 步骤五：按正确顺序输出

按照特工代码 $\texttt{A} \sim \texttt{Z}$ 的顺序输出每个特工的完整事件记录。对于每个事件：
- 如果有等待事件，先输出等待时间段和等待描述
- 然后输出实际活动时间段和活动描述
- 每个输出块后跟一个空行

---

## 算法复杂度分析

### 时间复杂度

- 特工数量最多 $26$ 个
- 每个特工的房间数量最多假设为 $K$（房间号 $xxyy$ 最多 $99 \times 99 = 9801$ 个可能，但实际输入有限）
- 资源数量：房间数 + 楼层数（最多 $100 + 20 = 120$ 个）
- 每个资源需要处理其上的所有特工事件，并按优先级队列处理
- 总复杂度：$O(\text{resources} \times \text{agents}^2)$，在 $26$ 个特工的情况下完全可行

### 空间复杂度

- 存储每个特工的行程和事件：$O(\text{agents} \times \text{rooms})$
- 事件索引映射：$O(\text{agents} \times \text{events})$
- 总空间复杂度：$O(26 \times \text{rooms})$，非常小

---

## 正确性证明

**引理 1**：初始事件序列（无竞争）正确表示了特工在理想情况下的活动时间线。

证明：根据题目给出的时间规则累加计算，每个活动的开始时间和持续时间都是正确的。$\square$

**引理 2**：`visiting` 函数正确模拟了资源竞争和排队。

证明：
- 每次找到最早到达资源的特工（考虑电梯的 $5$ 秒对齐规则）
- 按代码顺序排队（使用最小堆 `priority_queue`）
- 每次处理一个特工后，检查是否有其他特工在本次活动结束前到达，如果有，加入队列
- 队列处理完毕后，所有等待该资源的特工都被正确处理
- 延迟被正确传播到受影响特工的所有后续事件 $\square$

**引理 3**：按楼层分别处理电梯是正确的。

证明：题目中电梯在不同楼层被视为不同的资源，因为特工在不同楼层使用电梯时互不影响。$\square$

**引理 4**：输出顺序（按代码递增）符合题目要求。

证明：直接按 $\texttt{A}$ 到 $\texttt{Z}$ 遍历输出即可。$\square$

---

## 参考代码

```cpp
// Department
// UVa ID: 304
// Verdict: Accepted
// Submission Date: 2016-07-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 事件结构体：表示特工的一个具体活动
struct event
{
    string details;              // 活动描述
    string room_label;           // 关联的房间标签（用于排队标识）
    bool is_elevator_event = false;  // 是否为电梯相关事件
    int start_time = 0;          // 开始时间（秒）
    int duration = 0;            // 持续时间
    int waiting_time = 0;        // 开始等待的时间
    int waiting_duration = 0;    // 等待持续时间
};

// 行程结构体：特工的预定房间访问计划
struct schedule
{
    int floor, room, duration;   // 楼层、房间号、停留时间
    string room_label;           // 房间标签（四位字符串）
};

// 特工结构体：存储特工的所有信息
struct agent
{
    int enter_time;                      // 进入大楼时间
    vector<schedule> schedules;          // 预定行程列表
    vector<event> events;                // 实际活动事件列表
    map<string, int> event_indexer;      // 房间标签 → 事件索引
};

map<char, agent> agents;  // 代码 → 特工信息

// 将 HH:MM:SS 格式的时间字符串转换为秒数
int getTime(string text)
{
    return stoi(text.substr(0, 2)) * 3600 + 
           stoi(text.substr(3, 2)) * 60 + 
           stoi(text.substr(6, 2));
}

// 将秒数转换为 HH:MM:SS 格式并输出
void toTime(int seconds)
{
    cout << setw(2) << setfill('0') << seconds / 3600 << ":";
    cout << setw(2) << setfill('0') << (seconds % 3600) / 60 << ":";
    cout << setw(2) << setfill('0') << seconds % 60;
}

// 根据楼层和房间号生成四位房间标签
string getLabel(int floor, int room)
{
    string label;
    label += (floor < 10 ? "0" : "") + to_string(floor);
    label += (room < 10 ? "0" : "") + to_string(room);
    return label;
}

// 处理指定资源（房间或电梯）的访问排队
// label: 资源标识（房间标签如"0101"，或电梯标识如"elevator1"）
void visiting(string label)
{
    bool is_room_event = (label.find("elevator") == label.npos);
    map<char, bool> visited;  // 记录特工是否已处理

    while (true)
    {
        // 找到第一个可以访问该资源的特工
        int first_visitor = -1, minimum_start_time = 100000;
        for (int k = 'A'; k <= 'Z'; k++)
        {
            if (agents[k].event_indexer.count(label) && visited[k] == false)
            {
                int start_time = agents[k].events[agents[k].event_indexer[label]].start_time;
                
                // 电梯特殊规则：每5秒才能进入一人，需要对齐到5的倍数
                if (is_room_event == false)
                {
                    if (start_time % 5 > 0)
                        start_time += (5 - (start_time % 5));
                }

                if (start_time < minimum_start_time)
                {
                    minimum_start_time = start_time;
                    first_visitor = k;
                }
            }
        }

        // 没有更多特工需要访问该资源
        if (first_visitor == -1)
            return;

        int event_index = agents[first_visitor].event_indexer[label];
        int last_start_time = minimum_start_time;
        agents[first_visitor].events[event_index].waiting_duration = 0;

        visited[first_visitor] = true;

        // 等待队列：按代码升序（资历高的在前）
        priority_queue<char, vector<char>, greater<char>> waiting_queue;
        waiting_queue.push(first_visitor);

        // 处理队列中的所有特工
        while (!waiting_queue.empty())
        {
            int current_user = waiting_queue.top();
            waiting_queue.pop();

            event_index = agents[current_user].event_indexer[label];
            int delay = last_start_time - agents[current_user].events[event_index].start_time;
            if (delay > 0)
            {
                // 记录等待事件
                agents[current_user].events[event_index].waiting_time = 
                    agents[current_user].events[event_index].start_time;
                agents[current_user].events[event_index].waiting_duration = delay;
            }

            // 将延迟传播到该特工的所有后续事件
            for (int k = event_index; k < agents[current_user].events.size(); k++)
                agents[current_user].events[k].start_time += delay;

            // 当前活动的持续时间
            int last_duration = 5;
            if (is_room_event)
                last_duration = agents[current_user].events[event_index].duration;

            // 找出下一个可以加入队列的特工
            for (int k = 'A'; k <= 'Z'; k++)
                if (agents[k].event_indexer.count(label) && visited[k] == false)
                {
                    if (agents[k].events[agents[k].event_indexer[label]].start_time <= last_start_time + last_duration)
                    {
                        waiting_queue.push(k);
                        visited[k] = true;
                    }
                }
            last_start_time += last_duration;
        }
    }
}

// 为每个特工生成初始事件序列（无竞争的理想情况）
void getSchedule()
{
    for (int i = 'A'; i <= 'Z'; i++)
    {
        if (agents[i].schedules.size() == 0)
            continue;

        int last_time = agents[i].enter_time;
        event aEvent;

        // 1. 进入大楼
        aEvent.details = "Entry";
        aEvent.start_time = last_time;
        aEvent.duration = 30;
        agents[i].events.push_back(aEvent);
        last_time += aEvent.duration;

        // 2. 依次访问每个房间
        for (int j = 0; j < agents[i].schedules.size(); j++)
        {
            if (j == 0)  // 第一个房间
            {
                // 如果第一个房间不在1楼，需要坐电梯
                if (agents[i].schedules[j].floor > 1)
                {
                    aEvent.details = "Stay in elevator";
                    aEvent.is_elevator_event = true;
                    aEvent.start_time = last_time;
                    aEvent.duration = 30 * (agents[i].schedules[j].floor - 1);
                    agents[i].events.push_back(aEvent);
                    agents[i].event_indexer["elevator1"] = agents[i].events.size() - 1;
                    last_time += aEvent.duration;
                    
                    aEvent.details = "Transfer from elevator to room " + agents[i].schedules[j].room_label;
                    aEvent.is_elevator_event = false;
                    aEvent.start_time = last_time;
                    aEvent.duration = 10;
                    agents[i].events.push_back(aEvent);
                    last_time += aEvent.duration;
                }

                aEvent.details = "Stay in room " + agents[i].schedules[j].room_label;
                aEvent.is_elevator_event = false;
                aEvent.room_label = agents[i].schedules[j].room_label;
                aEvent.start_time = last_time;
                aEvent.duration = agents[i].schedules[j].duration;
                agents[i].events.push_back(aEvent);
                agents[i].event_indexer[agents[i].schedules[j].room_label] = agents[i].events.size() - 1;
                last_time += aEvent.duration;
            }
            else  // 后续房间
            {
                // 如果楼层变化，需要坐电梯
                if (agents[i].schedules[j].floor != agents[i].schedules[j - 1].floor)
                {
                    aEvent.details = "Transfer from room " + agents[i].schedules[j - 1].room_label + " to elevator";
                    aEvent.start_time = last_time;
                    aEvent.duration = 10;
                    agents[i].events.push_back(aEvent);
                    last_time += aEvent.duration;
                    
                    aEvent.details = "Stay in elevator";
                    aEvent.is_elevator_event = true;
                    aEvent.start_time = last_time;
                    aEvent.duration = 30 * abs(agents[i].schedules[j].floor - agents[i].schedules[j - 1].floor);
                    agents[i].events.push_back(aEvent);
                    agents[i].event_indexer["elevator" + to_string(agents[i].schedules[j - 1].floor)] = agents[i].events.size() - 1;
                    last_time += aEvent.duration;
                    
                    aEvent.details = "Transfer from elevator to room " + agents[i].schedules[j].room_label;
                    aEvent.start_time = last_time;
                    aEvent.duration = 10;
                    agents[i].events.push_back(aEvent);
                    last_time += aEvent.duration;
                }
                else  // 同层移动
                {
                    aEvent.details = "Transfer from room " + agents[i].schedules[j - 1].room_label + " to room " + agents[i].schedules[j].room_label;
                    aEvent.start_time = last_time;
                    aEvent.duration = 10;
                    agents[i].events.push_back(aEvent);
                    last_time += aEvent.duration;
                }

                aEvent.details = "Stay in room " + agents[i].schedules[j].room_label;
                aEvent.is_elevator_event = false;
                aEvent.room_label = agents[i].schedules[j].room_label;
                aEvent.start_time = last_time;
                aEvent.duration = agents[i].schedules[j].duration;
                agents[i].events.push_back(aEvent);
                agents[i].event_indexer[agents[i].schedules[j].room_label] = agents[i].events.size() - 1;
                last_time += aEvent.duration;
            }
        }

        // 3. 离开大楼
        if (agents[i].schedules.back().floor > 1)
        {
            aEvent.details = "Transfer from room " + agents[i].schedules.back().room_label + " to elevator";
            aEvent.start_time = last_time;
            aEvent.duration = 10;
            agents[i].events.push_back(aEvent);
            last_time += aEvent.duration;
            
            aEvent.details = "Stay in elevator";
            aEvent.is_elevator_event = true;
            aEvent.start_time = last_time;
            aEvent.duration = 30 * (agents[i].schedules.back().floor - 1);
            agents[i].events.push_back(aEvent);
            agents[i].event_indexer["elevator" + to_string(agents[i].schedules.back().floor)] = agents[i].events.size() - 1;
            last_time += aEvent.duration;
        }

        aEvent.details = "Exit";
        aEvent.start_time = last_time;
        aEvent.duration = 30;
        agents[i].events.push_back(aEvent);
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string block;
    while (cin >> block, block != ".")
    {
        agent aAgent;
        char code = block.front();
        cin >> block;
        aAgent.enter_time = getTime(block);

        // 读取房间列表直到遇到 0
        while (cin >> block, block != "0")
        {
            schedule aAction;
            aAction.floor = stoi(block.substr(0, 2));
            aAction.room = stoi(block.substr(2, 2));
            aAction.room_label = block;
            cin >> aAction.duration;
            aAgent.schedules.push_back(aAction);
        }
        agents[code] = aAgent;
    }

    // 生成初始事件序列
    getSchedule();

    // 按楼层、房间、电梯的顺序处理资源竞争
    for (int floor = 1; floor < 20; floor++)
    {
        // 处理本层的所有房间队列
        for (int room = 1; room < 20; room++)
            visiting(getLabel(floor, room));
            
        // 处理本层的电梯队列
        visiting("elevator" + to_string(floor));
    }

    // 按特工代码顺序输出结果
    for (int i = 'A'; i <= 'Z'; i++)
    {
        if (agents[i].events.size() == 0)
            continue;
        
        cout << (char)(i) << endl;
        for (int j = 0; j < agents[i].events.size(); j++)
        {
            // 如果有等待事件，先输出等待时间段
            if (agents[i].events[j].waiting_duration > 0)
            {
                toTime(agents[i].events[j].waiting_time);
                cout << " ";
                toTime(agents[i].events[j].waiting_time + agents[i].events[j].waiting_duration);
                cout << " ";

                if (agents[i].events[j].is_elevator_event)
                    cout << "Waiting in elevator queue" << endl;
                else
                    cout << "Waiting in front of room " << agents[i].events[j].room_label << endl;
            }
            
            // 输出实际活动时间段
            toTime(agents[i].events[j].start_time);
            cout << " ";
            toTime(agents[i].events[j].start_time + agents[i].events[j].duration);
            cout << " ";
            cout << agents[i].events[j].details << endl;
        }
        cout << endl;
    }

	return 0;
}
```

---

## 总结

本题的核心在于：
1. **事件驱动的模拟框架**：将特工的所有活动抽象为事件序列
2. **资源竞争处理**：房间和电梯作为互斥资源，需要排队
3. **优先级规则**：按代码字典序决定排队顺序
4. **电梯特殊规则**：每 $5$ 秒允许一人进入
5. **延迟传播**：等待时间会影响后续所有活动

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 初始事件生成 | 基于预定行程和时间规则累加计算 |
| 资源标识 | 房间用四位标签，电梯用 `elevator` + 楼层 |
| 排队处理 | 使用优先队列维护等待队列 |
| 电梯对齐 | 进入时间需对齐到 $5$ 的倍数 |
| 延迟传播 | 更新特工从当前事件开始的所有后续事件 |
| 输出格式 | 等待事件在前，实际活动在后，每个块后空行 |

### 模拟的核心思想

这种“先构造理想时间线，再处理冲突”的模拟方法，在处理资源竞争类问题时非常有效。它避免了在时间线上逐步推进的复杂逻辑，而是通过**冲突检测和延迟修正**来得到最终结果。
