#ifdef ShadowDrunk
//时间复杂度 预处理O（n） 查询 O(lgn)
//树链刨分一般按重链刨分，因为每次刨分都会使剩余节点减少一半或以上
//所以每个树最多刨分出lgn条链
//我们对树中的链进行dfs序列维护,每个树链中内部的节点dfs序都是有序的（子树中也是）
//于是结合线段树维护我们就可以实现以下操作
//O（lg * lg)
//修改两个节点之间最短路径上所有点的值
//查询两个节点之间最短路径上所有点的值
//O（lg)
//修改一个子树中所有点的值
//查询一个子树中所有点的值

    //基础数据
    //树链刨分数据
    int n, m, r, mod;   //n哥节点,m次询问,r为根节点,mod为模数
    int num;
    std::vector<std::vector<int>> vec;
    std::vector<int> deep;
    std::vector<int> fa;
    std::vector<int> sz;
    std::vector<int> son;
    std::vector<int> top;
    std::vector<int> id;
    std::vector<int> wight;
    //线段树数据
    std::vector<int> w_new; //根据id建立的新的权值
    std::vector<ll> tree;
    std::vector<ll> tag;

    //线段树部分
    ll ls(ll p){
        return p << 1;
    }

    ll rs(ll p){
        return p << 1 | 1;
    }

    void push_up(ll p){
        tree[p] = (tree[ls(p)] + tree[rs(p)]) % mod;
    }

    void build(ll p, ll pl, ll pr){
        if(pl == pr){
            tree[p] = w_new[pl] % mod; 
            return;
        }
        ll mid = (pl + pr) >> 1;
        build(ls(p), pl, mid);
        build(rs(p), mid + 1, pr);
        push_up(p);
    }

    void addtag(ll p, ll pl, ll pr, ll d){
        d %= mod;
        tag[p] += d;
        tag[p] %= mod;
        tree[p] += d * (pr - pl + 1);
        tree[p] %= mod;
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
            res = (res + query(L, R, ls(p), pl, mid)) % mod;
        if(R > mid)
            res = (res + query(L, R, rs(p), mid + 1, pr)) % mod;
        return res;
    }

    ll query(ll L, ll R){
        return query(L, R, 1, 1, n);
    }

    //树链刨分部分
    void dfs1(int node, int father){
        deep[node] = deep[father] + 1;
        fa[node] = father;
        sz[node] = 1;
        for(auto v : vec[node]){
            if(v != father){
                dfs1(v, node);
                sz[node] += sz[v];
                //标记重儿子
                if(!son[node] || sz[son[node]] < sz[v])
                    son[node] = v;
            }
        }
    }
    //重链刨分
    void dfs2(int node, int topx){
        //topx表示当前链的链头节点
        id[node] = ++num; //对每个节点新编号 
        top[node] = topx;
        if(!son[node])
            return;
        //顺着当前重链遍历
        dfs2(son[node], topx);

        for(auto v : vec[node]){
            //轻儿子重新开重链
            if(v != fa[node] && v != son[node]){
                dfs2(v, v);
            }
        }
    }

    //操作函数
    void update_range(int x, int y, int z){
        while(top[x] != top[y]){
            if(deep[top[x]] < deep[top[y]])
                std::swap(x, y);
            update(id[top[x]], id[x], z);
            x = fa[top[x]];
        }
        if(deep[x] > deep[y])
            std::swap(x, y);
        update(id[x], id[y], z);
    }

    ll query_range(int x, int y){
        ll ans = 0;
        while(top[x] != top[y]){
            if(deep[top[x]] < deep[top[y]])
                std::swap(x, y);
            ans = ans + query(id[top[x]], id[x]);
            ans %= mod;
            x = fa[top[x]];
        }
        if(deep[x] > deep[y])
            std::swap(x, y);
        ans = ans + query(id[x], id[y]);
        ans %= mod;
        return ans;
    }

    void update_tree(int x, int k){
        update(id[x], id[x] + sz[x] - 1, k);
    }

    ll query_tree(int x){
        return query(id[x], id[x] + sz[x] - 1);
    }

    //数据初始化
    num = 0;
    std::cin >> n >> m >> r >> mod;
    vec = std::vector<std::vector<int>>(n + 1);
    deep = std::vector<int>(n + 1, 0);
    fa = std::vector<int>(n + 1);
    sz = std::vector<int>(n + 1);
    son = std::vector<int>(n + 1);
    top = std::vector<int>(n + 1);
    id = std::vector<int>(n + 1);
    wight = std::vector<int>(n + 1);

    w_new = std::vector<int>(n + 1);
    tree = std::vector<ll> (n << 2);
    tag = std::vector<ll> (n << 2);

    //进行刨分
    dfs1(r, 0);
    dfs2(r, r);
    //先读入并刨分完再新键点权
    for(int i = 1; i <= n; i++){
        w_new[id[i]] = wight[i];
    }
    build(1, 1, n); //构建线段树

#endif