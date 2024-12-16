#ifdef ShadowDrunk
//时间复杂度O（n + m）
//强连通分量scc是指图中的一个子连通块，连通块中的每个点都可以互相到达
//Kosaraju的算法思路需要使用反图的技巧，总体想法类似于拓扑排序
//正向遍历确定了最高优先级的点可以跑到剩下的所有点
//反向遍历可以确定哪些点可以跑到它（第二次dfs跑反图）
    
    //核心数据
    int n, m;
    int cnt;
    std::vector<std::vector<int>> vec;
    std::vector<std::vector<int>> rvec; //存反图
    std::vector<int> S; //记录第一遍dfs的优先级
    std::vector<bool> vis;
    std::vector<int> sccno;

    //数据初始化
    std::cin >> n >> m;
    S.clear();
    vec = std::vector<std::vector<int>>(n + 1);
    rvec = std::vector<std::vector<int>>(n + 1);
    vis = std::vector<bool>(n + 1);
    sccno = std::vector<int>(n + 1);

    //核心算法
    void dfs1(int node){
        vis[node] = true;
        for(auto v : vec[node]){
            if(!vis[v])
                dfs1(v);
        }
        S.push_back(node);  //确定优先级，返回时优先级逐步升高
    }
    void dfs2(int node){
        sccno[node] = cnt;
        for(auto v : rvec[node])
            if(!sccno[v])
                dfs2(v);
    }
    void Kosaraju(){
        cnt = 0;   //强连通分量的数量
        for(int i = 1; i <= n; i++)
            if(!vis[i])
                dfs1(i);
        for(int j = n - 1; j >= 0; j--){
            //从优先级最高的点开始跑返图，确定被孤立的点属于同一强连通分量
            if(!sccno[S[j]]){
                cnt += 1;
                dfs2(S[j]);
            }
        }
    }

    //存图及调用
    for(int i = 0; i < m; i++){
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
        rvec[y].push_back(x);
    }
    Kosaraju();



#endif