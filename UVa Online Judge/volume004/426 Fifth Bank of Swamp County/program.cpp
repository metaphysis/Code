// Fifth Bank of Swamp County
// UVa ID: 426
// Verdict: Accepted
// Submission Date: 2016-08-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct item
{
    int number;
    string number_text, money, date;
    
    bool operator<(const item &another) const
    {
        return number < another.number;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line, date, number, money;

    getline(cin, line);
    int cases = stoi(line);
    
    getline(cin, line);
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << '\n';

        vector<item> checks;
        while (getline(cin, line), line.length() > 0)
        {
            money = "0.00";

            istringstream iss(line);
            iss >> date >> number >> money;

            // special cases
            while (money.length() > 0 && money.front() == '0') money.erase(money.begin());
            if (money.length() == 0) money += "0.00";
            if (money.front() == '.') money.insert(money.begin(), '0');
            if (money.back() == '.') money += "00";
            if (money.find('.') == money.npos) money += ".00";
            if (money[money.length() - 2] == '.') money.push_back('0');
            if (money[money.length() - 3] != '.') money.erase(money.end() - 1);
            if (stod(money) >= 1000000) continue;

            item data;
            data.number = stoi(number);
            data.number_text = to_string(data.number);
            data.money = money;
            data.date = date;
            checks.push_back(data);
        }
        
        sort(checks.begin(), checks.end());

        checks[0].number_text += ' ';
        for (int i = 1; i < checks.size(); i++)
            if (checks[i].number != checks[i - 1].number + 1)
                checks[i].number_text += '*';
            else
                checks[i].number_text += ' ';

        pair<int, int> column1, column2, column3;

        int total = checks.size();
        if (total % 3 == 0)
        {
            total /= 3;
            column1.first = 0, column1.second = total;
            column2.first = total, column2.second = 2 * total;
            column3.first = 2 * total, column3.second = checks.size();
        }
        else if (total % 3 == 1)
        {
            total -= 4;
            total /= 3;
            column1.first = 0, column1.second = total + 2;
            column2.first = total + 2, column2.second = 2 * total + 4;
            column3.first = 2 * total + 4, column3.second = checks.size();
        }
        else
        {
            total -= 2;
            total /= 3;
            column1.first = 0, column1.second = total + 1;
            column2.first = total + 1, column2.second = 2 * total + 2;
            column3.first = 2 * total + 2, column3.second = checks.size();
        }
        
        total = checks.size();
        for (int i = column1.first; i < column1.second; i++)
        {
            cout << setw(5) << right << checks[i].number_text;
            cout << setw(10) << right << checks[i].money;
            cout << ' ' << checks[i].date;
            
            if (i + column2.first < column2.second && i + column2.first < total)
            {
                cout << "   ";
                cout << setw(5) << right << checks[i + column2.first].number_text;
                cout << setw(10) << right << checks[i + column2.first].money;
                cout << ' ' << checks[i + column2.first].date;
            }
            
            if (i + column3.first < column3.second && i + column3.first < total)
            {
                cout << "   ";
                cout << setw(5) << right << checks[i + column3.first].number_text;
                cout << setw(10) << right << checks[i + column3.first].money;
                cout << ' ' << checks[i + column3.first].date;
            }

            cout << '\n';
        }
    }
    
	return 0;
}
