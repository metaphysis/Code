// The SetStack Computer
// UVa ID: 10296
// Verdict: Accepted
// Submission Date: 2021-11-10
// UVa Run Time: 0.060s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int id;
map<set<int>, int> idx;
stack<set<int>> stk;

int getId(set<int> s)
{
    if (idx.count(s)) return idx[s];
    return idx[s] = id++;
}

int main(int argc, char *argv[])
{
    //clock_t start = clock();
    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    //clock_t finish = clock();
    //cout << 1.0 * (finish - start) / CLOCKS_PER_SEC << " seconds.\n";

    set<int> E;
    int cases, n;
    string command;
    
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        id = 0;
        idx.clear();
        while (stk.size()) stk.pop();
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> command;
            if (command == "PUSH")
            {
                stk.push(E);
                cout << 0 << '\n';
            }
            else if (command == "DUP")
            {
                stk.push(stk.top());
                cout << stk.top().size() << '\n';
            }
            else if (command == "UNION")
            {
                set<int> A = stk.top(); stk.pop();
                set<int> B = stk.top(); stk.pop();
                set<int> C;
                set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
                cout << C.size() << '\n';
                stk.push(C);
            }
            else if (command == "INTERSECT")
            {
                set<int> A = stk.top(); stk.pop();
                set<int> B = stk.top(); stk.pop();
                set<int> C;
                set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
                cout << C.size() << '\n';
                stk.push(C);
            }
            else if (command == "ADD")
            {
                set<int> A = stk.top(); stk.pop();
                set<int> B = stk.top(); stk.pop();
                B.insert(getId(A));
                cout << B.size() << '\n';
                stk.push(B);
            }
        }
        cout << "***\n";
    }
    
    return 0;
}
