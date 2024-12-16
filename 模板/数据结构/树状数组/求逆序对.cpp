#ifdef ShadowDrunk
//求逆序对的关键就是把数的值当成树状数组的序号
//对于每个cur[i] ans += (i - sum(cur[i]));  （序号从1开始)
//基础树状数组
ll n = 1e5;
std::vector<ll> tree(n + 1, 0);
ll lowbit(ll x){
    return (-x) & x;
}
void update(ll x, ll d){
    while(x <= n){
        tree[x] += d;
        x += lowbit(x);
    }
}
ll sum(ll x){
    ll ans = 0;
    while(x > 0){
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}

//计算公式
for(int i = 1; i <= n; i++){
    update(rank[i], 1);
    ans += i - sum(rank[i]);
}

#endif