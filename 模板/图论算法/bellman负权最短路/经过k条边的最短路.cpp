#ifdef ShadowDrunk
//bellman-ford算法的时间复杂度是o（k * m)
//可以处理负权边
    //输入和初始化
    ll n, m, k; //k代表最多经过k条边
    std::cin >> n >> m >> k;
    std::vector<std::vector<std::pair<ll, ll>>> vec(n + 1);
    for(int i = 0; i < m; i++){
        ll x, y, len;
        std::cin >> x >> y >> len;
        vec[x].push_back({y, len});
    }
    std::vector<ll> dis(n + 1, LONG_MAX);
    dis[1] = 0;

    //算法核心
    for(int i = 0; i < k; i++){
        std::vector<ll> new_dis = dis;  //使用new_dis存储防止一条边更新为多条边
        for(int node = 1; node <= n; node++){
            for(auto p : vec[node]){
                ll to = p.ff;
                ll len = p.ss;
                new_dis[to] = std::min(new_dis[to], dis[node] + len);
            }
        }
        dis = new_dis;
    }

    //结果判断
    if(dis[n] >= LONG_MAX / 2)
        std::cout << "impossible" << endl;
    else    
        std::cout << dis[n] << endl;
        
#endif