// Student Grants
// UVa ID: 144
// Verdict: Accepted
// Submission Date: 2016-01-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct student
{
    int id, withdraw;
};

int main(int argc, char *argv[])
{
    int n, k;
    while (cin >> n >> k, n || k)
    {
        queue<student> students;
        for (int i = 1; i <= n; i++)
            students.push((student){i, 0});
        
        int coins = 0, remain = 0;
        while (true)
        {
            int current = (remain > 0) ? remain : ((++coins) > k ? (coins = 1) : coins);

            if (students.empty()) break;
                
            student aStudent = students.front();
            students.pop();

            if ((aStudent.withdraw + current) >= 40)
            {
                remain = aStudent.withdraw + current - 40;
                cout << setw(3) << right << aStudent.id;
            }
            else
            {
                aStudent.withdraw += current;
                students.push(aStudent);
                remain = 0;
            }
        }
        
        cout << endl;
    }
    
	return 0;
}
