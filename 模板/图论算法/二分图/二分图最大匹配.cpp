#ifdef ShadowDrunk
//时间复杂度O(n * m)
//图的匹配是指从图中挑出一些边，这些边不会共享同一个节点。
//最大匹配即匹配的最大边数

    //数据及初始化
    int n1, n2, m;  //左边n1个点，右边n2个点，m条边
    std::cin >> n1 >> n2 >> m;
    std::vector<std::vector<int>> vec(n1 + 1);
    std::vector<int> match(n2 + 1, 0);
    std::vector<bool> st(n2 + 1, false);
    
    for(int i = 0; i < m; i++){
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
    }

    //核心算法
    int res = 0;
    std::function<bool(int)> find = [&](int node) -> bool{
        for(auto v : vec[node]){
            if(!st[v]){ //防止重复考虑同一个点
                st[v] = true;
                if(match[v] == 0 || find(match[v])){    //能否完成匹配，包括给已匹配的换个对象
                    match[v] = node;
                    return true;
                }
            }
        }
        return false;
    };

    for(int i = 1; i <= n1; i++){   //从集合一枚举匹配集合二
        st = std::vector<bool>(n2 + 1, false);
        //注意每次尝试分配都要重置st
        if(find(i))
            res += 1;
    }
    std::cout << res << endl;
    
#endif