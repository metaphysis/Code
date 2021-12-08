int findFirst(int p, int left, int right, int qleft, int qright, int x)
{
    if (right < qleft || left > qright) return -1;
    if (left <= qleft && qright <= right)
    {
        if (st[p].max < x) return -1;
        while (left != right)
        {
            int middle = (left + right) >> 1;
            if (st[LC(p)].max > x) { p = LC(p); right = middle; }
            else { p = RC(p); left = middle + 1; }
        }
        return left;
    }
    int middle = (left + right) >> 1;
    int idx = findFirst(LC(p), left, middle, qleft, qright, x);
    if (idx != -1) return idx;
    return findFirst(RC(p), middle + 1, right, qleft, qright, x);
}
