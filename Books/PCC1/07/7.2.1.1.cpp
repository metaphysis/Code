template <typename _EuclideanRingElement>
_EuclideanRingElement __gcd(_EuclideanRingElement __m, _EuclideanRingElement __n)
{
    while (__n != 0)
    {
        _EuclideanRingElement __t = __m % __n;
        __m = __n;
        __n = __t;
    }
    return __m;
}
