[UVa 252 Trucking](https://blog.csdn.net/metaphysis/article/details/152929598)

## 题目概述

本题是一个复杂的物流调度模拟问题，需要模拟一个卡车货运公司的集装箱处理网络。系统包含多个中间集装箱处理中心（$\texttt{ICPC}$），每个中心有卸货门和转运门，需要处理拖车的到达、卸货、货物转运等操作，并计算平均等待时间和识别延迟货物。

## 问题分析

### 系统组成
1. **$\texttt{ICPC}$ 中心**：每个中心有 $\texttt{stripping doors}$（卸货门）和 $\texttt{relay doors}$（转运门）
2. **拖车**：运输货物的车辆，可能包含多个货物
3. **货物**：需要转运的货物，有体积、目的地等属性
4. **事件**：系统运行中的各种时间点事件

### 核心规则
1. **卸货门调度**：
   - 转运货物优先于本地货物
   - 相同类型货物中，运输时间长的优先
   - 卸货固定耗时 $2$ 小时

2. **转运门处理**：
   - 货物按目的地分类到不同转运门
   - 拖车装满（$100\%$）或当天所有货物到达时发车
   - 货物可以按 $1\%$ 为单位拆分

3. **时间约束**：
   - 每个目的地有最晚到达时间
   - 需要识别会迟到的货物

## 算法设计

### 数据结构
```cpp
struct Shipment {      // 货物
    int id, origin, next, volume, travelTime;
};

struct Trailer {       // 拖车
    int arrivalTime, centerId, shipmentCount, maxTravelTime;
    Shipment shipments[MAX_DOORS];
    bool hasRelay;
};

struct RelayDoor {     // 转运门
    int targetCenter, totalVolume, latestTime, sentVolume;
    vector<Shipment> shipments;
};

struct Event {         // 事件
    EventType type;    // 事件类型
    int time, doorId;  // 时间、门编号
    Trailer* trailerPtr; ICPC* centerPtr; Shipment shipment;
};
```

### 核心算法：事件驱动模拟

1. **事件类型**：
   - `TRAILER_ARRIVED`：拖车到达
   - `DOOR_FREE`：卸货门空闲
   - `SHIPMENT_STRIPPED`：货物卸货完成

2. **模拟流程**：
   - 使用优先队列处理事件，按时间排序
   - 处理同一时刻的所有事件
   - 每个时间点处理卸货和转运

3. **关键函数**：
   - `processStripping()`：处理拖车卸货
   - `processRelay()`：处理转运门货物发送
   - `processEvent()`：事件分发处理

## 实现细节

### 优先级调度
```cpp
bool Trailer::operator<(const Trailer& other) const {
    if (hasRelay && other.hasRelay) {
        if (maxTravelTime == other.maxTravelTime) 
            return arrivalTime > other.arrivalTime;
        return maxTravelTime < other.maxTravelTime;
    }
    if (hasRelay) return false;
    if (other.hasRelay) return true;
    return arrivalTime > other.arrivalTime;
}
```

### 货物拆分与装载
```cpp
void RelayDoor::processRelay(int currentTime, vector<Shipment>& lateShipments) {
    // 实现货物拆分和拖车装载逻辑
    // 当累计体积达到100%时发送拖车
    // 检查货物是否会在目的地迟到
}
```

## 复杂度分析

- **时间复杂度**：$O(E log E + N × D)$，其中 $E$ 是事件数量，$N$ 是中心数量，$D$ 是门数量
- **空间复杂度**：$O(N × D + M)$，其中 $M$ 是拖车数量

## 测试样例

### 输入样例
```
2
0 1 1
8 40 600
8 3 4
6 115 1200
2 95 1260
10 100 1440
4 55 1380
7
500 0 1
17 11 8 40 80
700 8 3
24 11 8 45 0
18 11 6 40 120
23 11 10 15 600
720 8 1
16 3 8 100 0
750 8 2
4 15 2 50 180
7 15 6 50 120
760 8 4
14 3 4 20 300
27 3 2 20 180
33 3 10 35 600
16 3 6 25 120
780 8 2
12 9 2 25 180
15 9 4 35 300
800 8 1
19 18 10 50 600
```

### 输出样例
```
There is no wait for a stripping door at ICPC 0.
The average wait for a stripping door at ICPC 8 is 63.3 minutes.

The late shipments are:
Id Origin Destination Volume
17  11  8  40
23  11  10  15
33  3  10  35
19  18  10  50
```

## 总结

本题是一个典型的事件驱动模拟问题，考察了对复杂业务逻辑的建模能力和对优先队列等数据结构的运用。关键点在于正确实现优先级调度规则和货物转运逻辑，以及准确计算等待时间和识别延迟货物。

---

## 参考代码

```cpp
// Trucking
// UVa ID: 252
// Verdict: Accepted
// Submission Date: 2025-10-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_CENTERS = 100 + 4;  // 最大中心数量
const int MAX_DOORS = 16;         // 每个中心最大门数

// 前向声明
struct ICPC;

// 货物结构体
struct Shipment {
    int id;        // 货物ID
    int origin;    // 始发中心
    int next;      // 下一个中转中心
    int volume;    // 货物体积（占拖车容量的百分比）
    int travelTime; // 运输时间（分钟）
};

// 拖车结构体
struct Trailer {
    int arrivalTime;       // 到达时间
    int centerId;          // 到达的中心编号
    int shipmentCount;     // 货物数量
    int maxTravelTime;     // 所有货物中最长的运输时间
    Shipment shipments[MAX_DOORS]; // 货物数组
    bool hasRelay;         // 是否有转运货物
    
    // 优先级比较运算符重载
    bool operator<(const Trailer& other) const {
        assert(centerId == other.centerId);
        // 转运货物优先于本地货物
        if (hasRelay && other.hasRelay) {
            // 都有转运货物时，运输时间长的优先
            if (maxTravelTime == other.maxTravelTime) 
                return arrivalTime > other.arrivalTime;
            return maxTravelTime < other.maxTravelTime;
        }
        // 只有一方有转运货物
        if (hasRelay) return false;    // 当前有转运，优先级更高
        if (other.hasRelay) return true; // 对方有转运，对方优先级更高
        // 都没有转运货物时，先到达的优先
        return arrivalTime > other.arrivalTime;
    }
};

// 转运门结构体
struct RelayDoor {
    int targetCenter;      // 目标中心编号
    int totalVolume;       // 发往该中心的总货量
    int latestTime;        // 最晚到达时间
    int sentVolume;        // 已发送货量
    vector<Shipment> shipments; // 等待发送的货物列表
    
    // 处理转运门的货物发送
    void processRelay(int currentTime, vector<Shipment>& lateShipments) {
        vector<Shipment> currentTrailer; // 当前准备发送的拖车
        int currentVolume = 0;           // 当前拖车已装载量
        
        // 遍历所有等待发送的货物
        for (auto& shipment : shipments) {
            Shipment remainingShipment = shipment;
            assert(shipment.next == targetCenter); // 验证目标中心
            assert(currentVolume <= 100);          // 验证当前装载量
            
            // 将货物加入当前拖车
            currentTrailer.push_back(shipment);
            
            // 检查是否需要拆分货物
            if (currentVolume + shipment.volume >= 100) {
                // 需要拆分：计算剩余货量
                remainingShipment.volume = currentVolume + shipment.volume - 100;
                // 调整当前拖车中该货物的数量
                currentTrailer.back().volume -= remainingShipment.volume;
            } else {
                // 货物可以完全装入
                remainingShipment.volume = 0;
            }
            
            // 更新当前拖车装载量
            currentVolume += currentTrailer.back().volume;
            
            // 如果拖车未满，继续处理下一个货物
            if (currentVolume < 100) {
                assert(remainingShipment.volume == 0);
                continue;
            }
            
            // 拖车已满，发送拖车
            assert(currentVolume == 100);
            
            // 检查每个货物是否会迟到
            for (auto& trailerItem : currentTrailer) {
                if (trailerItem.travelTime + currentTime > latestTime) {
                    lateShipments.push_back(trailerItem);
                }
                totalVolume -= trailerItem.volume; // 减少总货量
            }
            
            // 清空当前拖车，准备下一轮
            currentTrailer.clear();
            currentVolume = remainingShipment.volume;
            
            // 如果有剩余货物，加入下一轮处理
            if (remainingShipment.volume > 0) {
                currentTrailer.push_back(remainingShipment);
            }
        }
        
        // 清空原始货物列表
        shipments.clear();
        
        // 处理剩余的未满拖车
        if (currentTrailer.empty()) return;
        
        assert(currentVolume < 100);
        
        // 如果剩余货量等于总货量，说明是最后一批货物
        if (currentVolume == totalVolume) {
            // 发送最后一批货物
            for (auto& trailerItem : currentTrailer) {
                if (trailerItem.travelTime + currentTime > latestTime) {
                    lateShipments.push_back(trailerItem);
                }
                totalVolume -= trailerItem.volume;
            }
        } else {
            // 保留剩余货物等待下次发送
            shipments.assign(currentTrailer.begin(), currentTrailer.end());
        }
    }
};

// 事件类型枚举
enum EventType { 
    TRAILER_ARRIVED = 0,   // 拖车到达
    DOOR_FREE = 1,         // 卸货门空闲
    SHIPMENT_STRIPPED = 2  // 货物已卸货
};

// 事件结构体
struct Event {
    EventType type;        // 事件类型
    int time;              // 事件发生时间
    int doorId;            // 门编号
    
    // 事件优先级比较
    bool operator<(const Event& other) const {
        if (time != other.time) return time > other.time; // 时间早的优先
        if (type != other.type) return type < other.type; // 按类型排序
        return false;
    }
    
    Trailer* trailerPtr;   // 关联的拖车指针
    ICPC* centerPtr;       // 关联的中心指针
    Shipment shipment;     // 关联的货物
    
    Event(EventType eventType, int eventTime) 
        : type(eventType), time(eventTime), trailerPtr(nullptr), centerPtr(nullptr) {}
};

// 声明全局事件队列
extern priority_queue<Event> events;

// ICPC（集装箱处理中心）结构体
struct ICPC {
    int centerId;                      // 中心编号
    int strippingDoors;                // 卸货门数量
    int relayDoors;                    // 转运门数量
    bool isDoorUsed[MAX_DOORS];        // 卸货门占用状态
    vector<int> waitingTimes;          // 拖车等待时间记录
    vector<Shipment> lateShipments;    // 迟到货物列表
    RelayDoor relayDoorsArray[MAX_DOORS]; // 转运门数组
    priority_queue<Trailer> trailerQueue; // 等待卸货的拖车队列
    
    // 处理拖车卸货
    void processStripping(const Trailer& trailer, int currentTime, int doorIndex) {
        // 标记卸货门为占用状态
        isDoorUsed[doorIndex] = true;
        assert(doorIndex >= 0 && doorIndex < strippingDoors);
        
        // 创建卸货门释放事件（2小时后）
        Event doorEvent(DOOR_FREE, currentTime + 120);
        doorEvent.centerPtr = this;
        doorEvent.doorId = doorIndex;
        events.push(doorEvent);
        
        // 记录等待时间（如果拖车有等待）
        if (trailer.arrivalTime != currentTime) {
            assert(trailer.arrivalTime < currentTime);
            waitingTimes.push_back(currentTime - trailer.arrivalTime);
        }
        
        // 为每个转运货物创建卸货完成事件
        for (int i = 0; i < trailer.shipmentCount; i++) {
            const Shipment& shipment = trailer.shipments[i];
            // 本地货物不需要转运
            if (centerId == shipment.next) continue;
            
            Event stripEvent(SHIPMENT_STRIPPED, currentTime + 120);
            stripEvent.centerPtr = this;
            stripEvent.shipment = shipment;
            events.push(stripEvent);
        }
    }
    
    // 分配可用卸货门处理等待队列
    void processAllStripping(int currentTime) {
        for (int doorIndex = 0; doorIndex < strippingDoors; doorIndex++) {
            // 跳过被占用的门
            if (isDoorUsed[doorIndex]) continue;
            // 没有等待的拖车时退出
            if (trailerQueue.empty()) break;
            
            // 取出优先级最高的拖车进行卸货
            processStripping(trailerQueue.top(), currentTime, doorIndex);
            trailerQueue.pop();
        }
    }
    
    // 处理所有转运门的货物发送
    void processAllRelay(int currentTime) {
        for (int i = 0; i < relayDoors; i++) {
            relayDoorsArray[i].processRelay(currentTime, lateShipments);
        }
    }
    
    // 根据目标中心查找对应的转运门
    RelayDoor& findRelayDoor(const Shipment& shipment) {
        int relayIndex = -1;
        for (int i = 0; i < relayDoors; i++) {
            if (shipment.next == relayDoorsArray[i].targetCenter) {
                relayIndex = i;
                break;
            }
        }
        assert(relayIndex >= 0);
        return relayDoorsArray[relayIndex];
    }
};

// 定义全局事件队列
priority_queue<Event> events;

// ICPC输入重载运算符
istream& operator>>(istream& is, ICPC& center) {
    is >> center.centerId >> center.strippingDoors >> center.relayDoors;
    for (int i = 0; i < center.relayDoors; i++) {
        RelayDoor& relayDoor = center.relayDoorsArray[i];
        is >> relayDoor.targetCenter >> relayDoor.totalVolume >> relayDoor.latestTime;
        // 初始化转运门状态
        fill_n(center.isDoorUsed, MAX_DOORS, false);
        relayDoor.sentVolume = 0;
    }
    return is;
}

// 拖车输入重载运算符
istream& operator>>(istream& is, Trailer& trailer) {
    is >> trailer.arrivalTime >> trailer.centerId >> trailer.shipmentCount;
    trailer.hasRelay = false;
    trailer.maxTravelTime = -1;
    
    for (int i = 0; i < trailer.shipmentCount; i++) {
        Shipment& shipment = trailer.shipments[i];
        is >> shipment.id >> shipment.origin >> shipment.next >> shipment.volume >> shipment.travelTime;
        // 更新最长运输时间
        trailer.maxTravelTime = max(trailer.maxTravelTime, shipment.travelTime);
        // 检查是否有转运货物
        if (shipment.next != trailer.centerId) 
            trailer.hasRelay = true;
    }
    return is;
}

// 全局变量
int centerCount, trailerCount;
ICPC centers[MAX_CENTERS];
ICPC* centerMap[MAX_CENTERS];  // 中心编号到指针的映射
Trailer trailers[MAX_CENTERS]; // 拖车记录数组

// 事件处理函数
void processEvent(const Event& event) {
    int time = event.time;
    
    switch (event.type) {
        case TRAILER_ARRIVED:
            // 拖车到达：加入对应中心的等待队列
            centerMap[event.trailerPtr->centerId]->trailerQueue.push(*event.trailerPtr);
            break;
            
        case DOOR_FREE:
            // 卸货门空闲：标记门为可用状态
            assert(event.centerPtr);
            event.centerPtr->isDoorUsed[event.doorId] = false;
            break;
            
        case SHIPMENT_STRIPPED:
            // 货物卸货完成：将货物加入对应转运门
            assert(event.centerPtr);
            RelayDoor& relayDoor = event.centerPtr->findRelayDoor(event.shipment);
            relayDoor.shipments.push_back(event.shipment);
            break;
    }
}

int main() {
    while (cin >> centerCount && centerCount) {
        // 初始化中心映射
        memset(centerMap, 0, sizeof(centerMap));
        
        // 读取所有ICPC中心信息
        for (int i = 0; i < centerCount; i++) {
            ICPC& center = centers[i];
            cin >> center;
            centerMap[center.centerId] = &center;
        }
        
        // 读取拖车到达记录
        cin >> trailerCount;
        for (int i = 0; i < trailerCount; i++) {
            Trailer& trailer = trailers[i];
            cin >> trailer;
            // 创建拖车到达事件
            Event arrivalEvent(TRAILER_ARRIVED, trailer.arrivalTime);
            arrivalEvent.trailerPtr = &trailer;
            arrivalEvent.centerPtr = centerMap[trailer.centerId];
            events.push(arrivalEvent);
        }

        // 事件驱动模拟主循环
        while (!events.empty()) {
            int currentTime = events.top().time;
            
            // 处理同一时刻的所有事件
            while (!events.empty() && events.top().time == currentTime) {
                processEvent(events.top());
                events.pop();
            }

            // 每个中心处理卸货和转运
            for (int i = 0; i < centerCount; i++) {
                centers[i].processAllStripping(currentTime); // 分配卸货门
                centers[i].processAllRelay(currentTime);     // 处理转运发送
            }
        }

        // 输出每个中心的平均等待时间
        for (int i = 0; i < centerCount; i++) {
            ICPC& center = centers[i];
            if (center.waitingTimes.empty()) {
                cout << "There is no wait for a stripping door at ICPC " << center.centerId << "." << endl;
            } else {
                int sum = 0;
                for (int j = 0; j < center.waitingTimes.size(); j++) {
                    sum += center.waitingTimes[j];
                }
                // 计算平均值（保留一位小数）
                sum *= 10;
                sum /= center.waitingTimes.size();
                cout << "The average wait for a stripping door at ICPC " << center.centerId 
                     << " is " << sum / 10 << "." << sum % 10 << " minutes." << endl;
            }
        }
        
        // 输出迟到货物列表
        cout << "\nThe late shipments are:\nId Origin Destination Volume" << endl;
        for (int i = 0; i < centerCount; i++) {
            ICPC& center = centers[i];
            for (int j = 0; j < center.lateShipments.size(); j++) {
                Shipment& shipment = center.lateShipments[j];
                cout << setw(2) << shipment.id << setw(7) << shipment.origin 
                     << setw(12) << shipment.next << setw(7) << shipment.volume << endl;
            }
        }
    }

    return 0;
}
```
