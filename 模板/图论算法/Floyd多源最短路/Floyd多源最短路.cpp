#ifdef ShadowDrunk
//最坏时间复杂度是O(n * n * n）

    //数据初始化
    int n, m, k;    //这里的k是题目的k组查询
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> dis(n + 1, std::vector<int>(n + 1, INT_MAX / 2));
    //最终dis就会是距离
    for(int i = 1; i <= n; i++)
        dis[i][i] = 0;
    for(int i = 0; i < m; i++){
        int x, y, len;
        std::cin >> x >> y >> len;
        if(x != y)  //去除重边和自环
            dis[x][y] = std::min(dis[x][y], len);
    }

    //核心算法
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
                //类似于区间dp，枚举中间转移的点
            }
        }
    }

    //结果判断
    while(k--){
        int x, y;
        std::cin >> x >> y;
        if(dis[x][y] >= INT_MAX / 3)    //可能存在负权边
            std::cout << "impossible" << endl;
        else
            std::cout << dis[x][y] << endl;
    }

#endif