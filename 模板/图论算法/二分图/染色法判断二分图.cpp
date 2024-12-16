#ifdef ShadowDrunk
//二分图是值一个图可以将所有节点分为两个集合，两个集合内部不存在边
//二分图不存在奇数环

    //数据及初始化
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> vec(n + 1);
    for(int i = 0; i < m; i++){
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }

    //核心算法
    std::vector<int> color(n + 1, 0);   //记录节点的染色情况
    std::function<bool(int, int)> dfs = [&](int node, int col) -> bool {
        color[node] = col;
        for(auto v : vec[node]){
            if(!color[v]){
                if(!dfs(v, 3 - col))  // 3 - c 将1转换为2，2转换为1
                    return false;
            }
            else if(color[v] != 3 - color[node])    //判断相邻节点是否在同一个集合
                    return false;
        }

        return true;
    };

    bool check = true;
    for(int i = 1; i <= n; i++){
        if(!color[i]){
            if(!dfs(i, 1)){
                check = false;
                break;
            }
        }
    }

    //结果判断
    if(check)
        std::cout << YES << endl;
    else
        std::cout << NO << endl;
    
#endif