// Stock Prices
// UVa ID: 12266
// Verdict: Accepted
// Submission Date: 2026-01-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 定义订单结构体
struct Order {
    int shares; // 订单份额
    int price;  // 订单价格
};

// 比较器：用于卖出订单簿（小顶堆，价格低的优先）
struct SellCompare {
    bool operator()(const Order& a, const Order& b) const {
        return a.price > b.price; // 注意：优先队列默认是大顶堆，用大于号实现小顶堆
    }
};

// 比较器：用于买入订单簿（大顶堆，价格高的优先）
struct BuyCompare {
    bool operator()(const Order& a, const Order& b) const {
        return a.price < b.price; // 默认就是大顶堆比较方式
    }
};

// 处理单个测试用例
void processTestCase() {
    int n;
    cin >> n;
    // 卖出订单簿（小顶堆）
    priority_queue<Order, vector<Order>, SellCompare> sellBook;
    // 买入订单簿（大顶堆）
    priority_queue<Order, vector<Order>, BuyCompare> buyBook;
    int lastDealPrice = -1; // 最后一次成交价，初始未定义

    for (int i = 0; i < n; ++i) {
        string type, dummy1, dummy2; // dummy1 和 dummy2 用于读取 "shares at"
        int shares, price;
        cin >> type >> shares >> dummy1 >> dummy2 >> price;

        // 将新订单加入对应的订单簿
        if (type == "buy") {
            buyBook.push({shares, price});
        } else { // type == "sell"
            sellBook.push({shares, price});
        }

        // 核心：检查并执行所有可能的交易
        while (!buyBook.empty() && !sellBook.empty() && buyBook.top().price >= sellBook.top().price) {
            // 取出当前最优的买入和卖出订单
            Order buyOrder = buyBook.top(); buyBook.pop();
            Order sellOrder = sellBook.top(); sellBook.pop();

            // 计算成交数量
            int tradeShares = min(buyOrder.shares, sellOrder.shares);
            // 更新最后一次成交价格为卖出价
            lastDealPrice = sellOrder.price;

            // 更新订单剩余份额
            buyOrder.shares -= tradeShares;
            sellOrder.shares -= tradeShares;

            // 如果订单还有剩余，重新放回订单簿
            if (buyOrder.shares > 0) buyBook.push(buyOrder);
            if (sellOrder.shares > 0) sellBook.push(sellOrder);
        }

        // 输出处理完当前订单后的状态
        // 当前卖出价：卖出订单簿顶部的价格（若无则 -1）
        int askPrice = sellBook.empty() ? -1 : sellBook.top().price;
        // 当前买入价：买入订单簿顶部的价格（若无则 -1）
        int bidPrice = buyBook.empty() ? -1 : buyBook.top().price;

        // 格式化输出
        if (askPrice == -1) cout << "- ";
        else cout << askPrice << " ";

        if (bidPrice == -1) cout << "- ";
        else cout << bidPrice << " ";

        if (lastDealPrice == -1) cout << "-\n";
        else cout << lastDealPrice << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) processTestCase();
    return 0;
}
