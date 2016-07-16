// Student Grants
// UVa ID: 144
// Verdict: Accepted
// Submission Date: 2016-01-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct student
{
    int id;
    int total;
};

int main(int argc, char *argv[])
{
    int n, k;
    while (cin >> n >> k, n || k)
    {
        queue < student > students;
        for (int i = 1; i <= n; i++)
            students.push((student){ i, 0 });
        
        int store = 0, remain = 0;
        while (true)
        {
            int current = 
                (remain > 0) ? remain : ((++store) > k ? (store = 1) : store);

            if (students.empty())
                break;
                
            student aStudent = students.front();
            students.pop();
            if ((aStudent.total + current) >= 40)
            {
                remain = aStudent.total + current - 40;
                cout << setw(3) << right << aStudent.id;
            }
            else
            {
                aStudent.total += current;
                students.push(aStudent);
                remain = 0;
            }
        }
        
        cout << endl;
    }
    
	return 0;
}
