#ifdef ShadowDrunk
//时间复杂度为O(mlgm)
//需要借助并查集来快速判断点是否已经连通

    //数据及初始化
    int n, m;
    std::cin >> n >> m;
    std::vector<int> fa(n + 1);
    std::iota(fa.begin(), fa.end(), 0); //并查集初始化
    struct edge{
        int x, y, len;
        bool operator< (const edge& other){
            return len < other.len;
        }
    };  //存储所有的边

    std::vector<edge> cur(m);
    for(auto& x : cur){
        std::cin >> x.x >> x.y >> x.len;
    }

    //并查集核心算法
    std::function<int(int)> find = [&](int i) -> int{
        if(fa[i] != i)
            fa[i] = find(fa[i]);
        return fa[i];
    };

    //核心算法
    std::sort(cur.begin(), cur.end());

    int ans = 0;
    int count = 0;  //连接的边数
    for(int i = 0; i < m; i++){ //从小到大枚举所有的边
        int x = cur[i].x;
        int y = cur[i].y;
        int len = cur[i].len;

        x = find(x);
        y = find(y);
        if(x != y){ //当前存在节点没有连通
            fa[x] = y;
            ans += len;
            count += 1;
        }
    }

    //结果判断
    if(count < n - 1)   
        std::cout << "impossible" << endl;
    else
        std::cout << ans << endl;


#endif