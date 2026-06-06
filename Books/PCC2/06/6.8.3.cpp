int sg[10001], visited[512];
void grundy()
{
    sg[0] = 0, sg[1] = sg[2] = sg[3] = 1;
    for (int i = 4; i <= 10000; i++) {
        memset(visited, 0, sizeof(visited));
        for (int j = 3; j <= 5; j++)
            if (j <= i)
                visited[sg[i - j]] = 1;
        for (int j = 1; j < i - 5; j++) visited[sg[j] ^ sg[i - j - 5]] = 1;
        for (int j = min(5, i); j >= 3; j--) visited[sg[i - j]] = 1;
        for (int j = 0; ; j++)
            if (!visited[j]) {
                sg[i] = j;
                break;
            }
    }
}
