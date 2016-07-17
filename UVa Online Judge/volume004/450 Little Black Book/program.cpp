// Little Black Book
// UVa ID: 450
// Verdict: Accepted
// Submission Date: 2016-07-17
// UVa Run Time: 0.000s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct person
{
    // string 0 - department, 1 - title, 2 - firstname, 3 - lastname,
    // 4 - address, 5 - homephone, 6 - workphone, 7 - mailbox;
    vector<string> information;
    bool operator<(const person& another) const
    {
        return information[3] < another.information[3];
    }
};

vector<vector<string>> persons;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    vector<person> persons;
    for (int i = 1; i <= cases; i++)
    {
        string department;
        getline(cin, department);

        while (getline(cin, line), line.length() > 0)
        {
            person someone;
            someone.information.push_back(department);

            istringstream iss(line);
            string block;
            while (getline(iss, block, ','))
                someone.information.push_back(block);

            persons.push_back(someone);
        }
    }

    sort(persons.begin(), persons.end());
    for (auto someone : persons)
    {
        cout << "----------------------------------------\n";
        cout << someone.information[1] << ' ';
        cout << someone.information[2] << ' ';
        cout << someone.information[3] << '\n';
        
        cout << someone.information[4] << '\n';
        
        cout << "Department: " << someone.information[0] << '\n';
        cout << "Home Phone: " << someone.information[5] << '\n';
        cout << "Work Phone: " << someone.information[6] << '\n';
        cout << "Campus Box: " << someone.information[7] << '\n';
    }
    
	return 0;
}
