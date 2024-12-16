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
        int maxl = 0;
        int minr = H;
    }tree[max_sz];
    int root;   //同时开多个线段树时直接将root改成数组即可
    int cnt;

    node merage(node a, node b){
        node ans;
        ans.val = a.val + b.val;
        ans.maxl = std::max(a.maxl, b.maxl);
        ans.minr = std::min(a.minr, b.minr);
        return ans;
    }

    void push_up(ll p){
        int ls = tree[p].ls;
        int rs = tree[p].rs;
        tree[p] = merage(tree[tree[p].ls], tree[tree[p].rs]);
        tree[p].ls = ls;
        tree[p].rs = rs;
    }

    void addtag(int& p, ll pl, ll pr, int l, int r){
        if(!p){
            cnt += 1;
            p = cnt;
        }
        tree[p].val += 1;
        tree[p].maxl = std::max(tree[p].maxl, l);
        tree[p].minr = std::min(tree[p].minr, r);
    }

    void update(ll L, ll R, int& p, ll pl, ll pr, int l, int r){
        if(!p){
            cnt += 1;
            p = cnt;
        }
        if(L <= pl && pr <= R){
            addtag(p, pl, pr, l, r);
            return;
        }
        ll mid = (pl + pr) >> 1;
        if(L <= mid)
            update(L, R, tree[p].ls, pl, mid, l, r);
        if(R > mid)
            update(L, R, tree[p].rs, mid + 1, pr, l, r);
        push_up(p);
    }

    node query(ll L, ll R, ll p, ll pl, ll pr){
        if(!p){
            return node();
        }
        if(L <= pl && pr <= R)
            return tree[p];
        ll mid = (pl + pr) >> 1;

        if(L <= mid && R > mid)
            return merage(query(L, R, tree[p].ls, pl, mid), query(L, R, tree[p].rs, mid + 1, pr));
        if(L <= mid)
            return query(L, R, tree[p].ls, pl, mid);
        if(R > mid)
            return query(L, R, tree[p].rs, mid + 1, pr);
    }

    void update(ll L, ll R, int l, int r){
        root = 1;
        update(L, R, root, 1, H, l, r);
    }

    node query(ll L, ll R){
        return query(L, R, 1, 1, H);
    }

    //初始化
    cnt = 1;

    //多测清空
    for(int i = 1; i <= cnt; i++)
        tree[i] = node();

#endif