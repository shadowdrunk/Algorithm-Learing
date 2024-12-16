#ifdef ShadowDrunk
//本模板得内容是维护一个区间是否有长度大于等于1得回文子串
//主要特殊信息得维护体现在merge和qury里
//merge函数实际上也可以通过直接重载加号运算符来实现

ll n;
ll mod = 26;
struct node{
    bool two = false;
    bool three = false;
    //l1l2xxxr2r1
    int l1 = -1;
    int l2 = -1;
    int r1 = -1;
    int r2 = -1;
};
std::vector<node> tree;
std::vector<ll> a;
std::vector<ll> tag;

ll ls(ll p){
    return p << 1;
}

ll rs(ll p){
    return p << 1 | 1;
}

node merge(node a, node b){
    auto res = node();
    res.l1 = a.l1;
    res.l2 = a.l2;
    res.r1 = b.r1;
    res.r2 = b.r2;
    res.two = a.two | b.two;
    res.three = a.three | b.three;

    if(res.l2 == -1)
        res.l2 = b.l1;
    if(res.r2 == -1)
        res.r2 = a.r1;

    if(a.r1 != -1 && b.l1 != -1 && a.r1 == b.l1)
        res.two = true;
    if(a.r2 != -1 && b.l1 != -1 && a.r2 == b.l1)
        res.three = true;
    if(a.r1 != -1 && b.l2 != -1 && a.r1 == b.l2)
        res.three = true;
    
    
    return res;
}

void push_up(ll p){
    tree[p] = merge(tree[ls(p)], tree[rs(p)]);
}

void build(ll p, ll pl, ll pr){
    if(pl == pr){
        tree[p] = node();
        tree[p].l1 = a[pl];
        tree[p].r1 = a[pl]; 
        auto ans = tree[p];
        return;
    }
    ll mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void add(node& p, ll d){
    p.l1 = (p.l1 + d) % mod;
    p.r1 = (p.r1 + d) % mod;
    if(p.l2 != -1)
        p.l2 = (p.l2 + d) % mod;
    if(p.r2 != -1)
        p.r2 = (p.r2 + d) % mod;
}

void addtag(ll p, ll pl, ll pr, ll d){
    tag[p] += d;
    add(tree[p], d);
}

void push_down(ll p, ll pl, ll pr){
    if(tag[p]){
        ll mid = (pr + pl) >> 1;
        addtag(ls(p), pl, mid, tag[p]);
        addtag(rs(p), mid + 1, pr, tag[p]);
        tag[p] = 0;
    }
}

void update(ll L, ll R, ll p, ll pl, ll pr, ll d){
    if(L <= pl && pr <= R){
        addtag(p, pl, pr, d);
        return;
    }
    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;
    if(L <= mid)
        update(L, R, ls(p), pl, mid, d);
    if(R > mid)
        update(L, R, rs(p), mid + 1, pr, d);
    push_up(p);
}

void update(ll L, ll R, ll d){
    update(L, R, 1, 1, n, d);
}

node query(ll L, ll R, ll p, ll pl, ll pr){
    if(L <= pl && pr <= R)
        return tree[p];
    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;
    
    if(L <= mid && R > mid)
        return merge(query(L, R, ls(p), pl, mid), query(L, R, rs(p), mid + 1, pr));
    if(L <= mid)
        return query(L, R, ls(p), pl, mid);
    if(R > mid)
        return query(L, R, rs(p), mid + 1, pr);
}

node query(ll L, ll R){
    return query(L, R, 1, 1, n);
}

#endif