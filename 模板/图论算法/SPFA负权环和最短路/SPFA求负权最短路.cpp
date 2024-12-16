#ifdef ShadowDrunk
//最坏时间复杂度是O(n * m)
    //输入和初始化
    ll n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<ll, ll>>> vec(n + 1);
    for(int i = 0; i < m; i++){
        ll x, y, len;
        std::cin >> x >> y >> len;
        vec[x].push_back({y, len});
    }

    std::vector<ll> dis(n + 1, LONG_MAX);
    dis[1] = 0;
    std::vector<bool> st(n + 1, false);

    std::queue<ll> que;
    que.push(1);
    st[1] = true;
    
    //算法核心
    while(!que.empty()){
        ll node = que.front();
        que.pop();
        st[node] = false;
        for(auto v : vec[node]){
            ll to = v.ff;
            ll len = v.ss;
            if(dis[to] > dis[node] + len){  //只有当前节点因为更新变小了，它才有可能更新其它节点
                dis[to] = dis[node] + len;
                if(!st[to]){    //判断是否已经在队列中
                    que.push(to);
                    st[to] = true;
                }
            }
        }
    }

    //结果判断
    if(dis[n] == LONG_MAX)
        std::cout << "impossible" << endl;
    else    
        std::cout << dis[n] << endl;

#endif