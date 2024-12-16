#ifdef ShadowDrunk
//时间复杂度O（n + m）
//算法实现基于无向图求割点
//边连通分量是指每两个节点之间都有两条到达路径，路径中无重复边
//边双连通分量都是指极大边双连通分量
//我们在发现在dfn生成树中的转换出的有向图的强连通分量就是原图中的边双连通分量
//我们把dfn生成树中的强连通分量取出即可
    
    //核心数据
    int n, m;
    std::vector<std::vector<int>> vec;
    int dfn = 1;
    std::vector<int> num; //dfs生成序号
    std::vector<int> low; //能回溯到的点
    std::vector<std::vector<int>> dccno;    //存储的是每个点边双连通分量中的点
    std::vector<int> dcc;   //存储每个点属于哪个分双连通分量
    std::stack<int> stk;  

    //数据初始化
    std::cin >> n >> m;
    dfn = 1;
    vec = std::vector<std::vector<int>>(n + 1);
    low = std::vector<int>(n + 1);
    num = std::vector<int>(n + 1);
    dccno = std::vector<std::vector<int>>(1);   //调整至于dcc相同
    stk = std::stack<int>();
    dcc = std::vector<int>(n + 1, 0);

    //核心算法
    void dfs(int node, int fa){
        low[node] = num[node] = dfn++;
        int child = 0;
        stk.push(node);
        bool diff = false;
        for(auto v : vec[node]){
            if(v == fa && !diff){
                //注意重边的影响
                diff = true;
                continue;
            }
            if(!num[v]){
                child += 1;
                dfs(v, node);
                low[node] = std::min(low[node], low[v]);    //用其子节点回溯位置更新当前节点
            }
            else    //处理回溯边
                low[node] = std::min(low[node], num[v]);
        }

        //dfn搜索树创造的有向图中的强连通分量一定是边双连通分量
        if(low[node] == num[node]){
            std::vector<int> tmp;
            tmp.push_back(node);
            while(stk.top() != node){
                tmp.push_back(stk.top());
                stk.pop();
            }
            stk.pop();
            dccno.push_back(tmp);
        }
    }

    void Tarjan(){
        for(int i = 1; i <= n; i++)
            if(!num[i]){
                dfn = 1;
                dfs(i, -1);
            }
        for(int i = 1; i < dccno.size(); i++){
            for(auto node : dccno[i])
                dcc[node] = i;
        }
    }

    //建边及调用Tarjan
    for(int i = 0; i < m; i++){
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    Tarjan();


#endif