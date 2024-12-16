#ifdef ShadowDrunk
//使用动态开点实现的线段树
//注意空间要O(n * lgw),w是值域
//动态开点的空间复杂度比较大，需要谨慎使用，同时其通常只需要单点修改所以不用tag数组
//注意，动态开点线段树的根节点已经开好，我们需要将cnt初始化为1
//root 在开多颗动态开点权值线段树时会很方便


const int max_sz = 2e5 * 32; //数据量
const int H = 1e9+5;    //值域

struct node
{
    int ls;
    int rs;
    int val;
}tree[max_sz];
int root;   //同时开多个线段树时直接将root改成数组即可
int cnt;

void push_up(ll p){
    tree[p].val = tree[tree[p].ls].val + tree[tree[p].rs].val;
}

void addtag(int& p, ll pl, ll pr, ll d){
    if(!p){
        cnt += 1;
        p = cnt;
    }
    tree[p].val += d * (pr - pl + 1);
}

void update(ll L, ll R, int& p, ll pl, ll pr, ll d){
    if(!p){
        cnt += 1;
        p = cnt;
    }
    if(L <= pl && pr <= R){
        addtag(p, pl, pr, d);
        return;
    }
    ll mid = (pl + pr) >> 1;
    if(L <= mid)
        update(L, R, tree[p].ls, pl, mid, d);
    if(R > mid)
        update(L, R, tree[p].rs, mid + 1, pr, d);
    push_up(p);
}

ll query(ll L, ll R, ll p, ll pl, ll pr){
    if(!p){
        return 0;
    }
    if(L <= pl && pr <= R)
        return tree[p].val;
    ll mid = (pl + pr) >> 1;
    int res = 0;
    if(L <= mid)
        res += query(L, R, tree[p].ls, pl, mid);
    if(R > mid)
        res += query(L, R, tree[p].rs, mid + 1, pr);
    return res;
}

void update(ll L, ll R, ll d){
    root = 1;
    update(L, R, root, 1, H, d);
}

ll query(ll L, ll R){
    return query(L, R, 1, 1, H);
}

    //数据初始化
    std::cin >> n;
    cnt = 1;  //已经开好了根节点
    int m;
    std::cin >> m;
    for(int i = 1; i <= n; i++){
        ll x;
        std::cin >> x;
        update(i, i, x);
    }

#endif