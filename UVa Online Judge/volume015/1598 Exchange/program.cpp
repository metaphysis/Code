// Exchange
// UVa ID: 1598
// Verdict: Accepted
// Submission Date: 2025-11-22
// UVa Run Time: 1.530s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 订单结构体
struct Order {
    int size;    // 订单数量
    int price;   // 订单价格
    bool isBuy;  // 是否为买入订单
    // 构造函数，提供默认参数以便vector resize使用
    Order(int s = 0, int p = 0, bool buy = false) : size(s), price(p), isBuy(buy) {}
};

// 订单簿类，封装所有订单簿操作
struct OrderBook {
    // 买入订单：价格降序排列，每个价格对应订单索引列表
    map<int, vector<int>, greater<int>> buyOrders;
    // 卖出订单：价格升序排列，每个价格对应订单索引列表  
    map<int, vector<int>> sellOrders;
    // 存储所有订单
    vector<Order> allOrders;
    // 记录每个订单是否活跃
    vector<bool> active;
    
    // 初始化订单簿
    void init(int n) {
        buyOrders.clear();
        sellOrders.clear();
        allOrders.resize(n + 1);  // 索引从1开始
        active.assign(n + 1, false);
    }
    
    // 输出当前报价
    void printQuote() {
        int bidSize = 0, bidPrice = 0, askSize = 0, askPrice = 99999;
        
        // 查找最佳买入价和数量
        for (auto& pair : buyOrders) {
            int price = pair.first;
            int totalSize = 0;
            // 统计该价格下所有活跃订单的总数量
            for (int orderId : pair.second) {
                if (active[orderId]) {
                    totalSize += allOrders[orderId].size;
                }
            }
            if (totalSize > 0) {
                bidSize = totalSize;
                bidPrice = price;
                break;  // 找到最高价就退出
            }
        }
        
        // 查找最佳卖出价和数量
        for (auto& pair : sellOrders) {
            int price = pair.first;
            int totalSize = 0;
            // 统计该价格下所有活跃订单的总数量
            for (int orderId : pair.second) {
                if (active[orderId]) {
                    totalSize += allOrders[orderId].size;
                }
            }
            if (totalSize > 0) {
                askSize = totalSize;
                askPrice = price;
                break;  // 找到最低价就退出
            }
        }
        
        // 输出报价
        cout << "QUOTE " << bidSize << " " << bidPrice << " - " << askSize << " " << askPrice << endl;
    }
    
    // 处理买入订单
    void processBuy(int orderId) {
        Order& order = allOrders[orderId];  // 获取订单引用
        
        // 当订单还有数量且存在可匹配的卖出订单时循环
        while (order.size > 0 && !sellOrders.empty()) {
            auto it = sellOrders.begin();  // 获取最低卖出价
            int bestAsk = it->first;
            
            // 如果最低卖出价高于买入订单价格，无法匹配
            if (bestAsk > order.price) break;
            
            auto& orderList = it->second;  // 该价格下的订单列表
            
            // 遍历该价格下的所有订单（FIFO顺序）
            for (int i = 0; i < orderList.size() && order.size > 0; ) {
                int sellOrderId = orderList[i];
                
                // 跳过非活跃订单
                if (!active[sellOrderId]) {
                    orderList.erase(orderList.begin() + i);
                    continue;
                }
                
                Order& sellOrder = allOrders[sellOrderId];
                // 计算交易数量（取两者较小值）
                int tradeSize = min(order.size, sellOrder.size);
                // 输出交易信息
                cout << "TRADE " << tradeSize << " " << bestAsk << endl;
                
                // 更新订单数量
                order.size -= tradeSize;
                sellOrder.size -= tradeSize;
                
                // 如果卖出订单数量归零，标记为非活跃并移除
                if (sellOrder.size == 0) {
                    active[sellOrderId] = false;
                    orderList.erase(orderList.begin() + i);
                } else {
                    i++;  // 移动到下一个订单
                    break;  // 部分成交后退出当前价格级别的匹配
                }
            }
            
            // 如果该价格下没有活跃订单了，从订单簿中移除
            if (orderList.empty()) {
                sellOrders.erase(it);
            }
        }
        
        // 如果订单还有剩余数量，添加到买入订单簿
        if (order.size > 0) {
            buyOrders[order.price].push_back(orderId);
            active[orderId] = true;
        }
    }
    
    // 处理卖出订单（逻辑与买入对称）
    void processSell(int orderId) {
        Order& order = allOrders[orderId];
        
        while (order.size > 0 && !buyOrders.empty()) {
            auto it = buyOrders.begin();  // 获取最高买入价
            int bestBid = it->first;
            
            // 如果最高买入价低于卖出订单价格，无法匹配
            if (bestBid < order.price) break;
            
            auto& orderList = it->second;
            
            for (int i = 0; i < orderList.size() && order.size > 0; ) {
                int buyOrderId = orderList[i];
                
                if (!active[buyOrderId]) {
                    orderList.erase(orderList.begin() + i);
                    continue;
                }
                
                Order& buyOrder = allOrders[buyOrderId];
                int tradeSize = min(order.size, buyOrder.size);
                cout << "TRADE " << tradeSize << " " << bestBid << endl;
                
                order.size -= tradeSize;
                buyOrder.size -= tradeSize;
                
                if (buyOrder.size == 0) {
                    active[buyOrderId] = false;
                    orderList.erase(orderList.begin() + i);
                } else {
                    i++;
                    break;
                }
            }
            
            if (orderList.empty()) {
                buyOrders.erase(it);
            }
        }
        
        if (order.size > 0) {
            sellOrders[order.price].push_back(orderId);
            active[orderId] = true;
        }
    }
    
    // 处理取消订单请求
    void processCancel(int orderId) {
        // 检查订单编号有效性且订单当前活跃
        if (orderId >= 1 && orderId < allOrders.size() && active[orderId]) {
            active[orderId] = false;  // 标记为非活跃
        }
    }
};

int main() {
    int n;
    bool firstCase = true;  // 标记是否为第一个测试用例
    OrderBook book;         // 订单簿实例
    
    // 循环处理每个测试用例
    while (cin >> n) {
        // 测试用例间输出空行（第一个除外）
        if (!firstCase) cout << endl;
        firstCase = false;
        
        // 初始化订单簿
        book.init(n);
        
        // 处理n条消息
        for (int i = 1; i <= n; i++) {
            string type;
            cin >> type;
            
            if (type == "BUY") {
                int q, p;
                cin >> q >> p;
                // 创建买入订单并处理
                book.allOrders[i] = Order(q, p, true);
                book.processBuy(i);
            } else if (type == "SELL") {
                int q, p;
                cin >> q >> p;
                // 创建卖出订单并处理
                book.allOrders[i] = Order(q, p, false);
                book.processSell(i);
            } else if (type == "CANCEL") {
                int id;
                cin >> id;
                // 处理取消订单请求
                book.processCancel(id);
            }
            
            // 每次消息处理后输出当前报价
            book.printQuote();
        }
    }
    
    return 0;
}
