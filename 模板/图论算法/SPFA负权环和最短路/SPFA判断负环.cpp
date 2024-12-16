#ifdef ShadowDrunk
//最坏时间复杂度是O(n * m)
    //输入和初始化
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> vec(n + 1);
    for(int i = 0; i < m; i++){
        int x, y, len;
        std::cin >> x >> y >> len;
        vec[x].push_back({y, len});
    }
    std::vector<int> dis(n + 1, 0);
    std::vector<bool> vis(n + 1, false);
    std::vector<int>  cnt(n + 1, 0);
    
    //算法核心
    std::function<bool()> SPFA = [&]() -> bool{
        std::queue<int> que;
        for(int i = 1; i <= n; i++){
            que.push(i);    //开始需要将所有的节点都放进去，以防图不是连通的
            vis[i] = true;
        }
        while(!que.empty()){
            int node = que.front();
            que.pop();
            vis[node] = false;
            for(auto v : vec[node]){
                int to = v.ff;
                int len = v.ss;
                if(dis[to] > dis[node] + len){
                    dis[to] = dis[node] + len;
                    cnt[to] = cnt[node] + 1;    
                    if(cnt[to] >= n)    //如果跟新最短路的边数到达n及以上则一定存在负环
                        return true;
                    if(!vis[to]){
                        que.push(to);
                        vis[to] = true;
                    }
                }
            }
        }
        return false;
    };

    //结果判断
    if(SPFA())
        std::cout << "Yes" << endl;
    else
        std::cout << "No" << endl;

#endif