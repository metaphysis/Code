int z[1 << 20];

int Z(string &s)
{
    z[0] = s.length();
    for (int i = 1, j = 1, k; i < s.length(); i = k) {
        if (j < i) j = i;
        while (j < s.length() && s[j] == s[j - i]) j++;
        z[i] = j – i, k = i + 1;
        while (k + z[k - i] < j) z[k] = z[k - i], k++;
    }
}
