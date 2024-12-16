#ifdef ShadowDrunk

//基础数据
const int N = 2e6 + 10; //注意这里要多开点
const int mod = 998244353;
ll fact[N],infact[N];   //  阶乘和阶乘的逆元
//取模版本快速幂
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
//初始化阶乘
void init(int n = N){ // 预处理阶乘取模的余数和阶乘取模余数的逆元
    fact[0] = infact[0] = 1;
    for (int i = 1; i <= n; i ++ )
    {
        fact[i] = fact[i - 1] * i % mod;
        infact[i] = infact[i - 1] * qmi(i, mod - 2, mod) % mod;//模数不是质数用exgcd
    }
}
//组合数A和C
//C(a, b) = !a / !(a - b) * !(b)    //a个里挑b个
//A(a, b) = !a / !(a - b)
ll C(int a,int b){
    return fact[a] * infact[a-b] % mod * infact[b] % mod;
}   

ll A(int a, int b){    
    return fact[a] * infact[a-b] % mod;
}
//求逆元（小数可以直接调用infact）
ll contary(ll now){
    return qmi(now, mod - 2, mod);
}

#endif