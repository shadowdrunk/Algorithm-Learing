#ifdef ShadowDrunk
//时间复杂度O（nlgn + mlgn)
//实际上是一种虚点和分层图结合的思想
//我建立和线段树一样含义的虚点，一颗入树，每个区间虚点都可以0花费到达其子区间
//一颗出树每个区间虚点都可以0花费到达其父区间
//同时两个树最低层的单个叶子节点实际含义相同，0费用互联
//build的同时记得标注一下每个单点节点对应的tree中的下标
//我们处理单点连向区间时我们让出树的单点连向入树的区间
//处理区间连向单点时我们让出树的区间连向入树的单点
//注意，总是从出树连向入树
//建完图后我们直接跑需要的算法即可

    //核心数据
    ll n;
    struct edge{
        ll to;
        ll cost;
    };
    struct node{
        ll l;
        ll r;
    };
    std::vector<node> tree;
    std::vector<std::vector<edge>> vec;
    std::vector<int> leaf;
    ll D;  //一个树分层的大小
    //1 到 D 是入树
    //Ｄ + 1 到 2 * D 是出树

    //核心算法
    ll ls(ll p){
        return p << 1;
    }
    ll rs(ll p){
        return p << 1 | 1;
    }

    void build(ll p, ll pl, ll pr){
        tree[p].l = pl;
        tree[p].r = pr;
        if(pl == pr){
            leaf[pl] = p;
            
            //处理同意义节点
            edge to_chu = {p + D, 0};
            vec[p].push_back(to_chu);
            edge to_ru = {p, 0};
            vec[p + D].push_back(to_ru);
            return;
        }
        ll mid = (pl + pr) >> 1;

        //处理第一层入树
        edge left = {ls(p), 0};
        vec[p].push_back(left);
        edge right = {rs(p), 0};
        vec[p].push_back(right);

        //处理第二层出树
        edge back = {p + D, 0};
        vec[ls(p) + D].push_back(back);
        vec[rs(p) + D].push_back(back);

        build(ls(p), pl, mid);
        build(rs(p), mid + 1, pr);
    }

    void connect(ll L, ll R, ll p, int type, ll aim, ll wight){
        //type 1 是从区间连到单点
        //type 0 是从单点连到区间
        if(L <= tree[p].l && tree[p].r <= R){
            //注意都是从出树连接到入树
            if(type){
                edge ed = {leaf[aim], wight};
                vec[p + D].push_back(ed);
            }
            else{
                edge ed = {p, wight};
                vec[leaf[aim] + D].push_back(ed);
            }
            return;
        }

        ll mid = (tree[p].l + tree[p].r) >> 1;
        if(L <= mid)
            connect(L, R, ls(p), type, aim, wight);
        if(R > mid)
            connect(L, R, rs(p), type, aim, wight);
    }

    //数据初始化
    int n, m, str;
    std::cin >> n >> m >> str;
    tree = std::vector<node>(n << 2);
    D = n << 2;
    vec = std::vector<std::vector<edge>>(D * 2 + 1);
    leaf = std::vector<int>(n + 1);
    build(1, 1, n);

    //实际建边
    for(int i = 1; i <= m; i++){
        int op;
        std::cin >> op;
        if(op == 1){
            int x, y, w;
            std::cin >> x >> y >> w;
            vec[leaf[x]].push_back({leaf[y], w});
        }
        else{
            int x, l, r, w;
            std::cin >> x >> l >> r >> w;
            connect(l, r, 1, op % 2, x, w);
        }
    }

#endif