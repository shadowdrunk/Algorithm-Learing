#ifdef ShadowDrunk
//最小生成树是指从n个节点的图中挑出n - 1挑边使得图形成一个n个节点的连通图
//返回最终选择的边的边权的和
//时间复杂度为O（n * n)

    //数据及初始化
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> vec(n + 1, std::vector<int>(n + 1, INT_MAX));
    //朴素版多处理稀疏图，用邻接矩阵
    for(int i = 0; i < m; i++){
        int x, y, len;
        std::cin >> x >> y >> len;
        if(x != y){ //去除重边和自环
            vec[x][y] = std::min(vec[x][y], len);
            vec[y][x] = std::min(vec[y][x], len);
        }
    }
    std::vector<bool> st(n + 1, false); //在集合中的点
    std::vector<int> dis(n + 1, INT_MAX);   //点到集合的距离
    
    //算法核心
    std::function<int()> prim = [&]() -> int{
        int res = 0;
        for(int i = 0; i < n; i++){

            int node = -1;
            for(int j = 1; j <= n; j++){
                if(!st[j] && (node == -1 || dis[node] > dis[j]))
                    node = j;
            }   //找出距离集合最近的点

            if(i && (dis[node] == INT_MAX)) //图是不连通的
                return INT_MAX;

            for(int j = 1; j <= n; j++) //更新其余点到集合的距离
                dis[j] = std::min(dis[j], vec[node][j]);

            st[node] = true;
            if(i)
                res += dis[node];
        }
        return res;
    };

    //结果判断
    int ans = prim();
    if(ans == INT_MAX)
        std::cout << "impossible" << endl;
    else
        std::cout << ans << endl;

#endif