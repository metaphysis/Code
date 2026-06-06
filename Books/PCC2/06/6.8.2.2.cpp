const int MAXN = 1000010;
int main(int argc, char *argv[])
{
    int x, k, a[16];
    bool win[MAXN];
    while (cin >> x) {
        cin >> k;
        for (int i = 0; i < k; i++) cin >> a[i];
        win[0] = false;
        for (int i = 1; i <= x; i++) {
            win[i] = false;
            for (int j = 0; j < k; j++)
            win[i] |= ((a[j] <= i) && !win[i - a[j]]);
        }
        if (win[x]) cout << "The first player wins.\n";
        else cout << "The second player wins.\n";
    }
    return 0;
}
