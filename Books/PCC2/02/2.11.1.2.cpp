int findKthZero(int p, int left, int right, int k)
{
    if (k > st[p].field) return -1;
    if (left == right) return left;
    int middle = (left + right) >> 1;
    if (st[LC[p]].field >= k)
        return findKthZero(LC(p), left, middle, k);
    else
        return findKthZero(RC(p), middle + 1, right, k - st[LC(p)].field);
}
