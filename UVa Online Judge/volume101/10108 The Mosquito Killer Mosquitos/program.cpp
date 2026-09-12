// The Mosquito Killer Mosquitos
// UVa ID: 10108
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.000s

#include <bits/stdc++.h>  
#include <boost/multiprecision/cpp_int.hpp>  
using namespace std;  
using boost::multiprecision::cpp_int;  
  
cpp_int getSqrt(const cpp_int &value) {  
    if (value <= 1) return value;  
    cpp_int root = value;  
    cpp_int next = (root + 1) / 2;  
    while (next < root) {  
        root = next;  
        next = (root + value / root) / 2;  
    }  
    while ((root + 1) * (root + 1) <= value) root++;  
    while (root * root > value) root--;  
    return root;  
}  
  
string getSuffix(long long day) {  
    if (day == 11 || day == 12 || day == 13) return "'th";  
    if (day % 10 == 1) return "'st";  
    if (day % 10 == 2) return "'nd";  
    if (day % 10 == 3) return "'rd";  
    return "'th";  
}  
  
int main() {  
    ios::sync_with_stdio(false);  
    cin.tie(nullptr);  
    long long startMos, totalDay;  
    while (cin >> startMos >> totalDay) {  
        if (startMos < 0 || totalDay < 0) break;  
        cpp_int mos = startMos;  
        for (long long day = 1; day <= totalDay; day++) {  
            if (day % 7 == 0) mos = getSqrt(mos);  
            else mos = mos * (mos + 1) / 2;  
            if (mos <= 1) break;  
        }  
        cout << "Number of mosquitos in the pond at the end of "  
             << totalDay << getSuffix(totalDay)  
             << " day is " << mos << ".\n";  
    }  
    return 0;  
}
