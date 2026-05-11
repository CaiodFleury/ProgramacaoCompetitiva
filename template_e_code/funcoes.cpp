int mdc(int a, int b)
{
	return a%b? b : mdc(b,a%b);
}
int fexp(int a, int b, int mod)
{
    int res = 1;
    while(b > 0)
    {
        if(b & 1)res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
template<typename T> struct SegTree
{
    int n;
    vector<T> seg;
    function<T(T, T)> merge;
    T neutral;
    SegTree(int sz, function<T(T, T)> _merge, T _neutral)
    {
        merge = _merge;
        neutral = _neutral;
        n = 1;
        while(n < sz) n <<= 1;
        seg.assign(2 * n, neutral);
    }

    void update(int p, T v)
    {
        p += n;
        seg[p] = v;

        for(p >>= 1; p; p >>= 1)
            seg[p] = merge(seg[2 * p], seg[2 * p + 1]);
    }

    T query(int l, int r)
    {
        T resl = neutral;
        T resr = neutral;

        for(l += n, r += n; l <= r; l >>= 1, r >>= 1)
        {
            if(l & 1)
                resl = merge(resl, seg[l++]);

            if(!(r & 1))
                resr = merge(seg[r--], resr);
        }

        return merge(resl, resr);
    }
};