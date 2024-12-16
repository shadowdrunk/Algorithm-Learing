#ifdef ShadowDrunk
//这是一道基于exgcd对于二元一次不定方程求解的数量，上下界的一个模板

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

    //流程，包含不少数学推理
    ll a, b, c; //求ax + by = c
    std::cin >> a >> b >> c;
    ll gc = gcd(a, b);
    if(c % gc != 0){    //裴蜀定理
        std::cout << -1 << endl;
        return;
    }
    ll x0, y0;  //ax0 + bx0 == gcd(a, b)
    exgcd(a, b, x0, y0);

    ll x1 = x0 * c / gc;
    ll y1 = y0 * c / gc;
    //ax1 + bx1 == c (one of the solution)
    //a(x1 + db) + b(y1 - da) == c
    //d取到最小可能的正值时 dx = db， dy = da
    //其余解与x1，y1的偏差一定时dx与dy的倍数
    //x = x1 + sdx, y = y1 - sdy
    ll dx = b / gc;
    ll dy = a / gc;

    //x > 0, y > 0
    //注意涉及到了负数的上下取整，我们不能直接利用公式，而是要if判断
    ll down = (-x1 + 1) / dx;  
    if(down * dx < (-x1 + 1))  //上取整
        down += 1;
    
    ll up = (y1 - 1) / dy;
    if(up * dy > (y1 - 1))  //下取整
        up -= 1;

    //s chose down
    ll minn_x = x1 + down * dx;
    ll maxn_y = y1 - down * dy;
    //s chose up
    ll maxn_x = x1 + up * dx;
    ll minn_y = y1 - up * dy;

    if(down > up){
        //没有均为正整数解
        std::cout << minn_x << space << minn_y << endl;
        return;
    }

    ll number = up - down + 1;
    std::cout << number << space << minn_x << space << minn_y << space << maxn_x << space << maxn_y << endl;


#endif