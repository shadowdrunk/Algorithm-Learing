#ifdef ShadowDrunk
//a1 + a2 +...+ ai = 求和（1到k）Di - 求和（1到k）（i - 1）Di
//使用树状数组维护俩个求和即可
//注意大概率要开ll，并且比起二阶树状数组，使用线段树应该更合适
ll n = 1e5;
std::vector<ll> tree1(n + 1, 0);
std::vector<ll> tree2(n + 1, 0);
ll lowbit(ll x){
    return (-x) & x;
}
void update1(ll x, ll d){
    while(x <= n){
        tree1[x] += d;
        x += lowbit(x);
    }
}
void update2(ll x, ll d){
    while(x <= n){
        tree2[x] += d;
        x += lowbit(x);
    }
}
ll sum1(ll x){
    int ans = 0;
    while(x > 0){
        ans += tree1[x];
        x -= lowbit(x);
    }
    return ans;
}
ll sum2(ll x){
    ll ans = 0;
    while(x > 0){
        ans += tree2[x];
        x -= lowbit(x);
    }
    return ans;
}

//初始化维护
    for(int i = 1; i <= n; i++){
        update1(i, cur[i] - cur[i - 1]);
        update2(i, (i - 1) * (cur[i] - cur[i - 1]));
    }
//修改维护
    if(control == 1){
        int x, y, k;
        std::cin >> x >> y >> k;
        update1(x, k);
        update1(y + 1, -k);

        update2(x, (x - 1) * k);
        update2(y + 1, y * (-k));
    }
//查询公式
    y * sum1(y) - sum2(y) - (x - 1) * sum1(x - 1) + sum2(x - 1);
#endif