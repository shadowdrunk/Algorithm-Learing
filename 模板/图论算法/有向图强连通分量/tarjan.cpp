#ifdef ShadowDrunk
//时间复杂度O（n + m）
//强连通分量scc是指图中的一个子连通块，连通块中的每个点都可以互相到达
//tarjan的思路和无向图找割点的思路很想，我们发现当回溯到low[node] == num[node]时所有杠遍历过的子节点都是一个强连通分量中的
//所以我们可以使用栈记录当前遍历过的点，一次dfs即可
//或者我们也可以再dfs后手动将所有low相同的点记录为同一个sccno
    
    //核心数据
    int n;
    std::vector<int> low;
    std::vector<int> num;
    int dfn = 0;
    int cnt = 0;
    std::vector<int> sccno;
    std::stack<int> stk;
    std::vector<std::vector<int>> vec;

    //核心算法
    void dfs(int node){
        stk.push(node);
        dfn += 1;
        low[node] = num[node] = dfn;
        for(auto v : vec[node]){
            if(!num[v]){
                dfs(v);
                low[node] = std::min(low[node], low[v]);
            }
            else if(!sccno[v])
                low[node] = std::min(low[node], num[v]);
        }
        if(low[node] == num[node]){
            cnt += 1;
            while(true){
                int now = stk.top();
                sccno[now] = cnt;
                stk.pop();
                if(now == node)
                    break;
            }
        }
    }

    void Tarjan(){
        cnt = 0;
        dfn = 0;
        for(int i = 1; i <= n; i++)
            if(!num[i]){
                dfs(i);
            }   
    }

    //初始化,存边与调用
    std::cin >> n;
    low = std::vector<int>(n + 1);
    num = std::vector<int>(n + 1);
    sccno = std::vector<int>(n + 1, 0);
    vec = std::vector<std::vector<int>>(n + 1);
    for(int i = 1; i <= n; i++){
        int x;
        std::cin >> x;
        while(x != 0){
            vec[i].push_back(x);
            std::cin >> x;
        }
    }
    Tarjan();


#endif