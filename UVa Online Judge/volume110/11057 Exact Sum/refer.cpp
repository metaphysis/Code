#include<cstdio>
#include<algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    int n, price[10001];

    while (scanf("%d", &n) != EOF)
    {
        int money;
        for (int i = 0; i < n; i++)
            scanf("%d", &price[i]);
        scanf("%d", &money);

        sort(price, price + n);
        int mid = lower_bound(price, price + n, money / 2) - price;
        bool flag = true;

        for (; flag&&price[mid] <= money; mid++)
            for (int i = 1; i <= mid; i++)
                if (price[mid] + price[mid - i] == money)
                {
                    printf("Peter should buy books whose prices are %d and %d.\n\n", price[mid - i], price[mid]);
                    flag = false;
                    break;
                }
    }

    return 0;
}
