#ifdef ShadowDrunk
//单点修改区间查询就正常维护一个树状数组即可
//若是区间修改单点查询就当作维护一个差分的树状数组
//树状数组也是1序的

//全int
int n = 1e5;
std::vector<int> tree(n + 1, 0);
int lowbit(int x){
    return (-x) & x;
}
void update(int x, int d){
    while(x <= n){
        tree[x] += d;
        x += lowbit(x);
    }
}
int sum(int x){
    int ans = 0;
    while(x > 0){
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}

//全ll
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

#endif