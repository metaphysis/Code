#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string cards = "7J93JQKA23456789T8QKA23456789TJQKA23456789TJQKA2T456";

    for (int i = 1; i <= 100; i++)
    {
        shuffle (cards.begin(), cards.end(), default_random_engine(time(NULL)));
        for (int j = 0; j < cards.length(); j++)
        {
            if (j > 0)
                cout << ' ';
            cout << cards[j];
        }
        cout << '\n';
    }
    cout << "0\n";
    
    return 0;
}
