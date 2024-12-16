#ifdef ShadowDrunk
//可持久化线段树像是维护了n颗线段树，使得我们可以直接查询每个版本的线段树
//可持久化线段树的查询和修改（创建版本的操作）很像线段树上二分
//其操作的时间复杂度都是lgn的
//可持久化线段树的空间需要O(n * lg(4 * n))

    //核心数据
    int cnt = 0;    //记录可以使用的新节点
    std::vector<int> cur;   //原始数组
    std::vector<int> num;   //离散化去重之后的数
    std::vector<int> root;  //记录每个区间 (1, i)对应版本开始的根节点
    struct node{
        int ls;
        int rs;
        int sum;    //注意这里是权值线段树，注意sum含义
    };
    std::vector<node> tree;
    //要开的空间数为n * lg(4 * n)

    //建立空树(并不需要)
    int build(int pl, int pr){
        //初始构建一颗空树（实际上没有必要）
        int rt = ++cnt;
        tree[rt].sum = 0;
        int mid = (pl + pr) >> 1;
        if(pl < pr){
            tree[rt].ls = build(pl, mid);
            tree[rt].rs = build(mid + 1, pr);
        }
        return rt;
    }

    //核心操作
    int update(int pre, int pl, int pr, int x){
        //构建一颗只有lgn个新节点的新线段树
        int rt = ++cnt;
        //将该节点的左右儿子初始化为和上一颗线段树一样
        tree[rt].ls = tree[pre].ls;
        tree[rt].rs = tree[pre].rs;
        tree[rt].sum = tree[pre].sum + 1;   //插入一个数
        int mid = (pl + pr) >> 1;
        if(pl < pr){
            if(x <= mid)
                tree[rt].ls = update(tree[pre].ls, pl, mid, x);
            else
                tree[rt].rs = update(tree[pre].rs, mid + 1, pr, x);
        }
        return rt;
    }
    int query(int u, int v, int pl, int pr, int k){
        //查询区间[u + 1, v]的第k小的数
        if(pl == pr)
            return pl;
        
        //x为区间中左儿子数的大小
        int x = tree[tree[v].ls].sum - tree[tree[u].ls].sum;

        int mid = (pl + pr) >> 1;
        if(x >= k)
            return query(tree[u].ls, tree[v].ls, pl, mid, k);
        else
            return query(tree[u].rs, tree[v].rs, mid + 1, pr, k - x);
    }

    //数据初始化
    int n, m;
    std::cin >> n >> m;
    cnt = 0;
    cur.resize(n + 1, 0);
    tree.resize(n * 30, node());
    root.resize(n + 1, 0);
    for(int i = 1; i <= n; i++)
        std::cin >> cur[i];
    num = cur;
    std::sort(num.begin() + 1, num.end());
    num.erase(std::unique(num.begin() + 1, num.end()), num.end());
    int sz = num.size() - 1;

    //建立n个版本的线段树
    //root[0] = build(1, sz);   //初始化一颗含sz个元素的空树，实际上没有必要
    for(int i = 1; i <= n; i++){
        int x = std::lower_bound(num.begin() + 1, num.end(), cur[i]) - num.begin();
        root[i] = update(root[i - 1], 1, sz, x);
    }

    //查询操作
    while(m--){
        int x, y, k;
        std::cin >> x >> y >> k;
        int ans = query(root[x - 1], root[y], 1, sz, k);
        std::cout << num[ans] << endl;
    }

#endif