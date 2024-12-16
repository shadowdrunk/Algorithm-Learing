#ifdef ShadowDrunk
//使用树状数组来快速的找出区间最值得原理与树状数组本身类似
//tree[x] 存储得是x到x - lowbit(x)
//在更新时我们现需要更新cur得同时使用update。注意update得更新原理，先直接更新tree再用它的掌管的子树来更新x本身
//然后还要更新x的父节点数组
//区间查询时right - left >= lowbit(right) 时存在区间包含关系，可以快速查询完lowbit(right)长度的区间，剩余的暴力即可
ll n = 1e5;
std::vector<ll> cur(n + 1, 0);
std::vector<ll> tree(n + 1, 0);
ll lowbit(ll x){
    return (-x) & x;
}
void update(ll x, ll value){
    while(x <= n){
        tree[x] = value;    
        for(int i = 1; i < lowbit(x); i <<= 1){  
            //用子节点更新自己  
            tree[x] = std::max(tree[x], tree[x - i]);
        }
        //更新父节点
        x += lowbit(x); 
    }
}
ll query(ll left, ll right){
    ll ans = INT_MIN;
    while(left <= right){
        ans = std::max(ans, cur[right]);
        right -= 1;
        while(right - left >= lowbit(right)){
            ans = std::max(ans, tree[right]);
            right -= lowbit(right);
        }
    }
    return ans;
}

//更新方式
    cur[i] = new;
    update(cur[i], new);
#endif