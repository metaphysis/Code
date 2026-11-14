int n, k;
int used[1 << 21], sequence[22][1 << 21], top;
int bits, mask;

void dfs(int u)
{
    u = (u & mask) << 1;
    for (int v = 0; v <= 1; v++) {
        if (used[u + v]) continue;
        used[u + v] = 1;
        dfs(u + v);
        sequence[n][top++] = u + v;
    }
}

void trick()
{
    for (int i = 1; i <= 21; i++) {
        n = i;
        top = 0, bits = 1 << n, mask = (1 << (n - 1)) - 1;
        memset(used, 0, sizeof(int) * bits);
        dfs(0);
    }
}

int main(int argc, char *argv[])
{
    int cases;
    trick();
    cin >> cases;
    for (int c = 1; c <= cases; c++) {
        cin >> n >> k;
        cout << sequence[n][(1 << n) - 1 - k] << '\n';
    }
    return 0;
}
