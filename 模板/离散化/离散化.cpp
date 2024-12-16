#ifdef ShadowDrunk
//rank为离散化后的结果
    std::vector<std::pair<ll, ll>> cur(n);
    std::vector<ll> rank(n + 1);
    for(int i = 0; i < n; i++){
        std::cin >> cur[i].ff;
        cur[i].ss = i + 1;  //第i + 1个数
    }
    //将原始数据从小到大排序
    std::sort(cur.begin(), cur.end());
    for(int i = 1; i <= n; i++){
        rank[cur[i - 1].ss] = i;    //相对大小为i
    }
    
#endif