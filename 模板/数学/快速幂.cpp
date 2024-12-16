#ifdef ShadowDrunk

    //外置取模版本
    ll qmi(ll a, ll k, ll m){   //求a^k mod m
        a %= m;
        ll res = 1 % m;
        while (k)
        {
            if (k&1) res = res * a % m;//指数k为1的位乘上a^(1<<x)mod m
            a = a * a % m;//每一项是前一项的平方模m
            k >>= 1;
        }
        return res;
    }

    //取模版本
    std::function<ll(ll, ll, ll)> qmi = [&](ll a, ll k, ll m = LONG_LONG_MAX) -> ll{
                a = a % m;
                ll res = 1;
                while(k){
                    if(k % 2 == 1)
                        res = res * a % m;
                    a = a * a % m;
                    k = k / 2;
                }
                return res;
    };

    //不取模版本
    std::function<ll(ll, ll)> qmi = [&](ll a, ll k) -> ll{
                a = a;
                ll res = 1;
                while(k){
                    if(k % 2 == 1)
                        res = res * a;
                    a = a * a;
                    k = k / 2;
                }
                return res;
    };

#endif