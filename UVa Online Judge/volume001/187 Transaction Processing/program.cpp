// Transaction Processing
// UVa IDs: 187
// Verdict: Accepted
// Submission Date: 2016-03-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>

using namespace std;

struct transaction
{
    string number, name;
    long long money; 
};

map < string, string > account;
vector < string > sequences;
vector < transaction > allTransactions;

void checkBalances(string sequenceNumber)
{
    allTransactions.clear();
    
    long long balances = 0;
    for (int i = 0; i < sequences.size(); i++)
    {
        long long money = stoll(sequences[i].substr(6));
        string number = sequences[i].substr(3, 3);
        allTransactions.push_back((transaction){number, account[number], money});
        balances += money;
    }
    
    //cout << balances << endl;
    
    if (balances != 0)
    {
        cout << "*** Transaction " << sequenceNumber << " is out of balance ***\n";
        for (int i = 0; i < allTransactions.size(); i++)
        {
            cout << allTransactions[i].number << " ";
            cout << left << setw(30) << allTransactions[i].name << " ";
            cout << right << setw(10) << fixed << setprecision(2) <<
                 (allTransactions[i].money / 100.0) << "\n";
        }
        cout << "999 Out of Balance                 " << right << setw(10)
             << fixed << setprecision(2) << (-balances / 100.0) << "\n";
        cout << "\n";
    }
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        if (line.substr(0, 3) == "000")
            break; 
        string name = line.substr(3);
        if (name.length() > 30)
            name = name.substr(0, 30);
        account.insert(make_pair(line.substr(0, 3), name));
    }
    
    string oldSequence, newSequence;
    while (getline(cin, line))
    {
        if (line.substr(0, 6) == "000000")
        {
            checkBalances(oldSequence);
            break;
        }
           
        newSequence = line.substr(0, 3);
        if (oldSequence.length() == 0)
            oldSequence = newSequence;
        else if (oldSequence != newSequence)
        {
            checkBalances(oldSequence);
            sequences.clear();
            oldSequence = newSequence;
        }

        sequences.push_back(line);
    }
    
	return 0;
}
