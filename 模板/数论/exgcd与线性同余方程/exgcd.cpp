#ifdef ShadowDrunk
//时间复杂度为为O（lgn）
//拓展欧几里得定理是用来求解 ax + by == gcd（a, b)的一组特解的算法
//注意拓展欧几里得定理要求a与b互质（即gcd(a, b) == 1)

    //核心算法
    ll exgcd(ll a, ll b, ll& x, ll& y){
        if(!b){
            x = 1;
            y = 0;
            return a;
        }
        ll d = exgcd(b, a % b, x, y);
        ll t = x;
        x = y;
        y = t - (a / b) * y;
        return d;
    }

#endif