#ifdef ShadowDrunk
//时间复杂度O（n + m）
//割点是指删除了这个点会是图中连通块的数量增加，割边也是
//求割点时我们需要先对图中每个连通块跑一个dfs生成树
//然后记录每个节点的生成序号和能回退到的序号
//根据割点的含义，对于非根节点只有其子节点存在一个节点不能回溯到其祖先节点，那么当前节点就是割点
//割边则是不能回溯到其祖先节点及自己
//对于根节点只要其有两个子树即使割点
    
    //初始建边
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> vec(n + 1);
    for(int i = 0; i < m; i++){
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }

    //核心数据
    int dfn = 1;
    std::vector<int> num(n + 1, 0); //dfs生成序号
    std::vector<int> low(n + 1, 0); //能回溯到的点
    std::vector<bool> is_cut(n + 1, false); //是不是切点（切边则改为int记录以某个节点连接的切边数量）
    int start = 0;  //每个连通块跑生成树的起点

    //核心算法
    std::function<void(int, int)> dfs = [&](int node, int fa) -> void{
        low[node] = num[node] = dfn++;
        int child = 0;

        for(auto v : vec[node]){
            if(v != fa){
                if(!num[v]){
                    child += 1;
                    dfs(v, node);
                    low[node] = std::min(low[node], low[v]);    //用其子节点回溯位置更新当前节点
                    if(node != start && num[node] <= low[v]) 
                        is_cut[node] = true;

                    // 割边改为注释
                    // if(num[node] < low[v]) 
                    //    (node, v) is cut;
                }
                else    //处理回溯边
                    low[node] = std::min(low[node], num[v]);
            }
        }
        //判断根节点, 割边不用
        if(node == start && child >= 2){
            is_cut[node] = true;
        }
    };
    //有时图不一定连通
    for(int i = 1; i <= n; i++)
        if(!num[i]){
            dfn = 1;
            start = i;
            dfs(i, -1);
        }
    
    //答案与计数
    int sum = 0;
    for(int i = 1; i <= n; i++)
        if(is_cut[i])
            sum += 1;
    std::cout << sum << endl;
    for(int i = 1; i <= n; i++)
        if(is_cut[i])
            std::cout << i << space;

#endif