// Telephone Tangles
// UVa IDs: 139
// Verdict: Accepted
// Submission Date: 2016-01-19
// UVa Run Time: 0.085s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct price
{
    string code;
    string area;
    int cost;
};

int main(int argc, char *argv[])
{
    string line;
    vector < price > prices;

    // 处理第一部分输入
    while (getline(cin, line), line.find("000000") != 0)
    {        
        string code, area, fee;
        
        int index = 0;
        while (index < line.length() && isdigit(line[index]))
            code += line[index++];
        
        // 跳过空格，直到 $ 都属于国家或地区名称   
        index++;  
        while (index < line.length() && line[index] != '$')
            area += line[index++];

        // 跳过 $
        index++;  
        while (index < line.length())
        {
            if (isdigit(line[index]))
                fee += line[index];
            index++;
        }
        
        // cout << code << " "  << area << " " << fee << endl;
        
        prices.push_back((price) { code, area, stoi(fee) });
    }

    // 处理第二部分输入并输出
    while (getline(cin, line), line != "#")
    {
        int index = 0;
        string calledNumber, duration;

        while (index < line.length() && isdigit(line[index]))
            calledNumber += line[index++];
        while (index < line.length() && isblank(line[index]))
            index++;
        while (index < line.length() && isdigit(line[index]))
            duration += line[index++];

        string area, subscriber;
        double cost, totalCost;
        bool unknown = true;
        
        for (int i = 0; i < prices.size(); i++)
        {
            if (calledNumber.find(prices[i].code) == 0)
            {
                area = prices[i].area;
                subscriber = calledNumber.substr(prices[i].code.length());
                
                if (calledNumber.find("00") == 0)
                {
                    if (subscriber.length() < 4 || subscriber.length() > 10)
                        continue;
                }
                else if (calledNumber.find("0") == 0)
                {
                    if (subscriber.length() < 4 || subscriber.length() > 7)
                        continue;
                }
                                               
                cost = prices[i].cost / 100.00;
                totalCost = stoi(duration) * cost;
                unknown = false;
                break;
            }
        }
        
        if (unknown)
        {
            if (calledNumber.find("00") == 0 || calledNumber.find("0") == 0)
            {
                area = "Unknown";
                subscriber.clear();
                totalCost = -1.0;
            }
            else
            {
                area = "Local";
                subscriber = calledNumber;
                cost = 0.00;
                totalCost = 0.0;
                unknown = false;     
            }
        }

        cout.setf(ios::fixed);
        cout << setw(16) << left << calledNumber;
        cout << area;
        cout << string(35 - area.length() - subscriber.length(), ' ');
        cout << subscriber;
        cout << setw(5) << right << duration;
        
        if (unknown)
            cout << string(6, ' ');
        else
            cout << setw(6) << right << setprecision(2) << cost;
        
        cout << setw(7) << right << setprecision(2) << totalCost;
        cout << endl;
    }

    return 0;
}
