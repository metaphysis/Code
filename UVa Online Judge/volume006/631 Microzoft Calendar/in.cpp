#include <bits/stdc++.h>

using namespace std;

bool isLeapYear(int yyyy)
{
    return ((yyyy % 4 == 0 && yyyy % 100 != 0) || yyyy % 400 == 0);
}

int main(int argc, char *argv[])
{
    for (int i = 1600; i <= 5000; i += 100)
    {
        for (int j = 1; j <= 12; j++)
        {
            if (j == 2)
            {
                for (int k = 1; k <= 28; k++)
                {
                    cout << i << "-02-";
                    if (k < 10) cout << '0';
                    cout << k << '\n';
                }
                if (isLeapYear(i)) cout << i << "-02-29\n";
            }
            else
            {
                for (int k = 1; k <= 30; k++)
                {
                    cout << i << '-';
                    if (j < 10) cout << '0';
                    cout << j << '-';
                    if (k < 10) cout << '0';
                    cout << k << '\n';
                }
                
                if (j == 1 || j == 3 || j == 5 || j == 7 || j == 8 || j == 10 || j == 12)
                {
                    cout << i << '-';
                    if (j < 10) cout << '0';
                    cout << j << "-31\n";
                }
            }
        }
    }

    cout << "END\n";
    return 0;
}
