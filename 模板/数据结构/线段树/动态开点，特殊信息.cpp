#ifdef ShadowDrunk
//使用动态开点实现的线段树
//动态开点实际上也是一开始就分配好空间的
//不同于普通线段树类似于满二叉树的展开,动态开点线段树只用使用2 * n的空间就足够了
//时间复杂度和普通线段树一样
//本模板使用struct和merge实现,可以用来维护特殊的区间问题
//注意动态开点线段树的初始化和普通线段树不同,直接使用update进行初始化即可


struct node{
    ll val;
    ll ls = 0;
    ll rs = 0;
};
std::vector<node> tree;
std::vector<ll> tag;
ll n;
ll root;
ll cnt;

node merge(node a, node b){
    auto res = node();
    res.val = a.val + b.val;
    return res;
}

void push_up(ll p){
    auto now = merge(tree[tree[p].ls], tree[tree[p].rs]);
    tree[p].val = now.val;
}

void addtag(ll& p, ll pl, ll pr, ll d){
    //注意该函数的p是引用
    if(!p){
        //该节点此时不存在，动态开点
        //注意带着tag一起开
        cnt += 1;
        p = cnt;
    }
    tag[p] += d;
    tree[p].val += d * (pr - pl + 1);
}

void push_down(ll p, ll pl, ll pr){
    if(tag[p]){
        ll mid = (pr + pl) >> 1;
        addtag(tree[p].ls, pl, mid, tag[p]);
        addtag(tree[p].rs, mid + 1, pr, tag[p]);
        tag[p] = 0;
    }
}

void update(ll L, ll R, ll& p, ll pl, ll pr, ll d){
    //注意该函数的p是引用
    if(!p){
        //该节点此时不存在，动态开点
        //注意带着tag一起开
        cnt += 1;
        p = cnt;
    }

    if(L <= pl && pr <= R){
        addtag(p, pl, pr, d);
        return;
    }

    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;

    if(L <= mid)
        update(L, R, tree[p].ls, pl, mid, d);
    if(R > mid)
        update(L, R, tree[p].rs, mid + 1, pr, d);

    push_up(p);
}

node query(ll L, ll R, ll p, ll pl, ll pr){
    if(!p){
        //未存在的点没有进行过任何操作，值为0
        return node();
    }

    if(L <= pl && pr <= R)
        return tree[p];
        
    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;
    if(L <= mid && R > mid)
        return merge(query(L, R, tree[p].ls, pl, mid), query(L, R, tree[p].rs, mid + 1, pr));
    if(L <= mid)
        return query(L, R, tree[p].ls, pl, mid);
    if(R > mid)
        return query(L, R, tree[p].rs, mid + 1, pr);
}

void update(ll L, ll R, ll d){
    root = 1;
    update(L, R, root, 1, n, d);
}

node query(ll L, ll R){
    return query(L, R, 1, 1, n);
}

    //数据初始化
    std::cin >> n;
    tree = std::vector<node>(n << 1);
    tag = std::vector<ll>(n << 1);
    cnt = 1;  //已经开好了根节点
    int m;
    std::cin >> m;
    for(int i = 1; i <= n; i++){
        ll x;
        std::cin >> x;
        update(i, i, x);
    }

#endif