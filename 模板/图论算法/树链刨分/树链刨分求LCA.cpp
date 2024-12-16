#ifdef ShadowDrunk
//时间复杂度 预处理O（n） 查询 O(lgn)
//树链刨分一般按重链刨分，因为每次刨分都会使剩余节点减少一半或以上
//所以每个树最多刨分除lgn条链
//从任意节点跳到根节点最多经过lgn条链
//我们使用两次预处理进行重链刨分
//查询时如果在同一条重链，答案就是深度低的那个，否则就让重链链头深度高的节点跳到其链头的父节点（即上一个重链）

    //核心数据
    int n, m, s;    //n个节点，m次查询，根节点为s
    std::vector<std::vector<int>> vec;
    std::vector<int> deep;
    std::vector<int> fa;
    std::vector<int> sz;
    std::vector<int> son;
    std::vector<int> top;

    //数据初始化
    std::cin >> n >> m >> s;
    vec = std::vector<std::vector<int>>(n + 1);
    deep = std::vector<int>(n + 1, 0);
    fa = std::vector<int>(n + 1);
    sz = std::vector<int>(n + 1);
    son = std::vector<int>(n + 1);
    top = std::vector<int>(n + 1);

    //核心算法
    //预处理数据
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
        //id[node] = ++num; //对每个节点新编号 
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

    //求LCA
    int LCA(int x, int y){
        while(top[x] != top[y]){
            //跳转链头深度大的点
            if(deep[top[x]] < deep[top[y]])
                std::swap(x, y);
            x = fa[top[x]];
        }
        return (deep[x] < deep[y] ? x : y);
    }

    //存边及调用函数
    for(int i = 0; i < n - 1; i++){
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    //预处理数据
    dfs1(s, 0);
    //重链刨分
    dfs2(s, s);

#endif