#ifdef ShadowDrunk
//中国剩余定理用来求解线性同余方程组的解
//在模数互质的情况下我们可以直接使用构造的公式求解(此时构造的解再模M的条件下唯一)
//在模数不互质的情况下我们需要使用合并线性同余方程的数学推论来合并再求解
//a数组存储模数，m数组存储结果
//尽量使用模数不互质版，注意CRT有可能会爆ll，特别是模数不互质版，必要时候可用int128(__int128)

    //拓展欧几里得算法
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

    //模数不互质
    ll CRT(std::vector<ll>& a, std::vector<ll>& m){
        //x mod a === m
        //将多个线性同余方程进行合并再求解
        int n = a.size();
        ll a1 = a[0];
        ll m1 = m[0];

        bool check = true;
        for(int i = 1; i < n; i++){
            ll a2, m2;
            a2 = a[i];
            m2 = m[i];
            ll k1, k2;
            //a1 * k1 + m1 == x;
            //ai * k2 + m2 == x;
            //a1 * k1 - a2 * k2 = m2 - m1;
            ll d = exgcd(a1, a2, k1, k2);
            if((m2 - m1) % d != 0){
                check = false;
                break;
            }
            // k1 + a2 / d * k  all solutions
            // k2 + a1 / d * k
            k1 *= (m2 - m1) / d;
            ll tmp = a2 / d;
            //求最小正整数解，防止溢出
            k1 = (k1 % tmp + tmp) % tmp;
            // x == k * a1 + m1 + k * (a1 * a2 / d)
            // x == m1 + k * a1
            m1 = a1 * k1 + m1;
            a1 = std::abs(a1 / d * a2);
        }
        if(check)
            return (m1 % a1 + a1) % a1;
        else
            return -1;
    }

    //模数互质
    ll CRT(std::vector<ll>& a, std::vector<ll>& m){
        //x mod a == m
        ll ans = 0;
        ll M = 1;
        int n = a.size();
        for(int i = 0; i < n; i++)
            M *= a[i];

        for(int i = 0; i < n; i++){
            ll mi = M / a[i];
            ll b, k;
            // b * mi mod a[i] == 1 求mi在m[i]模数下的逆元
            // b * mi == a[i] * k + 1
            //要求mi与a[i]互质
            exgcd(mi, a[i], b, k);
            //mi * b = 1, 所以结果满足所有的线性同余方程
            ans = (ans + m[i] * mi * b % M) % M;
        }
        return (ans % M + M) % M;
    }

#endif