#ifdef ShadowDrunk
//时间复杂度 预处理O（nlgn） 查询 O(lgn)
//树上倍增算法求lca实质上倍增算法的一种运用
//我们预处理出每个节点的第 2 ^ x 个父亲节点是谁。

    //数据输入
    int n, m, s;    //s是根节点
    std::cin >> n >> m >> s;
    std::vector<std::vector<int>> vec(n + 1);
    for(int i = 0; i < n - 1; i++){
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    std::vector<std::vector<int>> fa(n + 1, std::vector<int>(32, -1));
    std::vector<int> depth(n + 1);

    //倍增算法核心预处理
    std::function<void(int, int)> dfs = [&](int node, int father) -> void{
        if(father != -1)
            depth[node] = depth[father] + 1;
        else    
            depth[node] = 1;
        fa[node][0] = father;
        for(int i = 1; i <= std::__lg(depth[node]); i++){
            fa[node][i] = fa[fa[node][i - 1]][i - 1];   //核心转移算法
        }
        for(auto v : vec[node]){
            if(v != father)
                dfs(v, node);
        }
    };
    dfs(s, -1);
    
    //lca算法核心
    std::function<int(int, int)> lca = [&](int x, int y) -> int{
        if(depth[x] < depth[y])
            std::swap(x, y);
        while(depth[x] > depth[y]){
            x = fa[x][std::__lg(depth[x] - depth[y])];
        }   //先统一到同一个高度
        if(x == y)  //特判是否是同一个节点
            return x;
        for(int i = std::__lg(depth[x]); i >= 0; i--){
            if(fa[x][i] != fa[y][i]){   //为了防止跳多了，我们最终目标是lca的下面一层
                x = fa[x][i];   //从高开始往低找不同的节点开始转移
                y = fa[y][i]; 
            }
        }
        return fa[x][0];    //最终节点的父节点就是lca
    };

    //查询调用
    while(m--){
        int x, y;
        std::cin >> x >> y;
        std::cout << lca(x, y) << endl;
    }

#endif