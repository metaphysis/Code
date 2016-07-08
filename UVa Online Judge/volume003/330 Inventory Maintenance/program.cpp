// Inventory Maintenance
// UVa IDs: 330
// Verdict: Accepted
// Submission Date: 2016-07-07
// UVa Run Time: 0.290s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct item
{
    string item_name;
    int quantity;
    double item_cost, item_selling_price;
};

double selling = 0.0, cost = 0.0, loss = 0.0;
map<string, item> inventory;

void report()
{
    double total_value = 0.0;
    
    cout << "                  INVENTORY REPORT" << endl;
    cout << "Item Name     Buy At      Sell At      On Hand        Value" << endl;
    cout << "---------     ------      -------      -------        -----" << endl;
    
    for (auto something : inventory)
    {
        cout << setw(14) << left << something.second.item_name;
        cout << setw(6) << right << fixed << setprecision(2) << something.second.item_cost;
        cout << setw(13) << right << fixed << setprecision(2) << something.second.item_selling_price;
        cout << setw(13) << right << something.second.quantity;
        
        double value = something.second.item_cost * something.second.quantity;
        total_value += value;
        cout << setw(13) << right << fixed << setprecision(2) << value;
        cout << endl;
    }

    cout << "------------------------" << endl;
    cout << "Total value of inventory                      ";
    cout << setw(13) << right << fixed << setprecision(2) << total_value << endl;
    cout << "Profit since last report                      ";
    cout << setw(13) << right << fixed << setprecision(2) << (selling - cost - loss) << endl;
    cout << endl;
    
    selling = 0.0, cost = 0.0, loss = 0.0;
}

void add()
{
    string item_name; double item_cost, item_selling_price;
    cin >> item_name >> item_cost >> item_selling_price;
    inventory[item_name] = (item){item_name, 0, item_cost, item_selling_price};
}

void remove()
{
    string item_name;
    cin >> item_name;
    if (inventory[item_name].quantity > 0)
        loss += inventory[item_name].quantity * inventory[item_name].item_cost;
    inventory.erase(item_name);
}

void sell()
{
    string item_name; int quantity;
    cin >> item_name >> quantity;
    if (inventory[item_name].quantity >= quantity)
    {
        selling += inventory[item_name].item_selling_price * quantity;
        cost += inventory[item_name].item_cost * quantity;
        inventory[item_name].quantity -= quantity;
    }
    else
    {
        selling += inventory[item_name].item_selling_price * inventory[item_name].quantity;
        cost += inventory[item_name].item_cost * inventory[item_name].quantity;
        inventory[item_name].quantity = 0;
    }
}

void buy()
{
    string item_name; int quantity;
    cin >> item_name >> quantity;
    inventory[item_name].quantity += quantity;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string action;
    while (cin >> action)
    {
        if (action == "*") break;
        if (action == "report") report();
        if (action == "new") add();
        if (action == "delete") remove();
        if (action == "sell") sell();
        if (action == "buy") buy();
    }
    
	return 0;
}
