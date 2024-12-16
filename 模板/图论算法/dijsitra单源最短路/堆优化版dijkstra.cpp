#ifdef ShadowDrunk
//使用邻接表存图，很难处理重边
//边数较少时比较适用
//时间复杂度为O(nlg(m)) m为边的数量
//注意dijkstra算法处理不了负权边

    //输入输出及初始化
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<ll, ll>>> vec(n + 1);
    for(int i = 0; i < m; i++){
        ll x, y, l;
        std::cin >> x >> y >> l;
        if(x != y)
            vec[x].push_back({y, l});
    }
    std::vector<ll> dis(n + 1, LONG_LONG_MAX);
    dis[1] = 0;
    std::set<ll> se;
    std::priority_queue<std::pair<ll, ll>, std::vector<std::pair<ll, ll>>, std::greater<std::pair<ll, ll>>> que;
    //开一个最小堆
    que.push({0, 1});
    //初始确定节点1最近且距离为0

    //算法核心
    std::function<ll()> dijkstra = [&]() -> ll{
        while(!que.empty()){
            ll node = que.top().ss;
            que.pop();
            if(se.count(node))
                continue;
            for(auto v : vec[node]){
                ll to = v.ff;
                ll len = v.ss;
                if(dis[to] > dis[node] + len){
                    dis[to] = dis[node] + len;
                    que.push({dis[to], to});
                    //跟新最短距离，由于优先队列的删除不方便，直接暴力插入
                }
            }
            se.insert(node);
        }
        return (dis[n] == INT_MAX ? -1 : dis[n]);
    };
    dijkstra();

#endif