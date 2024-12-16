#ifdef ShadowDrunk
//时间复杂度为为O（lgn）
//拓展欧几里得定理用来求解 ax + by == gcd（a, b)的一组特解的算法
//注意拓展欧几里得定理要求a与b互质（即gcd(a, b) == 1)
//线性同余方程为求解 a * x === b (mod m),求解一个符合条件的x    (翻译a * b mod m == b)
//基本原理是基于数学推导 a * x = m * y + b;
//a * x - y * m == b;
//所以根据裴蜀定理可知只有b是gcd(a, m)的倍数时才有解，用exgcd求出一组通解，然后放大倍数即可
//注意最后的x可以对m取可模，防止结果数字过大

    //扩展欧几里得算法
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

    //求解线性同余方程
    ll a, b, m;
    std::cin >> a >> b >> m;
    ll x, y;
    ll g = exgcd(a, m, x, y);
    if(b % g != 0){
        std::cout << "impossible" << endl;
        return;
    }
    x *= b / g;
    x %= m;
    std::cout << x << endl;

#endif