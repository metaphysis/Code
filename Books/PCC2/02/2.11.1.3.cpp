int findMinIndex(int p, int left, int right, int x)
{
    if (x > st[p].sum) return -1;
    if (left == right) return left;
    int middle = (left + right) >> 1;
    if (st[LC[p]].sum >= x)
        return findMinIndex(LC(p), left, middle, x);
    else
        return findMinIndex(RC(p), middle + 1, right, x - st[LC(p)].sum);
}
