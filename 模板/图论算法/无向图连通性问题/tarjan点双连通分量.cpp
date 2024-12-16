#ifdef ShadowDrunk
//时间复杂度O（n + m）
//算法实现基于无向图求割点
//点双连通分量是指每两个节点之间都有两条到达路径，路径中无重复点
//点双连通分量都是指极大点双连通分量
//我们在发现割点时实际上就是完成了对一个点双连通分量的遍历
//所以根据上面的思路，实际上本算法也可以用来求割点
//我们把路径中的点全部取出来即使点双连通分量
    
    //核心数据
    int n, m;
    std::vector<std::vector<int>> vec;
    int dfn = 1;
    std::vector<int> num; //dfs生成序号
    std::vector<int> low; //能回溯到的点
    std::vector<std::vector<int>> sccno;    //存储的是每个点双连通分量中的点
    std::stack<int> stk;  

    //数据初始化
    std::cin >> n >> m;
    vec = std::vector<std::vector<int>>(n + 1);
    low = std::vector<int>(n + 1);
    num = std::vector<int>(n + 1);
    sccno = std::vector<std::vector<int>>();
    stk = std::stack<int>();

    //核心算法
    void dfs(int node, int fa){
        low[node] = num[node] = dfn++;
        int child = 0;
        stk.push(node);
        for(auto v : vec[node]){
            if(v != fa){
                if(!num[v]){
                    child += 1;
                    dfs(v, node);
                    low[node] = std::min(low[node], low[v]);    //用其子节点回溯位置更新当前节点
                    if(num[node] <= low[v]){    //注意这是找割点的条件，v节点无法回溯到node上方
                        int cut = node;     //注意这里的cut并不一定是割点，根节点需要特判
                        int end = v;    //将过程中遍历到的点弹出
                        std::vector<int> tmp;
                        while(true){
                            int now = stk.top();
                            stk.pop();
                            
                            tmp.push_back(now);
                            if(now == end)
                                break;
                        }
                        tmp.push_back(cut); //将割点加入
                        sccno.push_back(tmp);
                    }
                }
                else    //处理回溯边
                    low[node] = std::min(low[node], num[v]);
            }
        }
        //判断独立节点与自环
        if(fa == -1 && child == 0){
            sccno.push_back({node});
        }
    }

    void Tarjan(){
        for(int i = 1; i <= n; i++)
            if(!num[i]){
                dfn = 1;
                dfs(i, -1);
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