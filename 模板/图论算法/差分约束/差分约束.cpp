#ifdef ShadowDrunk
//时间复杂度O(n * m) (实际上是SPFA的时间复杂度)
//差分约束实际上将两个点做差的不等式转换为了图论最短路最终结果的距离不等式
//这要问题就可以转换为图论的最短路，只要不存在负环就可以跑出最短路，此时的dis数组中就是满足差分条件的一组解

    //初始数据
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> vec(n + 1);
    std::vector<int> dis(n + 1, 0);
    std::vector<bool> vis(n + 1, false);
    std::vector<int>  cnt(n + 1, 0);

    //关键建边
    for(int i = 0; i < m; i++){
        int x, y, len;
        std::cin >> x >> y >> len;  // x - y <= len
        //dis[y] <= dis[x] + len(x, y)(最短路距离不等式)  //转换为 y <= x + len（同价于最短路不等式）
        vec[y].push_back({x, len});
    }

    //SPFA板子
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
    if(!SPFA()){
        for(int i = 1; i <= n; i++)
            std::cout << dis[i] << sendl[i == n];
    }
    else
        std::cout << NO << endl;
        
#endif