#ifdef ShadowDrunk
//没有进行堆优化
//使用邻接矩阵寸图
//时间复杂度为O(n ^ 2)
//注意dijstra算法处理不了负权边
    //输入和初始化
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<ll>> vec(n + 1, std::vector<ll>(n + 1, INT_MAX));
    for(int i = 0; i < m; i++){
        ll x, y, l;
        std::cin >> x >> y >> l;
        if(x != y)  //取出重边和自环的影响
            vec[x][y] = std::min(vec[x][y], l);
    }
    std::vector<ll> dis(n + 1, INT_MAX);
    dis[1] = 0;
    std::set<ll> se;
    //算法内核
    std::function<ll()> dijstra = [&]() -> ll{
        for(int i = 1; i <= n; i++){
            int t = -1;
            for(int j = 1; j <= n; j++){
                if(se.count(j))
                    continue;
                if(t == -1 || dis[j] < dis[t])
                    t = j;
            }
            for(int j = 1; j <= n; j++){
                dis[j] = std::min(dis[j], dis[t] + vec[t][j]);
            }
            se.insert(t);
        }
        return (dis[n] == INT_MAX ? -1 : dis[n]);
        //如果路径不存在就返回-1
    };

#endif