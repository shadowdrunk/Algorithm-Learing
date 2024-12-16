#ifdef ShadowDrunk
//注意pushdown和pushup的位置
//如果位置错误则会触发边界问题,造成re

ll n = 1e5;
std::vector<ll> tree(n << 2);
std::vector<ll> a(n + 1);
std::vector<ll> tag(n << 2);

ll ls(ll p){
    return p << 1;
}

ll rs(ll p){
    return p << 1 | 1;
}

void push_up(ll p){
    tree[p] = tree[ls(p)] + tree[rs(p)];
}

void build(ll p, ll pl, ll pr){
    if(pl == pr){
        tree[p] = a[pl]; 
        return;
    }
    ll mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void addtag(ll p, ll pl, ll pr, ll d){
    tag[p] += d;
    tree[p] += d * (pr - pl + 1);
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

ll query(ll L, ll R, ll p, ll pl, ll pr){
    if(L <= pl && pr <= R)
        return tree[p];
    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;
    ll res = 0;
    if(L <= mid)
        res += query(L, R, ls(p), pl, mid);
    if(R > mid)
        res += query(L, R, rs(p), mid + 1, pr);
    return res;
}

ll query(ll L, ll R){
    return query(L, R, 1, 1, n);
}

#endif