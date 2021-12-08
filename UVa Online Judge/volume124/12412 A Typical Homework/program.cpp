// A Typical Homework
// UVa ID: 12412
// Verdict: Accepted
// Submission Date: 2021-12-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 110;
const double EPSILON = 1e-5;
const string MENU = "Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n";

struct student
{
    int idx, rank;
    string sid, cid, name;
    int s1, s2, s3, s4, tot;
};

vector<student> data;

int cnt = 0;

bool sidDuplicated(string sid)
{
    for (int i = 0; i < data.size(); i++)
        if (data[i].sid == sid)
            return true;
    return false;
}

bool cmp_by_tot(student &st1, student &st2)
{
    return st1.tot > st2.tot;
}

bool cmp_by_idx(student &st1, student &st2)
{
    return st1.idx < st2.idx;
}

void rerank()
{
    sort(data.begin(), data.end(), cmp_by_tot);
    for (int i = 0; i < data.size(); i++)
    {
        if (!i) data[i].rank = 1;
        else
        {
            if (data[i].tot == data[i - 1].tot)
                data[i].rank = data[i - 1].rank;
            else
                data[i].rank = i + 1;
        }
    }
    sort(data.begin(), data.end(), cmp_by_idx);
}

void add()
{
    string sid, cid, name;
    int s1, s2, s3, s4;
    bool flag = false;
    while (true)
    {
        cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish.\n";
        cin >> sid;
        if (sid == "0") break;
        cin >> cid >> name >> s1 >> s2 >> s3 >> s4;
        if (sidDuplicated(sid)) cout << "Duplicated SID.\n";
        else
        {
            flag = true;
            data.push_back(student{cnt++, -1, sid, cid, name, s1, s2, s3, s4, s1 + s2 + s3 + s4});
        }
    }
    if (flag) rerank();
}

void remove()
{
    string sid_name;
    bool flag = false;
    while (true)
    {
        cout << "Please enter SID or name. Enter 0 to finish.\n";
        cin >> sid_name;
        if (sid_name == "0") break;
        int removed = 0;
        for (int i = (int)data.size() - 1; i >= 0; i--)
            if (data[i].sid == sid_name || data[i].name == sid_name)
            {
                removed++;
                data.erase(data.begin() + i);
            }
        cout << removed << " student(s) removed.\n";
        if (removed) flag = true;
    }
    if (flag) rerank();
}

void query()
{
    string sid_name;
    while (true)
    {
        cout << "Please enter SID or name. Enter 0 to finish.\n";
        cin >> sid_name;
        if (sid_name == "0") break;
        for (int i = 0; i < data.size(); i++)
            if (data[i].sid == sid_name || data[i].name == sid_name)
            {
                cout << data[i].rank;
                cout << ' ' << data[i].sid << ' ' << data[i].cid << ' ' << data[i].name;
                cout << ' ' << data[i].s1 << ' ' << data[i].s2 << ' ' << data[i].s3 << ' ' << data[i].s4;
                cout << ' ' << data[i].tot;
                cout << ' ' << fixed << setprecision(2) << (data[i].tot / 4.0 + EPSILON) << '\n';
            }
    }
}

void ranking()
{
    cout << "Showing the ranklist hurts students' self-esteem. Don't do that.\n";
}

void statistics()
{
    cout << "Please enter class ID, 0 for the whole statistics.\n";
    string cid;
    cin >> cid;
    int chinese_tot = 0, chinese_passed = 0, chinese_failed = 0;
    int math_tot = 0, math_passed = 0, math_failed = 0;
    int english_tot = 0, english_passed = 0, english_failed = 0;
    int programming_tot = 0, programming_passed = 0, programming_failed = 0;
    int passed4 = 0, passed3 = 0, passed2 = 0, passed1 = 0, passed0 = 0;
    int tot = 0;
    for (int i = 0; i < data.size(); i++)
        if (cid == "0" || data[i].cid == cid)
        {
            tot++;
            chinese_tot += data[i].s1;
            math_tot += data[i].s2;
            english_tot += data[i].s3;
            programming_tot += data[i].s4;
            int f1 = data[i].s1 >= 60, f2 = data[i].s2 >= 60, f3 = data[i].s3 >= 60, f4 = data[i].s4 >= 60;
            f1 ? chinese_passed++ : chinese_failed++;
            f2 ? math_passed++ : math_failed++;
            f3 ? english_passed++ : english_failed++;
            f4 ? programming_passed++ : programming_failed++;
            int f_tot = f1 + f2 + f3 + f4;
            if (f_tot >= 4) passed4++;
            if (f_tot >= 3) passed3++;
            if (f_tot >= 2) passed2++;
            if (f_tot >= 1) passed1++;
            if (f_tot == 0) passed0++;
        }

    cout << "Chinese\n";
    cout << "Average Score: " << fixed << setprecision(2) << (tot ? (1.0 * chinese_tot / tot + EPSILON) : (0.00)) << '\n';
    cout << "Number of passed students: " << chinese_passed << '\n';
    cout << "Number of failed students: " << chinese_failed << '\n';
    cout << '\n';

    cout << "Mathematics\n";
    cout << "Average Score: " << fixed << setprecision(2) << (tot ? (1.0 * math_tot / tot + EPSILON) : (0.00)) << '\n';
    cout << "Number of passed students: " << math_passed << '\n';
    cout << "Number of failed students: " << math_failed << '\n';
    cout << '\n';

    cout << "English\n";
    cout << "Average Score: " << fixed << setprecision(2) << (tot ? (1.0 * english_tot / tot + EPSILON) : (0.00)) << '\n';
    cout << "Number of passed students: " << english_passed << '\n';
    cout << "Number of failed students: " << english_failed << '\n';
    cout << '\n';

    cout << "Programming\n";
    cout << "Average Score: " << fixed << setprecision(2) << (tot ? (1.0 * programming_tot / tot + EPSILON) : (0.00)) << '\n';
    cout << "Number of passed students: " << programming_passed << '\n';
    cout << "Number of failed students: " << programming_failed << '\n';
    cout << '\n';

    cout << "Overall:\n";
    cout << "Number of students who passed all subjects: " << passed4 << '\n';
    cout << "Number of students who passed 3 or more subjects: " << passed3 << '\n';
    cout << "Number of students who passed 2 or more subjects: " << passed2 << '\n';
    cout << "Number of students who passed 1 or more subjects: " << passed1 << '\n';
    cout << "Number of students who failed all subjects: " << passed0 << '\n';
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int command;
    while (true)
    {
        cout << MENU << '\n';
        cin >> command;
        if (command == 0) break;
        if (command == 1) add();
        if (command == 2) remove();
        if (command == 3) query();
        if (command == 4) ranking();
        if (command == 5) statistics();
    }
    return 0;
}
