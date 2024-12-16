#ifdef ShadowDrunk
//笛卡尔树是指维护了一个二叉树，其每个元素有两个值（x，y）
//这棵二叉树对于x满足二叉搜索树的性质，对于y满足二叉堆的性质
//本模板是以元素的下标i作为x，值作为y，满足小根堆性质的笛卡尔树
//根据笛卡尔树的性质，笛卡尔树每个节点与其子树都是连续的区间

    //核心数据
    struct node{
        int ind;
        int ls;
        int rs;
        int val;
        int par;
        void init(int _ind, int _val, int _par){
            ind = _ind;
            val = _val;
            par = _par;
            ls = rs = 0;
        }
    };
    int n;
    std::vector<node> tree;

    //核心算法，建树
    int build_tree(){
        for(int i = 1; i <= n; i++){
            int k = i - 1;
            while(tree[k].val > tree[i].val)
                k = tree[k].par;
            tree[i].ls = tree[k].rs;
            tree[k].rs = i;
            tree[i].par = k;
            tree[tree[i].ls].par = i;
        }
        return tree[0].rs;
    }

    //数据初始化
    std::cin >> n;
    tree.resize(n + 1, node());
    tree[0].init(0, INT_MIN, 0);
    for(int i = 1; i <= n; i++){
        int x;
        std::cin >> x;
        tree[i].init(i, x, 0);
    }
    int root = build_tree();

#endif